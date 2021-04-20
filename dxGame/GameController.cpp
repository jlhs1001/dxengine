#include "GameController.h"

Scene* GameController::currentScene;
bool GameController::Loading;

void GameController::Init()
{
	Loading = true;
}

void GameController::LoadInitialScene(Scene* scene)
{
	Loading = true;
	currentScene = scene;
	currentScene->Load();
	Loading = false;
}

void GameController::SwitchScene(Scene* scene)
{
	Loading = true;
	currentScene->Unload();
	scene->Load();
	delete currentScene;
	currentScene = scene;
	Loading = false;
}

void GameController::Render()
{
	currentScene->Render();
}

void GameController::Update()
{
	currentScene->Update();
}