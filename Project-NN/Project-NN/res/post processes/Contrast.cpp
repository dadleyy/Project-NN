#include "Contrast.h"


Contrast::Contrast(void)
{
}


Contrast::~Contrast(void)
{
}


void Contrast::setEffectVariables()
{
	shader->GetVariableByName("threshold")->AsScalar()->SetFloat(threshold);
	shader->GetVariableByName("brightness")->AsScalar()->SetFloat(brightness);
}