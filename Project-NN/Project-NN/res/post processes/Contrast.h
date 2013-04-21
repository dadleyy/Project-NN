#pragma once
#include "..\..\entity\Drawable.h"

class Contrast : public Drawable
{
public:
	Contrast(void);
	~Contrast(void);

	float threshold;
	float brightness;
	virtual void setEffectVariables();
};

