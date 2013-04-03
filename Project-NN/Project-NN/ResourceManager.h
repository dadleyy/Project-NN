#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "framework/d3dx11effect.h"
#include "framework/Camera.h"
#include <unordered_map>
#include <random>

#include <iostream>
#include <fstream>
#include <regex>
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

//struct Material
//{
//	XMFLOAT4 color;
//};

class ResourceManager
{
public:
	ResourceManager(void);
	ResourceManager(ID3D11Device* device);
	ID3D11Device* pD3DDevice;
	~ResourceManager(void);
	std::unordered_map<char*, Mesh*> meshes;
	std::unordered_map<char*, Effect*> effects;
	//std::unordered_map<char*, Material*> materials;
	
	
	//void addMaterial(Material *m, char* name);
	void addEffect(WCHAR* file, char* name);
	void addTesellatedSphere(float radius, int divisions, char* name);
	bool addMesh(char* objFile, char* name);
    void makeCamera( );

    Camera camera;
	std::default_random_engine randomEngine;

private:
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
};

