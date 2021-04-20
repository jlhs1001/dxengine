#pragma once
#include <string>
#include <vector>
#include "Transform.h"

class GameObject
{
public:
	// GameObject name must be unique
	std::string name;

	// GameObject tag can be on multiple components
	std::string tag;

	Transform* transform;

	// layer in which to be rendered to
	int layer;

	std::vector<GameObject> children;

	/*Component states*/
	bool isCollided;
	bool isKinematic;

	GameObject(std::string name, std::string tag);

	void render();

	void onLoad(void (*func)());
	void onRender(void (*func)());
	void onDestroy(void (*func)());

	void onCollisionEnter(void (*func)());
	void onCollisionExit(void (*func)());
};
