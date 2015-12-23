//	Input.cpp
#include "Input.h"
#include "ThirdParty/luabridge/LuaBridge.h"
namespace neko
{

static Uint8 s_lastKeys[Input::NumKeys];
static bool s_bInitialized = false;

bool Input::IsKeyDown(int iKey)
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
	return pKeyStates[iKey] != 0;
}

bool Input::IsKeyPressed(int iKey)
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
	return (pKeyStates[iKey] != 0) && (s_lastKeys[iKey] == 0);
}

bool Input::IsKeyReleased(int iKey)
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
	return (pKeyStates[iKey] == 0) && (s_lastKeys[iKey] != 0);
}

InputManager::InputManager()
{
	ASSERT(!s_bInitialized);
	SDL_memset(s_lastKeys, 0, sizeof(Uint8) * Input::NumKeys);
	s_bInitialized = true;
}

InputManager::~InputManager()
{

}

void InputManager::Register(lua_State* pL)
{
	for(uint32 i = 0; i < Input::NumKeys; ++i)
	{
		m_keys[i] = i;
	}

	using namespace luabridge;
	getGlobalNamespace(pL)
		.beginNamespace("Input")
		.addFunction("IsKeyDown", Input::IsKeyDown)
		.addFunction("IsKeyPressed", Input::IsKeyPressed)
		.addFunction("IsKeyReleased", Input::IsKeyReleased)
		.addVariable("KC_0", &m_keys[SDL_SCANCODE_0], false)
		.addVariable("KC_1", &m_keys[SDL_SCANCODE_1], false)
		.addVariable("KC_2", &m_keys[SDL_SCANCODE_2], false)
		.addVariable("KC_3", &m_keys[SDL_SCANCODE_3], false)
		.addVariable("KC_4", &m_keys[SDL_SCANCODE_4], false)
		.addVariable("KC_5", &m_keys[SDL_SCANCODE_5], false)
		.addVariable("KC_6", &m_keys[SDL_SCANCODE_6], false)
		.addVariable("KC_7", &m_keys[SDL_SCANCODE_7], false)
		.addVariable("KC_8", &m_keys[SDL_SCANCODE_8], false)
		.addVariable("KC_9", &m_keys[SDL_SCANCODE_9], false)
		.addVariable("KC_Q", &m_keys[SDL_SCANCODE_Q], false)
		.addVariable("KC_W", &m_keys[SDL_SCANCODE_W], false)
		.addVariable("KC_E", &m_keys[SDL_SCANCODE_E], false)
		.addVariable("KC_R", &m_keys[SDL_SCANCODE_R], false)
		.addVariable("KC_T", &m_keys[SDL_SCANCODE_T], false)
		.addVariable("KC_Y", &m_keys[SDL_SCANCODE_Y], false)
		.addVariable("KC_U", &m_keys[SDL_SCANCODE_U], false)
		.addVariable("KC_I", &m_keys[SDL_SCANCODE_I], false)
		.addVariable("KC_O", &m_keys[SDL_SCANCODE_O], false)
		.addVariable("KC_P", &m_keys[SDL_SCANCODE_P], false)
		.addVariable("KC_A", &m_keys[SDL_SCANCODE_A], false)
		.addVariable("KC_S", &m_keys[SDL_SCANCODE_S], false)
		.addVariable("KC_D", &m_keys[SDL_SCANCODE_D], false)
		.addVariable("KC_F", &m_keys[SDL_SCANCODE_F], false)
		.addVariable("KC_G", &m_keys[SDL_SCANCODE_G], false)
		.addVariable("KC_H", &m_keys[SDL_SCANCODE_H], false)
		.addVariable("KC_J", &m_keys[SDL_SCANCODE_J], false)
		.addVariable("KC_K", &m_keys[SDL_SCANCODE_K], false)
		.addVariable("KC_L", &m_keys[SDL_SCANCODE_L], false)
		.addVariable("KC_Z", &m_keys[SDL_SCANCODE_Z], false)
		.addVariable("KC_X", &m_keys[SDL_SCANCODE_X], false)
		.addVariable("KC_C", &m_keys[SDL_SCANCODE_C], false)
		.addVariable("KC_V", &m_keys[SDL_SCANCODE_V], false)
		.addVariable("KC_B", &m_keys[SDL_SCANCODE_B], false)
		.addVariable("KC_N", &m_keys[SDL_SCANCODE_N], false)
		.addVariable("KC_M", &m_keys[SDL_SCANCODE_M], false)
		.addVariable("KC_SPACE", &m_keys[SDL_SCANCODE_SPACE], false)
		.addVariable("KC_RETURN", &m_keys[SDL_SCANCODE_RETURN], false)
		.addVariable("KC_LSHIFT", &m_keys[SDL_SCANCODE_LSHIFT], false)
		.addVariable("KC_RSHIFT", &m_keys[SDL_SCANCODE_RSHIFT], false)
		.addVariable("KC_LCTRL", &m_keys[SDL_SCANCODE_LCTRL], false)
		.addVariable("KC_RCTRL", &m_keys[SDL_SCANCODE_RCTRL], false)
		.endNamespace();
}

void InputManager::Update()
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
	SDL_memcpy(s_lastKeys, pKeyStates, sizeof(Uint8) * Input::NumKeys);
}

}	//	namespace neko
