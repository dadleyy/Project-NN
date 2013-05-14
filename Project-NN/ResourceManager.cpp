#include "ResourceManager.h"
#include <cstdlib>
#include "framework\OBJLoader.h"

using namespace std;

ResourceManager::ResourceManager(void) {
}


ResourceManager::~ResourceManager(void) {
}

ResourceManager::ResourceManager(ID3D11Device* device, ID3D11DeviceContext* immediateContext) : randomEngine((unsigned int)time(0)) {
	pD3DDevice = device;
	md3dImmediateContext = immediateContext;
	lightChange = 1;
	cameraChange = 1;
	numLights = 0;
}

void ResourceManager::addEffect(WCHAR* file, char* name) {
	HRESULT hr;

	Effect* e = new Effect;
	ID3DBlob* ppShader = NULL;
	hr = CompileShaderFromFile(file, NULL, "fx_5_0", &ppShader);

	if(hr == S_OK) {
		ID3DX11Effect* effect;
		HRESULT hr = D3DX11CreateEffectFromMemory(ppShader->GetBufferPointer(), ppShader->GetBufferSize(), 0, pD3DDevice, &e->effect);
		effects.insert(std::make_pair<char*, Effect*>(name, e));
	}
}

void ResourceManager::addTexture(WCHAR* file, char* name) {
	HRESULT hr;
	ID3D11ShaderResourceView* view;
	hr = D3DX11CreateShaderResourceViewFromFile(pD3DDevice,
	        file, 0, 0, &view, 0 );

	if(hr == S_OK) {
		textures.insert(std::make_pair<char*, ID3D11ShaderResourceView*>(name, view));
	}
}

void ResourceManager::addCubeMap(WCHAR* file, char* name) 
{
	HRESULT hr;
	ID3D11ShaderResourceView* view;

	D3DX11_IMAGE_LOAD_INFO loadInfo;
	loadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	hr = D3DX11CreateShaderResourceViewFromFile(pD3DDevice, file, &loadInfo, 0, &view, 0 );

	if(hr == S_OK) {
		textures.insert(std::make_pair<char*, ID3D11ShaderResourceView*>(name, view));
	}
}

bool ResourceManager::addMesh(char* objFile, char* name) {
	HRESULT hr;

	Mesh* mesh = new Mesh();

	int numVerts;
	int numIndex;

	OBJLoader obj;
	obj.readFile(objFile);

	numVerts = obj.getNumVerts();
	numIndex = obj.getNumInds();

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	D3D11_BUFFER_DESC bufferDescription;
	bufferDescription.Usage = D3D11_USAGE_IMMUTABLE; //the data will not change
	bufferDescription.ByteWidth = sizeof(float) * obj.numVerts * 8; //total number of bytes for all verticies
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER; //binds the buffer to the correct type
	bufferDescription.CPUAccessFlags = 0;	//0 means the cpu does not have access to the buffer
	bufferDescription.MiscFlags = 0; //only one D3D device

	//add the data for the buffer
	D3D11_SUBRESOURCE_DATA initData;
	float* v = obj.getVerticies();
	initData.pSysMem = v;

	//create the buffer
	hr = pD3DDevice->CreateBuffer(&bufferDescription, &initData, &vertexBuffer);

	//create index buffer
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = sizeof(unsigned int) * numIndex;
	bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	unsigned int* i = obj.getIndicies();
	initData.pSysMem = i;

	hr = pD3DDevice->CreateBuffer(&bufferDescription, &initData, &indexBuffer);

	//add the mesh to the vertex buffer map
	mesh->verticies = vertexBuffer;
	mesh->indicies = indexBuffer;
	mesh->numIndicies = numIndex;
	mesh->numVerts = numVerts;
	mesh->vertexStride = sizeof(float) * 8;
	meshes.insert( make_pair<char*, Mesh*>(name, mesh) );

	return 1;
}

void ResourceManager::addCBuffer(unsigned int byteWidth, char* name) {
	ID3D11Buffer* buffer;
	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = byteWidth;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	//D3D10_SUBRESOURCE_DATA initData;
	//LightStruct* v = lights[0];
	//initData.pSysMem = v;

	hr = pD3DDevice->CreateBuffer( &bd, NULL, &buffer );

	if(hr == S_OK)
		cBuffers.insert( make_pair<char*, ID3D11Buffer*>(name, buffer));
}

void ResourceManager::addLight(float posX, float posY, float posZ,
                               float colX, float colY, float colZ, float colA,
                               float dirX, float dirY, float dirZ,
                               float radius, float angle, float intensity, int falloff,
                               int onOff, int type) {
	if(numLights < 10) {
		numLights++;
		lights.push_back(createLight(posX, posY, posZ, colX, colY, colZ, colA, dirX, dirY, dirZ, radius, angle, intensity, falloff, onOff, type));
	}
}


Mesh* ResourceManager::getMesh( char* meshName ) {
	Mesh* m;
	try {
		m = meshes[ meshName ];
	} catch ( out_of_range e ) {
		m = 0;
	}
	return m;
}

ID3DX11Effect* ResourceManager::getEffect( char* effectName ) {
	Effect* e;
	try {
		e = effects.at( effectName );
	} catch ( out_of_range e ) {
		return 0;
	}
	return e->effect;
}

ID3D11Buffer* ResourceManager::getCBuffer( char* bufferName ) {
	ID3D11Buffer* b;
	try {
		b = cBuffers.at( bufferName );
	} catch ( out_of_range e ) {
		return 0;
	}
	return b;
}

void ResourceManager::updateShaderBuffers() {
	D3D11_MAPPED_SUBRESOURCE resource;

	//update light buffer if it has changed
	if(lightChange) {
		md3dImmediateContext->Map(getCBuffer("Light"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource);

		for(int i = 0; i < numLights; i++) {
			memcpy((float*)resource.pData+20*i, lights[i], 80);
		}
		memcpy((float*)resource.pData+200, &numLights, 16);

		md3dImmediateContext->Unmap(getCBuffer("Light"), 0);

		lightChange = 0;
	}

	//update camera buffer if it has changed
	if(cameraChange) {
		md3dImmediateContext->Map(getCBuffer("Camera"), 0, D3D11_MAP_WRITE_DISCARD, NULL,  &resource);

		memcpy((float*)resource.pData,    camera.getViewPointer(),  64);
		memcpy((float*)resource.pData+16, camera.getProjPointer(),  64);
		memcpy((float*)resource.pData+32, camera.getPosPointer(),    12);

		md3dImmediateContext->Unmap(getCBuffer("Camera"), 0);

		//cameraChange = 0;
	}
}


//***********************************************
//Microsofts shader compiler
//***********************************************
HRESULT ResourceManager::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ) {
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
	if( FAILED(hr) ) {
		if( pErrorBlob != NULL )
			OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
		if( pErrorBlob ) pErrorBlob->Release();
		return hr;
	}
	if( pErrorBlob ) pErrorBlob->Release();

	return S_OK;
}

void ResourceManager::setEffectBuffer( char* effectID, char* effectBufferName, char* localBufferName ){
	effects.at( effectID )->effect->GetConstantBufferByName( effectBufferName )->SetConstantBuffer( getCBuffer(localBufferName) );
}