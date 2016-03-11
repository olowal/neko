/****************************************************************************
//	Filename: GameObjectID.h
//	Description: A component that contains the game object, given automatically
	to all game objects.
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"
namespace neko
{
class GameObject;
struct GameObjectID
{
	const GameObject* gameObject;
};
}	//	namespace neko
