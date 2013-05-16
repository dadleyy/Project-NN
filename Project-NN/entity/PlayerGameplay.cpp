#include "PlayerGameplay.h"
#include "GameObject.h"
#include "Health.h"

bool PlayerGameplay::Init(GameObject* go) {
	health = go->GetComponent<Health>();
	return health != nullptr;
}

void PlayerGameplay::Update(float dt) {
	if(!health->IsAlive()) {
		DebugBreak();
	}
}