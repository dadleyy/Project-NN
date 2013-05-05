#include "GuiManager.h"

#include "Awesomium/WebCore.h"
#include "Awesomium/BitmapSurface.h"
#include "Awesomium/STLHelpers.h"

using namespace Awesomium;

WebView* webView = nullptr;

void GuiManager::Init() {
	WebConfig config;
	config.log_path = WSLit(".");
	config.log_level = kLogLevel_Normal;
	webCore = WebCore::Initialize(config);
	auto webView = webCore->CreateWebView(640, 480);
	webView->LoadURL(WebURL(WSLit("http://www.youtube.com")));
}

void GuiManager::Cleanup() {
	webCore->Shutdown();
}

void GuiManager::Update(float dt) {
	webCore->Update();
}

void GuiManager::Render() {
}