/****************************************************************************
//	Filename: String.h
//	Description: String class for managing text etc
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

template <typename StrType>
class IString
{
public:
	IString():
	m_pzString(NULL),
	m_uLength(0){}
	IString(const StrType& pzStr){}
	~IString(){}

	void Clear()
	{
		if(m_pzString != NULL)
		{
			free(m_pzString);
			m_pzString = NULL;
			m_uLength = 0;
		}
	}

	void Set(const StrType* pzStr);

	uint32 Length() const { return m_uLength; }
	bool Empty() const { return m_uLength == 0; }
	const StrType* CStr() const { return m_pzString; }

	StrType* Alloc(uint32 uNumChars)
	{
		Clear();
		m_pzString = (StrType*)malloc(sizeof(StrType) * uNumChars);
		return m_pzString;
	}

	bool operator == (const IString& sStr) const { return Compare(sStr) == 0; }
	bool operator != (const IString& sStr) const { return Compare(sStr) != 0; }
	bool operator >= (const IString& sStr) const { return Compare(sStr) >= 0; }
	bool operator <= (const IString& sStr) const { return Compare(sStr) <= 0; }
	bool operator > (const IString& sStr) const { return Compare(sStr) > 0; }
	bool operator < (const IString& sStr) const { return Compare(sStr) < 0; }

private:
	int _Cmp(const StrType* pzString) const;
	int Compare(const IString& sStr) const
	{
		if(m_pzString == NULL && sStr.m_pzString == NULL) { return 0; }
		else if(m_pzString != NULL && sStr.m_pzString == NULL) { return 1; }
		else if(m_pzString == NULL && sStr.m_pzString != NULL) { return -1; }
		return _Cmp(sStr.m_pzString);
	}

	StrType* m_pzString;
	uint32 m_uLength;
};

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

typedef IString<char> U8String;
typedef IString<wchar_t> WString;
typedef WString String;

}	//	namespace neko