//	Utils.cpp

#include "Utils.h"
#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"
using namespace luabridge;
namespace neko
{
namespace math
{
void Register(lua_State* pL)
{
	getGlobalNamespace(pL)
		.beginNamespace("math")
		.addFunction("Deg2Rad",neko::math::Deg2Rad)
		.addFunction("Rad2Deg",neko::math::Rad2Deg)
		.endNamespace();
}
}	//	namespace math
}	//	namespace neko
