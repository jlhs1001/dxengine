#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include "GameObject.h"

class Scene
{
protected:
	static Graphics* graphics;

public:
	static void Init(Graphics* gfx)
	{
		graphics = gfx;
	}

	//virtual bool grid;
	std::vector<GameObject> sceneObjects;

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};