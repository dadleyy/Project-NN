#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <unordered_map>
#include <xnamath.h>

#include "Component.h"
#include "framework/d3dx11effect.h"

class GameObject;
class Transform;

class Drawable : public Component
{
	
public:
	Drawable(void);
	~Drawable(void);

	bool Init(GameObject* go);

	virtual void draw();	
	virtual void createBuffer(char* mesh);
	virtual void addTexture(char* id, char* textureVariable);
	virtual void addEffectVariables(char* id, char* variableName, float* value);
    virtual void getEffectVariables(char* fxFilename, char* fxTechniqueName);
	virtual void setShader(char* effectName, char* techniqueName);
	virtual void setEffectVariables();
	virtual void setEffectTextures();

	XMFLOAT3 getPosition();
	void setPosition(XMFLOAT3 pos);
	std::unordered_map<ID3DX11EffectShaderResourceVariable*, ID3D11ShaderResourceView*> textures;
	std::unordered_map<ID3DX11EffectVariable*, float*> variables;
	std::unordered_map<char*, ID3DX11Effect*> shaders;
	std::unordered_map<char*, ID3DX11EffectTechnique*> techniques;
	std::unordered_map<char*, ID3D11InputLayout*> layouts;

protected:
	UINT vertexStride; //the size of an individual vertex in bytes
	UINT vertexOffset; //the offset for each vertex in bytes
	D3D11_PRIMITIVE_TOPOLOGY drawtopology;


	ID3D11Device*			pD3DDevice;    //reference to the DX device being used
	ID3D11DeviceContext*    deviceContext; //reference DX device context being used

	//pointers to compiles shader data, the effect and the technique
	char* effectID;

	ID3DX11Effect* currentShader;
	ID3DX11EffectTechnique*	currentTechnique;
	ID3D11InputLayout* currentLayout;

	//vertex buffer
	ID3D11Buffer*		pVertexBuffer;	//the buffer for our verticies
	//index buffer
	ID3D11Buffer*		indexBuffer;	//the buffer for our verticies

	int numVerts;
	int numIndicies;

    // world matrix
    XMFLOAT4X4 world;
	Transform* transform;
};

