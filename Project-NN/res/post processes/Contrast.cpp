#include "Contrast.h"


Contrast::Contrast(void)
{
}


Contrast::~Contrast(void)
{
}


void Contrast::setEffectVariables()
{
	currentShader->GetVariableByName("threshold")->AsScalar()->SetFloat(threshold);
	currentShader->GetVariableByName("brightness")->AsScalar()->SetFloat(brightness);
}