#pragma once
#include "Math.h"

class WindowManager
{
private:
	HWND hwnd_; // ������ ��ü ��ü
	MSG msg_; // �޼���?
	RECT savedRect_; // ����� �簢��?
	char cStrBuffer_[C_STR_BUFFER_SIZE]; // ���� �����ε� �� �𸣰ڰ�
	bool isFullscreen_; // Ǯ��ũ�� ����
	bool isResizable_; // ������ ���� ���� ����

public:
	WindowManager();
	~WindowManager();

	void SetTitle(const std::string& title); // Ÿ��Ʋ ����
	void SetPos(const Point2L& pos); // ��ġ ����
	void SetSize(const Size2U& size); // ũ�� ����
	void SetFullscreen(bool flag); // Ǯ��ũ�� ���� ����
	void SetResizable(bool flag); // ������ ���� ���� ���� ����
	void SetMaximizable(bool flag); // �ִ�ũ�� ���� ����
	void ToggleFullscreen(); // Ǯ��ũ�� ���

	HWND GetHwnd(); // ������ ��ü �޾ƿ���
	std::string GetTitle(); // Ÿ��Ʋ �޾ƿ���
	Point2L GetPos(); // ��ġ �޾ƿ���
	Size2U GetSize(); // ũ�� �޾ƿ���
	void Minimize(); // �ּ�ȭ
	void Maximize(); // �ִ�ȭ
	void Focus(); // ��Ŀ��
	void Foreground(); // ������
	void Activate(); // Ȱ��ȭ

	// �� �ּ� �ޱ� ������
	bool IsRunning();
	bool IsResizable();
	bool IsMaximizable();
	bool IsMinimized();
	bool IsMaximized();
	bool IsFocused();
	bool IsActive();
	bool IsFullscreen();
	bool MsgLoop();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // �޼��� ó�� �Լ�
};