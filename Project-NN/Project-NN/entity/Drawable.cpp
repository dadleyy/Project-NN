#include "Drawable.h"

#include "GameObject.h"
#include "Transform.h"
#include "ResourceManager.h"


Drawable::Drawable(void)
{
	numVerts = 0;
	pD3DDevice = resourceMgr->pD3DDevice;
	deviceContext = resourceMgr->md3dImmediateContext;
	pVertexBuffer = 0;
	pVertexLayout = 0;
	vertexStride = 0;
	vertexOffset = 0;
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4( &world, I );
}

Drawable::~Drawable(void)
{
}

bool Drawable::Init(GameObject* go) {
	transform = go->GetComponent<Transform>();
	return transform != nullptr;
}

XMFLOAT3* Drawable::getVerts(float radius, int divisions)
{
	//this does nothing ever
	return 0;
}
UINT* Drawable::getIndicies()
{
	//this does nothing ever
	return 0;
}

void Drawable::setEffectVariables()
{
	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	XMMATRIX w = scale * rotation * translate;
	XMMATRIX wn = w;

	//update the world matrix in the shader
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT hr = deviceContext->Map(resourceMgr->getCBuffer("Object"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource); 
	memcpy((float*)resource.pData,    &w._11,  64);
	memcpy((float*)resource.pData+16, &wn._11, 64);
	deviceContext->Unmap(resourceMgr->getCBuffer("Object"), 0);
}

void Drawable::setEffectTextures()
{
	for(auto it = textures.begin(); it != textures.end(); ++it) {
		it->first->AsShaderResource()->SetResource(it->second);
	}
}

void Drawable::draw()
{
	UINT stride = vertexStride;
	UINT offset = vertexOffset;

	// Clear the back buffer 
	deviceContext->IASetInputLayout( pVertexLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->Draw( numVerts, 0 );
	}
}


//***********************************************
//Microsofts shader compiler
//***********************************************
HRESULT Drawable::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, 0, 0, 0, szShaderModel, dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


void Drawable::getEffectVariables(char *effectID, char* fxTechniqueName )
{
	this->effectID = effectID;
	shader = resourceMgr->effects.at( effectID )->effect;
    technique = shader->GetTechniqueByName( fxTechniqueName );
}

//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void Drawable::createBuffer(char* mesh)
{
	HRESULT hr;

    cout << "creating buffer for: " << mesh << endl;

	//VERTEX BUFFER
	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = { 
											{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 ,                            D3D11_INPUT_PER_VERTEX_DATA, 0}, 
											{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}, 
											{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0} 
										};
	
	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
    technique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = pD3DDevice->CreateInputLayout(layout,
				3,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				&pVertexLayout);


	pVertexBuffer = resourceMgr->meshes.at(mesh)->verticies;
	indexBuffer = resourceMgr->meshes.at(mesh)->indicies;

	vertexStride = resourceMgr->meshes.at(mesh)->vertexStride;
	vertexOffset = resourceMgr->meshes.at(mesh)->vertexOffset;

	numVerts = resourceMgr->meshes.at(mesh)->numVerts;
	numIndicies = resourceMgr->meshes.at(mesh)->numIndicies;

    cout << mesh << " : " << resourceMgr->meshes.at(mesh)->numVerts << endl;
}


void Drawable::createBuffer()
{
	HRESULT hr;

	//VERTEX BUFFER
	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
	
	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
    technique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = pD3DDevice->CreateInputLayout(layout,
				1,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				&pVertexLayout);


	pVertexBuffer = resourceMgr->meshes.at("testSphere")->verticies;
	indexBuffer = resourceMgr->meshes.at("testSphere")->indicies;

	vertexStride = resourceMgr->meshes.at("testSphere")->vertexStride;
	vertexOffset = resourceMgr->meshes.at("testSphere")->vertexOffset;

	numVerts = resourceMgr->meshes.at("testSphere")->numVerts;
	numIndicies = resourceMgr->meshes.at("testSphere")->numIndicies;
}


void Drawable::addTexture(char* id, char* textureVariable) {
	auto diffuseMap = resourceMgr->getEffect(effectID)->GetVariableByName(textureVariable)->AsShaderResource();
	textures[diffuseMap] = resourceMgr->textures[id];
}


void Drawable::destroy()
{
	/*shader->Release();
	pVertexBuffer->Release();
	pVertexLayout->Release();*/
}