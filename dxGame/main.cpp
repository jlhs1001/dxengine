#include <Windows.h>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"

Graphics* graphics;




























// call engine entry point
// TODO: Change to Game class where you call Setup() method
void mMain()
{
	GameController::LoadInitialScene(new Level1());
}










































LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,L"MainWindow", L"dxGame", WS_OVERLAPPEDWINDOW, 100, 100, 
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, 0);
	
	if (!windowHandle) return -1;

	// Right before the window is shown, initialize our graphics object.
	graphics = new Graphics();

	if (!graphics->Init(windowHandle))
	{
		// manage some memory, then shut down.
		delete graphics;
		return -1;
	}

	Scene::Init(graphics);

	ShowWindow(windowHandle, nCmdShow);

	// call engine entry point
	// TODO: Change to Game class where you call Setup() method
	mMain();

	MSG message;

	message.message = WM_NULL;

	while (message.message != WM_QUIT)
	{
		// PeekMessage won't freeze the program!
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			// Update
			GameController::Update();
			// Render
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	delete graphics;
	// This will quit the application.
	return 0;
}