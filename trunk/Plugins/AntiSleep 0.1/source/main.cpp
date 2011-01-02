/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// core
#include "math.h"
#include <stdio.h>
// plugin
#include "main.h"
#include "natives.h"
#include "config.h"
#include "os.h"

AMX*	gAMX;
int		LastUpdate = -1;
int		max_sleep_time;
int		action;
char	creation_file[MAX_CREATION_FILE_LEN];

typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;

void **ppPluginData;
extern void *pAMXFunctions;

THREAD_IDENTIFY(AntiSleepThreadHandle);

THREAD_START(AntiSleepThread){
	while(true)
	{
		SLEEP(10);
		if(LastUpdate == -1) continue;

		if((GetTickCount() - LastUpdate) > max_sleep_time)
		{
			switch(action)
			{
			case ACTION_KILL_PROCESS:
				{
					exit(1);
					break;
				}
			case ACTION_CREATE_FILE:
				{
					FILE* f = fopen(creation_file,"w");
					fclose(f);
					LastUpdate = -1;
					break;
				}
			}
		}
	}
THREAD_END

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("================");
	logprintf("AntiSleep v " PLUGIN_VERSION);
	logprintf("by 009");
	logprintf("http://samp.club42.ru");
	logprintf("================");
	// config
	ReadConfig();
	// thread
	THREAD_RESULT(ThreadId);
	CREATE_THREAD(AntiSleepThreadHandle,AntiSleepThread,ThreadId);
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("================");
	logprintf("Useful functions v " PLUGIN_VERSION);
	logprintf("by 009");
	logprintf("http://samp.club42.ru");
	logprintf("================");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	gAMX = amx;
	NativesOnAMXLoad(amx);
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}
