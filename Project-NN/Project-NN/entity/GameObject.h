#pragma once

#include <vector>

class Component;


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

protected:
	std::vector<Component*> components;

	void InitComponents();
};
