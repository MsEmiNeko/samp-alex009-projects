#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

//----------------------------------------------------------

// logprintf
typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
// callpublicfs
typedef void (*AmxCallPublicFilterScript_t)(char* szFunctionName);
AmxCallPublicFilterScript_t AmxCallPublicFilterScript;
// callpublicgm
typedef void (*AmxCallPublicGameMode_t)(char* szFunctionName);
AmxCallPublicGameMode_t AmxCallPublicGameMode;
// csamphandle
typedef int (*CSampHandle_t) ();
CSampHandle_t CSampHandle;
// cconfighandle
typedef int (*CConfigHandle_t) ();
CConfigHandle_t CConfigHandle;
// raknethandle
typedef int (*RaknetHandle_t) ();
RaknetHandle_t RaknetHandle;
// loadfs
typedef void (*AmxLoadFilterScript_t)(char* szFileName,int unknown);
AmxLoadFilterScript_t AmxLoadFilterScript;
// unloadfs
typedef void (*AmxUnloadFilterScript_t)(char* szFileName);
AmxUnloadFilterScript_t AmxUnloadFilterScript;

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
	AmxCallPublicFilterScript = (AmxCallPublicFilterScript_t)ppData[PLUGIN_DATA_CALLPUBLIC_FS];
	AmxCallPublicGameMode = (AmxCallPublicGameMode_t)ppData[PLUGIN_DATA_CALLPUBLIC_GM];
	CSampHandle = (CSampHandle_t)ppData[PLUGIN_DATA_CSAMP_HANDLE];
	CConfigHandle = (CConfigHandle_t)ppData[PLUGIN_DATA_CCONFIG_HANDLE];
	RaknetHandle = (RaknetHandle_t)ppData[PLUGIN_DATA_RAKNET_HANDLE];
	AmxLoadFilterScript = (AmxLoadFilterScript_t)ppData[PLUGIN_DATA_LOAD_FILTERSCRIPT];
	AmxUnloadFilterScript = (AmxUnloadFilterScript_t)ppData[PLUGIN_DATA_UNLOAD_FILTERSCRIPT];

	logprintf("Load Plugin");
	logprintf("CSAMP: address 0x%X",CSampHandle());
	logprintf("CConfig: address 0x%X",CConfigHandle());
	logprintf("Raknet: address 0x%X",RaknetHandle());
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
}

AMX_NATIVE_INFO Natives[ ] =
{
	{ 0,					0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	logprintf("Load AMX: address 0x%X",amx);
	logprintf("CSAMP: address 0x%X",CSampHandle());
	logprintf("CConfig: address 0x%X",CConfigHandle());
	logprintf("Raknet: address 0x%X",RaknetHandle());
	return amx_Register( amx, Natives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	logprintf("Unload AMX: address 0x%X",amx);
	logprintf("CSAMP: address 0x%X",CSampHandle());
	logprintf("CConfig: address 0x%X",CConfigHandle());
	logprintf("Raknet: address 0x%X",RaknetHandle());
	return AMX_ERR_NONE;
}
