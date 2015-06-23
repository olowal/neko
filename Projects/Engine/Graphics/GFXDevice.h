/****************************************************************************
//	Filename: GFXDevice.h
//	Description: The graphics device responsible for rendering things.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

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

private:
	void DiscardDeviceResources();

	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGreyBrush;
	ID2D1SolidColorBrush* m_pCornFlowerBlueBrush;
};

}	//	namespace neko