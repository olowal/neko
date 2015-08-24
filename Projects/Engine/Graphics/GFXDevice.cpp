//	GFXDevice

#include "GFXDevice.h"
#include "Color.h"
#include "Texture.h"

namespace neko
{

GFXDevice::GFXDevice()
{
	m_pFactory = NULL;
	m_pRenderTarget = NULL;
	m_pSolidColorBrush = NULL;
	m_mModel.SetIdentity();
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

	ASSERT(m_pSolidColorBrush == NULL);
	
	hr = m_pRenderTarget->CreateSolidColorBrush(Color(Color::LightSlateGray), &m_pSolidColorBrush);

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

void GFXDevice::BeginDraw()
{
	ASSERT(m_pRenderTarget != NULL);
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void GFXDevice::EndDraw()
{
	ASSERT(m_pRenderTarget != NULL);
	
	m_pRenderTarget->EndDraw();
}

void GFXDevice::OnRender()
{

}

void GFXDevice::Clear(const Color& color)
{
	ASSERT(m_pRenderTarget != NULL);
	m_pRenderTarget->Clear(color);
}

void GFXDevice::DiscardDeviceResources()
{
	SafeRelease(m_pFactory);
	SafeRelease(m_pRenderTarget);
}

void GFXDevice::SetColor(const Color& color)
{
	ASSERT(m_pSolidColorBrush != NULL);
	m_pSolidColorBrush->SetColor(&color);
}

void GFXDevice::DrawRect(const Vec2& vPos, const Vec2& vSize, const Color& color)
{
	ASSERT(m_pRenderTarget != NULL);
	ASSERT(m_pSolidColorBrush != NULL);

	m_pSolidColorBrush->SetColor(&color);
	Vec2 vHalfSize = vSize * 0.5f;

	Mat3x2 mM;
	mM.SetIdentity();
	mM.SetTranslation(-vSize.m_fX + vPos.m_fX - vHalfSize.m_fX, -vSize.m_fY + vPos.m_fY - vHalfSize.m_fY);

	m_pRenderTarget->SetTransform(m_mModel * mM);

	D2D1_RECT_F rect = D2D1::RectF
		(
			vSize.m_fX,
			vSize.m_fY,
			(vSize.m_fX * 2.0f),
			(vSize.m_fY * 2.0f)
		);
	m_pRenderTarget->FillRectangle(rect, m_pSolidColorBrush);
}

void GFXDevice::DrawLine(float fXFrom, float fYFrom, float fXTo, float fYTo, const Color& color)
{
	ASSERT(m_pRenderTarget != NULL);
	ASSERT(m_pSolidColorBrush != NULL);
	
	m_pSolidColorBrush->SetColor(&color);

	D2D_POINT_2F from = { fXFrom, fYFrom };
	D2D_POINT_2F to = { fXTo, fYTo };

	m_pRenderTarget->DrawLine(from, to, m_pSolidColorBrush);
}

void GFXDevice::DrawLine(const Vec2& vFrom, const Vec2& vTo, const Color& color)
{
	DrawLine(vFrom.m_fX, vFrom.m_fY, vTo.m_fX, vTo.m_fY, color);
}

void GFXDevice::DrawBitmap(const Vec2& vPos, Texture* pTexture)
{
	ID2D1Bitmap* pB = pTexture->GetBitmap();
	D2D_SIZE_F size = pB->GetSize();
	Vec2 vHalfSize(size.width * 0.5f, size.height * 0.5f);
	Mat3x2 mM;
	mM.SetIdentity();
	mM.SetTranslation(-size.width + vPos.m_fX - vHalfSize.m_fX, -size.height + vPos.m_fY - vHalfSize.m_fY);
	m_pRenderTarget->SetTransform(m_mModel * mM);
	D2D1_RECT_F rect = D2D1::RectF
		(
			size.width,
			size.height,
			(size.width * 2.0f),
			(size.height * 2.0f)
		);
	m_pRenderTarget->DrawBitmap(pB, rect);
}

ID2D1Bitmap* GFXDevice::CreateBitmapFromWicBitmap(IWICFormatConverter* pConvertedSourceBitmap) const
{
	ASSERT(m_pRenderTarget != NULL);
	ID2D1Bitmap* pBitmap = NULL;
	HRESULT hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConvertedSourceBitmap, NULL, &pBitmap);
	if(!SUCCEEDED(hr))
	{
		return NULL;
	}

	return pBitmap;
}

}	//	namespace neko