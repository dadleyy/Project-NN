#include "Skybox.h"
#include "ResourceManager.h"

#include "Transform.h"
#include "Drawable.h"

extern ResourceManager* resourceMgr;

Skybox::Skybox(void)
{
	transform = new Transform();
    drawable = new Drawable();

	transform->position = XMFLOAT3(0,0,0); 
	transform->scale = XMFLOAT3( 150, 150, 150 );

    drawable->getEffectVariables("skyShader", "Render");
    drawable->createBuffer("Sphere");
	drawable->addTexture("skybox", "texCube");

	components.push_back(transform);
    components.push_back(drawable);

	GameObject::InitComponents();

	D3D11_RASTERIZER_DESC rasterDesc;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_FRONT;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	resourceMgr->pD3DDevice->CreateRasterizerState(&rasterDesc, &frontCullRasterState);
}

void Skybox::Draw()
{
	drawable->setEffectVariables();
	drawable->setEffectTextures();

	resourceMgr->md3dImmediateContext->RSSetState(frontCullRasterState);

    drawable->draw();

	resourceMgr->md3dImmediateContext->RSSetState(NULL);
}

Skybox::~Skybox(void)
{
}
