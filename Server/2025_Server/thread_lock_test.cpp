#include "pch.h"
#include "ThreadManager.h"

class TestLock
{
    USE_LOCK;

public:
    int32 TestRead()
    {
        READ_LOCK;

        if (m_queue.empty())
            return -1;

        return m_queue.front();
    }

    void TestPush()
    {
        WRITE_LOCK;

        m_queue.push(rand() % 100);
    }

    void TestPop()
    {
        WRITE_LOCK;

        if (m_queue.empty() == false)
            m_queue.pop();
    }

private:
    queue<int32> m_queue;
};

TestLock testlock;

void ThreadWrite()
{
    while (true)
    {
        testlock.TestPush();
        this_thread::sleep_for(1ms);
        testlock.TestPop();
    }
}

void ThreadRead()
{
    while (true)
    {
        int32 val = testlock.TestRead();
        cout << val << endl;
        this_thread::sleep_for(1ms);
    }
}

int main()
{
    for (int32 i = 0; i < 5; i++)
    {
        g_ThreadManager->Launch(ThreadWrite);
    }

    for (int32 i = 0; i < 5; i++)
    {
        g_ThreadManager->Launch(ThreadRead);
    }

    g_ThreadManager->Join();
}