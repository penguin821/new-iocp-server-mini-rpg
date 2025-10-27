#pragma once
#include "Types.h"

/*
여러 종류의 락 만들거임
32비트 플레그로 만들어서 상위16w 하위16r
[WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
W = WriteFlag (락 소유자 쓰레드 ID)
R = ReadFlag (공유 중인 락 갯수)

이미 write lock 중인 상태에서 write lock 추가 가능
이미 write lock 중인 상태에서 read lock 변경 가능
이미 read lock 중인 상태에서 write lock 변경 불가 (공유 중일 수 있으므로)
*/

class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};

public:
	void WriteLock(const char* name);
	void WriteUnlock(const char* name);
	void ReadLock(const char* name);
	void ReadUnlock(const char* name);

private:
	Atomic<uint32> m_lockFlag = EMPTY_FLAG;
	uint16 m_writeCount = 0;
};

class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock, const char* name) : m_lock(lock), m_name(name) { m_lock.ReadLock(name); }
	~ReadLockGuard() { m_lock.ReadUnlock(m_name); }

private:
	Lock& m_lock;
	const char* m_name;
};

class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock, const char* name) : m_lock(lock) { m_lock.WriteLock(name); }
	~WriteLockGuard() { m_lock.WriteUnlock(m_name); }

private:
	Lock& m_lock;
	const char* m_name;
};

