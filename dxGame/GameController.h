#pragma once
#include "Scene.h"

class GameController
{
	GameController() { }
	static Scene* currentScene;
public:
	// When loading is true, rendering stops.
	static bool Loading;

	static void Init();

	static void LoadInitialScene(Scene* scene);
	static void SwitchScene(Scene* scene);

	static void Render();
	static void Update();
};