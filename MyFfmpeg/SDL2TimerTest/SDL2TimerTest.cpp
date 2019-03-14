// SDL2TimerTest.cpp : Defines the entry point for the console application.
//

/*
1. Uint32 SDL_GetTicks() : ��ȡ��SDL���ʼ��(��ʱ��ģ���ʼ��)��ʼ����ǰ������ʱ��(ms);
2. Uint64 SDL_GetPerformanceCounter() : ��ȡ�߾��ȶ�ʱ���ĵ�ǰֵ;
3. Uint64 SDL_GetPerformanceFrequency() : ��ȡ�߽��ȶ�ʱ��Ƶ��(ÿ���Ӹ߾��ȶ�ʱ���Ĵ���);
4. void SDL_Delay(Uint32 ms) : �ӳٺ���;
5. SDL_TimerID SDL_AddTimer(Uint32 interval, SDL_TimerCallback callback, void *param) :
	��ϵͳ��������һ����ʱ��.
	SDL_TimerID�� ��ʱ����ID, ����ֵΪNULL����ʾ����ʧ��;
	interval:  ��ʱ���;
	callback: �ص�����, ��ʱʱ�䵽�����ô˺���;
	��ע: typedef Uint32(*SDL_TimerCallback)(Uint32 interval, void *param) :
	�ú�������ֵΪ�´λ��ѵ�ʱ��, ������0, �򲻻��ٻ���.

6. SDL_bool SDL_RemoveTimer(SDL_TimerID id) : ɾ������id�Ķ�ʱ��, ����ֵ��ʾ�Ƿ�ɾ���ɹ�.
*/

#include "stdafx.h"
#include "SDL.h"

void testfunc()
{
}

Uint32 callback(Uint32 interval, void *param)
{
	SDL_Log("current time: %d ms.\n", SDL_GetTicks());
	return interval;
}

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Uint32 start32;
	Uint32 loop_count = 50000;
	Uint64 start, now;

	if (SDL_Init(SDL_INIT_TIMER) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL Timer SubSystem: %s\n", SDL_GetError());
	}

	start32 = SDL_GetTicks();
	start = SDL_GetPerformanceCounter();
	for (Uint32 i = 0; i < loop_count; ++i)
	{
		testfunc();
	}
	SDL_Log("%d times function call take %d ms\n", loop_count, SDL_GetTicks() - start32);
	now = SDL_GetPerformanceCounter();
	SDL_Log("%d times function call take %f ms \n", loop_count, (double)(now - start) * 1000 / SDL_GetPerformanceFrequency());

	SDL_TimerID timer = SDL_AddTimer(100, callback, NULL);
	if (NULL == timer)
	{
		SDL_Log("add timer fail: %s\n", SDL_GetError());
	}

	Uint32 test = 100;
	while (test--)
	{
		SDL_Delay(100);
	}

	if (SDL_TRUE != SDL_RemoveTimer(timer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Remove timer fail: %s\n", SDL_GetError());
	}
	return 0;
}

