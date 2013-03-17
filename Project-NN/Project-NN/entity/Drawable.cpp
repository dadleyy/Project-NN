#include "Drawable.h"


Drawable::Drawable(void)
{
}

Drawable::Drawable(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	numVerts = 0;
	pD3DDevice = device;
	deviceContext = immediateContext;
	pVertexBuffer = 0;
	pVertexLayout = 0;
	vertexStride = 0;
	vertexOffset = 0;
}

Drawable::~Drawable(void)
{
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
	UINT stride = sizeof(float)*3;
	UINT offset = 0;

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
		deviceContext->DrawIndexed( numIndicies, 0, 0 );
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



//****************************************************************
//Creates all buffers needed for the object (vertex, index, etc.)
//and compiles the shaders to be used for this object
// **We need to add the index buffer code still**
//****************************************************************
void Drawable::createBuffer()
{
	HRESULT hr;
	//create the vertex shader
	ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( L"res/shaders/DrawSphere.fx", NULL, "fx_5_0", &ppShader ); 
	//hr = pD3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &vertexShader );
	D3DX11CreateEffectFromMemory(ppShader->GetBufferPointer(), ppShader->GetBufferSize(), 0, pD3DDevice, &effect);
	technique = effect->GetTechniqueByName("Render");

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

	XMFLOAT3 *v = getVerts(.3, 50);

	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * 3 * numVerts; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0;	//only one D3D device
	
	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = v;

	//Set the size of a single vertex
	vertexStride = sizeof(float)*3;

	//create the vertex buffer
	hr = pD3DDevice->CreateBuffer(&bufferDescription, &InitData, &pVertexBuffer);

	//INDEX BUFFER
	UINT* i = getIndicies();

	// Describe the index buffer we are going to create.
    D3D11_BUFFER_DESC indB;
    indB.Usage = D3D11_USAGE_IMMUTABLE;
    indB.ByteWidth = sizeof(UINT) * numIndicies;
    indB.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indB.CPUAccessFlags = 0;
    indB.MiscFlags = 0;
    indB.StructureByteStride = 0;

	// Specify the data to initialize the index buffer.
	InitData.pSysMem = i;

	// Create the index buffer.
	ID3D11Buffer* mIB;
	pD3DDevice->CreateBuffer(&indB, &InitData, &indexBuffer);
}



void Drawable::destroy()
{
	/*shader->Release();
	pVertexBuffer->Release();
	pVertexLayout->Release();*/
}


