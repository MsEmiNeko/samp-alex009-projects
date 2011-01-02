/*
*	Created:			08.05.10
*	Author:				009
*	Last Modifed:		-
*	Description:		нативы защиты от зависания сервера
*/

#if defined _antisleep_included
	#endinput
#endif

#define _antisleep_included
#pragma library antisleep

//
//	Defines
//
#define ACTION_KILL_PROCESS		0
#define ACTION_CREATE_FILE		1

//
//	Natives
//
native AntiSleepUpdate();