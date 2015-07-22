//	D2DApp.cpp

#include "D2DApp.h"
#include "Engine/Math/Utils.h"

using namespace neko;

D2DApp::D2DApp()
{
	m_fFPS = 0.0f;
	m_iMs = 0;
	m_uFrameIndex = 0;
}
D2DApp::~D2DApp(){}

bool D2DApp::Init(HINSTANCE hInstance)
{
	if(!Application::Init())
	{
		return false;
	}

	if(!m_wnd.Init(hInstance,
		L"D2DApp",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT))
	{
		return false;
	}

	return true;
}

void D2DApp::Run()
{
	dword dwFrameInterval = 1000 / 50;
	dword dwLastFrame = GetTick();
	float fAvgTime = 0.0f;
	while(!m_wnd.ShouldQuit())
	{
		if(m_wnd.MessagePump())
		{
			dword dwNow = GetTick();
			dword dwDiff = GetTickDiff(dwLastFrame, dwNow);
			int iWait = (int)neko::math::Clamp((int)(dwFrameInterval - dwDiff - 2), 0, 100);
			if(iWait > 1)
			{
				m_wnd.WaitMessage(iWait);
			}

			dwNow = GetTick();
			dwDiff = GetTickDiff(dwLastFrame, dwNow);

			if(dwDiff >= dwFrameInterval)
			{
				m_fFPS = 1000.0f / neko::math::Max(((float)dwDiff), 1.0f);
				m_iMs = (int)dwDiff;
				dwLastFrame = dwNow;
				dword dwCalcStart = GetTick();
				DoFrame();
				dword dwCalcEnd = GetTick();
				fAvgTime = fAvgTime * 0.99f + ((float)GetTickDiff(dwCalcStart, dwCalcEnd)) * 0.01f;
			}
		}
	}
}

void D2DApp::DoFrame()
{
	m_uFrameIndex++;
	//m_wnd.Refresh();	//	Will force the window to redraw its contents
	
	float fX = 0.0f;
	float fY = 0.0f;

	float fSpeed = 1.0f;

	if(::GetAsyncKeyState('W')) { fY = fSpeed; }
	if(::GetAsyncKeyState('S')) { fY = -fSpeed; }
	if(::GetAsyncKeyState('A')) { fX = -fSpeed; }
	if(::GetAsyncKeyState('D')) { fX = fSpeed; }

	m_camera.Translate(Vec2(fX, fY));
	
	neko::GFXDevice& device = m_wnd.GetDevice();

	device.SetModelMatrix(m_camera.GetModelMatrix());

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(m_wnd.GetWindowHandle(), &mousePos);

	device.BeginDraw();
	device.Clear(Color::SeaGreen);
	device.DrawRect(Vec2((float)mousePos.x, (float)mousePos.y), Vec2(100.0f, 150.0f), Color::Beige);
	device.EndDraw();
}

void D2DApp::OnShut()
{
	m_wnd.Close();
}