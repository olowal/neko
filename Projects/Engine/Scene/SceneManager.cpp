//	SceneManager.cpp

#include "SceneManager.h"

namespace neko
{

SceneManager::SceneManager(){}
SceneManager::~SceneManager(){}

SceneManager::SceneNode::SceneNode():
	m_pChild(NULL),
	m_pSibling(NULL){}
SceneManager::SceneNode::~SceneNode(){}

}	//	namespace neko