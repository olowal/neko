/****************************************************************************
//	Filename: GFXDevice.h
//	Description: The graphics device responsible for rendering things.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Math/Mat3x2.h"
#include "Engine/Math/Vec2.h"
#include "Engine/Graphics/Texture.h"

typedef struct lua_State lua_State;

namespace neko
{

class GFXDevice
{
public:
	GFXDevice();
	~GFXDevice();

	bool Init(SDL_Window* pWnd);
	void Shut();

	void OnResize(uint32 uWidth, uint32 uHeight);

	void BeginDraw();
	void EndDraw();

	void Clear(const Color& color);
	void SetClearColor(const Color& color);
	void SetColor(const Color& color) const;
	void DrawRect(const Vec2& vPos, const Vec2& vSize) const;
	void DrawLine(float fXFrom, float fYFrom, float fXTo, float fYTo) const;
	void DrawLine(const Vec2& vFrom, const Vec2& vTo) const;
	void DrawBitmap(const Vec2& vPos, SDL_Texture* pTexture, const SDL_Rect& size, float fAngle) const;

	void SetModelMatrix(const Mat3x2& mModel) { m_mModel = mModel; }

	SDL_Texture* LoadTextureFromBinary(const char* pzFilename) const;

	static void Register(lua_State* pL);

private:
	Mat3x2 m_mModel;
	SDL_Color m_color;
	SDL_Renderer* m_pRndr;
};

}	//	namespace neko