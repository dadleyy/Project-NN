#pragma once
#include "..\Drawable.h"
#include <vector>

using std::vector;

class DrawableInstancedModel : public Drawable
{
public:
	DrawableInstancedModel(void);
	~DrawableInstancedModel(void);
	
	ID3D11Buffer* instanceBuffer;
	vector<XMFLOAT4X4>* instances;

	virtual void createBuffer(char* mesh);
	virtual void setEffectVariables();
	virtual void setEffectTextures();
	void drawInstanced(int numInstances);
};

