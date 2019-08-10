#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"


InputManager::InputManager()
	:keyStateL_{0,}, // keyState�� ������ ���� ��� 0���� �ʱ�ȭ��Ŵ
	keyStateR_{0,}
{
	// directInput_ ������ Direct Input ��ü�� ��ƿ�
	DirectInput8Create(GetModuleHandleA(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8A, (void**)&directInput_, nullptr);

	// Keyboard ��ü �޾ƿ�
	directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, nullptr); // Ű���� ����̽� ���� ����
	keyboard_->SetDataFormat(&c_dfDIKeyboard); // ������ ������ Ű�����
	keyboard_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	// ��׶��忡���� ������� ����, ��ġ�� ����ϰ� ���� ���� ������ ����
	keyboard_->Acquire();

	// Mouse ��ü �޾ƿ�
	directInput_->CreateDevice(GUID_SysMouse, &mouse_, nullptr); // ���콺 ����̽� ���� ����
	mouse_->SetDataFormat(&c_dfDIMouse); // ������ ������ ���콺��
	//mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	mouse_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	// ��׶��忡���� ������� ����, ���� ��ġ�� ����ϰ� �ִ� �ٸ� ���α׷��� �������� ����
	mouse_->Acquire();
}
InputManager::~InputManager()
{
	if (mouse_) // ���콺 ��ü�� ������ ��
	{
		mouse_->Unacquire();
		mouse_->Release();
	}
	if (keyboard_) // Ű���� ��ü�� ������ ��
	{
		keyboard_->Unacquire();
		keyboard_->Release();
	}
	if (directInput_) // Direct Input ��ü�� ������ ��
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