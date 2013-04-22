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

	void Update(float dt);
	void HandleCollision(GameObject* other);

	Transform* transform;
	Collider* collider;

protected:
	std::vector<Component*> components;

	void InitComponents();
};
