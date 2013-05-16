#include "MenuDrawable.h"
#include "ResourceManager.h"
#include "MenuItem.h"
#include "Transform.h"
#include "MenuControlComponent.h"

MenuDrawable::MenuDrawable( ) : Drawable( ), ageVar(0), debug_count(0)
{
	drawtopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

bool MenuDrawable::Init(GameObject* go) {
	transform = go->GetComponent<Transform>( );
	control = go->GetComponent<MenuComponent>( );
	return transform != nullptr;
}

void MenuDrawable::draw( ) 
{
	// Clear the back buffer 
	deviceContext->IASetInputLayout( currentLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( drawtopology );

	if( ageVar == 0 )
		ageVar = currentShader->GetVariableByName("itemHoverAge")->AsScalar( );

	ageVar->SetFloat( control->getHoverAge( ) );

	D3DX11_TECHNIQUE_DESC techDesc;
	currentTechnique->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p)
	{
		currentTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->Draw( numVerts, 0 );
	}
}

void MenuDrawable::createBuffer( MenuItemDescription desc )
{
	HRESULT hr;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	vbd.ByteWidth = sizeof(MenuItemDescription); //total number of bytes for all verticies
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	vbd.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	vbd.MiscFlags = 0; //only one D3D device

	MenuItemBuffer buf;
	buf.width = desc.width;
	buf.height = desc.height;
	buf.position = XMFLOAT2( desc.position.x, desc.position.y );

	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &buf;

	hr = pD3DDevice->CreateBuffer( &vbd, &initData, &pVertexBuffer );
	if( hr == S_OK )
		std::cout << "okay buffer" << std::endl;
	
	vertexStride = sizeof( MenuItemDescription );
	vertexOffset = 0;
	numVerts = 1;
}