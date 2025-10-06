#pragma once

#define OUT

#define USE_MANY_LOCKS(count)	Lock locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(locks[idx]);
#define READ_LOCK				READ_LOCK_IDX(0)
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(locks[idx]);
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

// 코드에 의도적으로 엉뚱한 명령어를 통해 크래시 발생시키면
// 컴파일 단계에서 알아서 잡혀버릴 수 있으므로 의도적 크래시 발생 장치
#define CRASH(cause)								\
{													\
	uint32* crash = nullptr;						\
	__analysis_assume(crash != nullptr);			\
	*crash = 0xDEADBEEF;							\
}

// 특정 조건이 거짓일때 강제로 크래시

#define ASSERT_CRASH(expr)						\
{												\
	if (!(expr))								\
	{											\
		CRASH("ASSERT_CRASH");					\
		__analysis_assume(expr);				\
	}											\
}												\
