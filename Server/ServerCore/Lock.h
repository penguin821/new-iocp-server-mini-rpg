#pragma once
#include "Types.h"

/*
여러 종류의 락 만들거임
32비트 플레그로 만들어서 상위16w 하위16r
[WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
W = WriteFlag (락 소유자 쓰레드 ID)
R = ReadFlag (공유 중인 락 갯수)
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
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();

private:
	Atomic<uint32> m_lockFlag = EMPTY_FLAG;
	uint16 m_writeCount = 0;
};

