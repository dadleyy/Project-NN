#pragma once

class GuiManager {
public:
	void Init();
	void Cleanup();
	void Update(float dt);
	void Render();
};

extern GuiManager* guiMgr;