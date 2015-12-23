/****************************************************************************
//	Filename: Pair.h
//	Description: Holder of two data types
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

template <class TFirst, class TSecond>
class Pair
{
public:
	Pair(){}
	Pair(const TFirst& a, const TSecond& b):first(a),second(b){}

	TFirst first;
	TSecond second;
};

template <class TFirst, class TSecond>
static Pair<TFirst, TSecond> MakePair(const TFirst& first, const TSecond& second)
{
	return Pair<TFirst, TSecond>(first, second);
}

}	//	namespace neko
