/****************************************************************************
//	Filename: Window.h
//	Description: Creates a window
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

typedef struct lua_State lua_State;

namespace neko
{
namespace Window
{
	SDL_Window* Create(const char* szTitle, int iX, int iY, int iWidth, int iHeight);

	static void ConsoleOpen();
	static void ConsoleClose();

	void Register(lua_State* pL);

}	//	namespace Window
}	//	namespace neko
