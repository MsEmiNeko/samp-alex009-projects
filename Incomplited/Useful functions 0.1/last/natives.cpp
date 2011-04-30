/*
*	Created:			15.05.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// core
#include "math.h"
#include <malloc.h>
#include <stdio.h>
// plugin
#include "os.h"
#include "main.h"
// samp data
#include "samp structs.h"
#include "samp defines.h"

extern DWORD		CSampPointer;
extern DWORD		c_samp;
extern DWORD		c_mass;

extern DWORD		CPlayerWeaponSkillOffset;
extern DWORD		CVehicleDriverOffset;

extern DWORD		PlaybackDirAddr;
extern DWORD		LogFileAddr;
extern DWORD		BadCharsAddr;
extern DWORD		ChangeNameLogAddr;

/*
									Core
*/
// SetPlaybackDir(dir[]);
static cell AMX_NATIVE_CALL n_SetPlaybackDir( AMX* amx, cell* params )
{
	// playbackdir ( 0x49D95C )
	char* temp = new char[50];
	amx_StrParam(amx, params[2], temp);

	strcpy((PCHAR)PlaybackDirAddr,temp);

	return 1;
}

// DeleteLogFile();
static cell AMX_NATIVE_CALL n_DeleteLogFile( AMX* amx, cell* params )
{
	// logfile ( 0x4BD0F4 )
	DWORD oldp;
    VirtualProtect((LPVOID)(*(DWORD*)(LogFileAddr)), 5, PAGE_EXECUTE_READWRITE, &oldp);

	fclose(*(FILE**)(LogFileAddr));

	remove("server_log.txt");

	*(DWORD*)(LogFileAddr) = (DWORD)fopen("server_log.txt","a");
	return 1;
}

// GetLogFileLength();
static cell AMX_NATIVE_CALL n_GetLogFileLength( AMX* amx, cell* params )
{
	// logfile ( 0x4BD0F4 )
	FILE* fin = (FILE*)(*(DWORD*)(LogFileAddr));

	long curpos = ftell(fin);
	fseek(fin, 0, SEEK_END);

	long result = ftell(fin);
	fseek(fin, curpos, SEEK_SET);

	return (int)result;
}

// DeleteCrashFile();
static cell AMX_NATIVE_CALL n_DeleteCrashFile( AMX* amx, cell* params )
{
	remove("crashinfo.txt");
	return 1;
}

// DisableBadCharsCheck();
static cell AMX_NATIVE_CALL n_DisableBadCharsCheck( AMX* amx, cell* params )
{
	// in check name ( 0x475418 )
	*(BYTE*)(BadCharsAddr) = 0x00;
	return 1;
}

// DisableChangeNameLogging();
static cell AMX_NATIVE_CALL n_DisableChangeNameLogging( AMX* amx, cell* params )
{
	// in change name =/ ( 0x467E49 )
	for(int i = 0x0;i < 0x5;i += 0x1) *(BYTE*)(ChangeNameLogAddr + i) = 0x90;
	return 1;
}

/*
									Players
*/
// SetPlayerAdmin(playerid,true/false);
static cell AMX_NATIVE_CALL n_SetPlayerAdmin( AMX* amx, cell* params )
{
	int id = (int)params[1];

	c_samp = *(DWORD*)(CSampPointer);
	c_mass = *(DWORD*)(c_samp + C_SAMP_PLAYERS_OFFSET);

	if(!*(DWORD*)(c_mass + id*4)) return 0;

	*(DWORD*)(c_mass + id*4 + C_PLAYERS_IS_ADMIN_OFFSET) = ((int)params[2] != 0);
	return 1;
}

// GetPlayerSkillLevel(playerid,weapontype);
static cell AMX_NATIVE_CALL n_GetPlayerSkillLevel( AMX* amx, cell* params )
{
	int id = (int)params[1];

	c_samp = *(DWORD*)(CSampPointer);
	c_mass = *(DWORD*)(c_samp + C_SAMP_PLAYERS_OFFSET);

	if(!*(DWORD*)(c_mass + id*4)) return 0;

	DWORD player = *(DWORD*)(c_mass + id*4 + C_PLAYERS_PLAYER_OFFSET);
	return (int)*(WORD*)(player + 2*(int)params[2] + CPlayerWeaponSkillOffset);
}

/*
									Vehicles
*/
// IsVehicleCreated(vehicleid);
static cell AMX_NATIVE_CALL n_IsVehicleCreated( AMX* amx, cell* params )
{
	int id = (int)params[1];

	c_samp = *(DWORD*)(CSampPointer);
	c_mass = *(DWORD*)(c_samp + C_SAMP_VEHICLES_OFFSET);

	if(*(DWORD*)(c_mass + id*4)) return 1;
	else return 0;
}

// IsVehicleUsed(vehicleid);
static cell AMX_NATIVE_CALL n_IsVehicleUsed( AMX* amx, cell* params )
{
	int id = (int)params[1];

	c_samp = *(DWORD*)(CSampPointer);
	c_mass = *(DWORD*)(c_samp + C_SAMP_VEHICLES_OFFSET);

	if(*(DWORD*)(c_mass + id*4))
	{
		DWORD c_veh = *(DWORD*)(c_mass + id*4 + C_VEHICLES_VEHICLE_OFFSET);
		DWORD driver = *(DWORD*)(c_veh + CVehicleDriverOffset);
		c_mass = *(DWORD*)(c_samp + C_SAMP_PLAYERS_OFFSET);
		if(*(DWORD*)(c_mass + driver*4)) return 1;
		else return 0;
	}
	return 0;
}

// GetVehicleDriver(vehicleid);
static cell AMX_NATIVE_CALL n_GetVehicleDriver( AMX* amx, cell* params )
{
	int id = (int)params[1];

	c_samp = *(DWORD*)(CSampPointer);
	c_mass = *(DWORD*)(c_samp + C_SAMP_VEHICLES_OFFSET);

	if(*(DWORD*)(c_mass + id*4))
	{
		DWORD c_veh = *(DWORD*)(c_mass + id*4 + C_VEHICLES_VEHICLE_OFFSET);
		DWORD driver = *(DWORD*)(c_veh + CVehicleDriverOffset);
		c_mass = *(DWORD*)(c_samp + C_SAMP_PLAYERS_OFFSET);
		if(*(DWORD*)(c_mass + driver*4)) return (int)driver;
		else return INVALID_PLAYER_ID;
	}
	return INVALID_PLAYER_ID;
}

AMX_NATIVE_INFO Natives[ ] =
{
	// core
	{ "SetPlaybackDir",				n_SetPlaybackDir},
	{ "DeleteLogFile",				n_DeleteLogFile},
	{ "GetLogFileLength",			n_GetLogFileLength},
	{ "DeleteCrashFile",			n_DeleteCrashFile},
	{ "DisableBadCharsCheck",		n_DisableBadCharsCheck},
	{ "DisableChangeNameLogging",	n_DisableChangeNameLogging},
	// players
	{ "SetPlayerAdmin",				n_SetPlayerAdmin},
	{ "GetPlayerSkillLevel",		n_GetPlayerSkillLevel},
	{ "HidePlayer",					n_HidePlayer},
	{ "ShowPlayer",					n_ShowPlayer},
	// vehicles
	{ "IsVehicleCreated",			n_IsVehicleCreated},
	{ "IsVehicleUsed",				n_IsVehicleUsed},
	{ "GetVehicleDriver",			n_GetVehicleDriver},
	{ 0,							0 }
};

void NativesOnAMXLoad(AMX *amx)
{
	amx_Register( amx, Natives, -1 );
}