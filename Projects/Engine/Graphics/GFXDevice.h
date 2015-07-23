/****************************************************************************
//	Filename: GFXDevice.h
//	Description: The graphics device responsible for rendering things.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Graphics/Color.h"
#include "Engine/Math/Mat3x2.h"
#include "Engine/Math/Vec2.h"

namespace neko
{

class GFXDevice
{
public:
	GFXDevice();
	~GFXDevice();

	bool Init();
	bool CreateDeviceResources(HWND hWnd);

	void GetDesktopDpi(float& fDpiX, float& fDpiy);
	void OnResize(uint32 uWidth, uint32 uHeight);
	void OnRender();

	void BeginDraw();
	void EndDraw();

	void Clear(const Color& color);
	void SetColor(const Color& color);

	void DrawRect(const Vec2& vPos, const Vec2& vSize, const Color& color);
	void DrawLine(float fXFrom, float fYFrom, float fXTo, float fYTo, const Color& color);
	void DrawLine(const Vec2& vFrom, const Vec2& vTo, const Color& color);

	void SetModelMatrix(const Mat3x2& mModel) { m_mModel = mModel; }

	ID2D1Bitmap* CreateBitmapFromWicBitmap(IWICFormatConverter* pConvertedSourceBitmap) const;

private:
	void DiscardDeviceResources();

	Mat3x2 m_mModel;

	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pSolidColorBrush;
};

}	//	namespace neko