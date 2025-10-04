#include "pch.h"
#include "ThreadManager.h"

CoreGlobal Core;

void ThreadMain()
{
    while (true)
    {
        cout << "thread : " << LThreadID << endl;
        this_thread::sleep_for(1s);
    }
}

int main()
{
    for (int32 i = 0; i < 5; i++)
    {
        g_ThreadManager->Launch(ThreadMain);
    }

    g_ThreadManager->Join();
    // CRASH("test");
    // int32 a=3;
	// ASSERT_CRASH(a!=3);
}