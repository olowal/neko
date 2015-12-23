/****************************************************************************
//	Filename: SpriteRenderSystem.h
//	Description: This system will render sprites
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{

class GameObject;
struct SpriteComponent;
struct TransformComponent;
class SpriteRenderSystem
{
public:
	struct Components
	{
		TransformComponent* pTrans;
		SpriteComponent* pSprite;
	};

	static bool GetComponents(GameObject* pObj, Components* pComp);
	static void Run(Components* pComp, float fDelta);
};

}	//	namespace neko
