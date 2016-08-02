/****************************************************************************
//	Filename: LuaVM.h
//	Description: Lua Virtual Machine
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

#include "ThirdParty/Lua/lua.hpp"

namespace neko
{

class LuaVM
{
public:
	LuaVM(){}
	~LuaVM(){}

	lua_State* L() const { return m_L; }

	void LoadFiles(const char* szPath) const;

	void ExecuteFile(const char* szFilename) const;
	void ExecuteString(const char* szString) const;

	void Init();
	void Shut();

private:
	PRIVATE_COPY(LuaVM)
	
	lua_State* m_L;

	void Error(int iError) const;
};

}	//	namespace neko
