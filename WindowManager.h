#pragma once
#include "Math.h"

class WindowManager
{
private:
	HWND hwnd_; // 윈도우 객체 자체
	MSG msg_; // 메세지?
	RECT savedRect_; // 저장된 사각형?
	char cStrBuffer_[C_STR_BUFFER_SIZE]; // 글자 관련인데 난 모르겠고
	bool isFullscreen_; // 풀스크린 여부
	bool isResizable_; // 사이즈 변경 가능 여부

public:
	WindowManager();
	~WindowManager();

	void SetTitle(const std::string& title); // 타이틀 설정
	void SetPos(const Point2L& pos); // 위치 설정
	void SetSize(const Size2U& size); // 크기 설정
	void SetFullscreen(bool flag); // 풀스크린 여부 변경
	void SetResizable(bool flag); // 사이즈 변경 가능 여부 변경
	void SetMaximizable(bool flag); // 최대크기 여부 변경
	void ToggleFullscreen(); // 풀스크린 토글

	HWND GetHwnd(); // 윈도우 객체 받아오기
	std::string GetTitle(); // 타이틀 받아오기
	Point2L GetPos(); // 위치 받아오기
	Size2U GetSize(); // 크기 받아오기
	void Minimize(); // 최소화
	void Maximize(); // 최대화
	void Focus(); // 포커스
	void Foreground(); // 앞으로
	void Activate(); // 활성화

	// 아 주석 달기 귀찮아
	bool IsRunning();
	bool IsResizable();
	bool IsMaximizable();
	bool IsMinimized();
	bool IsMaximized();
	bool IsFocused();
	bool IsActive();
	bool IsFullscreen();
	bool MsgLoop();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // 메세지 처리 함수
};