#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockCheck.h"

ThreadManager* g_ThreadManager = nullptr;
DeadLockCheck* g_DeadLockCheck = nullptr;

class CoreGlobal // 概聪历 积己 鉴辑 包府
{
public:
	CoreGlobal()
	{
		g_ThreadManager = new ThreadManager();
		g_DeadLockCheck = new DeadLockCheck();
	}

	~CoreGlobal()
	{
		delete g_ThreadManager;
		delete g_DeadLockCheck;
	}
} g_CoreGlobal;