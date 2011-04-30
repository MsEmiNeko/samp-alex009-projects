/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// head
#include "SAMP/CSAMP.h"
#include "main.h"
#include "CNPC.h"
#include "hooks.h"
#include "natives.h"
#include "callbacks.h"
#include "defines.h"
#include "threads.h"
#include "os.h"

CNPC*		pNPC[MAX_NPCS];
CHooks*		pHooks = NULL;
CSAMP*		pSaMp = NULL;
CCallbacks*	pCallbacks = NULL;
char		VisualDeath = 1;
int			WeaponReload[MAX_PLAYERS];
AMX*		pAMX;

THREAD_IDENTIFY(NPCSyncThreadHandle);
THREAD_IDENTIFY(NPCDamageThreadHandle);
THREAD_IDENTIFY(ReloadThreadHandle);

float GetZCoord(float x,float y)
{
	int idx;
	cell* result = NULL;
	amx_FindNative(pAMX,"MapAndreas_FindZ_For2DCoord",&idx);
	amx_Push(pAMX,amx_ftoc(y));
	amx_Push(pAMX,amx_ftoc(x));
	amx_Exec(pAMX,result,idx);
	return amx_ctof(result);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	AmxCallPublicFilterScript = (AmxCallPublicFilterScript_t)ppData[PLUGIN_DATA_CALLPUBLIC_FS];
	AmxCallPublicGameMode = (AmxCallPublicGameMode_t)ppData[PLUGIN_DATA_CALLPUBLIC_GM];
	CSampHandle = (CSampHandle_t)ppData[PLUGIN_DATA_CSAMP_HANDLE];
	CConfigHandle = (CConfigHandle_t)ppData[PLUGIN_DATA_CCONFIG_HANDLE];
	RaknetHandle = (RaknetHandle_t)ppData[PLUGIN_DATA_RAKNET_HANDLE];
	AmxLoadFilterScript = (AmxLoadFilterScript_t)ppData[PLUGIN_DATA_LOAD_FILTERSCRIPT];
	AmxUnloadFilterScript = (AmxUnloadFilterScript_t)ppData[PLUGIN_DATA_UNLOAD_FILTERSCRIPT];

	// hooks load
	pHooks = new CHooks(reinterpret_cast<unsigned long>(ppData[PLUGIN_DATA_CSAMP_HANDLE]));
	// plugin load
	logprintf("================");
	logprintf("Controllable NPC v " PLUGIN_VERSION);
	logprintf("by 009");
	// callbacks init
	pCallbacks = new CCallbacks(pHooks->GetMutex());
	logprintf("callbacks initialized");
	// threads init
	THREAD_RESULT(Thread);
	CREATE_THREAD(NPCSyncThreadHandle,NPCSyncThread,Thread);
	CREATE_THREAD(NPCDamageThreadHandle,NPCDamageThread,Thread);
	CREATE_THREAD(ReloadThreadHandle,ReloadThread,Thread);
	logprintf("threads initialized");	
	// complete
	logprintf("loaded");
	logprintf("================");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("================");
	logprintf("Controllable NPC v " PLUGIN_VERSION);
	logprintf("by 009");
	logprintf("unloaded");
	logprintf("================");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	pAMX = amx;
	// link samp pointer
	pSaMp = (CSAMP*)CSampHandle();
	// natives
	NativesOnAMXLoad(amx);
	pCallbacks->CallbacksOnAMXLoad(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	pCallbacks->CallbacksOnAMXUnLoad(amx);
	return AMX_ERR_NONE;
}