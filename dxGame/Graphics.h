#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>

class Graphics
{
	/*
	The Graphics class is just a wrapper for the render target
	and normal drawing procedures.
	*/
	ID2D1Factory* factory;

	/*
	Initializing our text format component and our
	IDWriteFactory so we can render text to the screen.
	*/
	IDWriteTextFormat* pTextFormat;
	IDWriteFactory* pDWriteFactory;

	/* We will set up our render target to be our client drawing area,
	but the render target is the location in memory (probably on graphics card)
	where we are drawing stuff, basically where we are rendering to. */
	ID2D1HwndRenderTarget* renderTarget;

	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }

	// In direct2D, you BeginDraw, draw whatever bitmaps, animations, 
	// circles, rectangles, then you EndDraw.
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, D2D1::ColorF color);

	//void DrawRect(float x, float y, float width, float height, D2D1::ColorF color);
	void DrawRect(float x, float y, float width, float height, D2D1::ColorF color);
	//void DrawRect(float x, float y, float width, float height, , D2D1::ColorF color);

	void DrawLine(float fromX, float fromY, float toX, float toY, D2D1::ColorF color);

	void Text(const WCHAR* text, float x, float y);

	void SetBrush();

	// Helper functions
	static D2D1::ColorF rgb(float r, float g, float b)
	{
		return D2D1::ColorF(r, g, b, 1.0f);
	}

	static D2D1::ColorF rgba(float r, float g, float b, float a)
	{
		return D2D1::ColorF(r, g, b, a);
	}
};