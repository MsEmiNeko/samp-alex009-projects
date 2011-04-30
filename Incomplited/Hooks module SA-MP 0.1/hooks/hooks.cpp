/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include <stdio.h>

#include "functions_data.h"
#include "os.h"
#include "hooks.h"
#include "memsec.h"
#include "thread.h"
#include "addresses.h"

// vars
f_ClientConnect_1	pClientConnectOld;
f_ClientConnect_2	pClientConnect;
f_ClientConnect_3	pClientConnectNew;
f_ClientDisconnect	pClientDisconnect;
f_SpawnForWorld		pClientSpawn;
f_DeathForWorld		pClientDeath;
f_TeleportFunction	pTeleport;
unsigned long Code_Base;
unsigned long Code_Size;
unsigned long rData_Base;
unsigned long rData_Size;
/*
// add func
void RPC_Teleport(void * packet)
{
	void * packet_data = packet;
	int packet_len = *(unsigned long*)(packet + 4);


}
*/
// class
CHooks::CHooks(unsigned long s_version)
{
	// server version
	s_version -= SAMP_IMAGE_BASE;
	if(s_version == SAMP_02X) server_version = 0x2300;
	else if(s_version == SAMP_03aR4) server_version = 0x3140;
	else if(s_version == SAMP_03aR51) server_version = 0x3151;
	else if(s_version == SAMP_03aR52) server_version = 0x3152;
	else if(s_version == SAMP_03aR6) server_version = 0x3160;
	else if(s_version == SAMP_03aR7) server_version = 0x3170;
	else if(s_version == SAMP_03aR8) server_version = 0x3180;
	else if(s_version == SAMP_03bR1) server_version = 0x3210;
	else if(s_version == SAMP_03bR2) server_version = 0x3220;
	else if(s_version == SAMP_03cR1) server_version = 0x3310;
	else server_version = 0x9999;
	// sections data
	GetSectionDataByName(".text",&Code_Base,&Code_Size);
	GetSectionDataByName(".rdata",&rData_Base,&rData_Size);
	// find functions
	void *temp;
	// connect
	unsigned long connect = Search_ClientConnect();
	POINTER_TO_MEMBER(pClientConnectOld,(void *)(connect),f_ClientConnect_1);
	POINTER_TO_MEMBER(pClientConnect,(void *)(connect),f_ClientConnect_2);
	POINTER_TO_MEMBER(pClientConnectNew,(void *)(connect),f_ClientConnect_3);
	// disconnect
	POINTER_TO_MEMBER(pClientDisconnect,(void *)(Search_ClientDisconnect()),f_ClientDisconnect);
	// spawn
	POINTER_TO_MEMBER(pClientSpawn,(void *)(Search_ClientSpawn()),f_SpawnForWorld);
	// death
	POINTER_TO_MEMBER(pClientDeath,(void *)(Search_ClientDeath()),f_DeathForWorld);
	// thread addresses find
	unsigned long addr[2];
	Search_ThreadAddresses(&addr[0],&addr[1]);
	ThreadMutex = MultiThreadInit(addr[0],addr[1]);
	// write info
	printf("\n_____________________________________\n");
	printf("Hooks module for SA-MP\n");
	printf("by 009\n");
	printf("\n");
	printf("Server version: ");
	// show version
	if(s_version == SAMP_02X)			printf("0.2X");
	else if(s_version == SAMP_03aR4)	printf("0.3a R4");
	else if(s_version == SAMP_03aR51)	printf("0.3a R5-1");
	else if(s_version == SAMP_03aR52)	printf("0.3a R5-2");
	else if(s_version == SAMP_03aR6)	printf("0.3a R6");
	else if(s_version == SAMP_03aR7)	printf("0.3a R7");
	else if(s_version == SAMP_03aR8)	printf("0.3a R8");
	else if(s_version == SAMP_03bR1)	printf("0.3b R1");
	else if(s_version == SAMP_03bR2)	printf("0.3b R2");
	else if(s_version == SAMP_03cR1)	printf("0.3c R1");
	else
	{
		printf("unknown");
		printf("\nModule can work unstable with unknown server version");
	}
	printf("\n");
	// module version and comp list
	printf("Module version: " VERSION "\n");
	printf("_____________________________________\n\n");
}

CHooks::~CHooks()
{

}

void CHooks::ClientConnect(void* players,int id,char* name,int npc_flag)
{
	if(server_version > 0x3200)
	{
		if(pClientConnectNew == NULL) return;

		char* serial = new char[40];
		serial = "";

		CALL_ARGS(players,pClientConnectNew,id _ name _ serial _ npc_flag);
	}
	else if(server_version > 0x3100)
	{
		if(pClientConnect == NULL) return;

		CALL_ARGS(players,pClientConnect,id _ name _ npc_flag);
	}
	else
	{
		if(pClientConnectOld == NULL) return;

		CALL_ARGS(players,pClientConnectOld,id _ name);
	}
}

void CHooks::ClientDisconnect(void* players,int id,int reason)
{
	if(pClientDisconnect == NULL) return;

	CALL_ARGS(players,pClientDisconnect,id _ 1);
}

void CHooks::ClientSpawn(void* player)
{
	if(pClientSpawn == NULL) return;

	CALL_NOARGS(player,pClientSpawn);
}

void CHooks::ClientDeath(void* player,int reason,int killerid)
{
	if(pClientDeath == NULL) return;

	CALL_ARGS(player,pClientDeath,reason _ killerid);
}

MUTEX_IDENTIFY(CHooks::GetMutex())
{
	return ThreadMutex;
}

void CHooks::SetPlaybackDir(char* string)
{
	if(pPlaybackDir == NULL) return;

	strcpy((char*)(pPlaybackDir),string);
}

void CHooks::DeleteLogFile()
{
	if(pLogFile == NULL) return;

	FILE * f = pLogFile;

	fclose(f);

	remove("server_log.txt");

	pLogFile = (DWORD)(fopen("server_log.txt","a"));
}

int CHooks::GetLogFileLength()
{
	if(pLogFile == NULL) return -1;

	FILE * f = pLogFile;

	long curpos = ftell(f);
	fseek(f, 0, SEEK_END);

	long result = ftell(f);
	fseek(f, curpos, SEEK_SET);

	return static_cast<int>(result);
}

void CHooks::DisableBadCharsCheck()
{
	if(pBadName == NULL) return;

	*(BYTE*)(pBadName) = 0x00;
}

void CHooks::DisableChangeNameLogging()
{
	if(pChangeName == NULL) return;

	for(int i = 0x0;i < 0x5;i++) *(BYTE*)(pChangeName + i) = 0x90;
}

void CHooks::TargetAdminTeleportTo(unsigned long function)
{	
	void *temp;
	POINTER_TO_MEMBER(pTeleport,(void *)(function),f_TeleportFunction);
}

unsigned long CHooks::Search_ClientConnect()
{
	// vars
	unsigned long result = 0;
	unsigned long string_addr;
	int idx;
	int len = strlen(pc_string) - 1;
	unsigned char bytes[4];
	unsigned long max;
	// start search string addr
	max = (rData_Base + rData_Size);
	for(string_addr = max;string_addr > rData_Base;string_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(string_addr + idx > max) 
			{
				if(result == 1) result = 0;
				break;
			}
			if(*(char*)(string_addr + idx) == pc_string[idx]) result = 1;
			else 
			{
				if(result == 1) result = 0;
				break;
			}
		}
		if(result == 1) break;
	}
	if(result != 1) return 0; // error
	// string addr founded, parse address to bytes	
	bytes[0] = (unsigned char)(string_addr);
	bytes[1] = (unsigned char)(string_addr >> 8);
	bytes[2] = (unsigned char)(string_addr >> 16);
	bytes[3] = (unsigned char)(string_addr >> 24);
	// bytes get, find in code
	for(result = (Code_Base + Code_Size);result > Code_Base;result--)
	{
		for(idx = 0;idx < 4;idx++)
		{
			if(*(unsigned char*)(result + idx) != bytes[idx]) break;
		}
		if(idx == 4) break;
	}
	if(result == Code_Base) return 0; // error
	// string founded, move down to CC
	for(;result > Code_Base;result--)
	{
		if(*(unsigned char*)(result) == 0xCC)
		{
			result++;
			break;
		}
	}
	if(result == Code_Base) return 0; // error
	return result;
}

unsigned long CHooks::Search_ClientDisconnect()
{
	// vars
	unsigned long result = 0;
	unsigned long string_addr;
	int idx;
	int len = strlen(pd_string) - 1;
	unsigned char bytes[4];
	unsigned long max;
	// start search string addr
	max = (rData_Base + rData_Size);
	for(string_addr = max;string_addr > rData_Base;string_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(string_addr + idx > max) 
			{
				if(result == 1) result = 0;
				break;
			}
			if(*(char*)(string_addr + idx) == pd_string[idx]) result = 1;
			else 
			{
				if(result == 1) result = 0;
				break;
			}
		}
		if(result == 1) break;
	}
	if(result != 1) return 0; // error
	// string addr founded, parse address to bytes	
	bytes[0] = (unsigned char)(string_addr);
	bytes[1] = (unsigned char)(string_addr >> 8);
	bytes[2] = (unsigned char)(string_addr >> 16);
	bytes[3] = (unsigned char)(string_addr >> 24);
	// bytes get, find in code
	for(result = (Code_Base + Code_Size);result > Code_Base;result--)
	{
		for(idx = 0;idx < 4;idx++)
		{
			if(*(unsigned char*)(result + idx) != bytes[idx]) break;
		}
		if(idx == 4) break;
	}
	if(result == Code_Base) return 0; // error
	// string founded, move down to CC
	for(;result > Code_Base;result--)
	{
		if(*(unsigned char*)(result) == 0xCC)
		{
			result++;
			break;
		}
	}
	if(result == Code_Base) return 0; // error
	return result;
}

unsigned long CHooks::Search_ClientSpawn()
{
	// vars
	unsigned long result = 0;
	unsigned long data_addr;
	int idx;
	int len = 12;
	// start search data
	for(data_addr = (Code_Base + Code_Size);data_addr > Code_Base;data_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(ps_data[idx] == 0xFF) continue;
			if(*(unsigned char*)(data_addr + idx) != ps_data[idx]) break;
		}
		if(idx == len) break;
	}
	if(data_addr == Code_Base) return 0; // error
	// set on call
	data_addr += (len - 1);
	// set result data
	result = (*(BYTE*)(data_addr + 4) << 24) + (*(BYTE*)(data_addr + 3)<<16) + (*(BYTE*)(data_addr + 2)<<8) + *(BYTE*)(data_addr + 1);
	// call correct
	result += data_addr += 5;
	return result;
}

unsigned long CHooks::Search_ClientDeath()
{
	// vars
	unsigned long result = 0;
	unsigned long string_addr;
	int idx;
	int len = strlen(pde_string) - 1;
	unsigned char bytes[4];
	unsigned long max;
	// start search string addr
	max = (rData_Base + rData_Size);
	for(string_addr = max;string_addr > rData_Base;string_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(string_addr + idx > max) 
			{
				if(result == 1) result = 0;
				break;
			}
			if(*(char*)(string_addr + idx) == pde_string[idx]) result = 1;
			else 
			{
				if(result == 1) result = 0;
				break;
			}
		}
		if(result == 1) break;
	}
	if(result != 1) return 0; // error
	// string addr founded, parse address to bytes	
	bytes[0] = (unsigned char)(string_addr);
	bytes[1] = (unsigned char)(string_addr >> 8);
	bytes[2] = (unsigned char)(string_addr >> 16);
	bytes[3] = (unsigned char)(string_addr >> 24);
	// bytes get, find in code
	for(result = (Code_Base + Code_Size);result > Code_Base;result--)
	{
		for(idx = 0;idx < 4;idx++)
		{
			if(*(unsigned char*)(result + idx) != bytes[idx]) break;
		}
		if(idx == 4) break;
	}
	if(result == Code_Base) return 0; // error
	// string founded, move down to CC
	for(;result > Code_Base;result--)
	{
		if(*(unsigned char*)(result) == 0xCC)
		{
			result++;
			break;
		}
	}
	if(result == Code_Base) return 0; // error
	return result;
}

unsigned long CHooks::Search_SetPlaybackDir()
{
	// vars
	unsigned long result = 0;
	unsigned long data_addr;
	int idx;
	int len = 29;
	// start search data
	for(data_addr = (Code_Base + Code_Size);data_addr > Code_Base;data_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(rd_data[idx] == 0xFF) continue;
			if(*(unsigned char*)(data_addr + idx) != rd_data[idx]) break;
		}
		if(idx == len) break;
	}
	if(data_addr == Code_Base) return 0; // error
	// set on call
	data_addr += 0x1;
	// set result data
	result = (*(BYTE*)(data_addr + 4) << 24) + (*(BYTE*)(data_addr + 3)<<16) + (*(BYTE*)(data_addr + 2)<<8) + *(BYTE*)(data_addr + 1);
	return result;
}

void CHooks::Search_ThreadAddresses(unsigned long* addr1,unsigned long* addr2)
{
	// vars
	*addr1 = 0;
	*addr2 = 0;
	unsigned long data_addr;
	int idx;
	int len = 28;
	// start search data
	for(data_addr = (Code_Base + Code_Size);data_addr > Code_Base;data_addr--)
	{
		for(idx = 0;idx < len;idx++)
		{
			if(thread_data[idx] == 0xFF) continue;
			if(*(unsigned char*)(data_addr + idx) != thread_data[idx]) break;
		}
		if(idx == len) break;
	}
	if(data_addr == Code_Base) return; // error
	// start addr
	*addr1 = data_addr;
	// end
	*addr2 = data_addr + len;
}