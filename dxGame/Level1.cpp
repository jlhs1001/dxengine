#include "GameController.h"
#include "Level1.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Shape.h"
#include "Transform.h"

float x = 0.0f;
float xVel = 0.0f;

GameObject* player = new GameObject("player", "character");

void Level1::Load()
{
	y = 0.0f;
	ySpeed = 0.0f;

	sprites = new SpriteSheet(L"Image.png", graphics);

	
}

void Level1::Unload()
{

}

void Level1::Update()
{
	/* Here's what I want input to look like:
	Input::OnKeyDown("w", []() => {
		ySpeed -= 20.0f;
		Audio::PlaySound("soundFile.mp3");
	});

	*/
	//ySpeed += 1.0f;
	//y += ySpeed;
	//if (y > 600)
	//{
	//	y = 600;	
	//	ySpeed = -30.0f;
	//}
	xVel += 1.0f;
	x += 1.0f;
}

void Level1::Render()
{

	//Shape* shape = new Shape();	

	graphics->ClearScreen(0.0f, 0.0f, 0.5f);

	graphics->DrawCircle(x, 400.0f, 50.0f, Graphics::rgb(1.0f, 1.0f, 1.0f));
	graphics->DrawRect(10.0f, 8.0f, 50, 60, Graphics::rgb(1.0f, 0.5f, 0.25f));

	graphics->Text(L"Hi!", 80, 80);

	graphics->DrawLine(50, 50, 80, 80, Graphics::rgb(1.0f, 1.0f, 1.0f));
	
	sprites->Render();
}