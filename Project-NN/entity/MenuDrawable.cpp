#include "MenuDrawable.h"

MenuDrawable::MenuDrawable( ) : Drawable( )
{
	drawtopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

void MenuDrawable::draw() 
{
	// Clear the back buffer 
	deviceContext->IASetInputLayout( pVertexLayout );
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

void MenuDrawable::createBuffer(char* param)
{
	HRESULT hr;

	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = { 
		{"WIDTH",    0, DXGI_FORMAT_R32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"HEIGHT",   0, DXGI_FORMAT_R32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
	currentTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = pD3DDevice->CreateInputLayout(layout, 3, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize,&pVertexLayout);
	if( hr == S_OK )
		std::cout << "okay layout" << std::endl;


	MenuStruct item;
	item.width = 0.010f;
	item.height = 0.010f;
	item.pos = XMFLOAT2( 10.0f, 10.0f );
	menudata.push_back( item );

	item.width = 0.010f;
	item.height = 0.010f;
	item.pos = XMFLOAT2( 10.0f, 10.0f );
	menudata.push_back( item );


	item.width = 0.010f;
	item.height = 0.010f;
	item.pos = XMFLOAT2( 10.0f, 10.0f );
	menudata.push_back( item );


	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	vbd.ByteWidth = sizeof(MenuStruct); //total number of bytes for all verticies
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	vbd.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	vbd.MiscFlags = 0; //only one D3D device

	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &menudata[0];

	hr = pD3DDevice->CreateBuffer( &vbd, &initData, &pVertexBuffer );
	if( hr == S_OK )
		std::cout << "okay buffer" << std::endl;
	
	vertexStride = sizeof( MenuStruct );
	vertexOffset = 0;
	numVerts = menudata.size();
}