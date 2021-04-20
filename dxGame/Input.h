#pragma once
#include <Windows.h>
#include <string>

class Input
{
	UINT message;
public:
	std::string currentKey;

	
public:
	void Init(UINT* uMsg);

	UINT GetKeyDown();

	void OnKeyDown(void (*func)());
	void OnKeyUp(void (*func)());
	void OnMouseMove(void (*func)());
	void OnMouseDown(void (*func)());
};