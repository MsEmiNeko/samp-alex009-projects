/*
*	Created:			09.04.10
*	Author:				009
*	Last Modifed:		-
*/

#ifdef WIN32
	#include "windows.h"
	#define THREAD_IDENTIFY(a) HANDLE a
	#define THREAD_RESULT(a) DWORD a
	#define THREAD_START(a) DWORD WINAPI a(LPVOID lpParameter)
	#define THREAD_END return 1;}
	#define CREATE_THREAD(a,b,c) a = CreateThread(NULL,0,b,0,0,&c)
	#define UTILS();
	#define SLEEP(a) Sleep(a)
#else
	#include "pthread.h"
	#include "unistd.h"
	#define THREAD_IDENTIFY(a) pthread_t a
	#define THREAD_RESULT(a) int a
	#define THREAD_START(a) void* a(void* arg)
	#define THREAD_END }
	#define CREATE_THREAD(a,b,c) c = pthread_create(&a,NULL,b,NULL);
	#define UTILS(); TickCountLoad();
	#define SLEEP(a) usleep((a) * 1000)
	// types
	#define DWORD	unsigned long
	#define BOOL	int
	#define BYTE	unsigned char
	#define WORD	unsigned short
	#define FLOAT	float
	int GetTickCount();
	void TickCountLoad();
#endif
