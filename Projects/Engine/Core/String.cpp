//	String.cpp
#include "String.h"

namespace neko
{

template <>
IString<char>::IString(const char* szStr)
{
	m_pzString = NULL;
	m_uLength = 0;
	Set(szStr);
}

template <>
void IString<char>::Set(const char* pzStr)
{
	if(pzStr == NULL) { return; }
	m_uLength = (uint32)strlen(pzStr);
	const uint32 uSize = m_uLength + 1;
	m_pzString = Alloc(uSize);
	SDL_memcpy(m_pzString, pzStr, uSize);
}

template <>
void IString<wchar_t>::Set(const wchar_t* pzStr)
{
	if(pzStr == NULL) { return; }
	m_uLength = (uint32)wcslen(pzStr);
	const uint32 uSize = m_uLength + 1;
	m_pzString = Alloc(uSize);
	SDL_memcpy(m_pzString, pzStr, uSize * sizeof(wchar_t));
}

template <>
void IString<char>::Append(const char* pzStr)
{
	size_t uLength = SDL_strlen(pzStr);
	size_t uNewLength = m_uLength + uLength + 1;	//	+1 because of null terminating character
	m_pzString = (char*)realloc(m_pzString, uNewLength);
	SDL_strlcat(m_pzString, pzStr, uNewLength);
	m_uLength = m_uLength - 1;
}

template <>
int IString<char>::_Cmp(const char* pzStr) const
{
	return SDL_strcmp(m_pzString, pzStr);
}

template <>
int IString<wchar_t>::_Cmp(const wchar_t* pzStr) const
{
	return wcscmp(m_pzString, pzStr);
}

template <>
bool IString<char>::Equals(const char* szString) const
{
	return SDL_strcmp(m_pzString, szString) == 0;
}

}	//	namespace neko