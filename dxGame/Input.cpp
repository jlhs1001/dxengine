#include "Input.h"

void Input::Init(UINT *uMsg)
{
	message = *uMsg;
}

//void Input::OnKeyDown(void (*func)())
//{
//	if (message == WM_KEYDOWN)
//	{
//		func();
//	}
//}
//
//void Input::OnKeyUp(void (*func)())
//{
//	if (message == WM_KEYUP)
//	{
//		func();
//	}
//}
//
//void Input::OnMouseMove(void (*func)())
//{
//	if (message == WM_MOUSEMOVE)
//	{
//		func();
//	}
//}

UINT Input::GetKeyDown()
{
	return message;
}
