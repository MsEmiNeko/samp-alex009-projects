/*
*	Created:			12.03.09
*	Author:				009
*	Description:		Стриммер иконок, изменение любого параметра
*/

#if defined core_icons_included
	#endinput
#endif

#define core_icons_included
#pragma library core_icons

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/interiors.p"
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// news
// --------------------------------------------------
static
	// icons
	ModeIconState[MAX_MODE_ICONS char],
	ModeIconIconId[MAX_MODE_ICONS char],
	ModeIconColor[MAX_MODE_ICONS],
	Float:ModeIconPos[MAX_MODE_ICONS][3],
	ModeIconInterior[MAX_MODE_ICONS char],
	ModeIconVirtualWorld[MAX_MODE_ICONS],
	// player
	ModeIconPlayerOffset[MAX_PLAYERS char],
	ModeIconPlayerGameId[MAX_PLAYERS][MAX_MODE_ICONS char],
	ModeIconPlayerSlots[MAX_PLAYERS][MAX_ICONS char],
	// other
	ModeIconsOffset,
	ModeIconsCount;

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native CreateModeIcon(Icon,Color,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld);
native DestroyModeIcon(iconid);
native GetModeIconPos(iconid,&Float:X,&Float:Y,&Float:Z);
native SetModeIconPos(iconid,Float:X,Float:Y,Float:Z);
native GetModeIconModeInterior(iconid);
native SetModeIconModeInterior(iconid,modeinterior);
native GetModeIconVirtualWorld(iconid);
native SetModeIconVirtualWorld(iconid,virtualworld);
native GetModeIconIcon(iconid);
native SetModeIconIcon(iconid,icon);
native GetModeIconColor(iconid);
native SetModeIconColor(iconid,color);
native IsModeIconNeedToShow(playerid,iconid);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateModeIcon(Icon,Color,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld)
{
	Debug(DEBUG_START,"CreateModeIcon(%d,%d,%f,%f,%f,%d,%d)",Icon,Color,X,Y,Z,ModeInterior,VirtualWorld);
	for(new iconid = ModeIconsOffset;iconid < MAX_MODE_ICONS;iconid++)
	{
	    if(ModeIconState{iconid} == 1) continue;
		Debug(DEBUG_ACTION,"Finded free slot,id = %d , set main data",iconid);
		ModeIconState{iconid} = 1;
		Debug(DEBUG_ACTION,"Icon info set");
		ModeIconIconId{iconid} = Icon;
		ModeIconColor[iconid] = Color;
		Debug(DEBUG_ACTION,"Coordinates info set");
		ModeIconPos[iconid][0] = X;
		ModeIconPos[iconid][1] = Y;
		ModeIconPos[iconid][2] = Z;
		ModeIconInterior{iconid} = ModeInterior;
		ModeIconVirtualWorld[iconid] = VirtualWorld;
		Debug(DEBUG_ACTION,"Players info set");
		for(new playerid = 0;playerid < MAX_PLAYERS;playerid++)	ModeIconPlayerGameId[playerid]{iconid} = INVALID_ICON_ID;
		Debug(DEBUG_ACTION,"Set offset data(old: %d,%d)",ModeIconsOffset,ModeIconsCount);
		ModeIconsOffset = iconid;
		if(ModeIconsCount < iconid) ModeIconsCount = iconid;
		Debug(DEBUG_END,"CreateModeIcon(reason: complete)");
		return iconid;
	}
	Debug(DEBUG_END,"CreateModeIcon(reason: all slots used)");
	print("[ERROR] Core -> Icons -> CreateModeIcon (all slots used)");
	return 0;
}

stock DestroyModeIcon(iconid)
{
	Debug(DEBUG_START,"DestroyModeIcon(%d)",iconid);
	ModeIconState{iconid} = 0;
	Debug(DEBUG_ACTION,"Icon info set");
	ModeIconIconId{iconid} = 0;
	ModeIconColor[iconid] = 0;
	Debug(DEBUG_ACTION,"Coordinates info reset");
	for(new i = 0;i < 3;i++) ModeIconPos[iconid][i] = 0.0;
	ModeIconInterior{iconid} = 0;
	ModeIconVirtualWorld[iconid] = 0;
	Debug(DEBUG_ACTION,"Players info reset and destroy icon");
	HideModeIcon(iconid);
	Debug(DEBUG_ACTION,"Counter reset");
	if(ModeIconsOffset > iconid) ModeIconsOffset = iconid;
	if(ModeIconsCount == iconid) 
	{
		do ModeIconsCount--;
		while((ModeIconState{ ModeIconsCount } == 0) && (ModeIconsCount > 0));
	}
	Debug(DEBUG_END,"DestroyModeIcon(reason: complete)");
	return 1;
}

stock GetModeIconPos(iconid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetModeIconPos(%d)",iconid);
	X = ModeIconPos[iconid][0];
	Y = ModeIconPos[iconid][1];
	Z = ModeIconPos[iconid][2];
	Debug(DEBUG_END,"GetModeIconPos(reason: complete)");
	return 1;
}

stock SetModeIconPos(iconid,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetModeIconPos(%d,%f,%f,%f)",iconid,X,Y,Z);
	Debug(DEBUG_ACTION,"set new coords info");
	ModeIconPos[iconid][0] = X;
	ModeIconPos[iconid][1] = Y;
	ModeIconPos[iconid][2] = Z;
	HideModeIcon(iconid);
	Debug(DEBUG_END,"SetModeIconPos(reason: complete)");
	return 1;
}

stock GetModeIconModeInterior(iconid)
{
	Debug(DEBUG_SMALL,"GetModeIconModeInterior(%d)",iconid);
	return ModeIconInterior{iconid};
}

stock SetModeIconModeInterior(iconid,modeinterior)
{
	Debug(DEBUG_START,"SetModeIconModeInterior(%d,%d)",iconid,modeinterior);
	Debug(DEBUG_ACTION,"set new data and destroy icon");
	ModeIconInterior{iconid} = modeinterior;
	HideModeIcon(iconid);
	Debug(DEBUG_END,"SetModeIconModeInterior(reason: complete)");
	return 1;
}

stock GetModeIconVirtualWorld(iconid)
{
	Debug(DEBUG_SMALL,"GetModeIconVirtualWorld(%d)",iconid);
	return ModeIconVirtualWorld[iconid];
}

stock SetModeIconVirtualWorld(iconid,virtualworld)
{
	Debug(DEBUG_START,"SetModeIconVirtualWorld(%d,%d)",iconid,virtualworld);
	Debug(DEBUG_ACTION,"set new data and destroy icon");
	ModeIconVirtualWorld[iconid] = virtualworld;
	HideModeIcon(iconid);
	Debug(DEBUG_END,"SetModeIconVirtualWorld(reason: complete)");
	return 1;
}

stock GetModeIconIcon(iconid)
{
	Debug(DEBUG_SMALL,"GetModeIconIcon(%d)",iconid);
	return ModeIconIconId{iconid};
}

stock SetModeIconIcon(iconid,icon)
{
	Debug(DEBUG_START,"SetModeIconIcon(%d,%d)",iconid,icon);
	Debug(DEBUG_ACTION,"set new data and destroy icon");
	ModeIconIconId{iconid} = icon;
	HideModeIcon(iconid);
	Debug(DEBUG_END,"SetModeIconIcon(reason: complete)");
	return 1;
}

stock GetModeIconColor(iconid)
{
	Debug(DEBUG_SMALL,"GetModeIconColor(%d)",iconid);
	return ModeIconColor[iconid];
}

stock SetModeIconColor(iconid,color)
{
	Debug(DEBUG_START,"SetModeIconColor(%d,%d)",iconid,color);
	Debug(DEBUG_ACTION,"set new data and destroy icon");
	ModeIconColor[iconid] = color;
	HideModeIcon(iconid);
	Debug(DEBUG_END,"SetModeIconColor(reason: complete)");
	return 1;
}

stock IsModeIconNeedToShow(playerid,iconid)
{
	Debug(DEBUG_START,"IsModeIconNeedToShow(%d,%d)",playerid,iconid);
	new res = 0;
	if(!IsPlayerInRangeOfPoint(playerid,MODE_ICONS_DISTANCE,ModeIconPos[iconid][0],ModeIconPos[iconid][1],ModeIconPos[iconid][2])) res = 0;
#if defined GetPlayerModeInterior
    else if((GetPlayerModeInterior(playerid) != ModeIconInterior{iconid}) && (ModeIconInterior{iconid} != INVALID_MODE_INTERIOR_ID)) res = 0;
#else
    else if((GetPlayerInterior(playerid) != ModeIconInterior{iconid}) && (ModeIconInterior{iconid} != INVALID_MODE_INTERIOR_ID)) res = 0;
#endif
	else if((GetPlayerVirtualWorld(playerid) != ModeIconVirtualWorld[iconid]) && (ModeIconVirtualWorld[iconid] != INVALID_VIRTUAL_WORLD_ID)) res = 0;
	else res = 1;

	Debug(DEBUG_END,"IsModeIconNeedToShow(reason: complete)");
	return res;
}

// --------------------------------------------------
// static functions
// --------------------------------------------------
static stock HideModeIcon(iconid)
{
	for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		if(IsPlayerNPC(playerid)) continue;
		
		if(ModeIconPlayerGameId[playerid]{iconid} != INVALID_ICON_ID)
		{
		    ModeIconPlayerSlots[playerid]{ ModeIconPlayerGameId[playerid]{iconid} } = 0;
			RemovePlayerMapIcon(playerid,ModeIconPlayerGameId[playerid]{iconid});
			if(ModeIconPlayerOffset{playerid} > ModeIconPlayerGameId[playerid]{iconid}) ModeIconPlayerOffset{playerid} = ModeIconPlayerGameId[playerid]{iconid};
			ModeIconPlayerGameId[playerid]{iconid} = INVALID_ICON_ID;
		}
	}
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Icons_Init()
{
	Debug(DEBUG_START,"Core_Icons_Init()");
	print("[CORE] Icons load complete.");
	Debug(DEBUG_END,"Core_Icons_Init(reason: complete)");
}

Core_Icons_ResetStat(playerid)
{
	Debug(DEBUG_START,"Core_Icons_ResetStat(%d)",playerid);
	for(new iconid = 0;iconid < MAX_MODE_ICONS;iconid++) ModeIconPlayerGameId[playerid]{iconid} = INVALID_ICON_ID;
	ModeIconPlayerOffset{playerid} = 0;
	Debug(DEBUG_END,"Core_Icons_ResetStat(reason: complete)");
}

Core_Icons_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Core_Icons_PlayerUpdate(%d)",playerid);
	for(new iconid = 0;iconid < ModeIconsCount;iconid++)
	{
		if(ModeIconState{iconid} == 0) continue;

		if(ModeIconPlayerGameId[playerid]{iconid} != INVALID_ICON_ID)
		{
			if(IsModeIconNeedToShow(playerid,iconid)) continue;
			
			ModeIconPlayerSlots[playerid]{ ModeIconPlayerGameId[playerid]{iconid} } = 0;
			RemovePlayerMapIcon(playerid,ModeIconPlayerGameId[playerid]{iconid});
			if(ModeIconPlayerOffset{playerid} > ModeIconPlayerGameId[playerid]{iconid}) ModeIconPlayerOffset{playerid} = ModeIconPlayerGameId[playerid]{iconid};
			ModeIconPlayerGameId[playerid]{iconid} = INVALID_ICON_ID;
		}
		else
		{
			if(!IsModeIconNeedToShow(playerid,iconid)) continue;
			
			for(new i = ModeIconPlayerOffset{playerid};i < MAX_ICONS;i++)
			{
			    if(ModeIconPlayerSlots[playerid]{i}) continue;
			    
				ModeIconPlayerSlots[playerid]{i} = 1;
				ModeIconPlayerGameId[playerid]{iconid} = i;
				SetPlayerMapIcon(playerid,i,ModeIconPos[iconid][0],ModeIconPos[iconid][1],ModeIconPos[iconid][2],ModeIconIconId{iconid},ModeIconColor[iconid]);
				ModeIconPlayerOffset{playerid} = i;
				break;
			}
		}
	}
	Debug(DEBUG_END,"Core_Icons_PlayerUpdate(reason: complete)");
}
