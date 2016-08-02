//	GFXDevice

#include "GFXDevice.h"
#include "Color.h"
#include "Texture.h"

#include "Engine/Core/ResourceSerializer.h"
#include "ThirdParty/Lua/lua.hpp"
#include "ThirdParty/luabridge/LuaBridge.h"

namespace neko
{

static const GFXDevice* s_pDevice = NULL;

void GFXDevice::Register(lua_State * pL)
{
	/*using namespace luabridge;
	getGlobalNamespace(pL)
		.beginClass<GFXDevice>("SDL_Renderer_Device")
		.endClass();
	getGlobalNamespace(pL)
		.beginNamespace("GFXDevice")
		.addFunction("Create", &GFXDevice::CreateDevice)
		.endNamespace();*/
}
/*
GFXDevice* GFXDevice::CreateDevice(SDL_Window* pWnd)
{
	SDL_Renderer* pRnd = 
	ASSERT(pRnd != NULL);
	GFXDevice* pDevice = new GFXDevice(pRnd);
	SDL_RenderSetLogicalSize(pRnd,320,240);
	return pDevice;
}
*/
GFXDevice::GFXDevice()
{
	m_pRndr = NULL;
	m_mModel.SetIdentity();
}

GFXDevice::~GFXDevice()
{
	Shut();
}

bool GFXDevice::Init(SDL_Window* pWnd)
{
	Shut();
	m_pRndr = SDL_CreateRenderer(pWnd,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	return m_pRndr != NULL;
}

void GFXDevice::Shut()
{
	if(m_pRndr != NULL)
	{
		SDL_DestroyRenderer(m_pRndr);
		m_pRndr = NULL;
	}
}

void GFXDevice::OnResize(uint32 uWidth, uint32 uHeight)
{

}

void GFXDevice::BeginDraw()
{
	SDL_SetRenderDrawColor(m_pRndr, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderClear(m_pRndr);
}

void GFXDevice::EndDraw()
{
	SDL_RenderPresent(m_pRndr);
}

void GFXDevice::SetColor(const Color& color) const
{
	SDL_SetRenderDrawColor(m_pRndr, color.r, color.g, color.b, color.a);
}

void GFXDevice::SetClearColor(const Color& color)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;
	m_color.a = color.a;
}

void GFXDevice::DrawRect(const Vec2& vPos, const Vec2& vSize) const
{
	const Vec2& vModel = m_mModel.Pos();

	SDL_Rect rect;

	rect.x = (int)(vModel.m_fX + vPos.m_fX);
	rect.y = (int)(vModel.m_fY + vPos.m_fY);
	rect.w = (int)vSize.m_fX;
	rect.h = (int)vSize.m_fY;

	SDL_RenderDrawRect(m_pRndr, &rect);
}

void GFXDevice::DrawLine(float fXFrom, float fYFrom, float fXTo, float fYTo) const
{	
	//m_pSolidColorBrush->SetColor(&color);

	const Vec2& vModel = m_mModel.Pos();
	fXFrom += vModel.m_fX;
	fYFrom += vModel.m_fY;
	fXTo += vModel.m_fX;
	fYTo += vModel.m_fY;

	int iXFrom = static_cast<int>(fXFrom);
	int iYFrom = static_cast<int>(fYFrom);
	int iXTo = static_cast<int>(fXTo);
	int iYTo = static_cast<int>(fYTo);

	SDL_RenderDrawLine(m_pRndr, iXFrom, iYFrom, iXTo, iYTo);
}

void GFXDevice::DrawLine(const Vec2& vFrom, const Vec2& vTo) const
{
	DrawLine(vFrom.m_fX, vFrom.m_fY, vTo.m_fX, vTo.m_fY);
}

void GFXDevice::DrawBitmap(const Vec2& vPos, SDL_Texture* pTexture, const SDL_Rect& size, float fAngle) const
{
	SDL_Rect rct =
	{
		static_cast<int>(vPos.m_fX),
		static_cast<int>(vPos.m_fY),
		size.w,
		size.h
	};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(m_pRndr, pTexture, &size, &rct, static_cast<double>(fAngle), NULL, flip);
}

SDL_Texture* GFXDevice::LoadTextureFromBinary(const char* pzFilename) const
{
	return ResourceSerializer::LoadTextureFromBinary(m_pRndr, pzFilename);
}

}	//	namespace neko
