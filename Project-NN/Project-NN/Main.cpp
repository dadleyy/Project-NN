
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "framework/d3dApp.h"

#include "StateManager.h"
#include "states/TestState.h"
#include "ResourceManager.h"
#include "input.h"

ResourceManager* drawAtts;
int screenWidth;
int screenHeight;
void addResources();

class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

	void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);
    void OnKeyDown(WPARAM keyCode);
    void OnKeyUp(WPARAM keyCode);

private:
	StateManager manager;
	Input input;
};


void ShowConsoleWindow()
{
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//Show a console when debugging for stdout.
	ShowConsoleWindow();
#endif

	Game app(hInstance);
	
	if(!app.Init())
		return 0;
	
	return app.Run();
}
 

Game::Game(HINSTANCE hInstance) : D3DApp(hInstance), manager()
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


	manager.Init(md3dDevice, md3dImmediateContext);
	input.initialize(&manager);
	drawAtts = new ResourceManager(md3dDevice, md3dImmediateContext);
	addResources();
	drawAtts->camera.UpdateViewMatrix();
	manager.PushState(TestState::Instance());
	return true;
}

void Game::OnResize()
{
	D3DApp::OnResize();
    screenWidth = mClientWidth;
    screenHeight = mClientHeight;
}

void Game::UpdateScene(float dt)
{
	manager.Update(dt);
}

void Game::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	manager.Draw();

	HR(mSwapChain->Present(0, 0));
}


void Game::OnMouseDown(WPARAM btnState, int x, int y)
{
	input.OnMouseDown(btnState, x, y);
}
void Game::OnMouseUp(WPARAM btnState, int x, int y)
{
    input.OnMouseUp(btnState, x, y);
}

void Game::OnMouseMove(WPARAM btnState, int x, int y)
{
    input.OnMouseMove(btnState, x, y);
}

void Game::OnKeyDown(WPARAM keyCode)
{
    input.OnKeyDown(keyCode);
}
void Game::OnKeyUp(WPARAM keyCode)
{
    input.OnKeyUp(keyCode);
}

void addResources()
{
	drawAtts->addCBuffer(816, "Light");
	drawAtts->addCBuffer(144, "Camera");
	drawAtts->addCBuffer(128, "Object");

	drawAtts->addMesh("res/models/sphere.obj", "Sphere");
	drawAtts->addMesh("res/models/Dodecahedron.obj", "dodeca");

	drawAtts->addEffect(L"res/shaders/betterPhong.fx", "betterPhong" );

	drawAtts->addLight(5, 5, 10, 0.1, .2, 1.0, 1.0, 0, 0, 0, 15, 1, 1, QUADRATIC, 1, POINT_LIGHT);
	drawAtts->addLight(0, 1,  0, 1, 1, 0, 1.0, 0, 0, 0,  0, 0, .04,  NONE, 1, AMBIENT_LIGHT);
	drawAtts->addLight(-4, 0, 3.5, .6, .4, .2, 1.0,  0, 0, 0, 15, 1, 1, LINEAR, 1, POINT_LIGHT);
}
