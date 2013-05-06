#include "Glow.h"
#include "../../ResourceManager.h"

extern int screenWidth;
extern int screenHeight;
extern ResourceManager* resourceMgr;

Glow::Glow(void)
{
	screenScaleW = .5;
	screenScaleH = .5;
}


Glow::~Glow(void)
{
}


void Glow::setEffectVariables()
{
	float arr[2] = {(int)(screenWidth*screenScaleW),(int)(screenHeight*screenScaleH)};
	currentShader->GetVariableByName("texDimensions")->SetRawValue(arr, 0, 8);
}

void Glow::draw(char* blurTex, char* pass1, char* pass2, char* original)
{
	//This currently does a more squared blur rather than a perfect radial blur, because the horizontal blurred
	//texture is not what gets blurred vertically
	setShader("glowEffect", "Horz");
	currentShader->GetVariableByName("blurredTex1")->AsShaderResource()->SetResource(resourceMgr->textures[blurTex]);
	resourceMgr->md3dImmediateContext->OMSetRenderTargets(1, &resourceMgr->renderTargets[pass1], NULL);
	resourceMgr->md3dImmediateContext->ClearRenderTargetView(resourceMgr->renderTargets[pass1], reinterpret_cast<const float*>(&Colors::Black));
	Drawable::draw();

	setShader("glowEffect", "Add");
	currentShader->GetVariableByName("blurredTex1")->AsShaderResource()->SetResource(resourceMgr->textures[pass1]);
	currentShader->GetVariableByName("blurredTex2")->AsShaderResource()->SetResource(resourceMgr->textures[original]);
	resourceMgr->md3dImmediateContext->OMSetRenderTargets(1, &resourceMgr->renderTargets[pass2], NULL);
	resourceMgr->md3dImmediateContext->ClearRenderTargetView(resourceMgr->renderTargets[pass2], reinterpret_cast<const float*>(&Colors::Black));
	Drawable::draw();

	setShader("glowEffect", "Vert");
	currentShader->GetVariableByName("blurredTex1")->AsShaderResource()->SetResource(resourceMgr->textures[blurTex]);
	resourceMgr->md3dImmediateContext->OMSetRenderTargets(1, &resourceMgr->renderTargets[pass1], NULL);
	resourceMgr->md3dImmediateContext->ClearRenderTargetView(resourceMgr->renderTargets[pass1], reinterpret_cast<const float*>(&Colors::Black));
	Drawable::draw();

	setShader("glowEffect", "Add");
	currentShader->GetVariableByName("blurredTex1")->AsShaderResource()->SetResource(resourceMgr->textures[pass1]);
	currentShader->GetVariableByName("blurredTex2")->AsShaderResource()->SetResource(resourceMgr->textures[pass2]);
	resourceMgr->md3dImmediateContext->OMSetRenderTargets(1, &resourceMgr->renderTargets[original], NULL);
	resourceMgr->md3dImmediateContext->ClearRenderTargetView(resourceMgr->renderTargets[original], reinterpret_cast<const float*>(&Colors::Black));
	Drawable::draw();
}