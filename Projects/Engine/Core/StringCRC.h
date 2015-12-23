/****************************************************************************
//	Filename: StringCRC.h
//	Description: Creates a hash from a string
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class StringCRC
{
public:
	StringCRC();
	StringCRC(const char* sStr);
	~StringCRC();

	StringCRC& operator=(const char* sStr)
	{
		m_uChecksum = CalculateStringChecksum(sStr);
		return *this;
	}

	uint32 Get() const { return m_uChecksum; }
	void Clear() { m_uChecksum = 0; }

	static uint32 GetCRC(const char* pzStr);

private:
	uint32 m_uChecksum;

	uint32 CalculateStringChecksum(const char* sStr);
};

}	//	namespace neko
