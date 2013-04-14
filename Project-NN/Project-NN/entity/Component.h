#pragma once

class GameObject;

class Component {
public:
	/**
	 * Use this method to make sure the GameObject has the right
	 * components. This method will be called after all components have been constructed.
	 *
	 * If a component has no component dependencies and does not need any special initialization,
	 * it doesn't need to override this.
	 */
	virtual void Init(GameObject* go);

	/**
	 * Called every frame.
	 *
	 * If a component doesn't need to update (ie. it only holds data for other components), it
	 * doesn't need to override this.
	 */
	virtual void Update(float dt);

	/**
	 * Called when the game object this component is attached to collides with another game object.
	 *
	 * If a component doesn't care about collisions, it wouldn't need to override this.
	 */
	virtual void HandleCollision(GameObject* other);
};
