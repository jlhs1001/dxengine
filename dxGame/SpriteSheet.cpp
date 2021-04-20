#include "SpriteSheet.h"
#include <stdexcept>

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx)
{
	// Just setting the graphics object
	this->gfx = gfx;

	// We wanna know what this is so we set it to something we know.
	bmp = NULL;

	// This one's for error checking
	HRESULT hr;
	
	// Make us a WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL, // Not part of an aggregate
		CLSCTX_INPROC_SERVER, // DLL runs in the same process
		IID_IWICImagingFactory, // Reference to interface that
		(LPVOID*)&wicFactory); // pointer containing our factory

	// A dang bitmap decoder
	IWICBitmapDecoder* wicDecoder = NULL;

	hr = wicFactory->CreateDecoderFromFilename(
		filename, // Yes, it is actually the file name.
		NULL, // No preferred vender
		GENERIC_READ, // We are reading a file, not writing.
		WICDecodeMetadataCacheOnLoad, // Doesn't do much as we're destroying it after but it's required.
		&wicDecoder);

	//if (hr != S_OK) { return; }

	// Read a frame from the image:
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// Create a converter bc we want a dx bitmap not wic
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Setup the converter
	hr = wicConverter->Initialize(
		// The first two are really the only important ones to us.
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA, // God the pixel format
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	ID2D1Bitmap* bmp;
	hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, // our converter
		NULL,
		&bmp
	);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicFactory->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}

void SpriteSheet::Render()
{
	// TODO: it's almost 12:00 AM and I'm tired and want to get at least somewhere.
	// 	   Tommorow liam's tommorow job.
	//gfx->GetRenderTarget()->DrawBitmap(
	//	bmp,
	//	D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height), // coords (using a rect)
	//	1.0f, // Opacity
	//	// We're gonna do this instead of linear interpolation because with this we can see each pixel clearly.
	//	D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
	//	D2D1::RectF(0.0f, 0.0f,
	//		bmp->GetSize().width, bmp->GetSize().height)
	//);
}