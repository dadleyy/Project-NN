#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "..\framework\d3dx11effect.h"

class Drawable
{
public:
	Drawable(void);
	~Drawable(void);
	Drawable(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	virtual void createBuffer(); 
	void destroy(); //releases all buffers and deletes all pointers. Call before deleteing this object.
	void draw();	

protected:
	UINT vertexStride; //the size of an individual vertex in bytes
	UINT vertexOffset; //the offset for each vertex in bytes

	ID3D11Device*			pD3DDevice;    //reference to the DX device being used
	ID3D11DeviceContext*    deviceContext; //reference DX device context being used

	//pointers to compiles shader data, the effect and the technique
	ID3DX11Effect*			effect;
	ID3DX11EffectTechnique*	technique;
	ID3D10Blob*				ppShader;

	ID3D11Buffer*		pVertexBuffer;	//the buffer for our verticies
	ID3D11InputLayout*  pVertexLayout;	//the description of our verticies
	int numVerts;

	//Microsofts method that compiles shaders from inside a file
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
	//-Things needed in the future-
	//global shader paramterts[]
	//location
	//scale
	//etc.


	
	
};

