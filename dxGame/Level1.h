#pragma once

#include "Scene.h"
#include "Shape.h"

class Level1 : public Scene
{
	float y;
	float ySpeed;

	

	SpriteSheet* sprites;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};