//***************************************************************************************
// d3dApp.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Simple Direct3D demo application class.  
// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.
//***************************************************************************************

#ifndef D3DAPP_H
#define D3DAPP_H

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>
class Drawable;

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();
	
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	
	int Run();
 
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init();
	virtual void OnResize(); 
	virtual void UpdateScene(float dt)=0;
	virtual void DrawScene()=0; 
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse and keyboard input.
	virtual void OnMouseDownL(WPARAM btnState, int x, int y){ }
	virtual void OnMouseDownM(WPARAM btnState, int x, int y){ }
	virtual void OnMouseDownR(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUpL(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseUpM(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseUpR(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }
	virtual void OnKeyDown(WPARAM keyCode){ }
	virtual void OnKeyUp(WPARAM keyCode){ }

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameStats();

protected:

	HINSTANCE mhAppInst;
	HWND      mhMainWnd;
	bool      mAppPaused;
	bool      mMinimized;
	bool      mMaximized;
	bool      mResizing;
	UINT      m4xMsaaQuality;

	GameTimer mTimer;

	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;

	Drawable* finalDraw;

	//set up 2 additional render targets for post processing effects
	ID3D11Texture2D* originalImage;
	ID3D11Texture2D* targetTexture1;
	ID3D11Texture2D* targetTexture2;

	ID3D11RenderTargetView* originalView;
	ID3D11RenderTargetView* targetView1;
	ID3D11RenderTargetView* targetView2;

	ID3D11ShaderResourceView* originalImageResourceView;
	ID3D11ShaderResourceView* targetTextureResourceView1;
	ID3D11ShaderResourceView* targetTextureResourceView2;

	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	D3D_DRIVER_TYPE md3dDriverType;
	int mClientWidth;
	int mClientHeight;
	bool mEnable4xMsaa;
};

#endif // D3DAPP_H