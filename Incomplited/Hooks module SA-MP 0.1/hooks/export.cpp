/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "hooks.h"

CHooks * pHooks = NULL;

void __stdcall EXPORT_InitializeHooks(unsigned long version)
{
	if(!pHooks) pHooks = new CHooks(version);
}

void __stdcall EXPORT_ClientConnect(void* players,int id,char* name,int npc_flag)
{
	if(pHooks) pHooks->ClientConnect(players,id,name,1);
}

void __stdcall EXPORT_ClientDisconnect(void* players,int id,int reason)
{
	if(pHooks) pHooks->ClientDisconnect(players,id,reason);
}

void __stdcall EXPORT_ClientSpawn(void* player)
{
	if(pHooks) pHooks->ClientSpawn(player);
}

void __stdcall EXPORT_ClientDeath(void* player,int reason,int killerid)
{
	if(pHooks) pHooks->ClientDeath(player,reason,killerid);
}

MUTEX_IDENTIFY(__stdcall EXPORT_GetMutex())
{
	if(pHooks) return pHooks->GetMutex();
	return NULL;
}