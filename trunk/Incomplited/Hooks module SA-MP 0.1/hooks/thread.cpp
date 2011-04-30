/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt 
 */

#include "os.h"

MUTEX_IDENTIFY(MultiThreadMutex);

// call hook func
bool Unlock(void *address, int len)
{
	#ifdef WIN32
		DWORD
			oldp;
		// Shut up the warnings :D
		return !!VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &oldp);
	#else
		return !mprotect((void*)(((int)address / PAGESIZE) * PAGESIZE), PAGESIZE, PROT_WRITE | PROT_READ | PROT_EXEC);
	#endif
}

void CallHook(DWORD from, DWORD to) 
{
	if(Unlock((void*)from,5))
	{
		DWORD disp = to - (from + 5);
		*(BYTE *)(from) = 0xE8;
		*(DWORD *)(from + 1) = (DWORD)disp;
	}
}

void SAMP_ThreadComplete()
{
	// free mutex
	MUTEX_EXIT(MultiThreadMutex);
	// sleep
	SLEEP(5);
	// close mutex
	MUTEX_ENTER(MultiThreadMutex);
}

MUTEX_IDENTIFY(MultiThreadInit(unsigned long addr1,unsigned long addr2))
{
	// create mutex
	CREATE_MUTEX(MultiThreadMutex);
	// set hook
	CallHook(addr1,(unsigned long)SAMP_ThreadComplete);
	for(unsigned int i = addr1 + 5;i < addr2;i++) *(unsigned char*)(i) = 0x90;
	// result
	return MultiThreadMutex;
}