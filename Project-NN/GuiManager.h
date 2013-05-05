#pragma once

class GuiManager {
public:
	Init();
	Cleanup();
	Update(float dt);
	Render();
};

extern GuiManager* guiMgr;