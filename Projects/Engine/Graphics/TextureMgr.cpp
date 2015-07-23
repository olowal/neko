//	TextureMgr.cpp
#include "TextureMgr.h"

namespace neko
{

TextureMgr::TextureMgr()
{
	m_pIWICFactory = NULL;
}

TextureMgr::~TextureMgr()
{
	SafeRelease(&m_pIWICFactory);
}

bool TextureMgr::Init()
{
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
	CLSID_WICImagingFactory,
	NULL,
	CLSCTX_INPROC_SERVER,
	IID_PPV_ARGS(&m_pIWICFactory)
	);

	return SUCCEEDED(hr);
}

}	//	namespace neko