#pragma once
#include <stack>
#include <map>
#include <vector>

// Write 락 언락 시작할때 넣어서 디버그 모드면 이 클래스에 정보를 전달해
// 이 클래스가 그래프 알고리즘을 그려준 다음 락 싸이클이 일어나는지 판단
class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle(); // 데드락 판별 알고리즘

private:
	void DFS(int32 index);

private:
	unordered_map<const char*, int32>	m_nameToID;
	unordered_map<int32, const char*>	m_IdToName;
	stack<int32>						m_lockStack; // 락 실행순서 저장
	map<int32, set<int32>>				m_lockHistory;
	// 어떤락이 어떤락을 잡았는지(간선)

	Mutex m_lock;

private:
	vector<int32> m_discoveredOrder; // 노드가 발견된 순서 기록
	int32 m_discoveredCount = 0;
	vector<bool> m_finished; // DFS(i)가 종료 되었는지 여부
	vector<int32> m_parent; // 발견된 노드가 진행되면서 부모님이 누군지
};