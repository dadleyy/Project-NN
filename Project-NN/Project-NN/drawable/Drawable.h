#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

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


	ID3D11VertexShader*     vertexShader; //reference to the vertex shader for this object
	//ID3D11GeometryShader*	geometryShader;	//reference to the geometry shader for this object
	ID3D11PixelShader*      pixelShader; //reference to the pixel shader for this object

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

