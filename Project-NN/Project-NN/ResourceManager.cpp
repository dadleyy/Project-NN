#include "ResourceManager.h"
#include <cstdlib>

ResourceManager::ResourceManager(void)
{
}


ResourceManager::~ResourceManager(void)
{
}


ResourceManager::ResourceManager(ID3D11Device* device) : randomEngine((unsigned int)time(0))
{
	pD3DDevice = device;
}

//
//
//void DrawableAttributes::addMaterial(Material *m, char* name)
//{
//
//}


void ResourceManager::addEffect(WCHAR* file, char* name)
{
	Effect* e = new Effect;
	ID3DBlob* ppShader = NULL;
	CompileShaderFromFile(file, NULL, "fx_5_0", &ppShader);
	ID3DX11Effect* effect;
	HRESULT hr = D3DX11CreateEffectFromMemory(ppShader->GetBufferPointer(), ppShader->GetBufferSize(), 0, pD3DDevice, &e->effect);
	effects.insert(std::make_pair<char*, Effect*>(name, e));
}

void ResourceManager::addTesellatedSphere(float radius, int divisions, char* name)
{
	HRESULT hr = S_OK;
	Mesh* mesh = new Mesh();

	 if( divisions < 6 ) {
        divisions = 6;
    }
	
	 //define the vertex buffer
	float trigDelta = (360.0/divisions) * (3.1415926536/180);
	mesh->numVerts = divisions*ceil(divisions/2.0)*6;
	XMFLOAT3* verts = new XMFLOAT3[mesh->numVerts];
	int counter = 0;
	for(int k = 0; k < divisions; k++)
	{
		for(int i = 0; i < divisions/2; i++)
		{
			float angle1 = trigDelta * k;
			float angle2 = trigDelta * i;

			float X1 = radius*sin(angle2)*cos(angle1);
			float X2 = radius*cos(angle1+trigDelta)*sin(angle2);
			float X3 = radius*sin(angle2+trigDelta)*cos(angle1);
			float X4 = radius*cos(angle1+trigDelta)*sin(angle2+trigDelta);

			float Y1 = radius*sin(angle1)*sin(angle2);
			float Y2 = radius*sin(angle2+trigDelta)*sin(angle1);
			float Y3 = radius*sin(angle1+trigDelta)*sin(angle2);
			float Y4 = radius*sin(angle2+trigDelta)*sin(angle1+trigDelta);

			float Z1 = radius*cos(angle2)+radius;
			float Z2 = radius*cos(angle2+trigDelta)+radius;

			XMFLOAT3 p1(X1, Y1, Z1);
			XMFLOAT3 p2(X2, Y3, Z1);
			XMFLOAT3 p3(X3, Y2, Z2);
			XMFLOAT3 p4(X4, Y4, Z2);
			verts[counter] = p3;	counter++;
			verts[counter] = p2;	counter++;
			verts[counter] = p1;	counter++;
			verts[counter] = p3;	counter++;
			verts[counter] = p4;	counter++;
			verts[counter] = p2;	counter++;
			//addTriangle(p2, p3, p1);
			//addTriangle(p4, p3, p2);
		}
	}

	XMFLOAT3 *v = verts;

	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * 3 * mesh->numVerts; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0;	//only one D3D device
	
	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = v;

	//Set the size of a single vertex
	mesh->vertexStride = sizeof(float)*3;
	mesh->vertexOffset = 0;
	//create the vertex buffer
	hr = pD3DDevice->CreateBuffer(&bufferDescription, &InitData, &mesh->verticies);

	//define index buffer
	mesh->numIndicies = mesh->numVerts;
	UINT* indicies = new UINT[mesh->numIndicies];

	for(int k = 0; k < mesh->numIndicies; k++)
	{
		indicies[k] = k;
	}

	UINT* i = indicies;

	// Describe the index buffer we are going to create.
    D3D11_BUFFER_DESC indB;
    indB.Usage = D3D11_USAGE_IMMUTABLE;
    indB.ByteWidth = sizeof(UINT) * mesh->numIndicies;
    indB.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indB.CPUAccessFlags = 0;
    indB.MiscFlags = 0;
    indB.StructureByteStride = 0;

	// Specify the data to initialize the index buffer.
	InitData.pSysMem = i;

	// Create the index buffer.
	pD3DDevice->CreateBuffer(&indB, &InitData, &mesh->indicies);
	
	meshes.insert(std::make_pair<char*, Mesh*>(name,mesh));
}

void ResourceManager::addMesh(char* objFile, char* name)
{


}










//***********************************************
//Microsofts shader compiler
//***********************************************
HRESULT ResourceManager::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
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