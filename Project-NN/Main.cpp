
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <unordered_set>

#include "framework/d3dApp.h"

#include "StateManager.h"
#include "states/TestState.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "GuiManager.h"
#include "SceneManager.h"
#include "input.h"
#include "entity\Drawable.h"

ResourceManager* resourceMgr;
PhysicsManager* physicsMgr;
Input* input;
SceneManager* sceneMgr;
GuiManager* guiMgr;

int screenWidth;
int screenHeight;
void addResources();

class Game : public D3DApp {
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


void ShowConsoleWindow() {
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
                   PSTR cmdLine, int showCmd) {
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


Game::Game(HINSTANCE hInstance) : D3DApp(hInstance), manager() {
	mMainWndCaption = L"Project NN";
}

Game::~Game() {
}

bool Game::Init() {
	if(!D3DApp::Init())
		return false;

	L_btn = 1;
	M_btn = 2;
	R_btn = 3;
	input = new Input();

	manager.Init();

	resourceMgr = new ResourceManager(md3dDevice, md3dImmediateContext);
	addResources();
	
	physicsMgr = new PhysicsManager();
	sceneMgr = new SceneManager();

	//Call again to calculate aspect ratio now that the camera has been initialized.
	OnResize();

	resourceMgr->camera.UpdateViewMatrix();
	manager.PushState(TestState::Instance());
	return true;
}

void Game::OnResize() {
	D3DApp::OnResize();

	if(resourceMgr == nullptr)
		return;

	resourceMgr->textures["Original"] = originalImageResourceView;
	resourceMgr->textures["Pass1"]    = targetTextureResourceView1;
	resourceMgr->textures["Pass2"]    = targetTextureResourceView2;	

	resourceMgr->renderTargets["Original"] = originalView;
	resourceMgr->renderTargets["Pass1"]    = targetView1;
	resourceMgr->renderTargets["Pass2"]    = targetView2;

	finalDraw = new Drawable();
	finalDraw->getEffectVariables("genericPost", "Render");
	finalDraw->createBuffer("rectangle");
	finalDraw->addTexture("Original", "tex");

	screenWidth = mClientWidth;
	screenHeight = mClientHeight;

	resourceMgr->camera.SetLens(resourceMgr->camera.GetFovY(),
								((float)screenWidth)/screenHeight,
								resourceMgr->camera.GetNearZ(),
								resourceMgr->camera.GetFarZ());
}

void Game::UpdateScene(float dt) {
	physicsMgr->CheckForCollisions();
	manager.Update(dt);
	sceneMgr->Process();
	physicsMgr->Process();
}

void Game::DrawScene() 
{
	// Clear the back buffer 
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	//render the scene
	md3dImmediateContext->OMSetRenderTargets(1, &originalView, mDepthStencilView);
	md3dImmediateContext->ClearRenderTargetView(originalView, reinterpret_cast<const float*>(&Colors::Black));
	manager.Draw();
	
	//post Processing
	//*******************




	//*******************

	//draw final image
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, 0);
	finalDraw->setEffectTextures();
	finalDraw->draw();

	ID3D11ShaderResourceView* k[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	md3dImmediateContext->PSSetShaderResources(0, 16, k);

	HR(mSwapChain->Present(0, 0));
}


void Game::OnMouseDownL(WPARAM btnState, int x, int y) {
	input->OnMouseDown(btnState, L_btn, x, y);
}

void Game::OnMouseDownM(WPARAM btnState, int x, int y) {
	input->OnMouseDown(btnState, M_btn, x, y);
}

void Game::OnMouseDownR(WPARAM btnState, int x, int y) {
	input->OnMouseDown(btnState, R_btn, x, y);
}

void Game::OnMouseUpL(WPARAM btnState, int x, int y) {
	input->OnMouseUp(btnState, L_btn, x, y);
}

void Game::OnMouseUpM(WPARAM btnState, int x, int y) {
	input->OnMouseUp(btnState, M_btn, x, y);
}

void Game::OnMouseUpR(WPARAM btnState, int x, int y) {
	input->OnMouseUp(btnState, R_btn, x, y);
}

void Game::OnMouseMove(WPARAM btnState, int x, int y) {
	input->OnMouseMove(btnState, x, y);
}

void Game::OnKeyDown(WPARAM keyCode) {
	input->OnKeyDown(keyCode);
}
void Game::OnKeyUp(WPARAM keyCode) {
	input->OnKeyUp(keyCode);
}

void addResources() {
	//constant buffers
	resourceMgr->addCBuffer(816, "Light");
	resourceMgr->addCBuffer(144, "Camera");
	resourceMgr->addCBuffer(128, "Object");

	//textures
	resourceMgr->addTexture(L"res/textures/mossy-bricks.dds", "Test");
	resourceMgr->addTexture(L"res/textures/Grass_Diff.dds", "Test2");
	resourceMgr->addTexture(L"res/textures/quickie.dds", "quickie");
	resourceMgr->addTexture(L"res/textures/asteroidTexture.jpg", "asteroid");
	resourceMgr->addTexture(L"res/textures/asteroidBump.jpg", "asteroidBump");
	resourceMgr->addTexture(L"res/textures/shiphullTexture.jpg", "shipTexture");
	resourceMgr->addCubeMap(L"res/textures/SPACE.dds", "skybox");

	//meshes
	resourceMgr->addMesh("res/models/sphere.obj", "Sphere");
	resourceMgr->addMesh("res/models/Dodecahedron.obj", "dodeca");
	resourceMgr->addMesh("res/models/pinnace.obj", "cool");
	resourceMgr->addMesh("res/models/rect.obj", "rectangle");
	resourceMgr->addMesh("res/models/cool.obj", "enemy");
	resourceMgr->addMesh("res/models/asteroid.obj", "Asteroid");

	//effects
	resourceMgr->addEffect(L"res/shaders/betterPhong.fx", "betterPhong" );
	resourceMgr->addEffect(L"res/shaders/betterPhongInstanced.fx", "instancedPhong" );
	resourceMgr->addEffect(L"res/shaders/genericPostProcess.fx", "genericPost" );
	resourceMgr->addEffect(L"res/shaders/contrast.fx", "contrast" );
	resourceMgr->addEffect(L"res/shaders/skyboxShader.fx", "skyShader" );
	resourceMgr->addEffect(L"res/shaders/betterPhongInstancedBump.fx", "bumpInstancePhong" );

	//lights
	resourceMgr->addLight(5, 5, 10, 0.1, .2, 1.0, 1.0, 0, 0, 0, 15, 1, 1, QUADRATIC, 1, POINT_LIGHT);
	resourceMgr->addLight(0, 1,  0, 1, 1, 1, 1.0, 0, 0, 0,  0, 0, .3,  NONE, 1, AMBIENT_LIGHT);
	resourceMgr->addLight(30, 10, 3.5, .6, .6, .6, 1.0,  0, 0, 0, 0, 1, 1, NONE, 1, POINT_LIGHT);
	resourceMgr->addLight(-30, -30, 3.5, 0.0, 1.0, 1.0, 0.0,  1, 1, 0, 0, 5, 1, NONE, 1, SPOT_LIGHT);
}

