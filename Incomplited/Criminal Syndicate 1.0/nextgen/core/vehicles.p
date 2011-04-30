/*
*	Created:			06.03.09
*	Author:				009
*	Description:		Функции упрощения работы с транспортом
*/

#if defined core_vehicles_included
	#endinput
#endif

#define core_vehicles_included
#pragma library core_vehicles

// --------------------------------------------------
// includes
// --------------------------------------------------
#include	"../core/headers/vehicles.h"	// подключение обязательно
#tryinclude "../core/headers/defines.h"
#tryinclude "../core/resources/speedo_electro.r"
#tryinclude "../core/resources/speedo_analog.r"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define KEY_EXIT_VEHICLE				16
#define MODE_VEHICLES_LUGGAGE_RANGE		1.0
#define MODE_VEHICLES_DOOR_RANGE        1.0
#define NEVER							999_999_999

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
	SPEEDOMETER_ANALOG,
	SPEEDOMETER_ELECTRO
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	// vehicles
	ModeVehicleState[MAX_VEHICLES char],
	ModeVehicleColor[MAX_VEHICLES char][2 char],
	ModeVehicleKey[MAX_VEHICLES],
	ModeVehicleDoors[MAX_VEHICLES char],
	ModeVehicleRadioReq[MAX_VEHICLES],
	ModeVehicleSpeedoType[MAX_VEHICLES char],
	ModeVehicleSpeedoSubtype[MAX_VEHICLES char],
	ModeVehicleSpeedoId[MAX_VEHICLES char],
	Float:ModeVehicleFuel[MAX_VEHICLES],
	ModeVehicleEngineState[MAX_VEHICLES char],
	ModeVehicleTuning[MAX_VEHICLES][14],
	ModeVehiclePaintjob[MAX_VEHICLES char],
	// players
	Float:ModeVehiclePlayerLastPos[MAX_PLAYERS][3],
	Float:ModeVehiclePlayerLastVelocity[MAX_PLAYERS],
	ModeVehiclePlayerVehicleId[MAX_PLAYERS],
	// other
	ModeVehiclesCounter;

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native CreateModeVehicle(model,Float:posx,Float:posy,Float:posz,Float:angle,color1,color2,key,stype,ssubtype,sid);
native DestroyModeVehicle(vehicleid);
native GetModeVehiclePos(vehicleid,&Float:X,&Float:Y,&Float:Z);
native SetModeVehiclePos(vehicleid,Float:X,Float:Y,Float:Z);
native GetModeVehicleAngle(vehicleid,&Float:A);
native SetModeVehicleAngle(vehicleid,Float:A);
native GetModeVehicleHealth(vehicleid,&Float:health);
native SetModeVehicleHealth(vehicleid,Float:health);
native GetModeVehicleTuning(vehicleid,component);
native SetModeVehicleTuning(vehicleid,componentid);
native GetModeVehiclePaintjob(vehicleid);
native SetModeVehiclePaintjob(vehicleid,painjobid);
native GetModeVehicleColor(vehicleid,&color1,&color2);
native SetModeVehicleColor(vehicleid,color1,color2);
native GetModeVehicleKeysize(vehicleid);
native SetModeVehicleKeysize(vehicleid,key);
native GetModeVehicleSpeedoInfo(vehicleid,&stype,&ssubtype,&sid);
native SetModeVehicleSpeedoInfo(vehicleid,stype,ssubtype,sid);
native GetModeVehicleDoorStatus(vehicleid);
native SetModeVehicleDoorStatus(vehicleid,status);
native GetModeVehicleRadioStation(vehicleid);
native SetModeVehicleRadioStation(vehicleid,requency);
native Float:GetModeVehicleFuel(vehicleid);
native SetModeVehicleFuel(vehicleid,Float:fuel);
native GetModeVehicleEngineState(vehicleid);
native SetModeVehicleEngineState(vehicleid,state);
native Float:GetModeVehicleMaxLuggage(vehicleid);
native GetModeVehicleLuggageType(vehicleid);
native GetPlayerClosestModeVehicle(playerid);
native IsPlayerAroundLuggageModeVehicl(playerid,vehicleid);
native IsPlayerAroundDoorModeVehicle(playerid,vehicleid);
native GetModeVehicleType(model);
native GetModeVehicleSubType(model);
native GetMaxModeVehicleId();
native bool:IsModeVehicleActive(vehicleid);
native Float:GetModeVehicleMaxFuel(model);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateModeVehicle(model,Float:posx,Float:posy,Float:posz,Float:angle,color1,color2,key,stype,ssubtype,sid)
{
	Debug(DEBUG_START,"CreateModeVehicle(%d,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d)",model,posx,posy,posz,angle,color1,color2,key,stype,ssubtype,sid);
	if(color1 == -1) color1 = random(128);
	if(color2 == -1) color2 = random(128);
	Debug(DEBUG_ACTION,"create vehicle");
	new vehicleid = CreateVehicle(model,posx,posy,posz,angle,color1,color2,NEVER);
	Debug(DEBUG_ACTION,"vehicle id = %d",vehicleid);
	if(vehicleid == INVALID_VEHICLE_ID)
	{
		Debug(DEBUG_END,"CreateModeVehicle(reason: error)");
		print("[ERROR] Core -> Vehicles -> CreateModeVehicle (all slots used)");
		return INVALID_MODE_VEHICLE_ID;
	}
	Debug(DEBUG_ACTION,"set data");
	ModeVehicleState{vehicleid} = 1;
	ModeVehicleColor[vehicleid]{0} = color1;
	ModeVehicleColor[vehicleid]{1} = color2;
	ModeVehicleKey[vehicleid] = key;
	ModeVehicleDoors{vehicleid} = 0;
	ModeVehicleRadioReq[vehicleid] = 0;
	ModeVehicleSpeedoType{vehicleid} = stype;
	ModeVehicleSpeedoSubtype{vehicleid} = ssubtype;
	ModeVehicleSpeedoId{vehicleid} = sid;
	ModeVehicleFuel[vehicleid] = VehicleData[model - 400][vMaxFuel];
	ModeVehicleEngineState{vehicleid} = 0;
	for(new i = 0;i < 14;i++) ModeVehicleTuning[vehicleid][i] = 0;
	ModeVehiclePaintjob{vehicleid} = INVALID_PAINT_JOB;
	Debug(DEBUG_ACTION,"counters");
	if(ModeVehiclesCounter < vehicleid) ModeVehiclesCounter = vehicleid;
	Debug(DEBUG_END,"CreateModeVehicle(reason: complete)");
	return vehicleid;
}

stock DestroyModeVehicle(vehicleid)
{
	Debug(DEBUG_START,"DestroyModeVehicle(%d)",vehicleid);
	Debug(DEBUG_ACTION,"destroy vehicle");
	DestroyVehicle(vehicleid);
	Debug(DEBUG_ACTION,"reset data");
	ModeVehicleState{vehicleid} = 0;
	ModeVehicleColor[vehicleid]{0} = 0;
	ModeVehicleColor[vehicleid]{1} = 0;
	ModeVehicleKey[vehicleid] = 0;
	ModeVehicleDoors{vehicleid} = 0;
	ModeVehicleRadioReq[vehicleid] = 0;
	ModeVehicleSpeedoType{vehicleid} = 0;
	ModeVehicleSpeedoSubtype{vehicleid} = 0;
	ModeVehicleSpeedoId{vehicleid} = 0;
	ModeVehicleFuel[vehicleid] = 0.0;
	ModeVehicleEngineState{vehicleid} = 0;
	for(new i = 0;i < 14;i++) ModeVehicleTuning[vehicleid][i] = 0;
	ModeVehiclePaintjob{vehicleid} = INVALID_PAINT_JOB;
	Debug(DEBUG_ACTION,"counters");
	if(ModeVehiclesCounter == vehicleid) 
	{
		do ModeVehiclesCounter--;
		while(!ModeVehicleState{ModeVehiclesCounter});
	}
	Debug(DEBUG_END,"DestroyModeVehicle(reason: complete)");
	return 1;
}

stock GetModeVehiclePos(vehicleid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetModeVehiclePos(%d)",vehicleid);
	GetVehiclePos(vehicleid,X,Y,Z);
	Debug(DEBUG_END,"GetModeVehiclePos(reason: complete)");
	return 1;
}

stock SetModeVehiclePos(vehicleid,Float:X,Float:Y,Float:Z)
{
	Debug(DEBUG_START,"SetModeVehiclePos(%d,%f,%f,%f)",vehicleid,X,Y,Z);
	SetVehiclePos(vehicleid,X,Y,Z);
	Debug(DEBUG_END,"SetModeVehiclePos(reason: complete)");
	return 1;
}

stock GetModeVehicleAngle(vehicleid,&Float:A)
{
	Debug(DEBUG_START,"GetModeVehicleAngle(%d)",vehicleid);
	GetVehicleZAngle(vehicleid,A);
	Debug(DEBUG_END,"GetModeVehicleAngle(reason: complete)");
	return 1;
}

stock SetModeVehicleAngle(vehicleid,Float:A)
{
	Debug(DEBUG_START,"SetModeVehicleAngle(%d,%f)",vehicleid,A);
	SetVehicleZAngle(vehicleid,A);
	Debug(DEBUG_END,"SetModeVehicleAngle(reason: complete)");
	return 1;
}

stock GetModeVehicleColor(vehicleid,&color1,&color2)
{
	Debug(DEBUG_START,"GetModeVehicleColor(%d)",vehicleid);
	color1 = ModeVehicleColor[vehicleid]{0};
	color2 = ModeVehicleColor[vehicleid]{1};
	Debug(DEBUG_END,"GetModeVehicleColor(reason: complete)");
	return 1;
}

stock SetModeVehicleColor(vehicleid,color1,color2)
{
	Debug(DEBUG_START,"SetModeVehicleColor(%d,%d,%d)",vehicleid,color1,color2);
	ChangeVehicleColor(vehicleid,color1,color2);
	ModeVehicleColor[vehicleid]{0} = color1;
	ModeVehicleColor[vehicleid]{1} = color2;
	Debug(DEBUG_END,"SetModeVehicleColor(reason: complete)");
	return 1;
}

stock GetModeVehicleHealth(vehicleid,&Float:health)
{
	Debug(DEBUG_START,"GetModeVehicleHealth(%d)",vehicleid);
	GetVehicleHealth(vehicleid,health);
	Debug(DEBUG_END,"GetModeVehicleHealth(reason: complete)");
	return 1;
}

stock SetModeVehicleHealth(vehicleid,Float:health)
{
	Debug(DEBUG_START,"SetModeVehicleHealth(%d,%f)",vehicleid,health);
	SetVehicleHealth(vehicleid,health);
	Debug(DEBUG_END,"SetModeVehicleHealth(reason: complete)");
	return 1;
}

stock GetModeVehicleTuning(vehicleid,component)
{
	Debug(DEBUG_SMALL,"GetModeVehicleTuning(%d,%d)",vehicleid,component);
	return ModeVehicleTuning[vehicleid][component];
}

stock SetModeVehicleTuning(vehicleid,componentid)
{
	Debug(DEBUG_START,"SetModeVehicleTuning(%d,%d)",vehicleid,componentid);
	ModeVehicleTuning[vehicleid][GetVehicleComponentType(componentid)] = componentid;
	AddVehicleComponent(vehicleid,componentid);
	Debug(DEBUG_END,"SetModeVehicleTuning(reason: complete)");
	return 1;
}

stock GetModeVehiclePaintjob(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehiclePaintjob(%d)",vehicleid);
	return ModeVehiclePaintjob{vehicleid};
}

stock SetModeVehiclePaintjob(vehicleid,painjobid)
{
	Debug(DEBUG_START,"SetModeVehiclePaintjob(%d,%d)",vehicleid,painjobid);
	ModeVehiclePaintjob{vehicleid} = painjobid;
	ChangeVehiclePaintjob(vehicleid,painjobid);
	Debug(DEBUG_END,"SetModeVehiclePaintjob(reason: complete)");
	return 1;
}

stock GetModeVehicleKeysize(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleKeysize(%d)",vehicleid);
	return ModeVehicleKey[vehicleid];
}

stock SetModeVehicleKeysize(vehicleid,key)
{
	Debug(DEBUG_START,"SetModeVehicleKeysize(%d,%d)",vehicleid,key);
	ModeVehicleKey[vehicleid] = key;
	Debug(DEBUG_END,"SetModeVehicleKeysize(reason: complete)");
	return 1;
}

stock GetModeVehicleSpeedoInfo(vehicleid,&stype,&ssubtype,&sid)
{
	Debug(DEBUG_START,"GetModeVehicleSpeedoInfo(%d)",vehicleid);
	stype = ModeVehicleSpeedoType{vehicleid};
	ssubtype = ModeVehicleSpeedoSubtype{vehicleid};
	sid = ModeVehicleSpeedoId{vehicleid};
	Debug(DEBUG_END,"GetModeVehicleSpeedoInfo(reason: complete)");
	return 1;
}

stock SetModeVehicleSpeedoInfo(vehicleid,stype,ssubtype,sid)
{
	Debug(DEBUG_START,"SetModeVehicleSpeedoInfo(%d,%d,%d,%d)",vehicleid,stype,ssubtype,sid);
	ModeVehicleSpeedoType{vehicleid} = stype;
	ModeVehicleSpeedoSubtype{vehicleid} = ssubtype;
	ModeVehicleSpeedoId{vehicleid} = sid;
	Debug(DEBUG_END,"SetModeVehicleSpeedoInfo(reason: complete)");
	return 1;
}

stock GetModeVehicleDoorStatus(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleDoorStatus(%d)",vehicleid);
	return ModeVehicleDoors{vehicleid};
}

stock SetModeVehicleDoorStatus(vehicleid,status)
{
	Debug(DEBUG_START,"SetModeVehicleDoorStatus(%d,%d)",vehicleid,status);
	ModeVehicleDoors{vehicleid} = status;
	
	for(new i = 0;i <= GetMaxPlayerId();i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i)) continue;

		if(IsVehicleStreamedIn(vehicleid,i)) SetVehicleParamsForPlayer(vehicleid,i,0,status);
	}
	Debug(DEBUG_END,"SetModeVehicleDoorStatus(reason: complete)");
	return 1;
}

stock GetModeVehicleRadioStation(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleRadioStation(%d)",vehicleid);
	return ModeVehicleRadioReq[vehicleid];
}

stock SetModeVehicleRadioStation(vehicleid,requency)
{
	Debug(DEBUG_START,"SetModeVehicleRadioStation(%d,%d)",vehicleid,requency);
	ModeVehicleRadioReq[vehicleid] = requency;
	Debug(DEBUG_END,"SetModeVehicleRadioStation(reason: complete)");
	return 1;
}

stock Float:GetModeVehicleFuel(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleFuel(%d)",vehicleid);
	return ModeVehicleFuel[vehicleid];
}

stock SetModeVehicleFuel(vehicleid,Float:fuel)
{
	Debug(DEBUG_START,"SetModeVehicleFuel(%d,%f)",vehicleid,fuel);
	if(fuel > VehicleData[GetVehicleModel(vehicleid) - 400][vMaxFuel])
	{
		Debug(DEBUG_END,"SetModeVehicleFuel(reason: error)");
		printf("[ERROR] Core -> Vehicles -> SetModeVehicleFuel (invalid fuel amount for vehicle %d(max = %f) ,try fuel = %f)",vehicleid,VehicleData[GetVehicleModel(vehicleid) - 400][vMaxFuel],fuel);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	ModeVehicleFuel[vehicleid] = fuel;
	Debug(DEBUG_END,"SetModeVehicleFuel(reason: complete)");
	return 1;
}

stock GetModeVehicleEngineState(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleEngineState(%d)",vehicleid);
	return ModeVehicleEngineState{vehicleid};
}

stock SetModeVehicleEngineState(vehicleid,nstate)
{
	Debug(DEBUG_START,"SetModeVehicleEngineState(%d,%b)",vehicleid,nstate);
	ModeVehicleEngineState{vehicleid} = nstate;
	
	for(new i = 0;i <= GetMaxPlayerId();i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i)) continue;

		if(IsPlayerInVehicle(i,vehicleid))
		{
		    if(nstate)
		    {
		        TogglePlayerControllable(i,true);
				SetCameraBehindPlayer(i);
		    }
		    else
		    {
		        TogglePlayerControllable(i,false);
				SetCameraBehindPlayer(i);
		    }
		}
	}
	Debug(DEBUG_END,"SetModeVehicleEngineState(reason: complete)");
	return 1;
}

stock Float:GetModeVehicleMaxLuggage(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleMaxLuggage(%d)",vehicleid);
	return VehicleData[GetVehicleModel(vehicleid)][vMaxLuggage];
}

stock GetModeVehicleLuggageType(vehicleid)
{
	Debug(DEBUG_SMALL,"GetModeVehicleLuggageType(%d)",vehicleid);
	return VehicleData[GetVehicleModel(vehicleid)][vLuggageType];
}

stock GetPlayerClosestModeVehicle(playerid)
{
	Debug(DEBUG_START,"GetPlayerClosestModeVehicle(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"GetPlayerClosestModeVehicle(reason: error)");
		printf("[ERROR] Core -> Vehicles -> GetPlayerClosestModeVehicle (invalid player - %d)",playerid);
		return INVALID_MODE_VEHICLE_ID;
	}
	new vehicleid = INVALID_MODE_VEHICLE_ID,
		Float:distance = 69000.0,
		Float:tmp[7];
	GetPlayerPos(playerid,tmp[0],tmp[1],tmp[2]);
	for(new i = 0;i < ModeVehiclesCounter;i++)
	{
		if(!ModeVehicleState{i}) continue;
		if(!IsVehicleStreamedIn(i,playerid)) continue;
		GetVehiclePos(i,tmp[3],tmp[4],tmp[5]);
		tmp[6] = floatsqroot(floatpower(floatabs(floatsub(tmp[0],tmp[3])),2)+floatpower(floatabs(floatsub(tmp[1],tmp[4])),2)+floatpower(floatabs(floatsub(tmp[2],tmp[5])),2));
		if(distance < tmp[6]) continue;
		distance = tmp[6];
		vehicleid = i;
	}
	Debug(DEBUG_END,"GetPlayerClosestModeVehicle(reason: complete)");
	return vehicleid;
}

stock IsPlayerAroundLuggageModeVehicl(playerid,vehicleid)
{
	Debug(DEBUG_START,"IsPlayerAroundLuggageModeVehicl(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsPlayerAroundLuggageModeVehicl(reason: error)");
		printf("[ERROR] Core -> Vehicles -> IsPlayerAroundLuggageModeVehicl (invalid player - %d)",playerid);
		return 0;
	}
	new Float:tmp[4];
	GetVehiclePos(vehicleid,tmp[0],tmp[1],tmp[2]);
	GetVehicleZAngle(vehicleid,tmp[3]);
	tmp[0] += (-VehicleData[GetVehicleModel(vehicleid) - 400][vLenght] * floatsin(-tmp[3], degrees));
	tmp[1] += (-VehicleData[GetVehicleModel(vehicleid) - 400][vLenght] * floatcos(-tmp[3], degrees));
	Debug(DEBUG_END,"IsPlayerAroundLuggageModeVehicl(reason: complete)");
	return IsPlayerInRangeOfPoint(playerid,MODE_VEHICLES_LUGGAGE_RANGE,tmp[0],tmp[1],tmp[2]);
}

stock IsPlayerAroundDoorModeVehicle(playerid,vehicleid)
{
	Debug(DEBUG_START,"IsPlayerAroundDoorModeVehicle(%d)",playerid);
	if(!IsPlayerConnected(playerid))
	{
		Debug(DEBUG_END,"IsPlayerAroundDoorModeVehicle(reason: error)");
		printf("[ERROR] Core -> Vehicles -> IsPlayerAroundDoorModeVehicle (invalid player - %d)",playerid);
		return 0;
	}
	new Float:tmp[4];
	GetVehiclePos(vehicleid,tmp[0],tmp[1],tmp[2]);
	GetVehicleZAngle(vehicleid,tmp[3]);
	tmp[0] += (-VehicleData[GetVehicleModel(vehicleid) - 400][vWidth] * floatsin(-tmp[3], degrees));
	tmp[1] += (-VehicleData[GetVehicleModel(vehicleid) - 400][vWidth] * floatcos(-tmp[3], degrees));
	if(IsPlayerInRangeOfPoint(playerid,MODE_VEHICLES_DOOR_RANGE,tmp[0],tmp[1],tmp[2]))
	{
		Debug(DEBUG_END,"IsPlayerAroundDoorModeVehicle(reason: complete)");
		return 1;
	}
	tmp[0] += ((VehicleData[GetVehicleModel(vehicleid) - 400][vWidth] * 2) * floatsin(-tmp[3], degrees));
	tmp[1] += ((VehicleData[GetVehicleModel(vehicleid) - 400][vWidth] * 2) * floatcos(-tmp[3], degrees));
	if(IsPlayerInRangeOfPoint(playerid,MODE_VEHICLES_DOOR_RANGE,tmp[0],tmp[1],tmp[2]))
	{
		Debug(DEBUG_END,"IsPlayerAroundDoorModeVehicle(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"IsPlayerAroundDoorModeVehicle(reason: complete)");
	return 0;
}

stock GetModeVehicleType(model)
{
	return VehicleData[model - 400][vType];
}

stock GetModeVehicleSubType(model)
{
	return VehicleData[model - 400][vSubtype];
}

stock IsModeVehicleActive(vehicleid)
{
	return ModeVehicleState{vehicleid};
}

stock Float:GetModeVehicleMaxFuel(model)
{
	return VehicleData[model - 400][vMaxFuel];
}

stock GetMaxModeVehicleId()
{
	return ModeVehiclesCounter;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Vehicles_Init()
{
	Debug(DEBUG_START,"Core_Vehicles_Init()");
#if defined SpeedometerAnalogLoad
    SpeedometerAnalogLoad();
#endif
#if defined SpeedometerElectroLoad
    SpeedometerElectroLoad();
#endif
	print("[CORE] Vehicles load complete.");
	Debug(DEBUG_END,"Core_Vehicles_Init(reason: complete)");
}

Core_Vehicles_VehicleMod(vehicleid,componentid)
{
	Debug(DEBUG_START,"Core_Vehicles_VehicleMod(%d,%d)",vehicleid,componentid);
	ModeVehicleTuning[vehicleid][GetVehicleComponentType(componentid)] = componentid;
	Debug(DEBUG_END,"Core_Vehicles_VehicleMod(reason: complete)");
}

Core_Vehicles_VehiclePaintjob(vehicleid,paintjobid)
{
	Debug(DEBUG_START,"Core_Vehicles_VehiclePaintjob(%d,%d)",vehicleid,paintjobid);
	ModeVehiclePaintjob{vehicleid} = paintjobid;
	Debug(DEBUG_END,"Core_Vehicles_VehiclePaintjob(reason: complete)");
}

Core_Vehicles_VehicleRespray(vehicleid,color1,color2)
{
	Debug(DEBUG_START,"Core_Vehicles_VehicleRespray(%d,%d,%d)",vehicleid,color1,color2);
	ModeVehicleColor[vehicleid]{0} = color1;
	ModeVehicleColor[vehicleid]{1} = color2;
	Debug(DEBUG_END,"Core_Vehicles_VehicleRespray(reason: complete)");
}

Core_Vehicles_VehicleStreamIn(vehicleid,forplayerid)
{
	Debug(DEBUG_START,"Core_Vehicles_VehicleStreamIn(%d,%d)",vehicleid,forplayerid);
	if(!ModeVehicleDoors{vehicleid}) SetVehicleParamsForPlayer(vehicleid,forplayerid,0,0);
	else SetVehicleParamsForPlayer(vehicleid,forplayerid,0,1);
	Debug(DEBUG_END,"Core_Vehicles_VehicleStreamIn(reason: complete)");
}

Core_Vehicles_PlayerStateChang(playerid,newstate,oldstate)
{
	Debug(DEBUG_START,"Core_Vehicles_PlayerStateChang(%d,%d,%d)",playerid,newstate,oldstate);
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		switch(ModeVehicleSpeedoType{vehicleid})
		{
			case SPEEDOMETER_ANALOG:
			{
#if defined SpeedometerAnalogShow
				SpeedometerAnalogShow(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid});
#endif
			}
			case SPEEDOMETER_ELECTRO:
			{
#if defined SpeedometerElectroShow
				SpeedometerElectroShow(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid});
#endif
			}
		}
		
		ModeVehiclePlayerVehicleId[playerid] = vehicleid;
		
		if(ModeVehicleEngineState{vehicleid} == 0)
		{
			TogglePlayerControllable(playerid,false);
			SetCameraBehindPlayer(playerid);
		}
		GetPlayerPos(playerid,ModeVehiclePlayerLastPos[playerid][0],ModeVehiclePlayerLastPos[playerid][1],ModeVehiclePlayerLastPos[playerid][2]);
	}
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = ModeVehiclePlayerVehicleId[playerid];
		switch(ModeVehicleSpeedoType{vehicleid})
		{
		    case SPEEDOMETER_ANALOG:
			{
#if defined SpeedometerAnalogHide
				SpeedometerAnalogHide(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid});
#endif
			}
			case SPEEDOMETER_ELECTRO:
			{
#if defined SpeedometerElectroHide
				SpeedometerElectroHide(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid});
#endif
			}
		}
	}
	Debug(DEBUG_END,"Core_Vehicles_PlayerStateChang(reason: complete)");
}

Core_Vehicles_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Core_Vehicles_PlayerUpdate(%d)",playerid);
	if(!IsPlayerInAnyVehicle(playerid))
	{
		Debug(DEBUG_END,"Core_Vehicles_PlayerUpdate(reason: player not in vehicle)");
		return;
	}
	Debug(DEBUG_ACTION,"player in vehicle");
	new vehicleid = GetPlayerVehicleID(playerid),
		Float:tmp[4],
		data[3]; // for speedometers
	Debug(DEBUG_ACTION,"get velocity");
	GetVehicleVelocity(vehicleid,tmp[0],tmp[1],tmp[2]);
	tmp[3] = floatsqroot(floatpower(tmp[0],2) + floatpower(tmp[1],2) + floatpower(tmp[2],2)); // len of velocity vector - acceleration
	Debug(DEBUG_ACTION,"write acceleration");
	data[2] = floatround(tmp[3] - ModeVehiclePlayerLastVelocity[playerid]); // current acceleration - last acceleration = acceleration for speedometer
	ModeVehiclePlayerLastVelocity[playerid] = tmp[3]; // last = current
	Debug(DEBUG_ACTION,"write speed");	
	data[0] = floatround(tmp[3] * 161.0); // speed by current velocity, =* 161 - KM/h
	new model_ex = GetVehicleModel(vehicleid) - 400;
	Debug(DEBUG_ACTION,"check null fuel");
	if((ModeVehicleFuel[vehicleid] <= 0.0) && (ModeVehicleEngineState{vehicleid} == 1))
	{
		TogglePlayerControllable(playerid,false);
		SetCameraBehindPlayer(playerid);
		ModeVehicleEngineState{vehicleid} = 0;
	}
	else
	{
		Debug(DEBUG_ACTION,"get distance");
		GetVehiclePos(vehicleid,tmp[0],tmp[1],tmp[2]);
		tmp[3] = floatsqroot(floatpower(floatsub(tmp[0],ModeVehiclePlayerLastPos[playerid][0]),2)+floatpower(floatsub(tmp[1],ModeVehiclePlayerLastPos[playerid][1]),2)+floatpower(floatsub(tmp[2],ModeVehiclePlayerLastPos[playerid][2]),2));
		ModeVehiclePlayerLastPos[playerid][0] = tmp[0];
		ModeVehiclePlayerLastPos[playerid][1] = tmp[1];
		ModeVehiclePlayerLastPos[playerid][2] = tmp[2];
		Debug(DEBUG_ACTION,"lost fuel");
		ModeVehicleFuel[vehicleid] -= ((VehicleData[model_ex][vExpense] / 10_000.0) * tmp[3]); // expense / 10_000 - expense to 1 foot * distance
	}
	Debug(DEBUG_ACTION,"write fuel");
	data[1] = floatround((ModeVehicleFuel[vehicleid] / VehicleData[model_ex][vMaxFuel]) * 10.0); // current fuel / max fuel - min 0,max 1 => =*10 min 0 max 10
	Debug(DEBUG_ACTION,"show updated speedo");
	switch(ModeVehicleSpeedoType{vehicleid})
	{
	    case SPEEDOMETER_ANALOG:
		{
#if defined SpeedometerAnalogUpdate
			SpeedometerAnalogUpdate(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid},data);
#endif
		}
		case SPEEDOMETER_ELECTRO:
		{
#if defined SpeedometerElectroUpdate
			SpeedometerElectroUpdate(playerid,ModeVehicleSpeedoSubtype{vehicleid},ModeVehicleSpeedoId{vehicleid},data);
#endif
		}
	}
	Debug(DEBUG_END,"Core_Vehicles_PlayerUpdate(reason: complete)");
}

Core_Vehicles_PlayerKeySC(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Core_Vehicles_PlayerKeySC(%d,%d,%d)",playerid,newkeys,oldkeys);
	if((IsPlayerInAnyVehicle(playerid) == 0) || (ModeVehicleEngineState{GetPlayerVehicleID(playerid)} == 1))
	{
		Debug(DEBUG_END,"Core_Vehicles_PlayerKeySC(reason: player not in vehicle or engine on)");
		return;
	}
	if(newkeys & KEY_EXIT_VEHICLE)
	{
		TogglePlayerControllable(playerid,true);
		RemovePlayerFromVehicle(playerid);
	}
	Debug(DEBUG_END,"Core_Vehicles_PlayerKeySC(reason: complete)");
}
