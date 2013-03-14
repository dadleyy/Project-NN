#include "framework/d3dApp.h"
#include "framework/d3dx11Effect.h"
#include "framework/MathHelper.h"


class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	Game app(hInstance);
	
	if(!app.Init())
		return 0;
	
	return app.Run();
}
 

Game::Game(HINSTANCE hInstance) : D3DApp(hInstance)
{
	mMainWndCaption = L"Project NN";
}

Game::~Game()
{
}

bool Game::Init()
{
	if(!D3DApp::Init())
		return false;
	return true;
}

void Game::OnResize()
{
	D3DApp::OnResize();
}

void Game::UpdateScene(float dt)
{
}

void Game::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	HR(mSwapChain->Present(0, 0));
}