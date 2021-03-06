#include"stdafx.h"
#include"Engine.h"

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // 메모리 누수 검출용

	RG2R->Init(); // App의 초기화 함수 실행, 싱글톤이기 때문에 객체가 여기서 생성됨
	RG2R->MainLoop(); // 메인루프 시작
	RG2R->Release(); // 종료

	return 0; // 오류 없이 프로그램 종료
}