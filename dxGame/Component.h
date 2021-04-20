#pragma once
#include <string>
#include <vector>

class Component
{
public:
	std::string name;
	std::string tag;

	//Transform* transform;

	// layer in which to be rendered to
	int layer;

	std::vector<Component> children;

	/*Component states*/
	bool isCollided;
	bool isKinematic;

	Component();

	void render();
};