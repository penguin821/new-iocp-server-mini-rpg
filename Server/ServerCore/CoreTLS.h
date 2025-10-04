#pragma once

extern thread_local uint32 LThreadID; // 쓰레드 아이디 직접 1부터 시작해서 기입
// 이렇게 안하면 윈도우에서 쓰레드 아이디가를 아무 숫자 중구난방으로 만듦
