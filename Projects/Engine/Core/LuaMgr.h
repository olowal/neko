/****************************************************************************
//	Filename: LuaMgr.h
//	Description: Wrapper around lua functions
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

#include "ThirdParty/Lua/lua.hpp"

namespace neko
{

class LuaMgr
{
public:
	LuaMgr()
	{
		m_L = luaL_newstate();
		luaL_openlibs(m_L);
	}

	~LuaMgr()
	{
		lua_close(m_L);
	}

	lua_State* L() const { return m_L; }

	void LoadFiles(const char* szPath) const;

	void ExecuteFile(const char* szFilename) const;
	void ExecuteString(const char* szString) const;

private:
	PRIVATE_COPY(LuaMgr)
	
	lua_State* m_L;

	void Error(int iError) const;
};

}	//	namespace neko
