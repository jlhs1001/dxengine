#pragma once
#include "Graphics.h"
#include "Transform.h"

class DXRectangle
{
	float x, y;
	float width, height;
	DXRectangle(Transform* transform)
	{
		this->x = transform->x;
		this->y = transform->y;
		this->width = transform->width;
		this->height = transform->height;
	}

	void render(Graphics* graphics, D2D1::ColorF color)
	{
		graphics->DrawRect(this->x, this->y, this->width, this->height, color);
	}
};