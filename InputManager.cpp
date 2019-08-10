#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"


InputManager::InputManager()
	:keyStateL_{0,}, // keyState를 이전과 현재 모두 0으로 초기화시킴
	keyStateR_{0,}
{
	// directInput_ 변수에 Direct Input 객체를 담아옴
	DirectInput8Create(GetModuleHandleA(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8A, (void**)&directInput_, nullptr);

	// Keyboard 객체 받아옴
	directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, nullptr); // 키보드 디바이스 새로 생성
	keyboard_->SetDataFormat(&c_dfDIKeyboard); // 데이터 포맷을 키보드로
	keyboard_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	// 백그라운드에서는 사용하지 않음, 장치를 사용하고 있을 동안 뺏기지 않음
	keyboard_->Acquire();

	// Mouse 객체 받아옴
	directInput_->CreateDevice(GUID_SysMouse, &mouse_, nullptr); // 마우스 디바이스 새로 생성
	mouse_->SetDataFormat(&c_dfDIMouse); // 데이터 포맷을 마우스로
	//mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	// 백그라운드에서는 사용하지 않음, 같은 장치를 사용하고 있는 다른 프로그램을 방해하지 않음
	mouse_->Acquire();
}
InputManager::~InputManager()
{
	if (mouse_) // 마우스 객체가 존재할 때
	{
		mouse_->Unacquire();
		mouse_->Release();
	}
	if (keyboard_) // 키보드 객체가 존재할 때
	{
		keyboard_->Unacquire();
		keyboard_->Release();
	}
	if (directInput_) // Direct Input 객체가 존재할 때
	{
		directInput_->Release();
	}
}

void InputManager::Update(void)
{
	HRESULT result = 0;
	memcpy_s(keyStateL_, sizeof(keyStateL_), keyStateR_, sizeof(keyStateR_));
	result = keyboard_->GetDeviceState(sizeof(keyStateR_), (LPVOID)&keyStateR_);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard_->Acquire();
		}
	}

	memcpy_s(rgbButtonsL_, sizeof(rgbButtonsL_), mouseState_.rgbButtons, sizeof(mouseState_.rgbButtons));
	result = mouse_->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState_);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse_->Acquire();
		}
	}
}

#define LKEY(key) (keyStateL_[key] & 0x80 ? true : false)
#define RKEY(key) (keyStateR_[key] & 0x80 ? true : false)

KeyState InputManager::GetKeyState(KeyCode key)
{
	if (LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_STAY;
	if (!LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_ENTER;
	if (LKEY(key) && !RKEY(key)) return KeyState::KEYSTATE_EXIT;
	return KeyState::KEYSTATE_NONE;
}

#undef LKEY
#undef RKEY

#define LKEY(key) (rgbButtonsL_[key] & 0x80 ? true : false)
#define RKEY(key) (mouseState_.rgbButtons[key] & 0x80 ? true : false)

KeyState InputManager::GetMouseState(MouseCode key)
{
	if (LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_STAY;
	if (!LKEY(key) && RKEY(key)) return KeyState::KEYSTATE_ENTER;
	if (LKEY(key) && !RKEY(key)) return KeyState::KEYSTATE_EXIT;
	return KeyState::KEYSTATE_NONE;
}

#undef LKEY
#undef RKEY

Point2F InputManager::GetMousePos() const
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(RG2R_WindowM->GetHwnd(), &mousePoint);
	return Point2F(mousePoint.x, mousePoint.y);
}

long InputManager::GetMouseDeltaX(void) const
{
	return mouseState_.lX;
}

long InputManager::GetMouseDeltaY(void) const
{
	return mouseState_.lY;
}

int InputManager::GetMouseWheel(void) const
{
	return (int)mouseState_.lZ;
}