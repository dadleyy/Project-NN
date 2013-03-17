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

void Drawable::createBuffer()
{

}


void Drawable::draw()
{
	UINT stride = sizeof(float)*3;
	UINT offset = 0;

	// Clear the back buffer 
	deviceContext->IASetInputLayout( pVertexLayout );
	deviceContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &vertexStride, &vertexOffset );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	//deviceContext->VSSetShader( vertexShader, NULL, 0 );
	//deviceContext->PSSetShader( pixelShader, NULL, 0 );
    //deviceContext->Draw( numVerts, 0 );

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

void Drawable::destroy()
{
	/*shader->Release();
	pVertexBuffer->Release();
	pVertexLayout->Release();*/
}
