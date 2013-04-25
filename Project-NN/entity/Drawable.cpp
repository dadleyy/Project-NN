#include "Drawable.h"

#include "GameObject.h"
#include "Transform.h"
#include "ResourceManager.h"

extern ResourceManager* resourceMgr;

Drawable::Drawable(void) : world()
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

void Drawable::setEffectVariables()
{
	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	XMMATRIX w = scale * rotation * translate;

	//update the world matrix in the shader
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT hr = deviceContext->Map(resourceMgr->getCBuffer("Object"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource); 
	memcpy((float*)resource.pData,    &w._11,  64);
	memcpy((float*)resource.pData+16, &rotation._11, 64);
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
}


void Drawable::addTexture(char* id, char* textureVariable) {
	auto diffuseMap = resourceMgr->getEffect(effectID)->GetVariableByName(textureVariable)->AsShaderResource();
	textures[diffuseMap] = resourceMgr->textures[id];
}