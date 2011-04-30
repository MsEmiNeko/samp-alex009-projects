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
#include "hooks.h"
#include "natives.h"
#include "callbacks.h"
#include "defines.h"

void hOnPlayerSetPointOnMap(int,float,float,float);

CHooks*		pHooks = 0;
CSAMP*		pSaMp = 0;
CCallbacks*	pCallbacks = 0;
AMX*		pAMX = 0;

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
	logprintf("Useful functions v " PLUGIN_VERSION);
	logprintf("by 009");
	// callbacks init
	pCallbacks = new CCallbacks();
	logprintf("callbacks initialized");
	// opspom
	pHooks->TargetAdminTeleportTo((unsigned long)hOnPlayerSetPointOnMap);
	// complete
	logprintf("loaded");
	logprintf("================");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf("================");
	logprintf("Useful functions v " PLUGIN_VERSION);
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

// OnPlayerSetPointOnMap function
void hOnPlayerSetPointOnMap(int playerid,float x,float y,float z)
{
	pCallbacks->OnPlayerSetPointOnMap(playerid,x,y,z);
}