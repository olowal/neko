/****************************************************************************
//	Filename: CollisionScene.h
//	Description: Tests for collision shapes
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/LinkedList.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Physics2D/CircleShape.h"
namespace neko
{

class CollisionScene
{
public:
	CollisionScene();
	~CollisionScene();

	CircleShape* AddCircleShape();
	void RemoveCircle(CircleShape* pCircle);
	void CheckCollisions();
private:
	void AddShape(CollisionShape* pShape);

	LinkedList<CollisionShape> m_shapes;
	ObjectPool<CircleShape> m_circles;
};

}	//	namespace neko
