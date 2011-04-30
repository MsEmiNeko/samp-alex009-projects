/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

// SDK
#include "SDK/SDK.h"
// head
#include "main.h"
#include "natives.h"

EXPORT bool InitModule(char * szModuleName)
{
	LogPrintf("================");
	LogPrintf("Nodes reader v " PLUGIN_VERSION);
	LogPrintf("by 009");
	LogPrintf("loaded");
	LogPrintf("================");
	return true;
}

EXPORT void ScriptLoad(HSQUIRRELVM pVM)
{
	// natives
	NativesScriptLoad(pVM);
}

EXPORT void ScriptUnload(HSQUIRRELVM pVM)
{

}

EXPORT void Pulse()
{
	
}