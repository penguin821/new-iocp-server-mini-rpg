#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"

ThreadManager* g_ThreadManager = nullptr;

class CoreGlobal // 概聪历 积己 鉴辑 包府
{
public:
	CoreGlobal()
	{
		g_ThreadManager = new ThreadManager();
	}

	~CoreGlobal()
	{
		delete g_ThreadManager;
	}
} g_CoreGlobal;