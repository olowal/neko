/****************************************************************************
//	Filename: Application.h
//	Description: Base of an application
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Framework/ComponentManager.h"
#include "Engine/Framework/Input.h"
#include "Engine/Core/LuaMgr.h"

#include "ThirdParty/luabridge/LuaBridge.h"

namespace neko
{
class GFXDevice;
class Application
{
public:
	Application();
	virtual ~Application();

	bool Init(const char* pzTitle, int iW, int iH, int iX = SDL_WINDOWPOS_UNDEFINED, int iY = SDL_WINDOWPOS_UNDEFINED);
	void Shut();
	void Run();

	uint32 GetTickDiff(uint32 uStart, uint32 uEnd) const;

	uint32 GetFrameCount() const { return m_uFrameIndex; }
	float GetFramesPerSecond() const { return m_fFps; }

	bool CreateGameObject(const char* szHandle);
	void DestroyGameObject(luabridge::LuaRef obj);

protected:
	virtual bool OnInit(){ return true; }
	virtual void OnShut(){}
	virtual void DoFrame();

	virtual void Register(lua_State* pL);

	GFXDevice* m_pDevice;

	bool m_bShouldQuit;
private:
	bool MessagePump();
	ComponentManager m_componentManager;
	InputManager m_inputManager;
	LuaMgr m_lua;
	uint32 m_uFrameIndex;
	float m_fFps;
	int m_iMs;
};

}	//	namespace neko
