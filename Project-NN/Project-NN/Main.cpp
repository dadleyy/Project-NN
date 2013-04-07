
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
Input* input;
int screenWidth;
int screenHeight;

class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	~Game();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

	void OnMouseDownL(WPARAM btnState, int x, int y);
	void OnMouseDownM(WPARAM btnState, int x, int y);
	void OnMouseDownR(WPARAM btnState, int x, int y);
    void OnMouseUpL(WPARAM btnState, int x, int y);
	void OnMouseUpM(WPARAM btnState, int x, int y);
	void OnMouseUpR(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);
    void OnKeyDown(WPARAM keyCode);
    void OnKeyUp(WPARAM keyCode);



private:
	StateManager manager;
	UINT L_btn;
	UINT M_btn;
	UINT R_btn;
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
	L_btn = 1;
	M_btn = 2;
	R_btn = 3;
	input = new Input();
	manager.Init(md3dDevice, md3dImmediateContext);
//	input->initialize(&manager);
//	manager.setInput(&input);
	
	drawAtts = new ResourceManager(md3dDevice);
	drawAtts->addTesellatedSphere(.3, 50, "testSphere");
	drawAtts->addEffect(L"res/shaders/DrawSphere.fx", "sphereEffect");
	drawAtts->addEffect(L"res/shaders/phong.fx", "phong");
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


void Game::OnMouseDownL(WPARAM btnState, int x, int y)
{
	input->OnMouseDown(btnState, L_btn, x, y);
}

void Game::OnMouseDownM(WPARAM btnState, int x, int y)
{
	input->OnMouseDown(btnState, M_btn, x, y);
}

void Game::OnMouseDownR(WPARAM btnState, int x, int y)
{
	input->OnMouseDown(btnState, R_btn, x, y);
}

void Game::OnMouseUpL(WPARAM btnState, int x, int y)
{
    input->OnMouseUp(btnState, L_btn, x, y);
}

void Game::OnMouseUpM(WPARAM btnState, int x, int y)
{
    input->OnMouseUp(btnState, M_btn, x, y);
}

void Game::OnMouseUpR(WPARAM btnState, int x, int y)
{
    input->OnMouseUp(btnState, R_btn, x, y);
}



void Game::OnMouseMove(WPARAM btnState, int x, int y)
{
    input->OnMouseMove(btnState, x, y);
}

void Game::OnKeyDown(WPARAM keyCode)
{
    input->OnKeyDown(keyCode);
}
void Game::OnKeyUp(WPARAM keyCode)
{
    input->OnKeyUp(keyCode);
}