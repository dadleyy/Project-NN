#pragma once
#include "..\..\entity\Drawable.h"

class Contrast : public Drawable
{
public:
	Contrast(void);
	~Contrast(void);

	float threshold;
	virtual void setEffectVariables();
	virtual void getEffectVariables(char* fxFilename, char* fxTechniqueName);
};

