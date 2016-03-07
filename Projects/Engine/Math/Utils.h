/****************************************************************************
//	Filename: Utils.h
//	Description: Useful math functions
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
typedef struct lua_State lua_State;
namespace neko
{

namespace math
{

static const float PI = 3.14159265359f;
static const float PIHALF = 1.5707963268f;
static const float PIQUATER = 0.7853981633975f;

static const float DEGREE = 360.0f;
static const float DEGREEHALF = 180.0f;
static const float DEGREEQUATER = 90.0f;

// in game values are counted from max positive to min negative so we can set simple limitations on specific angles starting from zero
static const float DEGREEMAX = 180.0f;
static const float DEGREEMIN = -180.0f;

static const float DEG2RAD = ((PI * 2.0f) / DEGREE);
static const float RAD2DEG = (DEGREE / (PI * 2.0f));

template<typename CObj> 
const CObj& Min(const CObj& xV1, const CObj& xV2) 
{
	if(xV2>xV1)
	{return xV1;}
	else
	{return xV2;}
}

template<typename CObj> 
const CObj& Max(const CObj& xV1, const CObj& xV2) 
{
	if(xV2>xV1)
	{return xV2;}
	else
	{return xV1;}
}

template<typename CObj> 
const CObj& Clamp(const CObj& xV,const CObj& xMin, const CObj& xMax)
{
	if(xMin>xV)
	{return xMin;}
	else if(xV>xMax)
	{return xMax;}
	else 
	{return xV;}
};

template<typename CObj> 
void Swap(CObj& xObj1, CObj& xObj2) 
{
	CObj xTemp = xObj1;
	xObj1 = xObj2;
	xObj2 = xTemp;
}

static float Lerp(float p_fFrom,float p_fTo,float p_fT) 
{
	return (p_fFrom*(1.0f-p_fT))+(p_fTo*p_fT);
}

//	Wraps around DEGREEMAX DEGREEMIN
static float RotateAngle(float fAngle, float fValue)
{
	float fV = fAngle + fValue;

	if(fV > DEGREEMAX)
	{
		fV = DEGREEMIN + (fV - DEGREEMAX);
	}
	else if(fV < DEGREEMIN)
	{
		fV = DEGREEMAX + (fV + DEGREEMIN);
	}

	return fV;
}

static float Deg2Rad(float fDeg)
{
	return fDeg * DEG2RAD;
}

static float Rad2Deg(float fRad)
{
	return fRad * RAD2DEG;
}

void Register(lua_State* pL);

}	//	namespace math
}	//	namespace neko
