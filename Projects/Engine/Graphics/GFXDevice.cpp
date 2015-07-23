//	GFXDevice

#include "GFXDevice.h"
#include "Color.h"

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

	/*ASSERT(m_pRenderTarget != NULL);

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
			m_pSolidColorBrush,
			0.5f
			);
	}

	for(int y = 0; y < iH; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(size.height, static_cast<FLOAT>(y)),
			m_pSolidColorBrush,
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

	m_pRenderTarget->FillRectangle(rect1, m_pSolidColorBrush);
	
	const float fSpeed = 1.0f;
	static float fX = 10.0f;
	static float fY = 50.0f;

	if(::GetAsyncKeyState('W')) fY -= fSpeed;
	if(::GetAsyncKeyState('S')) fY += fSpeed;
	if(::GetAsyncKeyState('A')) fX -= fSpeed;
	if(::GetAsyncKeyState('D')) fX += fSpeed;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(fX, fY));
	m_pRenderTarget->DrawRectangle(rect2, m_pSolidColorBrush);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->EndDraw();*/
}

void GFXDevice::Clear(const Color& color)
{
	ASSERT(m_pRenderTarget != NULL);
	m_pRenderTarget->Clear(color);
}

void GFXDevice::DiscardDeviceResources()
{
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
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