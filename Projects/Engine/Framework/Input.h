/****************************************************************************
//	Filename: Input.h
//	Description: Helpers for input
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "ThirdParty/Lua/lua.hpp"
namespace neko
{

class Input
{
public:
	static const uint32 NumKeys = 256;
	static bool IsKeyDown(int iKey);
	static bool IsKeyPressed(int iKey);
	static bool IsKeyReleased(int iKey);
};

class InputManager : public Input
{
public:
	InputManager();
	virtual ~InputManager();

	void Register(lua_State* pL);
	void Update();

private:
	uint32 m_keys[Input::NumKeys];
};

}	//	namespace neko
