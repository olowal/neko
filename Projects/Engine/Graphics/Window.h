/****************************************************************************
//	Filename: Window.h
//	Description: Creates a window
*****************************************************************************/

#pragma once

#include "Engine/Common/Common.h"
#include "GFXDevice.h"

namespace neko
{

class GFXDevice;
class Window
{
public:
	Window();
	~Window();

	bool Init(HINSTANCE hInstance, const wchar_t* pzTitle, int iX, int iY, int iWidth, int iHeight);
	void Close();

	bool MessagePump();
	void WaitMessage(int iTimeout);
	void Refresh();

	GFXDevice& GetDevice() { return m_device; }
	HINSTANCE GetHInstance() const { return m_hInstance; }

	bool ShouldQuit() const { return m_bQuit; }
	bool IsActive() const { return m_bActive; }

	void SetTitle(const wchar_t* pzTitle);
	bool GetSize(int& uWidth, int& uHeight);

	static void ConsoleOpen();
	static void ConsoleClose();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

	GFXDevice m_device;

	HWND m_hWnd;
	HINSTANCE m_hInstance;

	uint32 m_uWidth;
	uint32 m_uHeight;

	bool m_bQuit;
	bool m_bActive;
};

}	//	namespace neko