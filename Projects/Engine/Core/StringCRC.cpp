//	StringCRC.cpp
#include "StringCRC.h"
namespace neko
{

StringCRC::StringCRC():m_uChecksum(0){}
StringCRC::~StringCRC(){}

uint32 StringCRC::CalculateStringChecksum(const char* sStr)
{
	const char* pP = sStr;
	m_uChecksum = 0;
	float fIntermediary;

	while (*pP)
	{
		fIntermediary = (float)(*pP);
		m_uChecksum += (uint32)fIntermediary;
		fIntermediary *= (uint32&)fIntermediary % 155323;
		m_uChecksum *= (uint32&)fIntermediary % 0xD5F288;
		m_uChecksum += (m_uChecksum >> 16);
		pP++;
	}
	return m_uChecksum;
}

}	//	namespace neko
