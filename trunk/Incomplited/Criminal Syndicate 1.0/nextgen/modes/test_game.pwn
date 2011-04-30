/*
*	Created:			04.10.10
*	Author:				009
*	Description:        Test mode for "Criminal Syndicate 1.0" gamemode's game modules
*/

main() {}

// --------------------------------------------------
// defines
// --------------------------------------------------
#define VERSION                     "1.0"
// settings
#define DEBUG                       // ВАЖНО! ОЧЕНЬ сильно понижает производительность мода / WARNING! VERY low gamemode speed
#define USING_FILES
//#define USING_SQLITE
//#define USING_MYSQL

// --------------------------------------------------
// enums
// --------------------------------------------------


// --------------------------------------------------
// news
// --------------------------------------------------
new DialogString[4096];

// --------------------------------------------------
// includes
// --------------------------------------------------
#include <a_samp>
#include <cs_core>
#include <cs_game>

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// forwards
// --------------------------------------------------

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnGameModeInit()
{
// Core load
#if defined core_debug_included
	Core_Debug_Init();
#endif
#if defined core_interiors_included
	Core_Interiors_Init();
#endif
#if defined core_pickups_included
	Core_Pickups_Init();
#endif
#if defined core_icons_included
    Core_Icons_Init();
#endif
#if defined core_3dtexts_included
    Core_3DText_Init();
#endif
#if defined core_objects_included
    Core_Objects_Init();
#endif
#if defined core_camera_included
    Core_Camera_Init();
#endif
#if defined core_holding_included
    Core_Holding_Init();
#endif
#if defined core_vehicles_included
    Core_Vehicles_Init();
#endif
// Game modules load
#if defined game_premise_included
    Premise_Init();
#endif
#if defined game_furniture_included
    Furniture_Init();
#endif

	// main
	DisableInteriorEnterExits();
	AddPlayerClass(2,2228.362548,734.670043,11.460936,0.0,0,0,0,0,0,0);
	// info
    print("\"Criminal Syndicate 1.0\" gamemode's game modules test " VERSION " by 009 loaded.");
}

public OnGameModeExit()
{
#if defined core_holding_included
	Core_Holding_Exit();
#endif
}

public OnPlayerConnect(playerid)
{
// Core load
#if defined core_utils_included
    Core_Utils_OnPlayerConnect(playerid);
#endif
	ResetStat(playerid);
}

public OnPlayerDisconnect(playerid,reason)
{
// try utils
#if defined core_utils_included
    Core_Utils_OnPlayerDisconnect(playerid,reason);
#endif
}

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
// try actions
#if defined core_actions_included
	Core_Actions_OPKSC(playerid,newkeys,oldkeys);
#endif
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_PlayerKeySC(playerid,newkeys,oldkeys);
#endif

#if defined game_furniture_included
    Furniture_PlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

    if(newkeys & KEY_FIRE)
	{
		static current_int;
		SetPlayerModeInterior(playerid,0);
		SetPlayerModeInterior(playerid,current_int);
    	current_int++;
    	if(current_int >= 84) current_int = 0;
	}

	if(newkeys & KEY_HANDBRAKE)
	{
		static current_fur;
		new Float:pos[3];
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		CreateFurniture(current_fur,pos[0],pos[1],pos[2],0.0,0.0,0.0,GetPlayerVirtualWorld(playerid));
		
    	current_fur++;
    	if(current_fur >= 148) current_fur = 0;
	}
}

public OnPlayerUpdate(playerid)
{
// try pickups
#if defined core_pickups_included
    Core_Pickups_PlayerUpdate(playerid);
#endif
// try icons
#if defined core_icons_included
    Core_Icons_PlayerUpdate(playerid);
#endif
// try 3dtexts
#if defined core_3dtexts_included
    Core_3DText_PlayerUpdate(playerid);
#endif
// try objects
#if defined core_objects_included
    Core_Objects_PlayerUpdate(playerid);
#endif
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_PlayerUpdate(playerid);
#endif

#if defined game_furniture_included
    Furniture_PlayerUpdate(playerid);
#endif
}

public OnPlayerStateChange(playerid,newstate,oldstate)
{
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_PlayerStateChang(playerid,newstate,oldstate);
#endif
}

public OnVehicleStreamIn(vehicleid,forplayerid)
{
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_VehicleStreamIn(vehicleid,forplayerid);
#endif
}

public OnVehicleRespray(playerid,vehicleid,color1,color2)
{
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_VehicleRespray(vehicleid,color1,color2);
#endif
}

public OnVehiclePaintjob(playerid,vehicleid,paintjobid)
{
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_VehiclePaintjob(vehicleid,paintjobid);
#endif
}

public OnVehicleMod(playerid,vehicleid,componentid)
{
// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_VehicleMod(vehicleid,componentid);
#endif
}

public OnPlayerStreamIn(playerid, forplayerid)
{
// try objects
#if defined core_objects_included
    Core_Objects_PlayerStream(playerid);
#endif
}

public OnPlayerStreamOut(playerid, forplayerid)
{
// try objects
#if defined core_objects_included
    Core_Objects_PlayerStream(playerid);
#endif
}

#if defined core_objects_included

public OnModeObjectDeath(objectid)
{

#if defined game_furniture_included
    Furniture_ModeObjectDeath(objectid);
#endif
	return 1;
}

#endif

#if defined core_camera_included

public OnPlayerCameraCompleteMoving(playerid,cameraid)
{

#if defined game_furniture_included
	if(Furniture_PlayerCCMoving(playerid,cameraid)) return 0;
#endif
	return 1;
}

#endif

#if defined core_actions_included

public OnPlayerActionSelectCheck(playerid,actionid)
{
#if defined game_premise_included
    if(Premise_PlayerActionCheck(playerid,actionid)) return 1;
#endif
#if defined game_furniture_included
    if(Furniture_PlayerActionCheck(playerid,actionid)) return 1;
#endif
	return 0;
}

public OnPlayerActionSelect(playerid,actionid)
{
#if defined game_premise_included
    if(Premise_PlayerActionSelect(playerid,actionid)) return 1;
#endif
#if defined game_furniture_included
    if(Furniture_PlayerActionSelect(playerid,actionid)) return 1;
#endif
	return 0;
}

#endif

#if defined core_dialogs_included

public OnModeDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
#if defined game_furniture_included
    Furniture_ModeDialogResponse(playerid,dialogid,response,listitem,inputtext);
#endif
	return 1;
}

#endif

#if defined core_pickups_included

public OnPlayerModePickupPickUp(playerid,pickupid)
{
	return 1;
}

#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
	new idx;
	new cmd[20];

	cmd = strtokex(cmdtext, idx);

	if(!strcmp(cmd, "/mi"))
	{
	    new id = strval(strtokex(cmdtext, idx));
	    SetPlayerModeInterior(playerid,id);
    	return 1;
	}
	if(!strcmp(cmd, "/veh"))
	{
	    new id = strval(strtokex(cmdtext, idx));
	    new Float:pos[4];
	    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
	    GetPlayerFacingAngle(playerid,pos[3]);
	    
	    new vid = CreateModeVehicle(id,pos[0],pos[1],pos[2],pos[3],-1,-1,0,0,0,0);
	    SetModeVehicleDoorStatus(vid,0);
	    SetModeVehicleEngineState(vid,1);
	    PutPlayerInVehicle(playerid,vid,0);
    	return 1;
	}
	
	if(!strcmp(cmd, "/eng"))
	{
	    SetModeVehicleEngineState(GetPlayerVehicleID(playerid),strval(strtokex(cmdtext, idx)));
    	return 1;
	}

	return 0;
}

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock ResetStat(playerid)
{
#if defined core_pickups_included
    Core_Pickups_ResetStat(playerid);
#endif
#if defined core_icons_included
    Core_Icons_ResetStat(playerid);
#endif
#if defined core_3dtexts_included
    Core_3DText_ResetStat(playerid);
#endif
#if defined core_objects_included
    Core_Objects_ResetStat(playerid);
#endif
#if defined core_camera_included
    Core_Camera_ResetStat(playerid);
#endif
}

strtokex(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
