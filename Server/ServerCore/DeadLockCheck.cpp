#include "pch.h"
#include "DeadLockCheck.h"

void DeadLockCheck::PushLock(const char* name)
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

void DeadLockCheck::PopLock(const char* name)
{
	LockGuard guard(m_lock);
	
	if (m_lockStack.empty())
		CRASH("MULTIPLE_UNLOCK");

	int32 lockID = m_nameToID[name];
	if (m_lockStack.top() != lockID)
		CRASH("INVALID_UNLOCK");

	m_lockStack.pop();
}

void DeadLockCheck::CheckCycle()
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

void DeadLockCheck::DFS(int32 here)
{
	if (m_discoveredOrder[here] != -1)
		return;

	m_discoveredOrder[here] = m_discoveredCount++;

	// 모든 인접한 정점을 순회한다
	auto findit = m_lockHistory.find(here);
	if (findit == m_lockHistory.end())
	{
		m_finished[here] = true;
		return;
	}

	set<int32>& nextSet = findit->second;
	for (int32 there : nextSet)
	{
		// 아직 방문한 적이 없다면 방문한다.
		if (m_discoveredOrder[there] == -1)
		{
			m_parent[there] = here;
			DFS(there);
			continue;
		}

		// 방문한 적이 있는데
		// here가 there보다 먼저 발견되었다면
		// there은 here의 후손이다 (순방향 간선)
		if (m_discoveredOrder[here] < m_discoveredOrder[there])
			continue;

		// 순방향 아니고, DFS(there) 아직 종료 안됐으면
		// there는 here의 선조다 (역방향 간선)
		if (m_finished[there] == false)
		{
			printf("% s -> % s\n", m_IdToName[here], m_IdToName[there]);
			int32 now = here;

			while (true)
			{
				printf("% s -> % s\n", m_IdToName[m_parent[now]], m_IdToName[now]);
				now = m_parent[now];
				if (now == there)
					break;
			}
			CRASH("DEADLOCK");
		}
	}
	m_finished[here] = true;
}
