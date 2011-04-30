/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <malloc.h>
#include <math.h>
// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// plugin
#include "SAMP/CSAMP.h"
#include "hooks.h"
#include "callbacks.h"
#include "defines.h"

extern	CSAMP*		pSaMp;
extern	CHooks*		pHooks;
extern	CCallbacks*	pCallbacks;


// SetPlaybackDir(dir[]);
static cell AMX_NATIVE_CALL n_SetPlaybackDir( AMX* amx, cell* params )
{
	// playbackdir ( 0x49D95C )
	char* temp = new char[50];
	amx_StrParam(amx, params[2], temp);

	pHooks->SetPlaybackDir(temp);
	return 1;
}

// DeleteLogFile();
static cell AMX_NATIVE_CALL n_DeleteLogFile( AMX* amx, cell* params )
{
	// logfile ( 0x4BD0F4 )
	pHooks->DeleteLogFile();
	return 1;
}

// GetLogFileLength();
static cell AMX_NATIVE_CALL n_GetLogFileLength( AMX* amx, cell* params )
{
	// logfile ( 0x4BD0F4 )
	return pHooks->GetLogFileLength();
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
	pHooks->DisableBadCharsCheck();
	return 1;
}

// DisableChangeNameLogging();
static cell AMX_NATIVE_CALL n_DisableChangeNameLogging( AMX* amx, cell* params )
{
	// in change name =/ ( 0x467E49 )
	pHooks->DisableChangeNameLogging();
	return 1;
}

/*
									Players
*/
// SetPlayerAdmin(playerid,true/false);
static cell AMX_NATIVE_CALL n_SetPlayerAdmin( AMX* amx, cell* params )
{
	int playerid = (int)params[1];

	if(!pSaMp->players->player[playerid]) return 0;

	pSaMp->players->IsAdmin[playerid] = (params[2] == 0?0:1);
	return 1;
}

// GetPlayerSkillLevel(playerid,weapontype);
static cell AMX_NATIVE_CALL n_GetPlayerSkillLevel( AMX* amx, cell* params )
{
	int playerid = (int)params[1];
	int type = (int)params[2];

	if(!pSaMp->players->player[playerid]) return 0;

	return pSaMp->players->player[playerid]->WeaponSkill[type];
}

/*
									Vehicles
*/
// IsVehicleCreated(vehicleid);
static cell AMX_NATIVE_CALL n_IsVehicleCreated( AMX* amx, cell* params )
{
	int vehicleid = (int)params[1];

	return (pSaMp->vehicles->vehicle[vehicleid] == 0?0:1);
}

// IsVehicleUsed(vehicleid);
static cell AMX_NATIVE_CALL n_IsVehicleUsed( AMX* amx, cell* params )
{
	int vehicleid = (int)params[1];

	if(!pSaMp->vehicles->vehicle[vehicleid]) return 0;

	unsigned short driver = pSaMp->vehicles->vehicle[vehicleid]->Driver;
	
	if(!pSaMp->players->player[driver]) return 0;
	return (pSaMp->players->player[driver]->VehicleId == vehicleid?1:0);
}

// GetVehicleDriver(vehicleid);
static cell AMX_NATIVE_CALL n_GetVehicleDriver( AMX* amx, cell* params )
{
	int vehicleid = (int)params[1];

	if(!pSaMp->vehicles->vehicle[vehicleid]) return 0;

	unsigned short driver = pSaMp->vehicles->vehicle[vehicleid]->Driver;

	if(!pSaMp->players->player[driver]) return INVALID_PLAYER_ID;
	return (pSaMp->players->player[driver]->VehicleId == vehicleid?driver:INVALID_PLAYER_ID);
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
	// vehicles
	{ "IsVehicleCreated",			n_IsVehicleCreated},
	{ "IsVehicleUsed",				n_IsVehicleUsed},
	{ "GetVehicleDriver",			n_GetVehicleDriver},
	{ 0,							0 }
};

void NativesOnAMXLoad(AMX* amx)
{
	amx_Register(amx, Natives, -1 );
}
