/****************************************************************************
//	Filename: D2DApp.h
//	Description: Base application for a Direct2D application.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Graphics/Window.h"
#include "Engine/Framework/Application.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Graphics/TextureMgr.h"

class D2DApp : public neko::Application
{
public:
	D2DApp();
	virtual ~D2DApp();

	bool Init(HINSTANCE hInstance);
	virtual void Run();

protected:
	void DoFrame();
	virtual bool OnInit(){return true;}
	virtual void OnShut();
private:
	neko::TextureMgr m_texMgr;
	neko::Camera m_camera;
	neko::Window m_wnd;
	float m_fFPS;
	int m_iMs;
	uint32 m_uFrameIndex;
};