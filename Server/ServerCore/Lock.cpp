#include "pch.h"
#include "Lock.h"
#include "CoreTLS.h"

void Lock::WriteLock()
{
	// 동일한 쓰레드가 소유하고 있다면 재귀락해도 무조건 성공
	const uint32 lockThreadID = (m_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (LThreadID == lockThreadID)
	{
		m_writeCount++;
		return;
	}

	// 아무도 소유하고 있지 않으면 경합해서 소유권 획득
	const int64 beginTick = ::GetTickCount64();
	const uint32 desired = ((LThreadID << 16) & WRITE_THREAD_MASK);
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = EMPTY_FLAG;
			if (m_lockFlag.compare_exchange_strong(OUT expected, desired))
			{
				m_writeCount++;
				return;
			}
		}
	}

	if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		CRASH("LOCK_TIMEOUT");

	this_thread::yield();
}

void Lock::WriteUnlock()
{

}

void Lock::ReadLock()
{

}

void Lock::ReadUnlock()
{

}
