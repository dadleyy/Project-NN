#pragma once

namespace Awesomium {
	class WebCore;
}

class GuiManager {
public:
	void Init();
	void Cleanup();
	void Update(float dt);
	void Render();
private:
	Awesomium::WebCore* webCore;
};

extern GuiManager* guiMgr;