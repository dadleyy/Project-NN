#include "DrawLasers.h"
#include "ResourceManager.h"
#include "../Transform.h"

extern ResourceManager* resourceMgr;

DrawLasers::DrawLasers(void) : Drawable()
{
	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * 100 * 4; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0; //only one D3D device

	//create the buffer
	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDescription, NULL, &vertexBuffer);

	glowColor[0]=0; glowColor[1]=1; glowColor[2]=0; glowColor[3]=1;
	laserColor[0]=1; laserColor[1]=0; laserColor[2]=0; laserColor[3]=1;
	glowMode = 0;
	transform = new Transform();
}


DrawLasers::~DrawLasers(void)
{
}


//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void DrawLasers::createBuffer()
{
	HRESULT hr;

	//VERTEX BUFFER
	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = { 
											{"POSITION",	   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0}, 
										};
	
	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
    currentTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = pD3DDevice->CreateInputLayout(layout,
				1,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				&pVertexLayout);

	vertexStride = 12;
	vertexOffset = 0;
}


void DrawLasers::draw()
{
	int size = points.size();
	if(size > 0)
	{
		UINT stride = vertexStride;
		UINT offset = vertexOffset;

	
		D3D11_MAPPED_SUBRESOURCE resource;
		deviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &points[0], sizeof(points)*16);
		deviceContext->Unmap(vertexBuffer, 0);

		// Clear the back buffer 
		deviceContext->IASetInputLayout( pVertexLayout );
		deviceContext->IASetVertexBuffers( 0, 1, &vertexBuffer, &vertexStride, &vertexOffset );
		deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
	
		D3DX11_TECHNIQUE_DESC techDesc;
		currentTechnique->GetDesc( &techDesc );
		for(UINT p = 0; p < techDesc.Passes; ++p)
		{
			currentTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
			deviceContext->Draw( size, 0 );
		}
	}
}
