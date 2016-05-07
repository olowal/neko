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
#include "Engine/Core/LuaMgr.h"

class D2DApp : public neko::Application
{
	typedef neko::Application Inherited;
public:
	D2DApp();
	virtual ~D2DApp();

	bool Init();

protected:
	//virtual void DoFrame();
	virtual bool OnInit();
	virtual void OnShut();
private:
	neko::TextureMgr m_texMgr;
	neko::Camera m_camera;
};