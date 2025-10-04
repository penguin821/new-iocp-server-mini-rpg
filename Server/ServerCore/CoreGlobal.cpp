#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"

ThreadManager* g_ThreadManager = nullptr;

CoreGlobal::CoreGlobal()
{
	g_ThreadManager = new ThreadManager();
}

CoreGlobal::~CoreGlobal()
{
	delete g_ThreadManager;
}
