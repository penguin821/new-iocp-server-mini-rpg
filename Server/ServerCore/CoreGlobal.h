#pragma once
// 전역으로 사용할 매니저류 클래스들 모음
extern class ThreadManager* g_ThreadManager;

class CoreGlobal // 매니저 생성 순서 관리
{
public:
	CoreGlobal();
	~CoreGlobal();
};