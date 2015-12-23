//	Window.cpp

#include "Window.h"
#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"

#include "io.h"
#include "fcntl.h"

SDL_Window* neko::Window::Create(const char* szTitle, int iX, int iY, int iWidth, int iHeight)
{
	SDL_Window* pWnd = SDL_CreateWindow(szTitle, iX, iY, iWidth, iHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	ASSERT(pWnd != NULL);
	return pWnd;
}

void neko::Window::ConsoleOpen()
{
	if(AllocConsole()==TRUE)
	{
		int hCrt;
		FILE *pFConFile;

		hCrt=_open_osfhandle((intptr_t)::GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);
		pFConFile=_fdopen(hCrt,"w");
		*stdout=*pFConFile;
		hCrt=_open_osfhandle((intptr_t)::GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);
		pFConFile=_fdopen(hCrt,"w");
		*stderr=*pFConFile;
		hCrt=_open_osfhandle((intptr_t)::GetStdHandle(STD_INPUT_HANDLE),_O_TEXT);
		pFConFile=_fdopen(hCrt,"r");
		*stdin=*pFConFile;
		setvbuf(stdout,NULL,_IONBF,0);
		setvbuf(stdin,NULL,_IONBF,0);
	};
}

void neko::Window::ConsoleClose()
{
	FreeConsole();
}

void neko::Window::Register(lua_State * pL)
{
	using namespace luabridge;

	getGlobalNamespace(pL)
		.beginClass<SDL_Window>("SDL_Window")
		.endClass();

	getGlobalNamespace(pL)
		.beginNamespace("Window")
		.addFunction("Create", neko::Window::Create)
		.addFunction("SetTitle", SDL_SetWindowTitle)
		.addFunction("GetTitle", SDL_GetWindowTitle)
		.endNamespace();
}
