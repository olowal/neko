//	Vec2.cpp

#include "Vec2.h"
#include "Engine/Math/Mat3x2.h"
#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"
using namespace luabridge;
namespace neko
{

Vec2 Vec2::Zero		= Vec2(0.0f, 0.0f);
Vec2 Vec2::Up		= Vec2(1.0f, 0.0f);
Vec2 Vec2::Right	= Vec2(0.0f, 1.0f);

Vec2 Vec2::operator*(const Mat3x2& mM) const
{
	Vec2 vV(0.0f, 0.0f);
	/*vV.m_fX = (m_fX * mM._11) + (m_fY * mM._21) + mM._31;
	vV.m_fY = (m_fX * mM._12) + (m_fY * mM._22) + mM._32;*/
	return vV;
}

void Vec2::Register(lua_State* pL)
{
	getGlobalNamespace(pL)
		.beginClass<Vec2>("Vec2")
		.addConstructor<void(*) (void)>()
		.addConstructor<void(*) (float,float)>()
		.addData("x",&Vec2::m_fX)
		.addData("y",&Vec2::m_fY)
		.endClass();
}

}	//	namespace neko