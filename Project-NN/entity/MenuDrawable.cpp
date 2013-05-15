#include "MenuDrawable.h"
#include "ResourceManager.h"
#include "MenuItem.h"
#include "Transform.h"

MenuDrawable::MenuDrawable( ) : Drawable( )
{
	drawtopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

bool MenuDrawable::Init(GameObject* go) {
	transform = go->GetComponent<Transform>();
	return transform != nullptr;
}

void MenuDrawable::setShader(char* effectName, char* techniqueName )
{
	currentShader = shaders[effectName];
	currentTechnique = techniques[techniqueName];
	currentLayout = layouts[techniqueName];
}

void MenuDrawable::getEffectVariables(char* effectID, char* techniqueName)
{
	this->effectID = effectID;
	shaders[effectID] = resourceMgr->effects.at( effectID )->effect;
	techniques[techniqueName] = shaders[effectID]->GetTechniqueByName( techniqueName );
	layouts[techniqueName] = resourceMgr->effects.at( effectID )->layouts.at( techniqueName );
}

void MenuDrawable::draw() 
{
	// Clear the back buffer 
	deviceContext->IASetInputLayout( currentLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( drawtopology );

	//translate, rotate, and scale matrix
	XMMATRIX translate = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->rotation));
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
	XMMATRIX w = scale * rotation * translate;

	//update the world matrix in the shader
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT hr = deviceContext->Map(resourceMgr->getCBuffer("Object"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource); 
	memcpy((float*)resource.pData,    &w._11,  64);
	deviceContext->Unmap(resourceMgr->getCBuffer("Object"), 0);

	D3DX11_TECHNIQUE_DESC techDesc;
	currentTechnique->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p)
	{
		currentTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->Draw( numVerts, 0 );
	}

}

void MenuDrawable::createBuffer( MenuItemDescription* desc )
{
	HRESULT hr;

	description = desc;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	vbd.ByteWidth = sizeof(MenuItemDescription); //total number of bytes for all verticies
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	vbd.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	vbd.MiscFlags = 0; //only one D3D device

	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = description;

	hr = pD3DDevice->CreateBuffer( &vbd, &initData, &pVertexBuffer );
	if( hr == S_OK )
		std::cout << "okay buffer" << std::endl;
	
	vertexStride = sizeof( MenuItemDescription );
	vertexOffset = 0;
	numVerts = 1;
}