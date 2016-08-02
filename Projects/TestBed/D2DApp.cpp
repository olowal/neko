//	D2DApp.cpp

#include "D2DApp.h"
#include "Engine/Math/Utils.h"
#include "Tank/TankComponentManager.h"
#include "Engine/Framework/Component.h"
#include "Engine/Framework/SpriteComponent.h"
#include "Engine/Framework/TransformComponent.h"
#include "Engine/Core/ResourceSerializer.h"
#include "Engine/Framework/GameObject.h"
#include "Engine/Framework/Input.h"

using namespace neko;

D2DApp::D2DApp()
{

}
D2DApp::~D2DApp(){}

bool D2DApp::Init()
{
	_Init<TankComponentManager>();
	m_pWnd = neko::Window::Create("TankTest", 100, 100, 800, 600);
	return Inherited::Init();
}

bool D2DApp::OnInit()
{
	//ResourceSerializer::SerializeToBinary("Textures/", NULL);
	//SDL_Texture* pT = m_device.LoadTextureFromBinary("mario_sprite");

	return true;
}

/*
void D2DApp::DoFrame()
{
	
	neko::Color clr;
	clr.a = 125;
	clr.b = 255;
	clr.r = 0;
	clr.g = 0;

	m_pDevice->SetColor(clr);
	m_pDevice->DrawLine(20.0f, 30.0f, 60.0f, 60.0f);
	Inherited::DoFrame(0.0f);
}*/

void D2DApp::OnShut()
{

}