#include "pch.h"
#include "DeadLockProfiler.h"

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard guard(m_lock);

	// 아이디를 찾거나 발급
	int32 lockID = 0;
	auto findit = m_nameToID.find(name);
	if (findit == m_nameToID.end())
	{
		lockID = static_cast<int32>(m_nameToID.size()); // 아이디 발급
		m_nameToID[name] = lockID;
		m_IdToName[lockID] = name;
	}
	else
	{
		lockID = findit->second;
	}
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(m_lock);
	
	if (m_lockStack.empty())
		CRASH("MULTIPLE_UNLOCK");

	int32 lockID = m_nameToID[name];
	if (m_lockStack.top() != lockID)
		CRASH("INVALID_UNLOCK");

	m_lockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const int32 lockCount = static_cast<int32>(m_nameToID.size());
	m_discoveredOrder = vector<int32>(lockCount, -1);
	m_discoveredCount = 0;
	m_finished = vector<bool>(lockCount, false);
	m_parent = vector<int32>(lockCount, -1);

	for (int32 lockId = 0; lockId < lockCount; lockId++)
		DFS(lockId);

	// 연산 끝났으면 초기화
	m_discoveredOrder.clear();
	m_finished.clear();
	m_parent.clear();
}

void DeadLockProfiler::DFS(int32 index)
{

}
