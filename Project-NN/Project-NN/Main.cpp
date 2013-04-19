
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "framework/d3dApp.h"

#include "StateManager.h"
#include "states/TestState.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "input.h"
#include "entity\Drawable.h"

ResourceManager* resourceMgr;
PhysicsManager* physicsMgr;
Input* input;

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

	manager.Init(md3dDevice, md3dImmediateContext);

	resourceMgr = new ResourceManager(md3dDevice, md3dImmediateContext);
	addResources();
	resourceMgr->textures.insert(make_pair<char*, ID3D11ShaderResourceView*>("Pass1", targetTextureResourceView1));
	resourceMgr->textures.insert(make_pair<char*, ID3D11ShaderResourceView*>("Pass2", targetTextureResourceView2));

	postRect = new Drawable(md3dDevice, md3dImmediateContext);
	postRect->getEffectVariables("genericPost", "Render");
	postRect->createBuffer("rectangle");
	postRect->addTexture("Pass1", "tex");

	physicsMgr = new PhysicsManager();

	//Call again to calculate aspect ratio now that the camera has been initialized.
	OnResize();

	resourceMgr->camera.UpdateViewMatrix();
	manager.PushState(TestState::Instance());
	return true;
}

void Game::OnResize() {
	D3DApp::OnResize();
	screenWidth = mClientWidth;
	screenHeight = mClientHeight;
	if(resourceMgr != nullptr)
		resourceMgr->camera.SetLens(resourceMgr->camera.GetFovY(),
		                            ((float)screenWidth)/screenHeight,
		                            resourceMgr->camera.GetNearZ(),
		                            resourceMgr->camera.GetFarZ());
}

void Game::UpdateScene(float dt) {
	//TODO: Commented because of performance issues.
	physicsMgr->CheckForCollisions();
	manager.Update(dt);
}

void Game::DrawScene() 
{
	// Clear the back buffer 
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Green));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	//render the scene
	resourceMgr->getEffect("genericPost")->GetVariableByName("tex")->AsShaderResource()->SetResource(NULL);

	md3dImmediateContext->OMSetRenderTargets(1, &targetView1, mDepthStencilView);
	md3dImmediateContext->ClearRenderTargetView(targetView1, reinterpret_cast<const float*>(&Colors::Cyan));
	manager.Draw();

	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, 0);

	postRect->getEffectVariables("genericPost", "Render");
	//postRect->setEffectTextures();
	resourceMgr->getEffect("genericPost")->GetVariableByName("tex")->AsShaderResource()->SetResource(targetTextureResourceView1);
	postRect->draw();

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

	//meshes
	resourceMgr->addMesh("res/models/sphere.obj", "Sphere");
	resourceMgr->addMesh("res/models/Dodecahedron.obj", "dodeca");
	resourceMgr->addMesh("res/models/pinnace.obj", "cool");
	resourceMgr->addMesh("res/models/rect.obj", "rectangle");
	resourceMgr->addMesh("res/models/cool.obj", "enemy");

	//effects
	resourceMgr->addEffect(L"res/shaders/betterPhong.fx", "betterPhong" );
	resourceMgr->addEffect(L"res/shaders/genericPostProcess.fx", "genericPost" );

	//lights
	resourceMgr->addLight(5, 5, 10, 0.1, .2, 1.0, 1.0, 0, 0, 0, 15, 1, 1, QUADRATIC, 1, POINT_LIGHT);
	resourceMgr->addLight(0, 1,  0, 1, 1, 0, 1.0, 0, 0, 0,  0, 0, .3,  NONE, 1, AMBIENT_LIGHT);
	resourceMgr->addLight(-4, 0, 3.5, .6, .4, .2, 1.0,  0, 0, 0, 15, 1, 1, LINEAR, 1, POINT_LIGHT);
	resourceMgr->addLight(-30, -30, 3.5, 0.0, 1.0, 1.0, 0.0,  1, 1, 0, 0, 5, 1, NONE, 1, SPOT_LIGHT);
}

