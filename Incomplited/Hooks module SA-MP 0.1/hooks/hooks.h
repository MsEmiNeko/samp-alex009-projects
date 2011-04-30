/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "functions.h"
#include "os.h"

#define VERSION		"0.1"

// class
class CHooks
{
public:
	// functions
	CHooks(unsigned long s_version);
	~CHooks();

	unsigned long Search_ClientConnect();
	unsigned long Search_ClientDisconnect();
	unsigned long Search_ClientSpawn();
	unsigned long Search_ClientDeath();
	unsigned long Search_SetPlaybackDir();
	void Search_ThreadAddresses(unsigned long* addr1,unsigned long* addr2);

	void ClientConnect(void* players,int id,char* name,int npc_flag);
	void ClientDisconnect(void* players,int id,int reason);
	void ClientSpawn(void* player);
	void ClientDeath(void* player,int reason,int killerid);
	void SetPlaybackDir(char* string);
	void DeleteLogFile();
	int GetLogFileLength();
	void DisableBadCharsCheck();
	void DisableChangeNameLogging();
	void TargetAdminTeleportTo(unsigned long function);

	MUTEX_IDENTIFY(GetMutex());
	
	// vars
	unsigned int server_version;

	MUTEX_IDENTIFY(ThreadMutex);
};