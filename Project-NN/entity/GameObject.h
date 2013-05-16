#pragma once

#include <vector>
#include <Windows.h>
#include <xnamath.h>

class Component;
class Drawable;
class Transform;
class Collider;


class GameObject {
public:
	template <class T>
	T* GetComponent() {
		for(auto it = components.begin(); it != components.end(); ++it) {
			auto result = dynamic_cast<T*>(*it);
			if(result != nullptr)
				return result;
		}
		return nullptr;
	}

	GameObject();
	virtual ~GameObject();
	virtual GameObject* Clone();
	void Update(float dt);
	void HandleCollision(GameObject* other);

	//If a game object isn't drawn, it doesn't need to override this.
	virtual void Draw();

	Transform* transform;
	Collider* collider;
	bool active;
	bool glow;
	float damage;

protected:
	std::vector<Component*> components;

	void InitComponents();
};
