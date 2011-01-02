/*
*	Created:			09.04.10
*	Author:				009
*	Last Modifed:		-
*/

#ifndef WIN32
	#include "sys/time.h"
	timeval start_time;
	timeval now_time;

	void TickCountLoad()
	{
		// get tick count ex
		gettimeofday(&start_time, 0);
	}

	int GetTickCount()
	{
		gettimeofday(&now_time,0);
		return (now_time.tv_usec - start_time.tv_usec) / 1000 + 1000 * (now_time.tv_sec - start_time.tv_sec);
	}
#endif