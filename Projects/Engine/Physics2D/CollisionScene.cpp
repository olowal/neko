//	CollisionScene.cpp
#include "CollisionScene.h"

namespace neko
{

struct CollisionPairGroup
{
	LinkedList<GameObject> pairs;
	GameObject* pGameObject;
	CollisionPairGroup() : pGameObject(NULL) {}
};

CollisionPairGroup* FindGroup(ObjectPool<CollisionPairGroup>& pairs, GameObject* pObj)
{
	CollisionPairGroup* pPairGroup = NULL;

	for(ObjectPool<CollisionPairGroup>::Iterator it = pairs.Begin(); !it.IsEnd(); ++it)
	{
		if((*it)->pGameObject == pObj)
		{
			pPairGroup = *it;
		}
	}

	return pPairGroup;
}

CollisionScene::CollisionScene():m_collisionPairs(32){}
CollisionScene::~CollisionScene(){}

void CollisionScene::Flag(GameObject* pObj)
{
	if(!m_flaggedObjects.Contains(pObj))
	{
		m_flaggedObjects.AddToLast(pObj);
	}
}

Pair<uint32, uint32> CollisionScene::ClearGroupForObject(LinkedList<GameObject>& affectedObsOut, LinkedList<GameObject>& pairs, GameObject * pObj)
{
	uint32 numObs = 0;
	uint32 numObsCleared = 0;
	LinkedList<GameObject>::Iterator it = pairs.Begin();
	while(!it.IsEnd())
	{
		GameObject* pCollPair = *it;

	}


	return Pair<uint32, uint32>();
}

void CollisionScene::CheckCollisions()
{

}

LinkedList<GameObject>& CollisionScene::FindOrCreateGroup(GameObject * pObj)
{
	CollisionPairGroup* pPairGroup = FindGroup(m_collisionPairs, pObj);

	if(pPairGroup == NULL)
	{
		pPairGroup = m_collisionPairs.Alloc();
		pPairGroup->pGameObject = pObj;
	}

	return pPairGroup->pairs;
}

}	//	namespace neko
