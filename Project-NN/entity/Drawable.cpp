#include "Drawable.h"

#include "GameObject.h"
#include "Transform.h"
#include "ResourceManager.h"

extern int screenWidth;
extern int screenHeight;
extern ResourceManager* resourceMgr;

Drawable::Drawable(void) : world(), drawtopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	numVerts = 0;
	pD3DDevice = resourceMgr->pD3DDevice;
	deviceContext = resourceMgr->md3dImmediateContext;

	currentLayout = 0;

	pVertexBuffer = 0;
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

void Drawable::addEffectVariables(char* id, char* variableName, float* value)
{
	auto var = currentShader->GetVariableByName(variableName);
	variables[var] = value;
}

void Drawable::addTexture(char* id, char* textureVariable) {
	auto diffuseMap = resourceMgr->getEffect(effectID)->GetVariableByName(textureVariable)->AsShaderResource();
	textures[diffuseMap] = resourceMgr->textures[id];
}

void Drawable::setEffectVariables()
{
	if(currentShader != 0)
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

		float arr[2] = {(int)(screenWidth*.5),(int)(screenHeight*.5)};
		currentShader->GetVariableByName("texDimensions")->SetRawValue(arr, 0, 8);

		for(auto it = variables.begin(); it != variables.end(); ++it) 
		{
			D3DX11_EFFECT_TYPE_DESC i;
			it->first->GetType()->GetDesc(&i);
			it->first->SetRawValue(it->second,0,(UINT)pow(4.0,i.Class+1));
		}
	}
}

void Drawable::setEffectTextures()
{
	for(auto it = textures.begin(); it != textures.end(); ++it) {
		HRESULT hr = it->first->AsShaderResource()->SetResource(it->second);
	}
}

void Drawable::setShader(char* effectName, char* techniqueName)
{
	currentShader = shaders[effectName];
	currentTechnique = techniques[techniqueName];
	currentLayout = layouts[techniqueName];
}

void Drawable::draw()
{
	UINT stride = vertexStride;
	UINT offset = vertexOffset;


	// Clear the back buffer 
	deviceContext->IASetInputLayout( currentLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( drawtopology );
	
	D3DX11_TECHNIQUE_DESC techDesc;
    currentTechnique->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        currentTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->Draw( numVerts, 0 );
	}
}

void Drawable::getEffectVariables(char *effectID, char* fxTechniqueName )
{
	this->effectID = effectID;
	shaders[effectID] = resourceMgr->effects.at( effectID )->effect;
    techniques[fxTechniqueName] = shaders[effectID]->GetTechniqueByName( fxTechniqueName );
	layouts[fxTechniqueName] = resourceMgr->effects.at( effectID )->layouts.at( fxTechniqueName );
}

//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void Drawable::createBuffer(char* mesh)
{
	HRESULT hr;
	pVertexBuffer = resourceMgr->meshes.at(mesh)->verticies;
	indexBuffer = resourceMgr->meshes.at(mesh)->indicies;

	vertexStride = resourceMgr->meshes.at(mesh)->vertexStride;
	vertexOffset = resourceMgr->meshes.at(mesh)->vertexOffset;

	numVerts = resourceMgr->meshes.at(mesh)->numVerts;
	numIndicies = resourceMgr->meshes.at(mesh)->numIndicies;
}
