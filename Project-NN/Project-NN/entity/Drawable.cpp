#include "Drawable.h"

#include "GameObject.h"
#include "Transform.h"


extern ResourceManager* drawAtts;

Drawable::Drawable(void)
{
}

Drawable::Drawable(ID3D11Device* device, ID3D11DeviceContext* immediateContext) : world()
{
	numVerts = 0;
	pD3DDevice = device;
	deviceContext = immediateContext;
	pVertexBuffer = 0;
	pVertexLayout = 0;
	vertexStride = 0;
	vertexOffset = 0;
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4( &world, I );
}

Drawable::~Drawable(void)
{
	delete transform;	
}

void Drawable::Init(GameObject* go) {
	transform = go->GetComponent<Transform>();
	//TODO: Check to make sure that transform is not null.
	if(transform == nullptr) {
		exit(1);
	}
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

void Drawable::draw()
{
	UINT stride = vertexStride;
	UINT offset = vertexOffset;

	//build world matrix and normal matrix
	XMMATRIX w = XMLoadFloat4x4( &world );
	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	w = scale * rotation * translate;
	//w = translate * rotation * scale;
	XMMATRIX wn = w;

	for(auto it = textures.begin(); it != textures.end(); ++it) {
		it->first->SetResource(it->second);
	}

	//update the world matrix in the shader
	D3D11_MAPPED_SUBRESOURCE resource;
	
	HRESULT hr = deviceContext->Map(drawAtts->getCBuffer("Object"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource); 
	memcpy((float*)resource.pData,    &w._11,  64);
	memcpy((float*)resource.pData+16, &wn._11, 64);
	deviceContext->Unmap(drawAtts->getCBuffer("Object"), 0);

	// Clear the back buffer 
	deviceContext->IASetInputLayout( pVertexLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
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
    technique = drawAtts->effects.at( effectID )->effect->GetTechniqueByName( fxTechniqueName );
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


	pVertexBuffer = drawAtts->meshes.at(mesh)->verticies;
	indexBuffer = drawAtts->meshes.at(mesh)->indicies;

	vertexStride = drawAtts->meshes.at(mesh)->vertexStride;
	vertexOffset = drawAtts->meshes.at(mesh)->vertexOffset;

	numVerts = drawAtts->meshes.at(mesh)->numVerts;
	numIndicies = drawAtts->meshes.at(mesh)->numIndicies;

    cout << mesh << " : " << drawAtts->meshes.at(mesh)->numVerts << endl;
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


	pVertexBuffer = drawAtts->meshes.at("testSphere")->verticies;
	indexBuffer = drawAtts->meshes.at("testSphere")->indicies;

	vertexStride = drawAtts->meshes.at("testSphere")->vertexStride;
	vertexOffset = drawAtts->meshes.at("testSphere")->vertexOffset;

	numVerts = drawAtts->meshes.at("testSphere")->numVerts;
	numIndicies = drawAtts->meshes.at("testSphere")->numIndicies;
}


void Drawable::addTexture(char* id, char* textureVariable) {
	auto diffuseMap = drawAtts->getEffect(effectID)->GetVariableByName(textureVariable)->AsShaderResource();
	textures[diffuseMap] = drawAtts->textures[id];
}


void Drawable::destroy()
{
	/*shader->Release();
	pVertexBuffer->Release();
	pVertexLayout->Release();*/
}