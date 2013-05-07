#include "DrawableInstancedModel.h"
#include "..\Transform.h"
#include "ResourceManager.h"

extern ResourceManager* resourceMgr;

DrawableInstancedModel::DrawableInstancedModel() : Drawable()
{
	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * 100000 * 32; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0; //only one D3D device

	//create the buffer
	pD3DDevice->CreateBuffer(&bufferDescription, NULL, &instanceBuffer);
	instances = new vector<XMFLOAT4X4>();
}


DrawableInstancedModel::~DrawableInstancedModel(void)
{
}


//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void DrawableInstancedModel::createBuffer(char* mesh)
{
	HRESULT hr;

	//VERTEX BUFFER
	//describe the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = { 
											{"POSITION",	   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0 ,                              D3D11_INPUT_PER_VERTEX_DATA, 0}, 
											{"NORMAL",		   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT ,   D3D11_INPUT_PER_VERTEX_DATA, 0}, 
											{"TEXCOORD",	   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D10_APPEND_ALIGNED_ELEMENT ,   D3D11_INPUT_PER_VERTEX_DATA, 0},
											{"WORLD",		   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,	                              D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLD",		   1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLD",		   2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLD",		   3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLDNORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLDNORMAL",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 80,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLDNORMAL",    2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 96,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
											{"WORLDNORMAL",    3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 112,						      D3D11_INPUT_PER_INSTANCE_DATA, 1}
										};
	
	//get required vertex information from a shader technique
	D3DX11_PASS_DESC passDesc;
    currentTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	hr = pD3DDevice->CreateInputLayout(layout,
				11,
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


//
void DrawableInstancedModel::setEffectVariables()
{

}

//
void DrawableInstancedModel::setEffectTextures()
{
	for(auto it = textures.begin(); it != textures.end(); ++it) {
		it->first->AsShaderResource()->SetResource(it->second);
	}
}


//Draw stuff
void DrawableInstancedModel::drawInstanced(int numInstances)
{
	//fill the instance buffer
	D3D11_MAPPED_SUBRESOURCE resource;

	deviceContext->Map(instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource); 
	memcpy((float*)resource.pData,    &(*instances)[0]._11,  numInstances*32*4);
	deviceContext->Unmap(instanceBuffer, 0);

	UINT stride[2] = {vertexStride, 128};
	UINT offset[2] = {vertexOffset, 0};

	// Clear the back buffer 
	deviceContext->IASetInputLayout( pVertexLayout );

	ID3D11Buffer* vbs[2] = {pVertexBuffer, instanceBuffer};
    deviceContext->IASetVertexBuffers(0, 2, vbs, stride, offset);

	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	D3DX11_TECHNIQUE_DESC techDesc;
    currentTechnique->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        currentTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->DrawInstanced(numVerts, numInstances, 0, 0);
	}

	instances->clear();
}