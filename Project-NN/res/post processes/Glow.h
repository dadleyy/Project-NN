#pragma once
#include "..\..\entity\Drawable.h"

class Glow : public Drawable
{
public:
	Glow(void);
	~Glow(void);

	float screenScaleW;
	float screenScaleH;
	virtual void setEffectVariables();
	virtual void draw(char* blurTex, char* pass1, char* pass2, char* original); 
};

