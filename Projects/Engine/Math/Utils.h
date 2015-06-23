/****************************************************************************
//	Filename: Utils.h
//	Description: Useful math functions
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

namespace math
{

template<typename CObj> const CObj& Min(const CObj& xV1, const CObj& xV2) 
	{if(xV2>xV1){return xV1;}else{return xV2;};};

template<typename CObj> const CObj& Max(const CObj& xV1, const CObj& xV2) 
	{if(xV2>xV1){return xV2;}else{return xV1;};};

template<typename CObj> const CObj& 
	Clamp(const CObj& xV,const CObj& xMin, const CObj& xMax)
	{if(xMin>xV){return xMin;}else if(xV>xMax){return xMax;}else {return xV;};};

template<typename CObj> static void Swap(CObj& xObj1, CObj& xObj2) 
{CObj xTemp = xObj1;xObj1 = xObj2;xObj2 = xTemp;};

static float Lerp(float p_fFrom,float p_fTo,float p_fT) {
	return (p_fFrom*(1.0f-p_fT))+(p_fTo*p_fT);

}	//	namespace math

}

}	//	namespace neko