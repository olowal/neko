//	String.cpp
#include "String.h"

namespace neko
{

template <>
void IString<char>::Set(const char* pzStr)
{
	if(pzStr == NULL) { return; }
	m_uLength = (uint32)strlen(pzStr);
	const uint32 uSize = m_uLength + 1;
	m_pzString = Alloc(uSize);
	memcpy_s(m_pzString, uSize, pzStr, uSize);
}

template <>
void IString<wchar_t>::Set(const wchar_t* pzStr)
{
	if(pzStr == NULL) { return; }
	m_uLength = (uint32)wcslen(pzStr);
	const uint32 uSize = m_uLength + 1;
	m_pzString = Alloc(uSize);
	memcpy_s(m_pzString, uSize * sizeof(wchar_t), pzStr, uSize * sizeof(wchar_t));
}

template <>
int IString<char>::_Cmp(const char* pzStr) const
{
	return strcmp(m_pzString, pzStr);
}

template <>
int IString<wchar_t>::_Cmp(const wchar_t* pzStr) const
{
	return wcscmp(m_pzString, pzStr);
}

}	//	namespace neko