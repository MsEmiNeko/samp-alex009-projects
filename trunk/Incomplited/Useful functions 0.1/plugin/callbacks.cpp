/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 *	Description: callbacks
 */

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// plugin
#include "callbacks.h"

CCallbacks::CCallbacks() 
{
	for(int i = 0;i < 17;i++) SampObjects[i] = 0;
}

CCallbacks::~CCallbacks() {}

void CCallbacks::OnPlayerSetPointOnMap(int playerid,float x,float y,float z)
{
	int index;
	cell ret;

	for(int i = 0;i < 17;i++)
	{
		if(SampObjects[i] != 0)
		{
			if(!amx_FindPublic(SampObjects[i],"OnPlayerSetPointOnMap",&index))
			{
				amx_Push(SampObjects[i],amx_ftoc(z));
				amx_Push(SampObjects[i],amx_ftoc(y));
				amx_Push(SampObjects[i],amx_ftoc(x));
				amx_Push(SampObjects[i],(cell)playerid);
				amx_Exec(SampObjects[i], &ret, index);
			}
		}
	}
	return;
}

void CCallbacks::CallbacksOnAMXLoad(AMX* amx)
{
	for(int i = 0;i < 17;i++)
	{
		if(SampObjects[i] == 0)
		{
			SampObjects[i] = amx;
			break;
		}
	}
}

void CCallbacks::CallbacksOnAMXUnLoad(AMX* amx)
{
	for(int i = 0;i < 17;i++)
	{
		if(SampObjects[i] == amx)
		{
			SampObjects[i] = 0;
			break;
		}
	}
}