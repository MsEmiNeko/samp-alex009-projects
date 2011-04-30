/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include <stdio.h>
#include "hooks.h"

// types
typedef void (__stdcall * typeInitializeHooks)(unsigned long version);
typedef void (__stdcall * typeClientConnect)(void* players,int id,char* name,int npc_flag);
typedef void (__stdcall * typeClientDisconnect)(void* players,int id,int reason);
typedef void (__stdcall * typeClientSpawn)(void* player);
typedef void (__stdcall * typeClientDeath)(void* player,int reason,int killerid);
typedef MUTEX_IDENTIFY( (__stdcall * typeGetMutex)());

// vars
typeInitializeHooks		fInitializeHooks;
typeClientConnect		fClientConnect;
typeClientDisconnect	fClientDisconnect;
typeClientSpawn			fClientSpawn;
typeClientDeath			fClientDeath;
typeGetMutex			fGetMutex;

// class
CHooks::CHooks(unsigned long s_version)
{
	if((mHooks = GetModuleHandle(L"hooks.dll")) == NULL) mHooks = LoadLibrary(L"./plugins/hooks.dll");
	if(mHooks)
	{
		fInitializeHooks	=	reinterpret_cast<typeInitializeHooks>(GetProcAddress(mHooks,	"EXPORT_InitializeHooks"));
		fClientConnect		=	reinterpret_cast<typeClientConnect>(GetProcAddress(mHooks,		"EXPORT_ClientConnect"));
		fClientDisconnect	=	reinterpret_cast<typeClientDisconnect>(GetProcAddress(mHooks,	"EXPORT_ClientDisconnect"));
		fClientSpawn		=	reinterpret_cast<typeClientSpawn>(GetProcAddress(mHooks,		"EXPORT_ClientSpawn"));
		fClientDeath		=	reinterpret_cast<typeClientDeath>(GetProcAddress(mHooks,		"EXPORT_ClientDeath"));
		fGetMutex			=	reinterpret_cast<typeGetMutex>(GetProcAddress(mHooks,			"EXPORT_GetMutex"));

		if(fInitializeHooks) fInitializeHooks(s_version);
	}
}

CHooks::~CHooks()
{

}

void CHooks::ClientConnect(void* players,int id,char* name,int npc_flag)
{
	if(fClientConnect) fClientConnect(players,id,name,npc_flag);
}

void CHooks::ClientDisconnect(void* players,int id,int reason)
{
	if(fClientDisconnect) fClientDisconnect(players,id,reason);
}

void CHooks::ClientSpawn(void* player)
{
	if(fClientSpawn) fClientSpawn(player);
}

void CHooks::ClientDeath(void* player,int reason,int killerid)
{
	if(fClientDeath) fClientDeath(player,reason,killerid);
}

MUTEX_IDENTIFY(CHooks::GetMutex())
{
	if(fGetMutex) return fGetMutex();
	return NULL;
}