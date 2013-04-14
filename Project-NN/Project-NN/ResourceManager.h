#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include <unordered_map>
#include <random>
#include <iostream>
#include <fstream>
#include <regex>

#include "framework/d3dx11effect.h"
#include "framework/Camera.h"
#include "entity/Light.h"

using namespace std;

struct Mesh
{
	ID3D11Buffer* verticies;
	ID3D11Buffer* indicies;

	int numVerts;
	int numIndicies;
	UINT vertexStride; 
	UINT vertexOffset; 
};

struct Effect
{
	ID3DX11Effect* effect;
};

class ResourceManager
{
public:
	ResourceManager(void);
	ResourceManager(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	ID3D11Device* pD3DDevice;
	ID3D11DeviceContext* md3dImmediateContext;

	~ResourceManager(void);
	unordered_map<char*, Mesh*> meshes;
	unordered_map<char*, Effect*> effects;
	unordered_map<char*, ID3D11Buffer*> cBuffers;
	vector<LightStruct*> lights;
	std::unordered_map<char*, ID3D11ShaderResourceView*> textures;
	//unordered_map<char*, Material*> materials;
	

	bool lightChange;
	unsigned int numLights;

	bool cameraChange;
	
	void addEffect(WCHAR* file, char* name);
	void addTexture(WCHAR* file, char* name);
	bool addMesh(char* objFile, char* name);
	void addCBuffer(unsigned int byteWidth, char* name);
    void addCamera( );
	void addLight(float posX, float posY, float posZ,
						 float colX, float colY, float colZ, float colA,
						 float dirX, float dirY, float dirZ,
						 float radius, float angle, float intensity, int falloff, 
						 int onOff, int type);

	Mesh* getMesh( char* meshName );
	ID3DX11Effect* getEffect( char* effectName );
	ID3D11Buffer* getCBuffer( char* bufferName );

    Camera camera;

	void updateShaderBuffers();

	std::default_random_engine randomEngine;

private:
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
};

extern ResourceManager* resourceMgr;