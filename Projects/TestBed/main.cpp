#include "Engine/Common/Common.h"
#include "D2DApp.h"
/*
int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
*/
int main()
{
	D2DApp app;
	if(!app.Init("TestBed", 800, 600))
	{
		return (int)-1;
	}

	app.Run();
	app.Shut();

	return (int)0;
}