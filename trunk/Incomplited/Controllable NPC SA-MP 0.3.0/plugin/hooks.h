/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "os.h"

// class
class CHooks
{
public:
	// functions
	CHooks(unsigned long s_version);
	~CHooks();

	void ClientConnect(void* players,int id,char* name,int npc_flag);
	void ClientDisconnect(void* players,int id,int reason);
	void ClientSpawn(void* player);
	void ClientDeath(void* player,int reason,int killerid);

	MUTEX_IDENTIFY(GetMutex());
	
	// vars
	HMODULE	mHooks;
};