#include "MenuDrawable.h"

MenuDrawable::MenuDrawable( ) : Drawable( )
{
	drawtopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

void MenuDrawable::createBuffer(char* param)
{
	HRESULT hr;

	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = { 
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"WIDTH",   0, DXGI_FORMAT_R32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"HEIGHT",   0, DXGI_FORMAT_R32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
	currentTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = pD3DDevice->CreateInputLayout(layout, 3, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize,&pVertexLayout);

	MenuStruct item;
	item.width = 100.0f;
	item.height = 100.0f;
	item.position = XMFLOAT2( 10.0f, 10.0f );

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	vbd.ByteWidth = sizeof(MenuStruct); //total number of bytes for all verticies
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	vbd.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	vbd.MiscFlags = 0; //only one D3D device

	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &item;

	hr = pD3DDevice->CreateBuffer( &vbd, &initData, &pVertexBuffer );
	
	vertexStride = sizeof( MenuStruct );
	vertexOffset = 0;
	numVerts = 1;
}