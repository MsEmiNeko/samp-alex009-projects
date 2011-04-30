/*
*	Created:			15.03.09
*	Author:				009
*	Description:		Стриммер пикапов, изменение любого параметра, дополнительные функции
*/

#if defined core_pickups_included
	#endinput
#endif

#define core_pickups_included
#pragma library core_pickups

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/interiors.p"
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define PICKUPS_TAKE_DISTANCE 	2.0

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	// pickups
	ModePickupState[MAX_MODE_PICKUPS char],
	ModePickupModel[MAX_MODE_PICKUPS],
	ModePickupType[MAX_MODE_PICKUPS char],
	ModePickupGameId[MAX_MODE_PICKUPS],
	ModePickupSeeCount[MAX_MODE_PICKUPS],
	Float:ModePickupCoords[MAX_MODE_PICKUPS][3],
	ModePickupInterior[MAX_MODE_PICKUPS char],
	ModePickupVirtualWorld[MAX_MODE_PICKUPS],
	ModePickupTypeEx[MAX_MODE_PICKUPS char],
	ModePickupTypeExParam[MAX_MODE_PICKUPS],
	// players
	ModePickupPlayerOnPickup[MAX_PLAYERS],
	ModePickupPlayerShowedPickups[MAX_PLAYERS][MAX_MODE_PICKUPS char],
	// server
	ServerPickupsOffset[MAX_PICKUPS],
	ModePickupsOffset,
	ModePickupsCount;

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native CreateModePickup(Model,Type,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld,TypeEx,TypeExParam);
native DestroyModePickup(pickupid);
native GetModePickupPos(pickupid,&Float:X,&Float:Y,&Float:Z);
native SetModePickupPos(pickupid,Float:X,Float:Y,Float:Z);
native GetModePickupModeInterior(pickupid);
native SetModePickupModeInterior(pickupid,modeinterior);
native GetModePickupVirtualWorld(pickupid);
native SetModePickupVirtualWorld(pickupid,virtualworld);
native GetModePickupModel(pickupid);
native GetModePickupType(pickupid);
native SetModePickupType(pickupid,type);
native GetModePickupTypeEx(pickupid);
native SetModePickupTypeEx(pickupid,type);
native GetModePickupTypeExParam(pickupid);
native SetModePickupTypeExParam(pickupid,typeparam);
native GetPlayerPickupOn(playerid);
native IsModePickupNeedToShow(playerid,pickupid);
*/

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward OnPlayerModePickupPickUp(playerid,pickupid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnPlayerPickUpPickup(playerid,pickupid)
{
	Debug(DEBUG_START,"OnPlayerPickUpPickup(%d,%d)",playerid,pickupid);
	if(ModePickupPlayerOnPickup[playerid] == ServerPickupsOffset[pickupid])
	{
		Debug(DEBUG_END,"OnPlayerPickUpPickup(reason: player on last pickup)");
		return 0;
	}
	
	ModePickupPlayerOnPickup[playerid] = ServerPickupsOffset[pickupid];
	OnPlayerModePickupPickUp(playerid,ServerPickupsOffset[pickupid]);
	Debug(DEBUG_END,"OnPlayerPickUpPickup(reason: complete)");
	return 1;
}

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateModePickup(Model,Type,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld,TypeEx,TypeExParam)
{
	Debug(DEBUG_START,"CreateModePickup(%d,%d,%f,%f,%f,%d,%d,%d,%d)",Model,Type,X,Y,Z,ModeInterior,VirtualWorld,TypeEx,TypeExParam);
	for(new pickupid = ModePickupsOffset;pickupid < MAX_MODE_PICKUPS;pickupid++)
	{
	    if(ModePickupState{pickupid} == 1) continue;
		Debug(DEBUG_ACTION,"Finded free slot,id = %d , set main data",pickupid);
		ModePickupState{pickupid} = 1;
		ModePickupSeeCount[pickupid] = 0;
		ModePickupGameId[pickupid] = INVALID_PICKUP_ID;
		Debug(DEBUG_ACTION,"Pickup info set");
		ModePickupModel[pickupid] = Model;
		ModePickupType{pickupid} = Type;
		Debug(DEBUG_ACTION,"Coordinates info set");
		ModePickupCoords[pickupid][0] = X;
		ModePickupCoords[pickupid][1] = Y;
		ModePickupCoords[pickupid][2] = Z;
		ModePickupInterior{pickupid} = ModeInterior;
		ModePickupVirtualWorld[pickupid] = VirtualWorld;
		Debug(DEBUG_ACTION,"Type Ex info set");
		ModePickupTypeEx{pickupid} = TypeEx;
		ModePickupTypeExParam[pickupid] = TypeExParam;
		Debug(DEBUG_ACTION,"Players info set");
		for(new playerid = 0;playerid < MAX_PLAYERS;playerid++) ModePickupPlayerShowedPickups[playerid]{pickupid} = 0;
		Debug(DEBUG_ACTION,"Set offset data(old: %d,%d)",ModePickupsOffset,ModePickupsCount);
		ModePickupsOffset = pickupid;
		if(ModePickupsCount < pickupid) ModePickupsCount = pickupid;
		Debug(DEBUG_END,"CreateModePickup(reason: complete)");
		return pickupid;
	}
	Debug(DEBUG_END,"CreateModePickup(reason: all slots used)");
	print("[ERROR] Core -> Pickups -> CreateModePickup (all slots used)");
	return 0;
}

stock DestroyModePickup(pickupid)
{
	Debug(DEBUG_START,"DestroyModePickup(%d)",pickupid);
	ModePickupState{pickupid} = 0;
	ModePickupSeeCount[pickupid] = 0;
	ModePickupGameId[pickupid] = INVALID_PICKUP_ID;
	Debug(DEBUG_ACTION,"Pickup info reset");
	ModePickupModel[pickupid] = 0;
	ModePickupType{pickupid} = 0;
	Debug(DEBUG_ACTION,"Coordinates info reset");
	for(new i = 0;i < 3;i++) ModePickupCoords[pickupid][i] = 0.0;
	ModePickupInterior{pickupid} = 0;
	ModePickupVirtualWorld[pickupid] = 0;
	Debug(DEBUG_ACTION,"TypeEx info reset");
	ModePickupTypeEx{pickupid} = 0;
	ModePickupTypeExParam[pickupid] = 0;
	Debug(DEBUG_ACTION,"Players info reset and destroy pickup");
	for(new playerid = 0;playerid < MAX_PLAYERS;playerid++) 
	{
		ModePickupPlayerShowedPickups[playerid]{pickupid} = 0;
		if(ModePickupPlayerOnPickup[playerid] == pickupid) ModePickupPlayerOnPickup[playerid] = INVALID_MODE_PICKUP_ID;
	}
	Debug(DEBUG_ACTION,"Counter reset");
	if(ModePickupsOffset > pickupid) ModePickupsOffset = pickupid;
	if(ModePickupsCount == pickupid) 
	{
		do ModePickupsCount--;
		while((ModePickupState{ ModePickupsCount } == 0) && (ModePickupsCount > 0));
	}
	Debug(DEBUG_END,"DestroyModePickup(reason: complete)");
	return 1;
}

stock GetModePickupPos(pickupid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetModePickupPos(%d)",pickupid);
	X = ModePickupCoords[pickupid][0];
	Y = ModePickupCoords[pickupid][1];
	Z = ModePickupCoords[pickupid][2];
	Debug(DEBUG_END,"GetModePickupPos(reason: complete)");
	return 1;
}

stock SetModePickupPos(pickupid,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetModePickupPos(%d,%f,%f,%f)",pickupid,X,Y,Z);
	Debug(DEBUG_ACTION,"set new coords info");
	ModePickupCoords[pickupid][0] = X;
	ModePickupCoords[pickupid][1] = Y;
	ModePickupCoords[pickupid][2] = Z;
	Debug(DEBUG_ACTION,"destroy pickup");
	if(ModePickupSeeCount[pickupid] != 0) HideModePickup(pickupid);
	Debug(DEBUG_END,"SetModePickupPos(reason: complete)");
	return 1;
}

stock GetModePickupModeInterior(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupModeInterior(%d)",pickupid);
	return ModePickupInterior{pickupid};
}

stock SetModePickupModeInterior(pickupid,modeinterior)
{
	Debug(DEBUG_START,"SetModePickupModeInterior(%d,%d)",pickupid,modeinterior);
	Debug(DEBUG_ACTION,"set new data and destroy pickup");
	ModePickupInterior{pickupid} = modeinterior;
	if(ModePickupSeeCount[pickupid] != 0) HideModePickup(pickupid);
	Debug(DEBUG_END,"SetModePickupModeInterior(reason: complete)");
	return 1;
}

stock GetModePickupVirtualWorld(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupVirtualWorld(%d)",pickupid);
	return ModePickupVirtualWorld[pickupid];
}

stock SetModePickupVirtualWorld(pickupid,virtualworld)
{
	Debug(DEBUG_START,"SetModePickupVirtualWorld(%d,%d)",pickupid,virtualworld);
	Debug(DEBUG_ACTION,"set new data and destroy pickup");
	ModePickupVirtualWorld[pickupid] = virtualworld;
	if(ModePickupSeeCount[pickupid] != 0) HideModePickup(pickupid);
	Debug(DEBUG_END,"SetModePickupVirtualWorld(reason: complete)");
	return 1;
}

stock GetModePickupModel(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupModel(%d)",pickupid);
	return ModePickupModel[pickupid];
}

stock GetModePickupType(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupType(%d)",pickupid);
	return ModePickupType{pickupid};
}

stock SetModePickupType(pickupid,type)
{
	Debug(DEBUG_START,"SetModePickupType(%d,%d)",pickupid,type);
	Debug(DEBUG_ACTION,"set new data and destroy pickup");
	ModePickupType{pickupid} = type;
	if(ModePickupSeeCount[pickupid] != 0) HideModePickup(pickupid);
	Debug(DEBUG_END,"SetModePickupType(reason: complete)");
	return 1;
}

stock GetModePickupTypeEx(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupTypeEx(%d)",pickupid);
	return ModePickupTypeEx{pickupid};
}

stock SetModePickupTypeEx(pickupid,type)
{
	Debug(DEBUG_START,"SetModePickupTypeEx(%d,%d)",pickupid,type);
	ModePickupTypeEx{pickupid} = type;
	Debug(DEBUG_END,"SetModePickupTypeEx(reason: complete)");
	return 1;
}

stock GetModePickupTypeExParam(pickupid)
{
	Debug(DEBUG_SMALL,"GetModePickupTypeExParam(%d)",pickupid);
	return ModePickupTypeExParam[pickupid];
}

stock SetModePickupTypeExParam(pickupid,typeparam)
{
	Debug(DEBUG_START,"SetModePickupTypeExParam(%d,%d)",pickupid,typeparam);
	ModePickupTypeExParam[pickupid] = typeparam;
	Debug(DEBUG_END,"SetModePickupTypeExParam(reason: complete)");
	return 1;
}

stock GetPlayerPickupOn(playerid)
{
	Debug(DEBUG_SMALL,"GetPlayerPickupOn(%d)",playerid);
	return ModePickupPlayerOnPickup[playerid];
}

stock IsModePickupNeedToShow(playerid,pickupid)
{
	Debug(DEBUG_START,"IsModePickupNeedToShow(%d,%d)",playerid,pickupid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsModePickupNeedToShow(reason: error)");
		printf("[ERROR] Core -> Pickups -> IsModePickupNeedToShow (try check pickup for offline player, playerid = %d)",playerid);
		return 0;
	}
	
	new res = 0;
	if(!IsPlayerInRangeOfPoint(playerid,MODE_PICKUPS_DISTANCE,ModePickupCoords[pickupid][0],ModePickupCoords[pickupid][1],ModePickupCoords[pickupid][2])) res = 0;
#if defined GetPlayerModeInterior
    else if((GetPlayerModeInterior(playerid) != ModePickupInterior{pickupid}) && (ModePickupInterior{pickupid} != INVALID_MODE_INTERIOR_ID)) res = 0;
#else
    else if((GetPlayerInterior(playerid) != ModePickupInterior{pickupid}) && (ModePickupInterior{pickupid} != INVALID_MODE_INTERIOR_ID)) res = 0;
#endif
	else if((GetPlayerVirtualWorld(playerid) != ModePickupVirtualWorld[pickupid]) && (ModePickupVirtualWorld[pickupid] != INVALID_VIRTUAL_WORLD_ID)) res = 0;
	else res = 1;
	
	Debug(DEBUG_END,"IsModePickupNeedToShow(reason: complete)");
	return res;
}

// --------------------------------------------------
// static functions
// --------------------------------------------------
static stock HideModePickup(pickupid)
{
    DestroyPickup(ModePickupGameId[pickupid]);
	ModePickupSeeCount[pickupid] = 0;
	ModePickupGameId[pickupid] = INVALID_PICKUP_ID;
	for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
	{
		ModePickupPlayerShowedPickups[playerid]{pickupid} = 0;
		if(ModePickupPlayerOnPickup[playerid] == pickupid) ModePickupPlayerOnPickup[playerid] = INVALID_MODE_PICKUP_ID;
	}
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Pickups_Init()
{
	Debug(DEBUG_START,"Core_Pickups_Init()");
	print("[CORE] Pickups load complete.");
	Debug(DEBUG_END,"Core_Pickups_Init(reason: complete)");
}

Core_Pickups_ResetStat(playerid)
{
	Debug(DEBUG_START,"Core_Pickups_ResetStat(%d)",playerid);
	for(new pickupid = 0;pickupid < MAX_MODE_PICKUPS;pickupid++) ModePickupPlayerShowedPickups[playerid]{pickupid} = 0;
	ModePickupPlayerOnPickup[playerid] = INVALID_MODE_PICKUP_ID;
	Debug(DEBUG_END,"Core_Pickups_ResetStat(reason: complete)");
}

Core_Pickups_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Core_Pickups_PlayerUpdate(%d)",playerid);
	if(ModePickupPlayerOnPickup[playerid] != INVALID_MODE_PICKUP_ID)
	{
		if(!IsPlayerInRangeOfPoint(playerid,PICKUPS_TAKE_DISTANCE,ModePickupCoords[ ModePickupPlayerOnPickup[playerid] ][0],ModePickupCoords[ ModePickupPlayerOnPickup[playerid] ][1],ModePickupCoords[ ModePickupPlayerOnPickup[playerid] ][2])) ModePickupPlayerOnPickup[playerid] = INVALID_MODE_PICKUP_ID;
	}
	for(new pickupid = 0;pickupid < ModePickupsCount;pickupid++)
	{
		if(ModePickupState{pickupid} == 0) continue;
		
		if(ModePickupPlayerShowedPickups[playerid]{pickupid} == 0)
		{
			if(!IsModePickupNeedToShow(playerid,pickupid)) continue;
			
			ModePickupPlayerShowedPickups[playerid]{pickupid} = 1;
			ModePickupSeeCount[pickupid]++;
			if(ModePickupSeeCount[pickupid] == 1)
			{
				ModePickupGameId[pickupid] = CreatePickup(ModePickupModel[pickupid],ModePickupType{pickupid},ModePickupCoords[pickupid][0],ModePickupCoords[pickupid][1],ModePickupCoords[pickupid][2],ModePickupVirtualWorld[pickupid]);
				ServerPickupsOffset[ ModePickupGameId[pickupid] ] = pickupid;
			}
		}
		else
		{
			if(IsModePickupNeedToShow(playerid,pickupid)) continue;
			
			ModePickupPlayerShowedPickups[playerid]{pickupid} = 0;
			ModePickupSeeCount[pickupid]--;
			if(ModePickupSeeCount[pickupid] == 0)
			{
				DestroyPickup(ModePickupGameId[pickupid]);
				ServerPickupsOffset[ ModePickupGameId[pickupid] ] = INVALID_MODE_PICKUP_ID;
			}
		}
	}
	Debug(DEBUG_END,"Core_Pickups_PlayerUpdate(reason: complete)");
}
