//	Application.cpp

#include "Application.h"
#include "Engine/Graphics/GFXDevice.h"
#include "Engine/Math/Utils.h"
#include "Engine/Framework/ComponentManager.h"
#include "Engine/Framework/GameObject.h"
#include "Engine/Graphics/Window.h"
#include "Engine/Core/StringUtil.h"

using namespace luabridge;

namespace neko
{

Application::Application()
{
	m_bShouldQuit = false;
	m_uFrameIndex = 0;
	m_fFps = 0.0f;
	m_iMs = 0;
}
Application::~Application(){}

bool Application::Init(const char* pzTitle, int iW, int iH, int iX, int iY)
{
		//	Set the application path to the executable path
		// In the case of development, we set the base to the folder Data

#ifdef FINAL_RELEASE
	{
		char* sPath = SDL_GetBasePath();
		
		if(sPath != NULL)
		{
			int iP = (int)SDL_strlen(sPath);
			while(iP > 0
				&& (sPath[iP - 1] != '/')
				&& (sPath[iP] != '\\'))
			{
				iP--;
			}
			sPath[iP] = '\0';
			_chdir(sPath);
			SDL_free(sPath);
		}
	}
#else
	_chdir("../../Data/");
#endif

	if(!OnInit())
	{
		return false;
	}

	lua_State* pL = m_lua.L();

	this->Register(pL);
	m_inputManager.Register(pL);
	Window::Register(pL);
	GameObject::Register(pL);
	GFXDevice::Register(pL);
	neko::math::Register(pL);

	m_componentManager.Init(pL);

	m_lua.LoadFiles("Scripts/");

	m_lua.ExecuteFile("default.lua");
	LuaRef defaultGame = getGlobal(pL, "defaultGame");

	if(defaultGame.isString())
	{
		const size_t uMaxLenght = 256;
		const char* sFolderName = "Games/";
		const char* sGameName = defaultGame.cast<const char*>();
		const char* sFileExtension = "/";

		char sFullPath[uMaxLenght];
		sFullPath[0] = '\0';

		uint32 uLength = 0;

		uLength = str::Copy(sFullPath, sFolderName);
		uLength = str::Concatenate(sFullPath, sGameName, uLength);
		uLength = str::Concatenate(sFullPath, sFileExtension, uLength);

		m_lua.LoadFiles(sFullPath);

		LuaRef game = getGlobal(pL,"Game");
		LuaRef main = game["Main"];
		if(main.isFunction())
		{
			main();

			LuaRef device = game["device"];
			if(!device.isNil())
			{
				m_pDevice = device.cast<GFXDevice*>();
				ASSERT(m_pDevice != NULL);
			}

			game["app"] = this;
		}

		LuaRef start = game["Start"];
		if(start.isFunction())
		{
			start();
		}
	}
	

	return true;
}

void Application::Run()
{
	const uint32 uFrameInterval = 1000 / 50;
	uint32 uLastFrame = SDL_GetTicks();
	float fAvgTime = 0.0f;
	while(!m_bShouldQuit)
	{
		if(MessagePump())
		{
			uint32 uNow = SDL_GetTicks();
			uint32 uDiff = GetTickDiff(uLastFrame, uNow);
			const float fDt = math::Min((static_cast<float>(uDiff) / 1000.0f), 1.0f);
			int iWait = math::Clamp((int)(uFrameInterval - uDiff - 2), 0, 100);
			if(iWait > 1)
			{
				SDL_WaitEventTimeout(NULL, iWait);
			}

			uNow = SDL_GetTicks();
			uDiff = GetTickDiff(uLastFrame, uNow);

			if(uDiff >= uFrameInterval)
			{
				m_fFps = 1000.0f / math::Max((float)uDiff, 1.0f);
				m_iMs = (int)uDiff;
				uLastFrame = uNow;
				const uint32 uCalcStart = SDL_GetTicks();
				++m_uFrameIndex;

				{
					lua_State* pL = m_lua.L();
					luabridge::LuaRef time = getGlobal(pL, "Time");
					time["deltaTime"] = fDt;
				}

				m_pDevice->BeginDraw();
				DoFrame(fDt);
				m_pDevice->EndDraw();
				const uint32 uCalcEnd = SDL_GetTicks();
				fAvgTime = fAvgTime * 0.99f + (float)(GetTickDiff(uCalcStart, uCalcEnd)) * 0.01f;
			}
		}
	}
}

bool Application::MessagePump()
{
	SDL_Event evt;
	while(SDL_PollEvent(&evt))
	{
		if(evt.type == SDL_QUIT)
		{
			m_bShouldQuit = true;
		}
	}

	return !m_bShouldQuit;
}

void Application::Shut()
{
	OnShut();
}

uint32 Application::GetTickDiff(uint32 uStart, uint32 uEnd) const
{
	if(uEnd > uStart)
	{
		return uEnd - uStart;
	}

	uint64 iD = ((uint64)2<<32) - uStart;
	iD += uEnd;
	return static_cast<uint32>(iD);
}

void Application::DoFrame(const float fDt)
{
	m_inputManager.Update();
	GameObject::UpdateComponents();
	m_componentManager.Run(fDt);
}

bool Application::CreateGameObject(const char* szHandle)
{
	lua_State* pL = m_lua.L();
	return GameObject::Create(pL, szHandle);
}

void Application::DestroyGameObject(luabridge::LuaRef obj)
{
	GameObject* pObj = obj[GameObject::ScriptHandle].cast<GameObject*>();
	
	if(pObj != NULL)
	{
		m_componentManager.Free(pObj);
	}
}

void Application::Register(lua_State* pL)
{
	getGlobalNamespace(pL)
		.beginClass<Application>("Application")
		.addFunction("CreateGameObject", &Application::CreateGameObject)
		.addFunction("DestroyGameObject",&Application::DestroyGameObject)
		.addFunction("GetFrameCount", &Application::GetFrameCount)
		.endClass();
}

}	//	namespace neko
