#include "Engine/Common/Common.h"
#include "Engine/Graphics/Window.h"

int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	neko::Window wnd;
	
	if(wnd.Init(hInstance, L"D2D", 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT))
	{
		while(!wnd.ShouldQuit())
		{
			if(wnd.MessagePump())
			{
				wnd.WaitMessage(1);
			}
		}
	}

	wnd.Close();

	return (int)0;
}