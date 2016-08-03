/****************************************************************************
//	Filename: Application.h
//	Description: Base of an application
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/ComponentManager.h"
#include "Engine/Framework/Input.h"
#include "Engine/Core/LuaVM.h"
#include "Engine/Graphics/GFXDevice.h"

#include "ThirdParty/luabridge/LuaBridge.h"

namespace neko
{

class Application
{
public:
	Application();
	virtual ~Application();

	bool Init();
	void Shut();
	void Run();

	uint32 GetTickDiff(uint32 uStart, uint32 uEnd) const;

	uint32 GetFrameCount() const { return m_uFrameIndex; }
	float GetFramesPerSecond() const { return m_fFps; }

	bool CreateGameObject(const char* szHandle);
	void DestroyGameObject(luabridge::LuaRef obj);

	static const char* GetApplicationPath() { return s_path; }

protected:
	template <class ComponentManagerType>
	void _Init() { m_pComponentManager = new ComponentManagerType(); }

	virtual bool OnInit(){ return true; }
	virtual void OnShut(){}
	virtual void DoFrame(const float fDt);

	virtual void Register(lua_State* pL);

	GFXDevice m_device;
	SDL_Window* m_pWnd;

	bool m_bShouldQuit;
private:
	static char s_path[neko::PATH_MAX];

	bool MessagePump();
	InputManager m_inputManager;
	LuaVM m_lua;
	ComponentManager* m_pComponentManager;
	
	uint32 m_uFrameIndex;
	float m_fFps;
	int m_iMs;
};

}	//	namespace neko
