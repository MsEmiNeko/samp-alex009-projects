/*
*	Created:			27.12.09
*	Author:				009
*	Description:		Стриммер 3D текстов, изменение любого параметра 
*/

#if defined core_3dtexts_included
	#endinput
#endif

#define core_3dtexts_included
#pragma library core_3dtexts

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/interiors.p"
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define MAX_3DTEXT_STRING 			512

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// enums
// --------------------------------------------------
enum
{
    TEXT3D_ATTACH_NONE,
	TEXT3D_ATTACH_PLAYER,
	TEXT3D_ATTACH_VEHICLE
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	// 3dtexts
	Mode3DTextState[MAX_MODE_3DTEXTS char],
	Mode3DTextText[MAX_MODE_3DTEXTS][MAX_3DTEXT_STRING char],
	Mode3DTextColor[MAX_MODE_3DTEXTS],
	Float:Mode3DTextDrawDistance[MAX_MODE_3DTEXTS],
	Mode3DTextLOS[MAX_MODE_3DTEXTS char],
	Float:Mode3DTextCoords[MAX_MODE_3DTEXTS][3],
	Mode3DTextInterior[MAX_MODE_3DTEXTS char],
	Mode3DTextVirtualWorld[MAX_MODE_3DTEXTS],
	Mode3DTextAttachType[MAX_MODE_3DTEXTS char],
	Mode3DTextAttachedTo[MAX_MODE_3DTEXTS],
	// players
	PlayerText3D:Mode3DTextGameId[MAX_PLAYERS][MAX_MODE_3DTEXTS],
	// servers
	Mode3DTextsOffset,
	Mode3DTextsCount;

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native CreateMode3DText(Text[],Color,Float:X,Float:Y,Float:Z,Float:DrawDistance,ModeInterior,VirtualWorld,LOS);
native DestroyMode3DText(text3did);
native GetMode3DTextPos(text3did,&Float:X,&Float:Y,&Float:Z);
native SetMode3DTextPos(text3did,Float:X,Float:Y,Float:Z);
native GetMode3DTextModeInterior(text3did);
native SetMode3DTextModeInterior(text3did,modeinterior);
native GetMode3DTextVirtualWorld(text3did);
native SetMode3DTextVirtualWorld(text3did,virtualworld);
native AttachMode3DTextToPlayer(text3did,playerid,Float:oX,Float:oY,Float:oZ);
native AttachMode3DTextToVehicle(text3did,vehicleid,Float:oX,Float:oY,Float:oZ);
native DeAttachMode3DText(text3did);
native IsMode3DTextAttached(text3did);
native GetMode3DTextText(text3did);
native SetMode3DTextText(text3did,Text[]);
native GetMode3DTextColor(text3did);
native SetMode3DTextColor(text3did,Color);
native Float:GetMode3DTextDrawDistance(text3did);
native SetMode3DTextDrawDistance(text3did,Float:DrawDistance);
native IsMode3DTextNeedToShow(playerid,text3did);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateMode3DText(Text[],Color,Float:X,Float:Y,Float:Z,Float:DrawDistance,ModeInterior,VirtualWorld,LOS)
{
	Debug(DEBUG_START,"CreateMode3DText(%s,%d,%f,%f,%f,%f,%d,%d,%d)",Text,Color,X,Y,Z,DrawDistance,ModeInterior,VirtualWorld,LOS);
	for(new text3did = Mode3DTextsOffset;text3did < MAX_MODE_3DTEXTS;text3did++)
	{
		if(Mode3DTextState{text3did} == 1) continue;
		Debug(DEBUG_ACTION,"Finded free slot,id = %d , set main data",text3did);
		Mode3DTextState{text3did} = true;
		strpack(Mode3DTextText[text3did],Text,MAX_3DTEXT_STRING);
		Mode3DTextColor[text3did] = Color;
		Mode3DTextDrawDistance[text3did] = DrawDistance;
		Mode3DTextLOS{text3did} = LOS;
		Debug(DEBUG_ACTION,"Set coordinates data");
		Mode3DTextCoords[text3did][0] = X;
		Mode3DTextCoords[text3did][1] = Y;
		Mode3DTextCoords[text3did][2] = Z;
		Mode3DTextInterior{text3did} = ModeInterior;
		Mode3DTextVirtualWorld[text3did] = VirtualWorld;
		Debug(DEBUG_ACTION,"Set attach data");
		Mode3DTextAttachType{text3did} = TEXT3D_ATTACH_NONE;
		Mode3DTextAttachedTo[text3did] = INVALID_3DTEXT_ATTACH_ID;
		Debug(DEBUG_ACTION,"Set offset data(old: %d,%d)",Mode3DTextsOffset,Mode3DTextsCount);
		Mode3DTextsOffset = text3did;
		if(Mode3DTextsCount < text3did) Mode3DTextsCount = text3did;
		Debug(DEBUG_ACTION,"New offset data: %d,%d",Mode3DTextsOffset,Mode3DTextsCount);
		Debug(DEBUG_END,"CreateMode3DText(reason: complete, id = %d)",text3did);
		return text3did;
	}
	Debug(DEBUG_END,"CreateMode3DText(reason: all slots used)");
	print("[ERROR] Core -> 3DTexts -> CreateMode3DText (all slots used)");
	return INVALID_MODE_3DTEXT_ID;
}

stock DestroyMode3DText(text3did)
{
	Debug(DEBUG_START,"DestroyMode3DText(%d)",text3did);
	Debug(DEBUG_ACTION,"Delete main data",text3did);
	Mode3DTextState{text3did} = 0;
	strpack(Mode3DTextText[text3did],"",MAX_3DTEXT_STRING);
	Mode3DTextColor[text3did] = 0;
	Mode3DTextDrawDistance[text3did] = 0.0;
	Mode3DTextLOS{text3did} = 0;
	Debug(DEBUG_ACTION,"Delete coordinates data");
	for(new i = 0;i < 3;i++) Mode3DTextCoords[text3did][i] = 0.0;
	Mode3DTextInterior{text3did} = 0;
	Mode3DTextVirtualWorld[text3did] = 0;
	Debug(DEBUG_ACTION,"Delete attach data");
	Mode3DTextAttachType{text3did} = TEXT3D_ATTACH_NONE;
	Mode3DTextAttachedTo[text3did] = INVALID_3DTEXT_ATTACH_ID;
	for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		if(Mode3DTextGameId[playerid][text3did] == INVALID_3DTEXT_PLAYER_ID) continue;
		DeletePlayer3DTextLabel(playerid,Mode3DTextGameId[playerid][text3did]);
		Mode3DTextGameId[playerid][text3did] = INVALID_3DTEXT_PLAYER_ID;
	}
	Debug(DEBUG_ACTION,"Delete offset data(old: %d,%d)",Mode3DTextsOffset,Mode3DTextsCount);
	if(Mode3DTextsOffset > text3did) Mode3DTextsOffset = text3did;
	if(Mode3DTextsCount == text3did) 
	{
		do Mode3DTextsCount--;
		while((Mode3DTextState{ Mode3DTextsCount } == 0) && (Mode3DTextsCount > 0));
	}
	Debug(DEBUG_ACTION,"New offset data: %d,%d",Mode3DTextsOffset,Mode3DTextsCount);
	Debug(DEBUG_END,"DestroyMode3DText(reason: complete)");
	return 1;
}

stock GetMode3DTextPos(text3did,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetMode3DTextPos(%d)",text3did);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE:
		{
			Debug(DEBUG_ACTION,"3DText not attached");
			X = Mode3DTextCoords[text3did][0];
			Y = Mode3DTextCoords[text3did][1];
			Z = Mode3DTextCoords[text3did][2];
			Debug(DEBUG_END,"GetMode3DTextPos(reason: complete)");
			return 1;
		}
		case TEXT3D_ATTACH_PLAYER:
		{
			Debug(DEBUG_ACTION,"3DText attached to player");
			if(!IsPlayerConnected(Mode3DTextAttachedTo[text3did]))
			{
				Debug(DEBUG_END,"GetMode3DTextPos(reason: error)");
				printf("[ERROR] Core -> 3DTexts -> GetMode3DTextPos (3dtext attached to offline player, text3did = %d, playerid = %d)",text3did,Mode3DTextAttachedTo[text3did]);
				return 0;
			}
			new Float:angle;
			GetPlayerFacingAngle(Mode3DTextAttachedTo[text3did],angle);
			GetPlayerPos(Mode3DTextAttachedTo[text3did],X,Y,Z);
			Debug(DEBUG_ACTION,"player pos: %f,%f,%f angle %f",X,Y,Z,angle);
			X += (Mode3DTextCoords[text3did][0] * floatsin(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatsin(-angle, degrees));
			Y += (Mode3DTextCoords[text3did][0] * floatcos(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatcos(-angle, degrees));
			Z += Mode3DTextCoords[text3did][2];
			Debug(DEBUG_END,"GetMode3DTextPos(reason: complete)");
			return 1;
		}
		case TEXT3D_ATTACH_VEHICLE: 
		{
			Debug(DEBUG_ACTION,"3DText attached to vehicle");
			new Float:angle;
			GetVehicleZAngle(Mode3DTextAttachedTo[text3did],angle);
			GetVehiclePos(Mode3DTextAttachedTo[text3did],X,Y,Z);
			Debug(DEBUG_ACTION,"vehicle pos: %f,%f,%f angle %f",X,Y,Z,angle);
			X += (Mode3DTextCoords[text3did][0] * floatsin(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatsin(-angle, degrees));
			Y += (Mode3DTextCoords[text3did][0] * floatcos(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatcos(-angle, degrees));
			Z += Mode3DTextCoords[text3did][2];
			Debug(DEBUG_END,"GetMode3DTextPos(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"GetMode3DTextPos(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> GetMode3DTextPos (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock SetMode3DTextPos(text3did,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetMode3DTextPos(%d)",text3did);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE:
		{
			Debug(DEBUG_ACTION,"3DText not attached");
			Mode3DTextCoords[text3did][0] = X;
			Mode3DTextCoords[text3did][1] = Y;
			Mode3DTextCoords[text3did][2] = Z;
			Debug(DEBUG_ACTION,"destroy 3dtext for players and show on new pos");
			HideMode3DText(text3did);
			Debug(DEBUG_END,"SetMode3DTextPos(reason: complete)");
			return 1;
		}
		case TEXT3D_ATTACH_PLAYER:
		{
			Debug(DEBUG_ACTION,"3DText attached to player");
			Mode3DTextCoords[text3did][0] = X;
			Mode3DTextCoords[text3did][1] = Y;
			Mode3DTextCoords[text3did][2] = Z;
			Debug(DEBUG_ACTION,"destroy 3dtext for players and show on new pos");
			HideMode3DText(text3did);
			Debug(DEBUG_END,"SetMode3DTextPos(reason: complete)");
			return 1;
		}
		case TEXT3D_ATTACH_VEHICLE: 
		{
			Debug(DEBUG_ACTION,"3DText attached to vehicle");
			Mode3DTextCoords[text3did][0] = X;
			Mode3DTextCoords[text3did][1] = Y;
			Mode3DTextCoords[text3did][2] = Z;
			Debug(DEBUG_ACTION,"destroy 3dtext for players and show on new pos");
			HideMode3DText(text3did);
			Debug(DEBUG_END,"SetMode3DTextPos(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"SetMode3DTextPos(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> SetMode3DTextPos (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock GetMode3DTextModeInterior(text3did)
{
	Debug(DEBUG_START,"GetMode3DTextModeInterior(%d)",text3did);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE,TEXT3D_ATTACH_VEHICLE:
		{
			Debug(DEBUG_END,"GetMode3DTextModeInterior(reason: complete)");
			return Mode3DTextInterior{text3did};
		}
		case TEXT3D_ATTACH_PLAYER:
		{
			Debug(DEBUG_END,"GetMode3DTextModeInterior(reason: complete)");
#if defined GetPlayerModeInterior
			return GetPlayerModeInterior(Mode3DTextAttachedTo[text3did]);
#else
    		return GetPlayerInterior(Mode3DTextAttachedTo[text3did]);
#endif
		}
	}
	Debug(DEBUG_END,"GetMode3DTextModeInterior(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> GetMode3DTextModeInterior (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock SetMode3DTextModeInterior(text3did,modeinterior)
{
	Debug(DEBUG_START,"SetMode3DTextModeInterior(%d,%d)",text3did,modeinterior);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE:
		{
			Debug(DEBUG_END,"SetMode3DTextModeInterior(reason: complete)");
			Mode3DTextInterior{text3did} = modeinterior;
			return 1;
		}
		case TEXT3D_ATTACH_PLAYER,TEXT3D_ATTACH_VEHICLE:
		{
			Debug(DEBUG_END,"SetMode3DTextModeInterior(reason: error)");
			printf("[ERROR] Core -> 3DTexts -> SetMode3DTextModeInterior (try set mode interior attached 3D text, text3did = %d)",text3did);
			return 0;
		}
	}
	Debug(DEBUG_END,"SetMode3DTextModeInterior(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> SetMode3DTextModeInterior (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock GetMode3DTextVirtualWorld(text3did)
{
	Debug(DEBUG_START,"GetMode3DTextVirtualWorld(%d)",text3did);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE,TEXT3D_ATTACH_VEHICLE:
		{
			Debug(DEBUG_END,"GetMode3DTextVirtualWorld(reason: complete)");
			return Mode3DTextVirtualWorld[text3did];
		}
		case TEXT3D_ATTACH_PLAYER:
		{
			Debug(DEBUG_END,"GetMode3DTextVirtualWorld(reason: complete)");
			return GetPlayerVirtualWorld(Mode3DTextAttachedTo[text3did]);
		}
	}
	Debug(DEBUG_END,"GetMode3DTextVirtualWorld(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> GetMode3DTextVirtualWorld (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock SetMode3DTextVirtualWorld(text3did,virtualworld)
{
	Debug(DEBUG_START,"SetMode3DTextVirtualWorld(%d,%d)",text3did,virtualworld);
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_NONE:
		{
			Debug(DEBUG_END,"SetMode3DTextVirtualWorld(reason: complete)");
			Mode3DTextVirtualWorld[text3did] = virtualworld;
			return 1;
		}
		case TEXT3D_ATTACH_PLAYER,TEXT3D_ATTACH_VEHICLE:
		{
			Debug(DEBUG_END,"SetMode3DTextVirtualWorld(reason: error)");
			printf("[ERROR] Core -> 3DTexts -> SetMode3DTextVirtualWorld (try set world attached 3D text, text3did = %d)",text3did);
			return 0;
		}
	}
	Debug(DEBUG_END,"SetMode3DTextVirtualWorld(reason: error)");
	printf("[ERROR] Core -> 3DTexts -> SetMode3DTextVirtualWorld (unknown 3dtext's status, text3did = %d)",text3did);
	return 0;
}

stock AttachMode3DTextToPlayer(text3did,playerid,Float:oX,Float:oY,Float:oZ)
{
	Debug(DEBUG_START,"AttachMode3DTextToPlayer(%d,%d,%f,%f,%f)",text3did,playerid,oX,oY,oZ);
	if(Mode3DTextAttachType{text3did} != TEXT3D_ATTACH_NONE)
	{
		Debug(DEBUG_END,"AttachMode3DTextToPlayer(reason: error)");
		printf("[ERROR] Core -> 3DTexts -> AttachMode3DTextToPlayer (try attach also attached 3dtext, text3did = %d)",text3did);
		return 0;
	}
	Debug(DEBUG_ACTION,"set attaching data");
	Mode3DTextCoords[text3did][0] = oX;
	Mode3DTextCoords[text3did][1] = oY;
	Mode3DTextCoords[text3did][2] = oZ;
	Mode3DTextAttachType{text3did} = TEXT3D_ATTACH_PLAYER;
	Mode3DTextAttachedTo[text3did] = playerid;
	Debug(DEBUG_ACTION,"destroy 3dtext for players and show attached");
	HideMode3DText(text3did);
	Debug(DEBUG_END,"AttachMode3DTextToPlayer(reason: complete)");
	return 1;
}

stock AttachMode3DTextToVehicle(text3did,vehicleid,Float:oX,Float:oY,Float:oZ)
{
	Debug(DEBUG_START,"AttachMode3DTextToVehicle(%d,%d,%f,%f,%f)",text3did,vehicleid,oX,oY,oZ);
	if(Mode3DTextAttachType{text3did} != TEXT3D_ATTACH_NONE)
	{
		Debug(DEBUG_END,"AttachMode3DTextToVehicle(reason: error)");
		printf("[ERROR] Core -> 3DTexts -> AttachMode3DTextToVehicle (try attach also attached 3dtext, text3did = %d)",text3did);
		return 0;
	}
	Debug(DEBUG_ACTION,"set attaching data");
	Mode3DTextCoords[text3did][0] = oX;
	Mode3DTextCoords[text3did][1] = oY;
	Mode3DTextCoords[text3did][2] = oZ;
	Mode3DTextAttachType{text3did} = TEXT3D_ATTACH_VEHICLE;
	Mode3DTextAttachedTo[text3did] = vehicleid;
	Debug(DEBUG_ACTION,"destroy 3dtext for players and show attached");
	HideMode3DText(text3did);
	Debug(DEBUG_END,"AttachMode3DTextToVehicle(reason: complete)");
	return 1;
}

stock DeAttachMode3DText(text3did)
{
	Debug(DEBUG_START,"DeAttachMode3DText(%d)",text3did);
	if(Mode3DTextAttachType{text3did} == TEXT3D_ATTACH_NONE)
	{
		Debug(DEBUG_END,"DeAttachMode3DText(reason: error)");
		printf("[ERROR] Core -> 3DTexts -> DeAttachMode3DText (try deattach not attached 3dtext, text3did = %d)",text3did);
		return 0;
	}
	new Float:angle,
		Float:X,
		Float:Y,
		Float:Z;
	Debug(DEBUG_ACTION,"delete attaching data");
	switch(Mode3DTextAttachType{text3did})
	{
		case TEXT3D_ATTACH_PLAYER:
		{
			Debug(DEBUG_ACTION,"3DText attached to player");
			if(!IsPlayerConnected(Mode3DTextAttachedTo[text3did]))
			{
				Debug(DEBUG_END,"DeAttachMode3DText(reason: error)");
				printf("[ERROR] Core -> 3DTexts -> DeAttachMode3DText (3dtext attached to offline player, text3did = %d, playerid = %d)",text3did,Mode3DTextAttachedTo[text3did]);
				return 0;
			}
			GetPlayerFacingAngle(Mode3DTextAttachedTo[text3did],angle);
			GetPlayerPos(Mode3DTextAttachedTo[text3did],X,Y,Z);
			Debug(DEBUG_ACTION,"player pos: %f,%f,%f angle %f",X,Y,Z,angle);
			X += (Mode3DTextCoords[text3did][0] * floatsin(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatsin(-angle, degrees));
			Y += (Mode3DTextCoords[text3did][0] * floatcos(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatcos(-angle, degrees));
			Z += Mode3DTextCoords[text3did][2];
		}
		case TEXT3D_ATTACH_VEHICLE: 
		{
			Debug(DEBUG_ACTION,"3DText attached to vehicle");
			GetVehicleZAngle(Mode3DTextAttachedTo[text3did],angle);
			GetVehiclePos(Mode3DTextAttachedTo[text3did],X,Y,Z);
			Debug(DEBUG_ACTION,"player pos: %f,%f,%f angle %f",X,Y,Z,angle);
			X += (Mode3DTextCoords[text3did][0] * floatsin(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatsin(-angle, degrees));
			Y += (Mode3DTextCoords[text3did][0] * floatcos(-(angle - 90.0), degrees)) + (Mode3DTextCoords[text3did][1] * floatcos(-angle, degrees));
			Z += Mode3DTextCoords[text3did][2];
		}
	}
	Mode3DTextCoords[text3did][0] = X;
	Mode3DTextCoords[text3did][1] = Y;
	Mode3DTextCoords[text3did][2] = Z;
	Mode3DTextAttachType{text3did} = TEXT3D_ATTACH_NONE;
	Mode3DTextAttachedTo[text3did] = 0;
	Debug(DEBUG_ACTION,"destroy 3dtext for players and show deattached");
	HideMode3DText(text3did);
	Debug(DEBUG_END,"DeAttachMode3DText(reason: complete)");
	return 1;
}

stock IsMode3DTextAttached(text3did)
{
	Debug(DEBUG_SMALL,"DeAttachMode3DText(%d)",text3did);
	if(Mode3DTextAttachType{text3did} == TEXT3D_ATTACH_NONE) return 0;
	return 1;
}

stock GetMode3DTextText(text3did)
{
	Debug(DEBUG_SMALL,"GetMode3DTextText(%d)",text3did);
	static text[MAX_3DTEXT_STRING];
	strunpack(text,Mode3DTextText[text3did]);
	Debug(DEBUG_END,"GetMode3DTextText(reason: complete)");
	return text;
}

stock SetMode3DTextText(text3did,text[])
{
	Debug(DEBUG_START,"SetMode3DTextText(%d,%s)",text3did,text);
	strpack(Mode3DTextText[text3did],text,MAX_3DTEXT_STRING);
	HideMode3DText(text3did);
	Debug(DEBUG_END,"SetMode3DTextText(reason: complete)");
	return 1;
}

stock GetMode3DTextColor(text3did)
{
	Debug(DEBUG_SMALL,"GetMode3DTextColor(%d)",text3did);
	return Mode3DTextColor[text3did];
}

stock SetMode3DTextColor(text3did,Color)
{
	Debug(DEBUG_START,"SetMode3DTextColor(%d,%d)",text3did,Color);
	Mode3DTextColor[text3did] = Color;
	HideMode3DText(text3did);
	Debug(DEBUG_END,"SetMode3DTextColor(reason: complete)");
	return 1;
}

stock Float:GetMode3DTextDrawDistance(text3did)
{
	Debug(DEBUG_SMALL,"GetMode3DTextDrawDistance(%d)",text3did);
	return Mode3DTextDrawDistance[text3did];
}

stock SetMode3DTextDrawDistance(text3did,Float:DrawDistance)
{
	Debug(DEBUG_START,"SetMode3DTextDrawDistance(%d,%f)",text3did,DrawDistance);
	Mode3DTextDrawDistance[text3did] = DrawDistance;
	HideMode3DText(text3did);
	Debug(DEBUG_END,"SetMode3DTextDrawDistance(reason: complete)");
	return 1;
}

stock IsMode3DTextNeedToShow(playerid,text3did)
{
	Debug(DEBUG_START,"IsMode3DTextNeedToShow(%d,%d)",playerid,text3did);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsMode3DTextNeedToShow(reason: error)");
		printf("[ERROR] Core -> 3DTexts -> IsMode3DTextNeedToShow (try check 3dtext for offline player, playerid = %d)",playerid);
		return 0;
	}
	new res = 0;
	Debug(DEBUG_ACTION,"Get current coordinates");
	new Float:pos[3],
		modeinterior = GetMode3DTextModeInterior(text3did),
		virtualworld = GetMode3DTextVirtualWorld(text3did);
	GetMode3DTextPos(text3did,pos[0],pos[1],pos[2]);
	if(!IsPlayerInRangeOfPoint(playerid,MODE_3DTEXTS_DISTANCE,pos[0],pos[1],pos[2])) res = 0;
#if defined GetPlayerModeInterior
    else if((GetPlayerModeInterior(playerid) != modeinterior) && (modeinterior != INVALID_MODE_INTERIOR_ID)) res = 0;
#else
    else if((GetPlayerInterior(playerid) != modeinterior) && (modeinterior != INVALID_MODE_INTERIOR_ID)) res = 0;
#endif
	else if((GetPlayerVirtualWorld(playerid) != virtualworld) && (virtualworld != INVALID_VIRTUAL_WORLD_ID)) res = 0;
	else res = 1;
	
	Debug(DEBUG_END,"IsMode3DTextNeedToShow(reason: complete)");
	return res;
}

// --------------------------------------------------
// static functions
// --------------------------------------------------
static stock HideMode3DText(text3did)
{
	for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		if(IsPlayerNPC(playerid)) continue;
		if(Mode3DTextGameId[playerid][text3did] == INVALID_3DTEXT_PLAYER_ID) continue;
		DeletePlayer3DTextLabel(playerid,Mode3DTextGameId[playerid][text3did]);
		Mode3DTextGameId[playerid][text3did] = INVALID_3DTEXT_PLAYER_ID;
	}
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_3DText_Init()
{
	Debug(DEBUG_START,"Core_3DText_Init()");
	print("[CORE] 3DTexts load complete.");
	Debug(DEBUG_END,"Core_3DText_Init(reason: complete)");
}

Core_3DText_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Core_3DText_PlayerUpdate(%d)",playerid);
	for(new text3did = 0;text3did <= Mode3DTextsCount;text3did++)
	{
		if(Mode3DTextState{text3did} == 0) continue;
		
		if(Mode3DTextGameId[playerid][text3did] == INVALID_3DTEXT_PLAYER_ID)
		{
			if(IsMode3DTextNeedToShow(playerid,text3did))
			{
				static text[MAX_3DTEXT_STRING];
				strunpack(text,Mode3DTextText[text3did]);
				switch(Mode3DTextAttachType{text3did})
				{
					case TEXT3D_ATTACH_NONE: Mode3DTextGameId[playerid][text3did] = CreatePlayer3DTextLabel(playerid,text,Mode3DTextColor[text3did],Mode3DTextCoords[text3did][0],Mode3DTextCoords[text3did][1],Mode3DTextCoords[text3did][2],Mode3DTextDrawDistance[text3did],INVALID_PLAYER_ID,INVALID_VEHICLE_ID,Mode3DTextLOS{text3did});
					case TEXT3D_ATTACH_PLAYER: Mode3DTextGameId[playerid][text3did] = CreatePlayer3DTextLabel(playerid,text,Mode3DTextColor[text3did],Mode3DTextCoords[text3did][0],Mode3DTextCoords[text3did][1],Mode3DTextCoords[text3did][2],Mode3DTextDrawDistance[text3did],Mode3DTextAttachedTo[text3did],INVALID_VEHICLE_ID,Mode3DTextLOS{text3did});
					case TEXT3D_ATTACH_VEHICLE: Mode3DTextGameId[playerid][text3did] = CreatePlayer3DTextLabel(playerid,text,Mode3DTextColor[text3did],Mode3DTextCoords[text3did][0],Mode3DTextCoords[text3did][1],Mode3DTextCoords[text3did][2],Mode3DTextDrawDistance[text3did],INVALID_PLAYER_ID,Mode3DTextAttachedTo[text3did],Mode3DTextLOS{text3did});
				}
			}
		}
		else if(!IsMode3DTextNeedToShow(playerid,text3did))
		{
			DeletePlayer3DTextLabel(playerid,Mode3DTextGameId[playerid][text3did]);
			Mode3DTextGameId[playerid][text3did] = INVALID_3DTEXT_PLAYER_ID;
		}
	}
	Debug(DEBUG_END,"Core_3DText_PlayerUpdate(reason: complete)");
}

Core_3DText_ResetStat(playerid)
{
	Debug(DEBUG_START,"Core_3DText_ResetStat(%d)",playerid);
	for(new text3did = 0;text3did < MAX_MODE_3DTEXTS;text3did++) Mode3DTextGameId[playerid][text3did] = INVALID_3DTEXT_PLAYER_ID;
	Debug(DEBUG_END,"Core_3DText_ResetStat(reason: complete)");
}
