/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// plugin
#include "os.h"
// core
#include "math.h"
#include <stdio.h>
// plugin
#include "main.h"
#include "natives.h"
#include "callbacks.h"
#include "hooks.h"
// samp data
#include "samp address.h"
#include "samp defines.h"
#include "samp structs.h"

// main vars
extern DWORD		c_samp;
extern DWORD		c_players;
extern DWORD		CSampPointer;

int		SampVersion;

AMX*	gAMX;


typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;

void **ppPluginData;
extern void *pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("================");
	logprintf("Useful functions v " PLUGIN_VERSION);
	logprintf("by 009");
	logprintf("http://samp.club42.ru");

	BYTE testval1 = *(BYTE*)(TEST_ADDR_1);
	BYTE testval2 = *(BYTE*)(TEST_ADDR_2);
	if( (testval1 == R4_DATA_1) && (testval2 == R4_DATA_2) )
	{
		CSampPointer = R4_C_SAMP_STRUCTURE;
		SampVersion = SAMP_VERSION_034;
		logprintf("Server R4 detected");
	}
	if( (testval1 == R51_DATA_1) && (testval2 == R51_DATA_2) )
	{
		CSampPointer = R51_C_SAMP_STRUCTURE;
		SampVersion = SAMP_VERSION_0351;
		logprintf("Server R5-1 detected");
	}
	if( (testval1 == R52_DATA_1) && (testval2 == R52_DATA_2) )
	{
		CSampPointer = R52_C_SAMP_STRUCTURE;
		SampVersion = SAMP_VERSION_0352;
		logprintf("Server R5-2 detected");
	}
	if( (testval1 == R6_DATA_1) && (testval2 == R6_DATA_2) )
	{
		CSampPointer = R6_C_SAMP_STRUCTURE;
		SampVersion = SAMP_VERSION_036;
		logprintf("Server R6 detected");
	}
	if( (testval1 == R7_DATA_1) && (testval2 == R7_DATA_2) )
	{
		CSampPointer = R7_C_SAMP_STRUCTURE;
		SampVersion = SAMP_VERSION_037;
		logprintf("Server R7 detected");
	}
	logprintf("================");
	// hooks!
	HooksInstall(SampVersion);
	// unlock all memory :=P
	DWORD oldp;
    VirtualProtect((LPVOID)(0x401000),(0x4BEB20 - 0x401000), PAGE_EXECUTE_READWRITE, &oldp);
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
	CallbacksOnAMXLoad(amx);
	NativesOnAMXLoad(amx);
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}
