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
	Drawable(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	void destroy(); //releases all buffers and deletes all pointers. Call before deleting this object.

	void Init(GameObject* go);

	void draw();	
	virtual void createBuffer(); 
	virtual void createBuffer(char* mesh);
	virtual void addTexture(char* id, char* textureVariable);
	virtual XMFLOAT3* getVerts(float radius, int divisions);
	virtual UINT* getIndicies();
    virtual void getEffectVariables(char* fxFilename, char* fxTechniqueName);
	virtual void setEffectVariables();
	virtual void setEffectTextures();
	XMFLOAT3 getPosition();
	void setPosition(XMFLOAT3 pos);
	std::unordered_map<ID3DX11EffectShaderResourceVariable*, ID3D11ShaderResourceView*> textures;
protected:
	UINT vertexStride; //the size of an individual vertex in bytes
	UINT vertexOffset; //the offset for each vertex in bytes

	ID3D11Device*			pD3DDevice;    //reference to the DX device being used
	ID3D11DeviceContext*    deviceContext; //reference DX device context being used

	

	//pointers to compiles shader data, the effect and the technique
	char* effectID;
	ID3DX11EffectTechnique*	technique;

	//vertex buffer
	ID3D11Buffer*		pVertexBuffer;	//the buffer for our verticies
	ID3D11InputLayout*  pVertexLayout;	//the description of our verticies
	//index buffer
	ID3D11Buffer*		indexBuffer;	//the buffer for our verticies

	int numVerts;
	int numIndicies;


	//Microsofts method that compiles shaders from inside a file
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
  
    // world matrix
    XMFLOAT4X4 world;
	Transform* transform;
};

