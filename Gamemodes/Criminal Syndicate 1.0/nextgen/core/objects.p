/*
*	Created:			23.08.09
*	Author:				009
*	Description:		Стриммер обьектов, изменение любого параметра 
*/

#if defined core_objects_included
	#endinput
#endif

#define core_objects_included
#pragma library core_objects

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/interiors.p"
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define MAX_SHOWED_OBJECTS 			255
#define MODE_OBJECTS_KICK_DISTANCE 	5.0

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
	// objects
	ModeObjectState[MAX_MODE_OBJECTS char],
	ModeObjectHidden[MAX_MODE_OBJECTS char],
	ModeObjectModel[MAX_MODE_OBJECTS],
	ModeObjectStaticObject[MAX_MODE_OBJECTS][MAX_PLAYERS char], // if MAX_SHOWED_OBJECTS <= 256
	ModeObjectAttachObjectId[MAX_MODE_OBJECTS char], // if MAX_SHOWED_OBJECTS <= 256
	ModeObjectAttachedTo[MAX_MODE_OBJECTS],
	Float:ModeObjectCoords[MAX_MODE_OBJECTS][3],
	Float:ModeObjectRots[MAX_MODE_OBJECTS][3],
	ModeObjectInterior[MAX_MODE_OBJECTS char],
	ModeObjectVirtualWorld[MAX_MODE_OBJECTS],
	ModeObjectType[MAX_MODE_OBJECTS char],
	ModeObjectTypeParam[MAX_MODE_OBJECTS],
	Float:ModeObjectMaxHealth[MAX_MODE_OBJECTS],
	Float:ModeObjectHealth[MAX_MODE_OBJECTS],
	// players
	ModeObjectPlayerClosestId[MAX_PLAYERS],
	ModeObjectPlayerShowedCount[MAX_PLAYERS char], // if MAX_SHOWED_OBJECTS <= 256
	ModeObjectPlayerAttachedId[MAX_PLAYERS],
	// server
	ModeObjectsOffset,
	ModeObjectsCount;

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward OnModeObjectDeath(objectid);
	
// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateModeObject(Model,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ,ModeInterior,VirtualWorld,Float:Health,Type,TypeParam)
{
	Debug(DEBUG_START,"CreateModeObject(%d,%f,%f,%f,%f,%f,%f,%d,%d,%f,%d,%d)",Model,X,Y,Z,rX,rY,rZ,ModeInterior,VirtualWorld,Health,Type,TypeParam);
	for(new objectid = ModeObjectsOffset;objectid < MAX_MODE_OBJECTS;objectid++)
	{
	    if(ModeObjectState{objectid} == 1) continue;
		Debug(DEBUG_ACTION,"Finded free slot,id = %d , set main data",objectid);
		ModeObjectState{objectid} = 1;
		ModeObjectHidden{objectid} = 0;
		ModeObjectModel[objectid] = Model;
		ModeObjectMaxHealth[objectid] = Health;
		ModeObjectHealth[objectid] = Health;
		Debug(DEBUG_ACTION,"set static data");
		for(new playerid = 0;playerid < MAX_PLAYERS;playerid++) ModeObjectStaticObject[objectid]{playerid} = INVALID_OBJECT_ID;
		Debug(DEBUG_ACTION,"set attach data");
		ModeObjectAttachObjectId{objectid} = INVALID_OBJECT_ID;
		ModeObjectAttachedTo[objectid] = INVALID_PLAYER_ID;
		Debug(DEBUG_ACTION,"set coordinates data");
		ModeObjectCoords[objectid][0] = X;
		ModeObjectCoords[objectid][1] = Y;
		ModeObjectCoords[objectid][2] = Z;
		ModeObjectRots[objectid][0] = rX;
		ModeObjectRots[objectid][1] = rY;
		ModeObjectRots[objectid][2] = rZ;
		ModeObjectInterior{objectid} = ModeInterior;
		ModeObjectVirtualWorld[objectid] = VirtualWorld;
		Debug(DEBUG_ACTION,"set type data");
		ModeObjectType{objectid} = Type;
		ModeObjectTypeParam[objectid] = TypeParam;
		Debug(DEBUG_ACTION,"set offsets(old: %d,%d)",ModeObjectsOffset,ModeObjectsCount);
		ModeObjectsOffset = objectid;
		if(ModeObjectsCount < objectid) ModeObjectsCount = objectid;
		Debug(DEBUG_END,"CreateModeObject(reason: complete)");
		return objectid;
	}
	Debug(DEBUG_END,"CreateModeObject(reason: error)");
	print("[ERROR] Core -> Objects -> CreateModeObject (all slots used)");
	return 0;
}

stock DestroyModeObject(objectid)
{
	Debug(DEBUG_START,"DestroyModeObject(%d)",objectid);
	ModeObjectState{objectid} = 0;
	ModeObjectHidden{objectid} = 0;
	ModeObjectModel[objectid] = 0;
	ModeObjectMaxHealth[objectid] = 0.0;
	ModeObjectHealth[objectid] = 0.0;
	Debug(DEBUG_ACTION,"free players data");
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
		{
			if(!IsPlayerConnected(playerid)) continue;
			if(IsPlayerNPC(playerid)) continue;
		
			if(ModeObjectStaticObject[objectid]{playerid} == INVALID_OBJECT_ID) continue;
			DestroyPlayerObject(playerid,ModeObjectStaticObject[objectid]{playerid});
			ModeObjectPlayerShowedCount{playerid}--;
			ModeObjectStaticObject[objectid]{playerid} = INVALID_OBJECT_ID;
			if(ModeObjectPlayerClosestId[playerid] == objectid) ModeObjectPlayerClosestId[playerid] = INVALID_MODE_OBJECT_ID;
		}
	}
	else
	{
	    DestroyObject(ModeObjectAttachObjectId{objectid});
		ModeObjectAttachObjectId{objectid} = INVALID_OBJECT_ID;
	}
	Debug(DEBUG_ACTION,"attach info reset");
	ModeObjectAttachObjectId{objectid} = INVALID_OBJECT_ID;
	ModeObjectAttachedTo[objectid] = INVALID_PLAYER_ID;
	Debug(DEBUG_ACTION,"coordinates info reset");
	for(new i = 0;i < 3;i++)
	{
		ModeObjectCoords[objectid][i] = 0.0;
		ModeObjectRots[objectid][i] = 0.0;
	}
	ModeObjectInterior{objectid} = 0;
	ModeObjectVirtualWorld[objectid] = 0;
	Debug(DEBUG_ACTION,"type info reset");
	ModeObjectType{objectid} = 0;
	ModeObjectTypeParam[objectid] = 0;
	Debug(DEBUG_ACTION,"set offsets");
	if(ModeObjectsOffset > objectid) ModeObjectsOffset = objectid;
	if(ModeObjectsCount == objectid) 
	{
		do ModeObjectsCount--;
		while((ModeObjectState{ ModeObjectsCount } == 0) && (ModeObjectsCount > 0));
	}
	Debug(DEBUG_END,"DestroyModeObject(reason: complete)");
	return 1;
}

stock GetModeObjectPos(objectid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetModeObjectPos(%d)",objectid);
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    Debug(DEBUG_ACTION,"get coords from object's data");
		X = ModeObjectCoords[objectid][0];
		Y = ModeObjectCoords[objectid][1];
		Z = ModeObjectCoords[objectid][2];
		Debug(DEBUG_END,"GetModeObjectPos(reason: complete)");
		return 1;
	}
	else
	{
	    Debug(DEBUG_ACTION,"get player coords");
		new Float:angle;
		GetPlayerFacingAngle(ModeObjectAttachedTo[objectid],angle);
		GetPlayerPos(ModeObjectAttachedTo[objectid],X,Y,Z);
		Debug(DEBUG_ACTION,"get object coords from player's");
		X += (ModeObjectCoords[objectid][0] * floatsin(-(angle - 90.0), degrees)) + (ModeObjectCoords[objectid][1] * floatsin(-angle, degrees));
		Y += (ModeObjectCoords[objectid][0] * floatcos(-(angle - 90.0), degrees)) + (ModeObjectCoords[objectid][1] * floatcos(-angle, degrees));
		Z += ModeObjectCoords[objectid][2];
		Debug(DEBUG_END,"GetModeObjectPos(reason: complete)");
		return 1;
	}
}

stock SetModeObjectPos(objectid,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetModeObjectPos(%d,%f,%f,%f)",objectid,X,Y,Z);
    if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    Debug(DEBUG_ACTION,"set new coords");
		ModeObjectCoords[objectid][0] = X;
		ModeObjectCoords[objectid][1] = Y;
		ModeObjectCoords[objectid][2] = Z;
		
		for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
		{
			if(!IsPlayerConnected(playerid)) continue;
			if(IsPlayerNPC(playerid)) continue;
			if(ModeObjectStaticObject[objectid]{playerid} == INVALID_OBJECT_ID) continue;
			
			if(IsModeObjectNeedToShow(playerid,objectid)) SetPlayerObjectPos(playerid,objectid,X,Y,Z);
		}
	}
	Debug(DEBUG_END,"SetModeObjectPos(reason: complete)");
	return 1;
}

stock GetModeObjectRot(objectid,&Float:rX,&Float:rY,&Float:rZ)
{
	Debug(DEBUG_START,"GetModeObjectRot(%d)",objectid);
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
		Debug(DEBUG_ACTION,"object static");
		rX = ModeObjectRots[objectid][0];
		rY = ModeObjectRots[objectid][1];
		rZ = ModeObjectRots[objectid][2];
		Debug(DEBUG_END,"GetModeObjectRot(reason: complete)");
		return 1;
	}
	else
	{
		Debug(DEBUG_ACTION,"object attached");
		rX = ModeObjectRots[objectid][0];
		rY = ModeObjectRots[objectid][1];
		GetPlayerFacingAngle(ModeObjectAttachedTo[objectid],rZ);
		Debug(DEBUG_END,"GetModeObjectRot(reason: complete)");
		return 1;
	}
}

stock SetModeObjectRot(objectid,Float:rX,Float:rY,Float:rZ)
{
	Debug(DEBUG_START,"SetModeObjectRot(%d,%f,%f,%f)",objectid,rX,rY,rZ);
    if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    Debug(DEBUG_ACTION,"set new rots");
		ModeObjectRots[objectid][0] = rX;
		ModeObjectRots[objectid][1] = rY;
		ModeObjectRots[objectid][2] = rZ;

		for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
		{
			if(!IsPlayerConnected(playerid)) continue;
			if(IsPlayerNPC(playerid)) continue;
			if(ModeObjectStaticObject[objectid]{playerid} == INVALID_OBJECT_ID) continue;

			SetPlayerObjectRot(playerid,objectid,rX,rY,rZ);
		}
	}
	Debug(DEBUG_END,"SetModeObjectRot(reason: complete)");
	return 1;
}

stock GetModeObjectModeInterior(objectid)
{
	Debug(DEBUG_START,"GetModeObjectModeInterior(%d)",objectid);
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
		Debug(DEBUG_END,"GetModeObjectModeInterior(reason: complete)");
		return ModeObjectInterior{objectid};
	}
	else
	{
		Debug(DEBUG_END,"GetModeObjectModeInterior(reason: complete)");
#if defined GetPlayerModeInterior
		return GetPlayerModeInterior(ModeObjectAttachedTo[objectid]);
#else
    	return GetPlayerInterior(ModeObjectAttachedTo[objectid]);
#endif
	}
}

stock SetModeObjectModeInterior(objectid,modeinterior)
{
	Debug(DEBUG_START,"SetModeObjectModeInterior(%d,%d)",objectid,modeinterior);
    if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    ModeObjectInterior{objectid} = modeinterior;
	    HideObject(objectid);
	    Debug(DEBUG_END,"SetModeObjectModeInterior(reason: complete)");
		return 1;
	}
	else
	{
		Debug(DEBUG_END,"SetModeObjectModeInterior(reason: error)");
		printf("[ERROR] Core -> Objects -> SetModeObjectModeInterior (try to set mode interior while object attached, objectid = %d)",objectid);
		return 0;
	}
}

stock GetModeObjectVirtualWorld(objectid)
{
	Debug(DEBUG_START,"GetModeObjectVirtualWorld(%d)",objectid);
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
		Debug(DEBUG_END,"GetModeObjectVirtualWorld(reason: complete)");
		return ModeObjectVirtualWorld[objectid];
	}
	else
	{
		Debug(DEBUG_END,"GetModeObjectVirtualWorld(reason: complete)");
		return GetPlayerVirtualWorld(ModeObjectAttachedTo[objectid]);
	}
}

stock SetModeObjectVirtualWorld(objectid,virtualworld)
{
	Debug(DEBUG_START,"SetModeObjectVirtualWorld(%d,%d)",objectid,virtualworld);
    if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    ModeObjectVirtualWorld[objectid] = virtualworld;
	    HideObject(objectid);
	    Debug(DEBUG_END,"SetModeObjectVirtualWorld(reason: complete)");
		return 1;
	}
	else
	{
		Debug(DEBUG_END,"SetModeObjectVirtualWorld(reason: error)");
		printf("[ERROR] Core -> Objects -> SetModeObjectVirtualWorld (try to set virtual world while object attached, objectid = %d)",objectid);
		return 0;
	}
}

stock AttachModeObjectToPlayer(objectid,playerid,Float:oX,Float:oY,Float:oZ,Float:orX,Float:orY,Float:orZ)
{
	Debug(DEBUG_START,"AttachModeObjectToPlayer(%d,%d,%f,%f,%f,%f,%f,%f)",objectid,playerid,oX,oY,oZ,orX,orY,orZ);
	if(ModeObjectAttachObjectId{objectid} != INVALID_OBJECT_ID)
	{
		Debug(DEBUG_END,"AttachModeObjectToPlayer(reason: error)");
		printf("[ERROR] Core -> Objects -> AttachModeObjectToPlayer (try attach also attached object, objectid = %d)",objectid);
		return 0;
	}
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"AttachModeObjectToPlayer(reason: error)");
		printf("[ERROR] Core -> Objects -> AttachModeObjectToPlayer (try attach object to offline player, objectid = %d, playerid = %d)",objectid,playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"Destroy object for players");
	HideObject(objectid);
	Debug(DEBUG_ACTION,"set info");
	ModeObjectAttachObjectId{objectid} = CreateObject(ModeObjectModel[objectid],0.0,0.0,0.0,0.0,0.0,0.0,150.0);
	ModeObjectAttachedTo[objectid] = playerid;
	ModeObjectCoords[objectid][0] = oX;
	ModeObjectCoords[objectid][1] = oY;
	ModeObjectCoords[objectid][2] = oZ;
	ModeObjectRots[objectid][0] = orX;
	ModeObjectRots[objectid][1] = orY;
	ModeObjectRots[objectid][2] = orZ;
	AttachObjectToPlayer(ModeObjectAttachObjectId{objectid},playerid,oX,oY,oZ,orX,orY,orZ);
	ModeObjectPlayerAttachedId[playerid] = objectid;
	Debug(DEBUG_END,"AttachModeObjectToPlayer(reason: complete)");
	return 1;
}

stock DeAttachModeObject(objectid)
{
	Debug(DEBUG_START,"DeAttachModeObject(%d)",objectid);
	if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
		Debug(DEBUG_END,"DeAttachModeObject(reason: error)");
		printf("[ERROR] Core -> Objects -> DeAttachModeObject (try deattach not attached object, objectid = %d)",objectid);
		return 0;
	}
	Debug(DEBUG_ACTION,"get player pos");
	new Float:angle,
		Float:Pos[3];
	GetPlayerFacingAngle(ModeObjectAttachedTo[objectid],angle);
	GetPlayerPos(ModeObjectAttachedTo[objectid],Pos[0],Pos[1],Pos[2]);
	Debug(DEBUG_ACTION,"get object pos using player's pos");
	Pos[0] += (ModeObjectCoords[objectid][0] * floatsin(-(angle - 90.0), degrees)) + (ModeObjectCoords[objectid][1] * floatsin(-angle, degrees));
	Pos[1] += (ModeObjectCoords[objectid][0] * floatcos(-(angle - 90.0), degrees)) + (ModeObjectCoords[objectid][1] * floatcos(-angle, degrees));
	Pos[2] += ModeObjectCoords[objectid][2];
	Debug(DEBUG_ACTION,"write object data");
	ModeObjectCoords[objectid][0] = Pos[0];
	ModeObjectCoords[objectid][1] = Pos[1];
	ModeObjectCoords[objectid][2] = Pos[2];
	ModeObjectRots[objectid][2] = angle;
#if defined GetPlayerModeInterior
	ModeObjectInterior{objectid} = GetPlayerModeInterior(ModeObjectAttachedTo[objectid]);
#else
    ModeObjectInterior{objectid} = GetPlayerInterior(ModeObjectAttachedTo[objectid]);
#endif
	ModeObjectVirtualWorld[objectid] = GetPlayerVirtualWorld(ModeObjectAttachedTo[objectid]);
	Debug(DEBUG_ACTION,"delete info about attach");
	DestroyObject(ModeObjectAttachObjectId{objectid});
	ModeObjectAttachObjectId{objectid} = INVALID_OBJECT_ID;
	ModeObjectPlayerAttachedId[ ModeObjectAttachedTo[objectid] ] = INVALID_MODE_OBJECT_ID;
	ModeObjectAttachedTo[objectid] = INVALID_PLAYER_ID;
	Debug(DEBUG_END,"DeAttachModeObject(reason: complete)");
	return 1;
}

stock IsModeObjectAttached(objectid)
{
	Debug(DEBUG_SMALL,"IsModeObjectAttached(%d)",objectid);
	return (ModeObjectAttachObjectId{objectid} != INVALID_OBJECT_ID);
}

stock GetPlayerAttachedModeObject(playerid)
{
	Debug(DEBUG_START,"GetPlayerAttachedModeObject(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerAttachedModeObject(reason: error)");
		printf("[ERROR] Core -> Objects -> GetPlayerAttachedModeObject (try get attached object offline player's, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_END,"GetPlayerAttachedModeObject(reason: complete)");
	return ModeObjectPlayerAttachedId[playerid];
}

stock GetModeObjectModel(objectid)
{
	Debug(DEBUG_SMALL,"GetModeObjectModel(%d)",objectid);
	return ModeObjectModel[objectid];
}

stock GetModeObjectType(objectid)
{
	Debug(DEBUG_SMALL,"GetModeObjectType(%d)",objectid);
	return ModeObjectType{objectid};
}

stock SetModeObjectType(objectid,type)
{
	Debug(DEBUG_SMALL,"SetModeObjectType(%d,%d)",objectid,type);
	ModeObjectType{objectid} = type;
	return 1;
}

stock GetModeObjectTypeParam(objectid)
{
	Debug(DEBUG_SMALL,"GetModeObjectTypeParam(%d)",objectid);
	return ModeObjectTypeParam[objectid];
}

stock SetModeObjectTypeParam(objectid,typeparam)
{
	Debug(DEBUG_SMALL,"SetModeObjectTypeParam(%d,%d)",objectid,typeparam);
	ModeObjectTypeParam[objectid] = typeparam;
	return 1;
}

stock Float:GetModeObjectHealth(objectid)
{
	Debug(DEBUG_SMALL,"GetModeObjectHealth(%d)",objectid);
	return ModeObjectHealth[objectid];
}

stock SetModeObjectHealth(objectid,Float:health)
{
	Debug(DEBUG_SMALL,"SetModeObjectHealth(%d,%f)",objectid,health);
	ModeObjectHealth[objectid] = health;
	return 1;
}

stock GetPlayerClosestModeObject(playerid)
{
	Debug(DEBUG_SMALL,"GetPlayerClosestModeObject(%d)",playerid);
	return ModeObjectPlayerClosestId[playerid];
}

stock Float:GetPlayerDistanceToModeObject(playerid,objectid)
{
	Debug(DEBUG_START,"GetPlayerDistanceToModeObject(%d,%d)",playerid,objectid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerDistanceToModeObject(reason: error)");
		printf("[ERROR] Core -> Objects -> GetPlayerDistanceToModeObject (try get distance to object offline player's, playerid = %d)",playerid);
		return 0.0;
	}
	new Float:pos[3],Float:d;
	GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
	d = floatsqroot(floatpower(pos[0] - ModeObjectCoords[objectid][0],2) + floatpower(pos[1] - ModeObjectCoords[objectid][1],2) + floatpower(pos[2] - ModeObjectCoords[objectid][2],2));
	Debug(DEBUG_END,"GetPlayerDistanceToModeObject(reason: complete)");
	return d;
}

stock IsModeObjectNeedToShow(playerid,objectid)
{
	Debug(DEBUG_START,"IsModeObjectNeedToShow(%d,%d)",playerid,objectid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsModeObjectNeedToShow(reason: error)");
		printf("[ERROR] Core -> Objects -> IsModeObjectNeedToShow (try check object for offline player, playerid = %d)",playerid);
		return 0;
	}
	new res = 0;
	if(ModeObjectHidden{objectid} == 1) res = 0;
	else
	{
	    new Float:pos[3],
			modeinterior = GetModeObjectModeInterior(objectid),
			virtualworld = GetModeObjectVirtualWorld(objectid);
		GetModeObjectPos(objectid,pos[0],pos[1],pos[2]);
		
		if(!IsPlayerInRangeOfPoint(playerid,MODE_OBJECTS_DISTANCE,pos[0],pos[1],pos[2])) res = 0;
#if defined GetPlayerModeInterior
		else if((GetPlayerModeInterior(playerid) != modeinterior) && (modeinterior != INVALID_MODE_INTERIOR_ID)) res = 0;
#else
		else if((GetPlayerInterior(playerid) != modeinterior) && (modeinterior != INVALID_MODE_INTERIOR_ID)) res = 0;
#endif
		else if((GetPlayerVirtualWorld(playerid) != virtualworld) && (virtualworld != INVALID_VIRTUAL_WORLD_ID)) res = 0;
		else res = 1;
	}
	Debug(DEBUG_END,"IsModeObjectNeedToShow(reason: complete)");
	return res;
}

stock IsPlayerRangeOfModeObject(playerid,Float:range,objectid)
{
	Debug(DEBUG_START,"IsPlayerRangeOfModeObject(%d,%f,%d)",playerid,range,objectid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsPlayerRangeOfModeObject(reason: error)");
		printf("[ERROR] Core -> Objects -> IsPlayerRangeOfModeObject (try check range of object for offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_END,"IsPlayerRangeOfModeObject(reason: complete)");
	new Float:pos[3];
	GetModeObjectPos(objectid,pos[0],pos[1],pos[2]);
	return IsPlayerInRangeOfPoint(playerid,range,pos[0],pos[1],pos[2]);
}

stock HideModeObject(objectid)
{
	Debug(DEBUG_START,"HideModeObject(%d)",objectid);
	ModeObjectHidden{objectid} = 1;
	Debug(DEBUG_END,"HideModeObject(reason: complete)");
	return 1;
}

stock ShowModeObject(objectid)
{
	Debug(DEBUG_START,"ShowModeObject(%d)",objectid);
	ModeObjectHidden{objectid} = 0;
	Debug(DEBUG_END,"ShowModeObject(reason: complete)");
	return 1;
}

stock IsModeObjectStreamedIn(objectid,playerid)
{
	Debug(DEBUG_START,"IsModeObjectStreamedIn(%d,%d)",objectid,playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsModeObjectStreamedIn(reason: error)");
		printf("[ERROR] Core -> Objects -> IsModeObjectStreamedIn (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_END,"IsModeObjectStreamedIn(reason: complete)");
	return (ModeObjectStaticObject[objectid]{playerid} != INVALID_OBJECT_ID);
}

stock GetMaxModeObjectId()
{
    Debug(DEBUG_SMALL,"GetMaxModeObjectId()");
	return ModeObjectsCount;
}

stock IsValidModeObject(objectid)
{
    Debug(DEBUG_SMALL,"IsValidModeObject(%d)",objectid);
	return ModeObjectState{objectid};
}

// --------------------------------------------------
// static functions
// --------------------------------------------------
static stock HideObject(objectid)
{
    if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
	{
	    for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
		{
			if(!IsPlayerConnected(playerid)) continue;
			if(IsPlayerNPC(playerid)) continue;
			
			if(ModeObjectStaticObject[objectid]{playerid} == INVALID_OBJECT_ID) continue;
			DestroyPlayerObject(playerid,ModeObjectStaticObject[objectid]{playerid});
			ModeObjectStaticObject[objectid]{playerid} = INVALID_OBJECT_ID;
			if(ModeObjectPlayerClosestId[playerid] == objectid) ModeObjectPlayerClosestId[playerid] = INVALID_MODE_OBJECT_ID;
            ModeObjectPlayerShowedCount{playerid}--;
		}
	}
	else
	{
	    DestroyObject(ModeObjectAttachObjectId{objectid});
	    // recreate, hide attach may only destroy/deattach
	    ModeObjectAttachObjectId{objectid} = CreateObject(ModeObjectModel[objectid],0.0,0.0,0.0,0.0,0.0,0.0,150.0);
		AttachObjectToPlayer(ModeObjectAttachObjectId{objectid},ModeObjectAttachedTo[objectid],ModeObjectCoords[objectid][0],ModeObjectCoords[objectid][1],ModeObjectCoords[objectid][2],ModeObjectRots[objectid][0],ModeObjectRots[objectid][1],ModeObjectRots[objectid][2]);
	}
}

static stock IsPlayerAttackObject(playerid,objectid,Float:pos_x,Float:pos_y,Float:pos_z)
{
   	if(IsPlayerInRangeOfPoint(playerid,MODE_OBJECTS_KICK_DISTANCE,pos_x,pos_y,pos_z))
	{
		if(ModeObjectPlayerClosestId[playerid] == objectid)
		{
			new Float:angle,
				Float:pos[3];
			GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
			GetPlayerFacingAngle(playerid,angle);
			new Float:distance = GetPlayerDistanceToModeObject(playerid,objectid);
			pos[0] += (distance * floatsin(-angle, degrees)) - pos_x;
			pos[1] += (distance * floatcos(-angle, degrees)) - pos_y;
			pos[2] -= pos_z;
			return (floatpower(pos[0],2) + floatpower(pos[1],2) + floatpower(pos[2],2) < floatpower(MODE_OBJECTS_KICK_DISTANCE,2));
		}
	}
	return 0;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Objects_Init()
{
	Debug(DEBUG_START,"Core_Objects_Init()");
	print("[CORE] Objects load complete.");
	Debug(DEBUG_END,"Core_Objects_Init(reason: complete)");
}

Core_Objects_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Core_Objects_PlayerUpdate(%d)",playerid);
	for(new objectid = 0;objectid <= ModeObjectsCount;objectid++)
	{
		if(ModeObjectState{objectid} == 0) continue;
		
		if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
		{
			if(ModeObjectStaticObject[objectid]{playerid} == INVALID_OBJECT_ID)
			{
				if(!IsModeObjectNeedToShow(playerid,objectid)) continue;
				if(ModeObjectPlayerShowedCount{playerid} == MAX_SHOWED_OBJECTS)
				{
					static
						Float: dist,
						Float: d,
						id;
					dist = 0.0;
					for(new nobjectid = 0;nobjectid <= ModeObjectsCount;nobjectid++)
					{
						if(ModeObjectState{nobjectid} == 0) continue;
						if(ModeObjectStaticObject[nobjectid]{playerid} == INVALID_OBJECT_ID) continue;
						d = GetPlayerDistanceToModeObject(playerid,nobjectid);
						if(d > dist)
						{
							dist = d;
							id = nobjectid;
						}
					}
					if(GetPlayerDistanceToModeObject(playerid,objectid) < dist) HideObject(id);
					else continue;
				}
				if(ModeObjectPlayerShowedCount{playerid} < MAX_SHOWED_OBJECTS )
				{
					ModeObjectStaticObject[objectid]{playerid} = CreatePlayerObject(playerid,ModeObjectModel[objectid],ModeObjectCoords[objectid][0],ModeObjectCoords[objectid][1],ModeObjectCoords[objectid][2],ModeObjectRots[objectid][0],ModeObjectRots[objectid][1],ModeObjectRots[objectid][2],150.0);
					ModeObjectPlayerShowedCount{playerid}++;
				}
			}
			else
			{
				if(!IsModeObjectNeedToShow(playerid,objectid)) HideObject(objectid);
				else
				{
					if(ModeObjectPlayerClosestId[playerid] == INVALID_MODE_OBJECT_ID) ModeObjectPlayerClosestId[playerid] = objectid;
					else if(GetPlayerDistanceToModeObject(playerid,ModeObjectPlayerClosestId[playerid]) > GetPlayerDistanceToModeObject(playerid,objectid)) ModeObjectPlayerClosestId[playerid] = objectid;
#if defined IsPlayerControllable
                    if(!IsPlayerControllable(playerid)) continue;
#endif
					if(ModeObjectMaxHealth[objectid] < 0.0) continue;
					
					new keys[3];
					GetPlayerKeys(playerid,keys[0],keys[1],keys[2]);
					if(keys[0] & KEY_FIRE)
					{
					    if(!IsPlayerAttackObject(playerid,objectid,ModeObjectCoords[objectid][0],ModeObjectCoords[objectid][1],ModeObjectCoords[objectid][2])) continue;

	 					ModeObjectHealth[objectid] -= 5.0;
						new Float:hel = (ModeObjectHealth[objectid] / ModeObjectMaxHealth[objectid]) * 100.0;

						if(hel > 90.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~g~----------",1000,5);
						else if(hel > 80.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~g~---------",1000,5);
						else if(hel > 70.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~y~--------",1000,5);
						else if(hel > 60.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~y~-------",1000,5);
						else if(hel > 50.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~y~------",1000,5);
						else if(hel > 40.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~y~-----",1000,5);
						else if(hel > 30.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~r~----",1000,5);
						else if(hel > 20.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~r~---",1000,5);
						else if(hel > 10.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~r~--",1000,5);
						else if(hel > 0.0) GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~r~-",1000,5);
						else
						{
						    if(OnModeObjectDeath(objectid)) DestroyModeObject(objectid);
						}
					}
				}
			}
		}
	}
	Debug(DEBUG_END,"Core_Objects_PlayerUpdate(reason: complete)");
}

Core_Objects_ResetStat(playerid)
{
	Debug(DEBUG_START,"Core_Objects_ResetStat(%d)",playerid);
	for(new objectid = 0;objectid < MAX_MODE_OBJECTS;objectid++) ModeObjectStaticObject[objectid]{playerid} = INVALID_OBJECT_ID;
	ModeObjectPlayerShowedCount{playerid} = 0;
	ModeObjectPlayerClosestId[playerid] = INVALID_MODE_OBJECT_ID;
	ModeObjectPlayerAttachedId[playerid] = INVALID_MODE_OBJECT_ID;
	Debug(DEBUG_END,"Core_Objects_ResetStat(reason: complete)");
}

Core_Objects_PlayerStream(playerid)
{
	Debug(DEBUG_START,"Core_Objects_PlayerStream(%d)",playerid);
	if(ModeObjectPlayerAttachedId[playerid] != INVALID_MODE_OBJECT_ID)
	{
		Debug(DEBUG_ACTION,"player attaching object");
		new objectid = ModeObjectPlayerAttachedId[playerid];
		if(ModeObjectAttachObjectId{objectid} == INVALID_OBJECT_ID)
		{
			Debug(DEBUG_END,"Core_Objects_PlayerStream(reason: error)");
			printf("[ERROR] Core -> Objects -> Core_Objects_PlayerStream (player attached not attached object, playerid = %d)",playerid);
			return 0;
		}
		HideObject(playerid);
		Debug(DEBUG_END,"Core_Objects_PlayerStream(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Core_Objects_PlayerStream(reason: complete)");
	return 1;
}
