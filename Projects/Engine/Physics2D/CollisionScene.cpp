//	CollisionScene.cpp
#include "CollisionScene.h"

namespace neko
{

CollisionScene::CollisionScene():
m_circles(64){}
CollisionScene::~CollisionScene(){}

CircleShape* CollisionScene::AddCircleShape()
{
	CircleShape* pCircle = m_circles.Alloc();
	m_shapes.AddToLast(pCircle);
	return pCircle;
}

void CollisionScene::RemoveCircle(CircleShape* pCircle)
{
	m_circles.Free(pCircle);
}

void CollisionScene::CheckCollisions()
{
	for(auto it = m_shapes.Begin(); !it.IsEnd(); ++it)
	{
		CollisionShape* pShapeA = (*it);

		/*for(auto it2 = m_shapes.Begin(); !it2.IsEnd(); ++it2)
		{
			CollisionShape* pShapeB = (*it2);
			if(pShapeA != pShapeB
				&& pShapeA->Intersects(pShapeB))
			{
			
			}
		}*/
	}
}

}	//	namespace neko
