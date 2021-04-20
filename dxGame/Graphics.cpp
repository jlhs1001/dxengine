#include "Graphics.h"

Graphics::Graphics()
{
	// We want factory and renderTarget to start as an 
	// arbitrary known value, so nullptr is an obvious choice.
	factory = nullptr;
	renderTarget = nullptr;
	brush = nullptr;
}

Graphics::~Graphics()
{
	// We've gotta manage some memory!
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pTextFormat) pTextFormat->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	// This doesn't return a factory, instead a result, so we have
	// to pass a pointer to our factory to create it.
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	// problem creating factory, so shut down.
	if (res != S_OK) return false;

	// create a rect and set it to window client area
	RECT windowRect;
	GetClientRect(windowHandle, &windowRect);

	// create window handle render target and return an HRESULT
	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle, D2D1::SizeU(windowRect.right, windowRect.bottom)),
		&renderTarget);

	// problems creating render target, so shut down.
	if (res != S_OK) return false;

	// creating a black solid color brush
	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;

	// Create the write factory
	res = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	);
	if (res != S_OK) return false;

	res = pDWriteFactory->CreateTextFormat(
		L"Arial", // Font family
		NULL, // font collection
		DWRITE_FONT_WEIGHT_REGULAR, // default font weight
		DWRITE_FONT_STYLE_NORMAL, // default font style
		DWRITE_FONT_STRETCH_NORMAL, // default font stretch
		11.0f, // font size
		L"en-us", // locale name
		&pTextFormat // reference to our text format
	);

	// all is well!
	return true;
}

// TODO: replace with rgb function call which returns D2D1::ColorF
void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, D2D1::ColorF color)
{
	/*
	A slow way to draw a circle, but a working way to draw a circle.
	*/

	brush->SetColor(color);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawRect(float x, float y, float width, float height, D2D1::ColorF color)
{
	brush->SetColor(color);
	renderTarget->DrawRectangle(
		D2D1::RectF(x, y, width, height),
		brush,
		1.0f
	);
}

void Graphics::Text(const WCHAR* text, float x, float y)
{
	HRESULT hr;

	//static const WCHAR text = L"Hello, World!";
	//renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->DrawTextW(
		text,
		sizeof(text),
		pTextFormat,
		D2D1::RectF(x, y, renderTarget->GetSize().width, renderTarget->GetSize().height),
		brush
	);
}

void Graphics::DrawLine(float fromX, float fromY, float toX, float toY, D2D1::ColorF color)
{
	brush->SetColor(color);
	renderTarget->DrawLine(
		D2D1::Point2F(fromX, fromY),
		D2D1::Point2F(toX, toY),
		brush
	);
}

//void Graphics::SetBrush(D2D1::ColorF color, const char* brushStyle)
//{
//	if (brush) brush->Release();
//	if (brushStyle == "solid")
//	{
//		renderTarget->CreateSolidColorBrush(color, &brush);
//	}
//	else if (brushStyle == "gradient")
//	{
//
//	}
//}