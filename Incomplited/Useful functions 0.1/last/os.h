/*
*	Created:			09.04.10
*	Author:				009
*	Last Modifed:		-
*/

#define POINTER_TO_MEMBER(m,n,o) temp = n, m = *(o *)&temp

#ifdef WIN32
	#include "windows.h"
#else
	#include "unistd.h"
	// types
	#define DWORD	unsigned long
	#define BOOL	int
	#define BYTE	unsigned char
	#define WORD	unsigned short
	#define FLOAT	float
	int GetTickCount();
	void TickCountLoad();
#endif
