/*
*	Created:			15.04.09
*	Author:				009
*	Description:		Функции передвижения камеры игрока
*/

#if defined core_camera_included
	#endinput
#endif

#define core_camera_included
#pragma library core_camera

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/headers/enums.h"
#tryinclude "../core/headers/defines.h"

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
	CAMERA_MODE_MOVE_NONE,
	CAMERA_MODE_MOVE_POS,
	CAMERA_MODE_MOVE_POS_EX,
	CAMERA_MODE_MOVE_POS_AROUND,
	CAMERA_MODE_MOVE_POS_AROUND2,
	CAMERA_MODE_MOVE_POS_AROUND3
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	Float:ModeCameraPlayerCoords[MAX_PLAYERS][6],
	Float:ModeCameraPlayerVectors[MAX_PLAYERS][6],
	ModeCameraPlayerAroundPlayerid[MAX_PLAYERS],
	ModeCameraPlayerAroundDirection[MAX_PLAYERS char],
	ModeCameraPlayerCameraMode[MAX_PLAYERS char],
	ModeCameraPlayerCameraId[MAX_PLAYERS char],
	ModeCameraPlayerFrames[MAX_PLAYERS];

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native MovePlayerCamera(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:vX,Float:vY,Float:vZ,Float:speed);
native MovePlayerCameraEx(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:lX,Float:lY,Float:lZ,Float:speed);
native MovePlayerCameraAroundPlayer(playerid,cameraid,aroundid,Float:radius,Float:speed,direction);
native MovePlayerCameraAroundXYZ(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,direction);
native MovePlayerCameraAroundXYZEx(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,Float:minAngle,Float:maxAngle,direction);
native Float:GetPlayerCameraAroundRadius(playerid);
native SetPlayerCameraAroundRadius(playerid,Float:radius);
native GetPlayerCameraAroundCenter(playerid,&Float:X,&Float:Y,&Float:Z);
native SetPlayerCameraAroundCenter(playerid,Float:X,Float:Y,Float:Z);
native GetPlayerCameraAroundDirection(playerid);
native SetPlayerCameraAroundDirection(playerid,direction);
native StopPlayerCamera(playerid,bool:returncamera);
native IsPlayerCameraMoving(playerid);
*/

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward Core_Camera_Update();
forward OnPlayerCameraCompleteMoving(playerid,cameraid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public Core_Camera_Update()
{
//	Debug(DEBUG_START,"Core_Camera_Update()");
	for(new playerid = 0;playerid <= GetMaxPlayerId();playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		if(IsPlayerNPC(playerid)) continue;
		
		switch(ModeCameraPlayerCameraMode{playerid})
		{
			case CAMERA_MODE_MOVE_POS:
			{
			    ModeCameraPlayerCoords[playerid][0] += ModeCameraPlayerVectors[playerid][0];
			    ModeCameraPlayerCoords[playerid][1] += ModeCameraPlayerVectors[playerid][1];
			    ModeCameraPlayerCoords[playerid][2] += ModeCameraPlayerVectors[playerid][2];
			    ModeCameraPlayerCoords[playerid][3] += ModeCameraPlayerVectors[playerid][3];
			    ModeCameraPlayerCoords[playerid][4] += ModeCameraPlayerVectors[playerid][4];
			    ModeCameraPlayerCoords[playerid][5] += ModeCameraPlayerVectors[playerid][5];
				SetPlayerCameraPos(playerid,ModeCameraPlayerCoords[playerid][0],ModeCameraPlayerCoords[playerid][1],ModeCameraPlayerCoords[playerid][2]);
                SetPlayerCameraLookAt(playerid,ModeCameraPlayerCoords[playerid][3],ModeCameraPlayerCoords[playerid][4],ModeCameraPlayerCoords[playerid][5]);
                if(--ModeCameraPlayerFrames[playerid] == 0)
                {
                    if(OnPlayerCameraCompleteMoving(playerid,ModeCameraPlayerCameraId{playerid})) Core_Camera_ResetStat(playerid);
                }
			}
			case CAMERA_MODE_MOVE_POS_EX:
			{
			    ModeCameraPlayerCoords[playerid][0] += ModeCameraPlayerVectors[playerid][0];
			    ModeCameraPlayerCoords[playerid][1] += ModeCameraPlayerVectors[playerid][1];
			    ModeCameraPlayerCoords[playerid][2] += ModeCameraPlayerVectors[playerid][2];
				SetPlayerCameraPos(playerid,ModeCameraPlayerCoords[playerid][0],ModeCameraPlayerCoords[playerid][1],ModeCameraPlayerCoords[playerid][2]);
                if(--ModeCameraPlayerFrames[playerid] == 0)
                {
                    if(OnPlayerCameraCompleteMoving(playerid,ModeCameraPlayerCameraId{playerid})) Core_Camera_ResetStat(playerid);
                }
			}
			case CAMERA_MODE_MOVE_POS_AROUND:
			{
				if(!IsPlayerConnected(ModeCameraPlayerAroundPlayerid[playerid])) Core_Camera_ResetStat(playerid);
				if(GetPlayerVirtualWorld(ModeCameraPlayerAroundPlayerid[playerid]) != GetPlayerVirtualWorld(playerid)) SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(ModeCameraPlayerAroundPlayerid[playerid]));
				new Float:pos[3];
				GetPlayerPos(ModeCameraPlayerAroundPlayerid[playerid],pos[0],pos[1],pos[2]);
				SetPlayerCameraLookAt(playerid,pos[0],pos[1],pos[2]);
				pos[0] += (ModeCameraPlayerCoords[playerid][0] * floatsin(-ModeCameraPlayerCoords[playerid][1], degrees));
				pos[1] += (ModeCameraPlayerCoords[playerid][0] * floatcos(-ModeCameraPlayerCoords[playerid][1], degrees));
				SetPlayerCameraPos(playerid,pos[0],pos[1],(pos[2] + 2.0));
				switch(ModeCameraPlayerAroundDirection{playerid})
				{
					case DIRECTION_LEFT: ModeCameraPlayerCoords[playerid][1] -= ModeCameraPlayerCoords[playerid][2];
					case DIRECTION_RIGHT: ModeCameraPlayerCoords[playerid][1] += ModeCameraPlayerCoords[playerid][2];
				}
			}
			case CAMERA_MODE_MOVE_POS_AROUND2:
			{
				new Float:pos[3];
				pos[0] = ModeCameraPlayerCoords[playerid][0];
				pos[1] = ModeCameraPlayerCoords[playerid][1];
				pos[2] = ModeCameraPlayerCoords[playerid][2];
				pos[0] += (ModeCameraPlayerCoords[playerid][3] * floatsin(-ModeCameraPlayerCoords[playerid][4], degrees));
				pos[1] += (ModeCameraPlayerCoords[playerid][3] * floatcos(-ModeCameraPlayerCoords[playerid][4], degrees));
				SetPlayerCameraPos(playerid,pos[0],pos[1],(pos[2] + ModeCameraPlayerCoords[playerid][3] / 10.0));
				SetPlayerCameraLookAt(playerid,ModeCameraPlayerCoords[playerid][0],ModeCameraPlayerCoords[playerid][1],ModeCameraPlayerCoords[playerid][2]);
				switch(ModeCameraPlayerAroundDirection{playerid})
				{
					case DIRECTION_LEFT: ModeCameraPlayerCoords[playerid][4] -= ModeCameraPlayerCoords[playerid][5];
					case DIRECTION_RIGHT: ModeCameraPlayerCoords[playerid][4] += ModeCameraPlayerCoords[playerid][5];
				}
			}
			case CAMERA_MODE_MOVE_POS_AROUND3:
			{
				new Float:pos[3];
				pos[0] = ModeCameraPlayerCoords[playerid][0];
				pos[1] = ModeCameraPlayerCoords[playerid][1];
				pos[2] = ModeCameraPlayerCoords[playerid][2];
				pos[0] += (ModeCameraPlayerCoords[playerid][3] * floatsin(-ModeCameraPlayerVectors[playerid][1], degrees));
				pos[1] += (ModeCameraPlayerCoords[playerid][3] * floatcos(-ModeCameraPlayerVectors[playerid][1], degrees));
				SetPlayerCameraPos(playerid,pos[0],pos[1],(pos[2] + ModeCameraPlayerCoords[playerid][3] / 10.0));
				SetPlayerCameraLookAt(playerid,ModeCameraPlayerCoords[playerid][0],ModeCameraPlayerCoords[playerid][1],ModeCameraPlayerCoords[playerid][2]);
                switch(ModeCameraPlayerAroundDirection{playerid})
				{
					case DIRECTION_LEFT:
					{
						ModeCameraPlayerVectors[playerid][1] -= ModeCameraPlayerVectors[playerid][0];
						if(ModeCameraPlayerVectors[playerid][1] <= ModeCameraPlayerCoords[playerid][4])
						{
						    if(OnPlayerCameraCompleteMoving(playerid,ModeCameraPlayerCameraId{playerid})) Core_Camera_ResetStat(playerid);
						}
					}
					case DIRECTION_RIGHT:
					{
						ModeCameraPlayerVectors[playerid][1] += ModeCameraPlayerVectors[playerid][0];
						if(ModeCameraPlayerVectors[playerid][1] >= ModeCameraPlayerCoords[playerid][5])
						{
						    if(OnPlayerCameraCompleteMoving(playerid,ModeCameraPlayerCameraId{playerid})) Core_Camera_ResetStat(playerid);
						}
					}
				}
			}
		}
	}
//	Debug(DEBUG_END,"Core_Camera_Update(reason: complete)");
}

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock MovePlayerCamera(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:vX,Float:vY,Float:vZ,Float:speed)
{
	Debug(DEBUG_START,"MovePlayerCamera(%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f)",playerid,cameraid,sX,sY,sZ,eX,eY,eZ,vX,vY,vZ,speed);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"MovePlayerCamera(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCamera (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"gen data");
	ModeCameraPlayerCoords[playerid][0] = sX;
	ModeCameraPlayerCoords[playerid][1] = sY;
	ModeCameraPlayerCoords[playerid][2] = sZ;
	ModeCameraPlayerCoords[playerid][3] = sX + vX;
	ModeCameraPlayerCoords[playerid][4] = sY + vY;
	ModeCameraPlayerCoords[playerid][5] = sZ + vZ;
	ModeCameraPlayerVectors[playerid][0] = (eX - sX) / ((eX - sX) * 10);
	ModeCameraPlayerVectors[playerid][1] = (eY - sY) / ((eY - sY) * 10);
	ModeCameraPlayerVectors[playerid][2] = (eZ - sZ) / ((eZ - sZ) * 10);
	ModeCameraPlayerVectors[playerid][3] = vX;
	ModeCameraPlayerVectors[playerid][4] = vY;
	ModeCameraPlayerVectors[playerid][5] = vZ;
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_POS;
	ModeCameraPlayerCameraId{playerid} = cameraid;
	Debug(DEBUG_END,"MovePlayerCamera(reason: complete)");
	return 1;
}

stock MovePlayerCameraEx(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:lX,Float:lY,Float:lZ,Float:speed)
{
	Debug(DEBUG_START,"MovePlayerCameraEx(%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f)",playerid,cameraid,sX,sY,sZ,eX,eY,eZ,lX,lY,lZ,speed);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"MovePlayerCameraEx(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCameraEx (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"gen data");
	ModeCameraPlayerCoords[playerid][0] = sX;
	ModeCameraPlayerCoords[playerid][1] = sY;
	ModeCameraPlayerCoords[playerid][2] = sZ;
	ModeCameraPlayerCoords[playerid][3] = lX;
	ModeCameraPlayerCoords[playerid][4] = lY;
	ModeCameraPlayerCoords[playerid][5] = lZ;
	ModeCameraPlayerVectors[playerid][0] = (eX - sX) / ((eX - sX) * 10);
	ModeCameraPlayerVectors[playerid][1] = (eY - sY) / ((eY - sY) * 10);
	ModeCameraPlayerVectors[playerid][2] = (eZ - sZ) / ((eZ - sZ) * 10);
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_POS_EX;
	ModeCameraPlayerCameraId{playerid} = cameraid;
	Debug(DEBUG_END,"MovePlayerCameraEx(reason: complete)");
	return 1;
}

stock MovePlayerCameraAroundPlayer(playerid,cameraid,aroundid,Float:radius,Float:speed,direction)
{
	Debug(DEBUG_START,"MovePlayerCameraAroundPlayer(%d,%d,%d,%f,%f,%d)",playerid,cameraid,aroundid,radius,speed,direction);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"MovePlayerCameraAroundPlayer(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCameraAroundPlayer (offline player, playerid = %d)",playerid);
		return 0;
	}
	if(!IsPlayerConnected(aroundid))
	{
		Debug(DEBUG_END,"MovePlayerCameraAroundPlayer(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCameraAroundPlayer (offline player, playerid = %d)",aroundid);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	ModeCameraPlayerCoords[playerid][0] = radius;
	ModeCameraPlayerCoords[playerid][1] = 0.0;
	ModeCameraPlayerCoords[playerid][2] = speed;
	ModeCameraPlayerAroundPlayerid[playerid] = aroundid;
	ModeCameraPlayerAroundDirection{playerid} = direction;
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_POS_AROUND;
	ModeCameraPlayerCameraId{playerid} = cameraid;
	Debug(DEBUG_END,"MovePlayerCameraAroundPlayer(reason: complete)");
	return 1;
}

stock MovePlayerCameraAroundXYZ(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,direction)
{
	Debug(DEBUG_START,"MovePlayerCameraAroundXYZ(%d,%d,%f,%f,%f,%f,%f,%d)",playerid,cameraid,X,Y,Z,radius,speed,direction);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"MovePlayerCameraAroundXYZ(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCameraAroundXYZ (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	ModeCameraPlayerCoords[playerid][0] = X;
	ModeCameraPlayerCoords[playerid][1] = Y;
	ModeCameraPlayerCoords[playerid][2] = Z;
	ModeCameraPlayerCoords[playerid][3] = radius;
	ModeCameraPlayerCoords[playerid][4] = 0.0;
	ModeCameraPlayerCoords[playerid][5] = speed;
	ModeCameraPlayerAroundDirection{playerid} = direction;
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_POS_AROUND2;
	ModeCameraPlayerCameraId{playerid} = cameraid;
	Debug(DEBUG_END,"MovePlayerCameraAroundXYZ(reason: complete)");
	return 1;
}

stock MovePlayerCameraAroundXYZEx(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,Float:minAngle,Float:maxAngle,direction)
{
	Debug(DEBUG_START,"MovePlayerCameraAroundXYZEx(%d,%d,%f,%f,%f,%f,%f,%f,%f,%d)",playerid,cameraid,X,Y,Z,radius,speed,minAngle,maxAngle,direction);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"MovePlayerCameraAroundXYZEx(reason: error)");
		printf("[ERROR] Core -> Camera -> MovePlayerCameraAroundXYZEx (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	ModeCameraPlayerCoords[playerid][0] = X;
	ModeCameraPlayerCoords[playerid][1] = Y;
	ModeCameraPlayerCoords[playerid][2] = Z;
	ModeCameraPlayerCoords[playerid][3] = radius;
	ModeCameraPlayerCoords[playerid][4] = minAngle;
	ModeCameraPlayerCoords[playerid][5] = maxAngle;
	ModeCameraPlayerVectors[playerid][0] = speed;
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_POS_AROUND3;
	ModeCameraPlayerCameraId{playerid} = cameraid;
	ModeCameraPlayerAroundDirection{playerid} = direction;
	switch(direction)
	{
	    case DIRECTION_RIGHT: ModeCameraPlayerVectors[playerid][1] = minAngle;
		case DIRECTION_LEFT: ModeCameraPlayerVectors[playerid][1] = maxAngle;
	}
	Debug(DEBUG_END,"MovePlayerCameraAroundXYZEx(reason: complete)");
	return 1;
}

stock Float:GetPlayerCameraAroundRadius(playerid)
{
	Debug(DEBUG_START,"GetPlayerCameraAroundRadius(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerCameraAroundRadius(reason: error)");
		printf("[ERROR] Core -> Camera -> GetPlayerCameraAroundRadius (offline player, playerid = %d)",playerid);
		return 0.0;
	}
	Debug(DEBUG_END,"GetPlayerCameraAroundRadius(reason: complete)");
	switch(ModeCameraPlayerCameraMode{playerid})
	{
	    case CAMERA_MODE_MOVE_POS_AROUND: return ModeCameraPlayerCoords[playerid][0];
	    case CAMERA_MODE_MOVE_POS_AROUND2: return ModeCameraPlayerCoords[playerid][3];
	    case CAMERA_MODE_MOVE_POS_AROUND3: return ModeCameraPlayerCoords[playerid][3];
	}
	return 0.0;
}

stock SetPlayerCameraAroundRadius(playerid,Float:radius)
{
	Debug(DEBUG_START,"SetPlayerCameraAroundRadius(%d,%f)",playerid,radius);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"SetPlayerCameraAroundRadius(reason: error)");
		printf("[ERROR] Core -> Camera -> SetPlayerCameraAroundRadius (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	switch(ModeCameraPlayerCameraMode{playerid})
	{
	    case CAMERA_MODE_MOVE_POS_AROUND: ModeCameraPlayerCoords[playerid][0] = radius;
	    case CAMERA_MODE_MOVE_POS_AROUND2: ModeCameraPlayerCoords[playerid][3] = radius;
	    case CAMERA_MODE_MOVE_POS_AROUND3: ModeCameraPlayerCoords[playerid][3] = radius;
	}
	Debug(DEBUG_END,"SetPlayerCameraAroundRadius(reason: complete)");
	return 1;
}

stock GetPlayerCameraAroundCenter(playerid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetPlayerCameraAroundCenter(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerCameraAroundCenter(reason: error)");
		printf("[ERROR] Core -> Camera -> GetPlayerCameraAroundCenter (offline player, playerid = %d)",playerid);
		return 0;
	}
	switch(ModeCameraPlayerCameraMode{playerid})
	{
	    case CAMERA_MODE_MOVE_POS_AROUND:
	    {
	        GetPlayerPos(ModeCameraPlayerAroundPlayerid[playerid],X,Y,Z);
	    }
	    case CAMERA_MODE_MOVE_POS_AROUND2,CAMERA_MODE_MOVE_POS_AROUND3:
	    {
	        X = ModeCameraPlayerCoords[playerid][0];
	        Y = ModeCameraPlayerCoords[playerid][1];
	        Z = ModeCameraPlayerCoords[playerid][2];
	    }
	}
	Debug(DEBUG_END,"GetPlayerCameraAroundCenter(reason: complete)");
	return 1;
}

stock SetPlayerCameraAroundCenter(playerid,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetPlayerCameraAroundCenter(%d,%f,%f,%f)",playerid,X,Y,Z);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"SetPlayerCameraAroundCenter(reason: error)");
		printf("[ERROR] Core -> Camera -> SetPlayerCameraAroundCenter (offline player, playerid = %d)",playerid);
		return 0;
	}
	switch(ModeCameraPlayerCameraMode{playerid})
	{
	    case CAMERA_MODE_MOVE_POS_AROUND2,CAMERA_MODE_MOVE_POS_AROUND3:
	    {
	        ModeCameraPlayerCoords[playerid][0] = X;
			ModeCameraPlayerCoords[playerid][1] = Y;
			ModeCameraPlayerCoords[playerid][2] = Z;
	    }
	}
	Debug(DEBUG_END,"SetPlayerCameraAroundCenter(reason: complete)");
	return 1;
}

stock GetPlayerCameraAroundDirection(playerid)
{
	Debug(DEBUG_START,"GetPlayerCameraAroundDirection(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerCameraAroundDirection(reason: error)");
		printf("[ERROR] Core -> Camera -> GetPlayerCameraAroundDirection (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_END,"GetPlayerCameraAroundDirection(reason: complete)");
	return ModeCameraPlayerAroundDirection{playerid};
}

stock SetPlayerCameraAroundDirection(playerid,direction)
{
	Debug(DEBUG_START,"SetPlayerCameraAroundDirection(%d,%d)",playerid,direction);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"SetPlayerCameraAroundDirection(reason: error)");
		printf("[ERROR] Core -> Camera -> SetPlayerCameraAroundDirection (offline player, playerid = %d)",playerid);
		return 0;
	}
	ModeCameraPlayerAroundDirection{playerid} = direction;
	Debug(DEBUG_END,"SetPlayerCameraAroundDirection(reason: complete)");
	return 1;
}

stock StopPlayerCamera(playerid,bool:returncamera)
{
	Debug(DEBUG_START,"StopPlayerCamera(%d,%b)",playerid,returncamera);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"StopPlayerCamera(reason: error)");
		printf("[ERROR] Core -> Camera -> StopPlayerCamera (offline player, playerid = %d)",playerid);
		return 0;
	}
	Core_Camera_ResetStat(playerid);
	if(returncamera == true) SetCameraBehindPlayer(playerid);
	Debug(DEBUG_END,"StopPlayerCamera(reason: complete)");
	return 1;
}

stock IsPlayerCameraMoving(playerid)
{
	Debug(DEBUG_START,"IsPlayerCameraMoving(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsPlayerCameraMoving(reason: error)");
		printf("[ERROR] Core -> Camera -> IsPlayerCameraMoving (offline player, playerid = %d)",playerid);
		return 0;
	}
	Debug(DEBUG_END,"IsPlayerCameraMoving(reason: complete)");
	return (ModeCameraPlayerCameraMode{playerid} != CAMERA_MODE_MOVE_NONE);
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Camera_Init()
{
	Debug(DEBUG_START,"Core_Camera_Init()");
	SetTimer("Core_Camera_Update",20,1);
	print("[CORE] Camera load complete.");
	Debug(DEBUG_END,"Core_Camera_Init(reason: complete)");
}

Core_Camera_ResetStat(playerid)
{
	Debug(DEBUG_START,"Core_Camera_ResetStat(%d)",playerid);
	ModeCameraPlayerCameraMode{playerid} = CAMERA_MODE_MOVE_NONE;
	ModeCameraPlayerCameraId{playerid} = INVALID_MODE_CAMERA_ID;
	for(new i = 0;i < 6;i++)
	{
	    ModeCameraPlayerCoords[playerid][i] = 0.0;
	    ModeCameraPlayerVectors[playerid][i] = 0.0;
	}
	ModeCameraPlayerAroundDirection{playerid} = 0;
	ModeCameraPlayerAroundPlayerid[playerid] = INVALID_PLAYER_ID;
	ModeCameraPlayerFrames[playerid] = 0;
	Debug(DEBUG_END,"Core_Camera_ResetStat(reason: complete)");
}
