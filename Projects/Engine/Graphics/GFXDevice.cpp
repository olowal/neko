//	GFXDevice

#include "GFXDevice.h"

namespace neko
{

GFXDevice::GFXDevice()
{
	m_pFactory = NULL;
	m_pRenderTarget = NULL;
	m_pLightSlateGreyBrush = NULL;
	m_pCornFlowerBlueBrush = NULL;
}

GFXDevice::~GFXDevice()
{
	DiscardDeviceResources();
}

bool GFXDevice::Init()
{
	ASSERT(!m_pFactory);
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	return hr == S_OK;
	return false;
}

bool GFXDevice::CreateDeviceResources(HWND hWnd)
{
	ASSERT(m_pFactory != NULL);
	ASSERT(!m_pRenderTarget);
	RECT rc;
	GetClientRect(hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	HRESULT hr = m_pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &m_pRenderTarget);

	if(hr != S_OK)
	{
		return false;
	}

	ASSERT(m_pLightSlateGreyBrush == NULL);
	ASSERT(m_pCornFlowerBlueBrush == NULL);

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGreyBrush);

	if(hr != S_OK)
	{
		return false;
	}

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_pCornFlowerBlueBrush);

	if(hr != S_OK)
	{
		return false;
	}

	return true;
}

void GFXDevice::GetDesktopDpi(float& fDpiX, float& fDpiy)
{
	ASSERT(m_pFactory != NULL);
	m_pFactory->GetDesktopDpi(&fDpiX, &fDpiy);
}

void GFXDevice::OnResize(uint32 uWidth, uint32 uHeight)
{
	if(m_pRenderTarget != NULL)
	{
		m_pRenderTarget->Resize(D2D1::SizeU(uWidth, uHeight));
	}
}

void GFXDevice::OnRender()
{
	ASSERT(m_pRenderTarget != NULL);

	m_pRenderTarget->BeginDraw();
	
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Red));

	D2D1_SIZE_F size = m_pRenderTarget->GetSize();

	int iW = (int)size.width;
	int iH = (int)size.height;

	for(int x = 0; x < iW; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), size.height),
			m_pLightSlateGreyBrush,
			0.5f
			);
	}

	for(int y = 0; y < iH; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(size.height, static_cast<FLOAT>(y)),
			m_pLightSlateGreyBrush,
			0.5f
			);
	}

	D2D1_RECT_F rect1 = D2D1::RectF(
		size.width * 0.5f - 50.0f,
		size.height * 0.5f - 50.0f,
		size.width * 0.5f + 50.0f,
		size.height * 0.5f + 50.0f
		);

	D2D1_RECT_F rect2 = D2D1::RectF(
		size.width * 0.5f - 100.0f,
		size.height * 0.5f - 100.0f,
		size.width * 0.5f + 100.0f,
		size.height * 0.5f + 100.0f
		);

	m_pRenderTarget->FillRectangle(rect1, m_pLightSlateGreyBrush);
	
	const float fSpeed = 1.0f;
	static float fX = 10.0f;
	static float fY = 50.0f;

	if(::GetAsyncKeyState('W')) fY -= fSpeed;
	if(::GetAsyncKeyState('S')) fY += fSpeed;
	if(::GetAsyncKeyState('A')) fX -= fSpeed;
	if(::GetAsyncKeyState('D')) fX += fSpeed;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(fX, fY));
	m_pRenderTarget->DrawRectangle(rect2, m_pCornFlowerBlueBrush);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->EndDraw();
}

void GFXDevice::DiscardDeviceResources()
{
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
}



}	//	namespace neko