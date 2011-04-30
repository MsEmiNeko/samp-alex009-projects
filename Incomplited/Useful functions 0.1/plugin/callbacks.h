/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 *	Description: callbacks
 */

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

class CCallbacks
{
public:
	CCallbacks() ;
	~CCallbacks();

	void OnPlayerSetPointOnMap(int playerid,float x,float y,float z);

	void CallbacksOnAMXLoad(AMX* amx);
	void CallbacksOnAMXUnLoad(AMX* amx);

	// vars
	AMX* SampObjects[17];
};