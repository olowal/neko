/****************************************************************************
//	Filename: CollisionScene.h
//	Description: Tests for collision shapes
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/LinkedList.h"
#include "Engine/Core/ObjectPool.h"
#include "Engine/Core/Pair.h"
#include "Engine/Physics2D/CollisionShape.h"
namespace neko
{
struct CollisionPairGroup;
class GameObject;
class CollisionScene
{
public:
	CollisionScene();
	~CollisionScene();

	void Flag(GameObject* pObj);
	Pair<uint32, uint32> ClearGroupForObject(LinkedList<GameObject>& affectedObsOut, LinkedList<GameObject>& pairs, GameObject* pObj);

	void CheckCollisions();
private:
	LinkedList<GameObject>&  FindOrCreateGroup(GameObject* pObj);

	LinkedList<GameObject> m_flaggedObjects;
	ObjectPool<CollisionPairGroup> m_collisionPairs;
};

}	//	namespace neko
