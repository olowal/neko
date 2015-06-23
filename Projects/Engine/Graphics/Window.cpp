//	Window.cpp

#include "Window.h"

#include "io.h"
#include "fcntl.h"

namespace neko
{

static const LPCWSTR g_pzWindowClassName = L"Direct2DWindow";

Window::Window()
{
	m_hInstance = NULL;
	m_hWnd = NULL;
	m_uWidth = 0;
	m_uHeight = 0;
	m_bQuit = false;
	m_bActive = false;
}

Window::~Window()
{
	Close();
}

bool Window::Init(HINSTANCE hInstance, const wchar_t* pzTitle, int iX, int iY, int iWidth, int iHeight)
{
	if(!m_device.Init())
	{
		return false;
	}

	m_hInstance = hInstance;

	WNDCLASSEXW wnd = { sizeof(WNDCLASSEXW) };
	wnd.style			= CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc		= Window::WndProc;
	wnd.cbClsExtra		= 0;
	wnd.cbWndExtra		= sizeof(LONG_PTR);
	wnd.hInstance		= hInstance;
	wnd.hbrBackground	= NULL;
	wnd.lpszMenuName	= NULL;
	wnd.hCursor			= LoadCursor(NULL, IDI_APPLICATION);
	wnd.lpszClassName	= g_pzWindowClassName;

	::RegisterClassExW(&wnd);

	float fDpiX = 0.0f;
	float fDpiY = 0.0f;

	m_device.GetDesktopDpi(fDpiX, fDpiY);	//	Do I want to scale window to dpi?

	m_hWnd = ::CreateWindowExW(0, wnd.lpszClassName, pzTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_TILED |
		WS_SIZEBOX | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
		WS_VISIBLE | WS_SYSMENU, 
		iX, iY, 
		iWidth, 
		iHeight,
		0, 0, 
		hInstance, 
		this);

	if(m_hWnd == NULL)
	{
		return false;
	}

	m_device.CreateDeviceResources(m_hWnd);
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::SetClassLongPtrW(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	return true;
}

void Window::Close()
{
	if(m_hWnd)
	{
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	::UnregisterClassW(g_pzWindowClassName, m_hInstance);
}

void Window::WaitMessage(int iTimeout)
{
	if(m_hWnd == NULL)
	{
		return;
	}

	HANDLE ahHnd = INVALID_HANDLE_VALUE;
	::MsgWaitForMultipleObjects(0, &ahHnd, FALSE, iTimeout, QS_ALLINPUT);
}

void Window::Refresh()
{
	::InvalidateRect(m_hWnd, NULL, FALSE);
}

bool Window::MessagePump()
{
	if(m_hWnd == NULL)
	{
		return false;
	}

	MSG msg;
	bool bDone = false;
	
	while(!bDone && !m_bQuit)
	{
		if(::PeekMessageW(&msg, m_hWnd, 0, 0, PM_REMOVE))
		{
			if(::GetMessageW(&msg, m_hWnd, 0, 0))
			{
				::TranslateMessage(&msg);
				::DispatchMessageW(&msg);
			}
			else
			{
				bDone = true;
				m_bQuit = true;
			}
		}
		else
		{
			bDone = true;
		}
	}

	return !m_bQuit;
}

void Window::SetTitle(const wchar_t* pzTitle)
{
	::SetWindowTextW(m_hWnd, pzTitle);
}

bool Window::GetSize(int& iWidth, int& iHeight)
{
	if(m_hWnd == NULL)
	{
		iWidth = 0;
		iHeight = 0;
		return false;
	}

	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	iWidth = static_cast<int>(rc.right - rc.left);
	iHeight = static_cast<int>(rc.bottom - rc.top);
	return true;
}

void Window::ConsoleOpen()
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

void Window::ConsoleClose()
{
	FreeConsole();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lparam;
		Window* pWnd = (Window*)pcs->lpCreateParams;
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
	}
	else
	{
		Window* pWnd = reinterpret_cast<Window*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(hWnd, GWLP_USERDATA)));

		if(pWnd)
		{
			switch(msg)
			{
			case WM_QUIT:
				pWnd->m_bQuit = true;
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				pWnd->m_bQuit = true;
				break;
			case WM_SYSCOMMAND:
				{
					if(wparam == SC_CLOSE)
					{
						pWnd->m_bQuit = true;
					}
				}
				break;
			case WM_ACTIVATE:
				pWnd->m_bActive = (wparam != 0);
				break;
			case WM_DISPLAYCHANGE:
				pWnd->Refresh();
				break;
			case WM_SIZE:
				{
					uint32 uW = static_cast<uint32>(LOWORD(lparam));
					uint32 uH = static_cast<uint32>(HIWORD(lparam));
					pWnd->GetDevice().OnResize(uW, uH);
				}
				break;
			case WM_PAINT:
				pWnd->GetDevice().OnRender();
				::ValidateRect(hWnd, NULL);
				break;
			}
		}
	}

	return ::DefWindowProcW(hWnd, msg, wparam, lparam);
}

}	//	namespace neko