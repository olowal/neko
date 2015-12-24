/****************************************************************************
//	Filename: CollisionShape.h
//	Description: CollisionShape
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Math/Vec2.h"
namespace neko
{

struct Circle2D
{
	Vec2 center;
	float radius;
};
struct Box2D
{
	Vec2 center;
	Vec2 extents;
};
struct Line2D
{
	Vec2 begin;
	Vec2 end;
};

template <class Shape>
class CollisionShape2D
{
public:
	CollisionShape2D(){}
	~CollisionShape2D(){}

	Vec2 GetPosition() const { return position + shape.center; }

	Shape shape;
	Vec2 position;
};

typedef CollisionShape2D<Circle2D> CircleShape2D;
typedef CollisionShape2D<Box2D> BoxShape2D;

}	//	namespace neko
