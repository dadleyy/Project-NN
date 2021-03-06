
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <unordered_set>

#include "framework/d3dApp.h"

#include "StateManager.h"
#include "states/MainMenu.h"
#include "states/Gameplay.h"
#include "states/Credits.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "input.h"
#include "entity\Drawable.h"

ResourceManager* resourceMgr;
PhysicsManager* physicsMgr;
Input* input;
SceneManager* sceneMgr;

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


	resourceMgr = new ResourceManager(md3dDevice, md3dImmediateContext);
	addResources( );
	
	physicsMgr = new PhysicsManager();
	sceneMgr = new SceneManager();

	//Call again to calculate aspect ratio now that the camera has been initialized.
	OnResize();

	resourceMgr->camera.UpdateViewMatrix();
	manager.Init(MainMenu::Instance());
	return true;
}

void Game::OnResize() {
	D3DApp::OnResize();

	if(resourceMgr == nullptr)
		return;

	resourceMgr->textures["Original"] = originalImageResourceView;
	resourceMgr->textures["Pass1"]    = targetTextureResourceView1;
	resourceMgr->textures["Pass2"]    = targetTextureResourceView2;	
	resourceMgr->textures["Depth"]    = depthTextureResourceView;
	resourceMgr->textures["DScale"]  = targetTextureResourceViewScaledDown;
	resourceMgr->textures["DScale2"]  = targetTextureResourceViewScaledDown2;
	

	resourceMgr->renderTargets["Original"] = originalView;
	resourceMgr->renderTargets["Pass1"]    = targetView1;
	resourceMgr->renderTargets["Pass2"]    = targetView2;
	resourceMgr->renderTargets["DScale"]  = targetViewScaledDown;
	resourceMgr->renderTargets["DScale2"]  = targetViewScaledDown2;

	resourceMgr->viewports["Original"] = mScreenViewport;
	resourceMgr->viewports["DScale2"]  = mScreenViewportDiv5;

	finalDraw = new Drawable();
	finalDraw->getEffectVariables("genericPost", "Render");
	finalDraw->setShader("genericPost", "Render");
	finalDraw->createBuffer("rectangle");
	finalDraw->addTexture("Original", "tex");

	screenWidth = mClientWidth;
	screenHeight = mClientHeight;

	std::cout << "whoa resize" << std::endl;

	resourceMgr->camera.SetLens(resourceMgr->camera.GetFovY(),
								((float)screenWidth)/screenHeight,
								resourceMgr->camera.GetNearZ(),
								resourceMgr->camera.GetFarZ());
}

void Game::UpdateScene(float dt) {
	manager.Update(dt);
	physicsMgr->CheckForCollisions();
	
	sceneMgr->Process();
	physicsMgr->Process();
}

void Game::DrawScene() 
{

	//md3dImmediateContext->ClearState( );
	// Clear the back buffer 
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	// render the scene
	md3dImmediateContext->OMSetRenderTargets(1, &originalView, mDepthStencilView);
	md3dImmediateContext->ClearRenderTargetView(originalView, reinterpret_cast<const float*>(&Colors::Black));
	manager.Draw();
	
	// post Processing
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
	resourceMgr->setCursor( );
	input->OnMouseDown(btnState, L_btn, x, y);
}

void Game::OnMouseDownM(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
	input->OnMouseDown(btnState, M_btn, x, y);
}

void Game::OnMouseDownR(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
	input->OnMouseDown(btnState, R_btn, x, y);
}

void Game::OnMouseUpL(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
	input->OnMouseUp(btnState, L_btn, x, y);
}

void Game::OnMouseUpM(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
	input->OnMouseUp(btnState, M_btn, x, y);
}

void Game::OnMouseUpR(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
	input->OnMouseUp(btnState, R_btn, x, y);
}

void Game::OnMouseMove(WPARAM btnState, int x, int y) {
	resourceMgr->setCursor( );
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

	std::cout << "=== COMPILING CURSORS ===" << std::endl;
	resourceMgr->addCursor(L"res/cursors/default-cursor.cur","default");
	resourceMgr->addCursor(L"res/cursors/hover-cursor.cur","hover");
	resourceMgr->addCursor(L"res/cursors/shooting-cursor.cur","shooting");
	resourceMgr->addCursor(L"res/cursors/active-cursor.cur","active");


	std::cout << "=== COMPILING TEXTURES ===" << std::endl;
	//textures
	resourceMgr->addTexture(L"res/textures/mossy-bricks.dds", "Test");
	resourceMgr->addTexture(L"res/textures/Grass_Diff.dds", "Test2");
	resourceMgr->addTexture(L"res/textures/quickie.dds", "quickie");
	resourceMgr->addTexture(L"res/textures/asteroidTexture.jpg", "asteroid");
	resourceMgr->addTexture(L"res/textures/bombTex.jpg", "bomb");
	resourceMgr->addTexture(L"res/textures/bombBumpTex.jpg", "bombBump");
	resourceMgr->addTexture(L"res/textures/bombGlowTex.jpg", "bombGlow");
	resourceMgr->addTexture(L"res/textures/asteroidBump.jpg", "asteroidBump");
	resourceMgr->addTexture(L"res/textures/shiphullTexture.jpg", "shipTexture");
	resourceMgr->addCubeMap(L"res/textures/SPACE.dds", "skybox");

	// menu textures
	resourceMgr->addTexture(L"res/textures/play-button.png", "playBtn");
	resourceMgr->addTexture(L"res/textures/credit-button.png", "creditBtn");
	resourceMgr->addTexture(L"res/textures/back-button.png", "backBtn");
	resourceMgr->addTexture(L"res/textures/guide-button.png", "guideBtn");
	resourceMgr->addTexture(L"res/textures/exit-button.png", "exitBtn");
	resourceMgr->addTexture(L"res/textures/close-button.png", "closeBtn");
	resourceMgr->addTexture(L"res/textures/bg-template.png", "menuBG");
	resourceMgr->addTexture(L"res/textures/instructions-bg.png", "instructionsBG");
	resourceMgr->addTexture(L"res/textures/credits-bg.png", "creditsBG");


	std::cout << "=== COMPILING MESHES ===" << std::endl;
	//meshes
	resourceMgr->addMesh("res/models/sphere.obj", "Sphere");
	resourceMgr->addMesh("res/models/Dodecahedron.obj", "dodeca");
	resourceMgr->addMesh("res/models/pinnace.obj", "cool");
	resourceMgr->addMesh("res/models/rect.obj", "rectangle");
	resourceMgr->addMesh("res/models/cool.obj", "enemy");
	resourceMgr->addMesh("res/models/asteroid.obj", "Asteroid");


	std::cout << "=== COMPILING EFFECTS ===" << std::endl;
	//effects
	resourceMgr->addEffect(L"res/shaders/betterPhong.fx", "betterPhong" );
	resourceMgr->addEffect(L"res/shaders/betterPhongBump.fx", "betterPhongBump" );
	resourceMgr->addEffect(L"res/shaders/betterPhongInstanced.fx", "instancedPhong" );
	resourceMgr->addEffect(L"res/shaders/genericPostProcess.fx", "genericPost" );
	resourceMgr->addEffect(L"res/shaders/contrast.fx", "contrast" );
	resourceMgr->addEffect(L"res/shaders/skyboxShader.fx", "skyShader" );
	resourceMgr->addEffect(L"res/shaders/betterPhongInstancedBump.fx", "bumpInstancePhong" );
	resourceMgr->addEffect(L"res/shaders/glowDraw.fx", "glowDraw" );
	resourceMgr->addEffect(L"res/shaders/glowEffect.fx", "glowEffect" );
	resourceMgr->addEffect(L"res/shaders/lasers.fx", "laserEffect" );
	resourceMgr->addEffect(L"res/shaders/ui.fx", "menuEffect" );


	std::cout << "=== SETTING BUFFER REFERENCES ===" << std::endl;
	// set effect buffer references
	resourceMgr->setEffectBuffer( "betterPhong", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "betterPhong", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "betterPhong", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "betterPhongBump", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "betterPhongBump", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "betterPhongBump", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "instancedPhong", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "instancedPhong", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "instancedPhong", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "genericPost", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "genericPost", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "genericPost", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "contrast", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "contrast", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "contrast", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "skyShader", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "skyShader", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "skyShader", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "bumpInstancePhong", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "bumpInstancePhong", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "bumpInstancePhong", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "glowDraw", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "glowDraw", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "glowDraw", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "glowEffect", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "glowEffect", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "glowEffect", "LightsBuffer", "Light" );

	resourceMgr->setEffectBuffer( "laserEffect", "perObject", "Object" );
	resourceMgr->setEffectBuffer( "laserEffect", "CameraBuffer", "Camera" );
	resourceMgr->setEffectBuffer( "laserEffect", "LightsBuffer", "Lights" );
	
	std::cout << "=== COMPILING INPUT LAYOUTS ===" << std::endl;
	// input layouts

	std::cout << "-> adding basic effect input layout" << std::endl;
	D3D11_INPUT_ELEMENT_DESC basic_format[] = { 
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 ,                            D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0} 
	};
	InputLayoutDescription bld;
	bld.format = basic_format;
	bld.size = 3;

	resourceMgr->addInputLayout( &bld, "betterPhong", "Render" );
	resourceMgr->addInputLayout( &bld, "betterPhongBump", "Render" );
	resourceMgr->addInputLayout( &bld, "genericPost", "Render" );
	resourceMgr->addInputLayout( &bld, "contrast", "Render" );
	resourceMgr->addInputLayout( &bld, "skyShader", "Render" );
	resourceMgr->addInputLayout( &bld, "glowDraw", "RenderGlowy" );
	resourceMgr->addInputLayout( &bld, "glowEffect", "Horz" );
	resourceMgr->addInputLayout( &bld, "glowEffect", "Vert" );
	resourceMgr->addInputLayout( &bld, "glowEffect", "Add" );

	std::cout << "-> adding laser effect input layout" << std::endl;
	D3D11_INPUT_ELEMENT_DESC laser_format[] = { 
		{"POSITION",	   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	InputLayoutDescription lld;
	lld.format = laser_format;
	lld.size = 1;
	resourceMgr->addInputLayout( &lld, "laserEffect", "RenderLasers" );

	std::cout << "-> adding menu effect input layout" << std::endl;
	D3D11_INPUT_ELEMENT_DESC menu_format[] = { 
		{"WIDTH",    0, DXGI_FORMAT_R32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"HEIGHT",   0, DXGI_FORMAT_R32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	InputLayoutDescription mld;
	mld.format = menu_format;
	mld.size = 3;
	resourceMgr->addInputLayout( &mld, "menuEffect", "Render" );

	std::cout << "-> adding instanced effect input layout" << std::endl;
	D3D11_INPUT_ELEMENT_DESC bump_phong_format[] = { 
		{"POSITION",	   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0 ,                              D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"NORMAL",		   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT ,   D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"TEXCOORD",	   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D10_APPEND_ALIGNED_ELEMENT ,   D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"WORLD",		   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,	                              D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLD",		   1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLD",		   2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLD",		   3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLDNORMAL",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLDNORMAL",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 80,	                          D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLDNORMAL",    2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 96,						      D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"WORLDNORMAL",    3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 112,						      D3D11_INPUT_PER_INSTANCE_DATA, 1}
	};
	InputLayoutDescription bipd;
	bipd.format = bump_phong_format;
	bipd.size = 11;
	resourceMgr->addInputLayout( &bipd, "bumpInstancePhong", "Render" );
	resourceMgr->addInputLayout( &bipd, "instancedPhong", "Render" );

	std::cout << "=== ADDING LIGHTS ===" << std::endl;
	//LIGHTS
	resourceMgr->addLight(40, 40, 3.5, .4, .5, .85, 1.0,  -.3, 0, 1, 0, 1, .4, NONE, 1, DIRECTIONAL_LIGHT);
	resourceMgr->addLight(40, 40, 3.5, .85, .75, .75, 1.0,  1, 0, -.3, 0, 1, .7, NONE, 1, DIRECTIONAL_LIGHT);
	resourceMgr->addLight(-30, -30, 3.5, 0.0, 1.0, 1.0, 0.0,  1, 1, 0, 55, 45, 2, LINEAR, 1, SPOT_LIGHT);

	std::cout << "=== COMPILING BLEND STATES ===" << std::endl;
	// blend states

	D3D11_BLEND_DESC default_blend;
	ZeroMemory( &default_blend, sizeof(D3D11_BLEND_DESC) );
	default_blend.AlphaToCoverageEnable = FALSE;
	default_blend.IndependentBlendEnable = FALSE;
	default_blend.RenderTarget[0].BlendEnable = FALSE;
	default_blend.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	default_blend.RenderTarget[0].DestBlend	= D3D11_BLEND_ZERO;
	default_blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	default_blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	default_blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	default_blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	default_blend.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;
	resourceMgr->addBlendState( default_blend, "defaultBlend" );


	D3D11_BLEND_DESC button_blend;
	ZeroMemory( &button_blend, sizeof(D3D11_BLEND_DESC) );
	button_blend.AlphaToCoverageEnable = FALSE;
	button_blend.IndependentBlendEnable = FALSE;
	button_blend.RenderTarget[0].BlendEnable = TRUE;
	button_blend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	button_blend.RenderTarget[0].DestBlend	= D3D11_BLEND_ONE;
	button_blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	button_blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	button_blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	button_blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	button_blend.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;
	resourceMgr->addBlendState( button_blend, "buttonBlend" );

}
