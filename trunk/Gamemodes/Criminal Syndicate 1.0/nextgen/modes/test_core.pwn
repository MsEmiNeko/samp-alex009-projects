/*
*	Created:			27.09.10
*	Author:				009
*	Description:        Test mode for "Criminal Syndicate 1.0" gamemode's core
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
// includes
// --------------------------------------------------
#include <a_samp>
#include <cs_core>

// --------------------------------------------------
// enums
// --------------------------------------------------


// --------------------------------------------------
// news
// --------------------------------------------------


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
	// try debug
#if defined core_debug_included
	Core_Debug_Init();
	
	Debug(DEBUG_START,"ModeInit");
#endif
// try interiors
#if defined core_interiors_included
	Core_Interiors_Init();
#endif
// try pickups
#if defined core_pickups_included
	Core_Pickups_Init();
#endif
// try icons
#if defined core_icons_included
    Core_Icons_Init();
#endif
// try 3dtexts
#if defined core_3dtexts_included
    Core_3DText_Init();
#endif
// try objects
#if defined core_objects_included
    Core_Objects_Init();
#endif
// try camera
#if defined core_camera_included
    Core_Camera_Init();
#endif
// try holding
#if defined core_holding_included
    Core_Holding_Init();
	/*
    // Test all speed
    new testc = 50;
	new start = GetTickCount();
	new temp[25];
	for(new i = 0;i < testc;i++)
	{
	    if(!IsHoldingExist("Players","Nick",HOLDING_NAME_INT,i)) AddHolding("Players","Nick",HOLDING_NAME_INT,i);
	}
	printf("Add speed: %d ticks",GetTickCount() - start);
	start = GetTickCount();
	for(new i = 0;i < testc;i++)
	{
	    if(IsHoldingExist("Players","Nick",HOLDING_NAME_INT,i))
	    {
	        if(OpenHolding("Players","Nick",HOLDING_MODE_WRITE,HOLDING_NAME_INT,i))
	        {
			    SetHoldingDataInt("integer",10);
			    SetHoldingDataFloat("float",10.0);
			    SetHoldingDataString("string","its string");
			    CloseHolding();
			}
	    }
	}
	printf("Write speed: %d ticks",GetTickCount() - start);
	start = GetTickCount();
	new ineg,Float:flo,str[25];
	for(new i = 0;i < testc;i++)
	{
	    if(IsHoldingExist("Players","Nick",HOLDING_NAME_INT,i))
	    {
	        if(OpenHolding("Players","Nick",HOLDING_MODE_READ,HOLDING_NAME_INT,i))
	        {
	            ineg = GetHoldingDataInt("integer");
			    flo = GetHoldingDataFloat("float");
			    GetHoldingDataStringEx("string",str,25);
				printf("%d - [%d] [%f] [%s]",i,ineg,flo,str);
			    CloseHolding();
	        }
	    }
	}
	printf("Read speed: %d ticks",GetTickCount() - start);
	*/
	/*
	// test read speed in * rows
	new testc = 5000;
	new start = GetTickCount();
	new temp[25];
	new ineg,Float:flo,str[25];
	for(new i = 0;i < testc;i++)
	{
	    if(!IsHoldingExist("Players","Nick",HOLDING_NAME_INT,i)) AddHolding("Players","Nick",HOLDING_NAME_INT,i);
	}
	printf("Add speed: %d ticks",GetTickCount() - start);
	for(new i = 1;i <= 10;i++)
	{
		start = GetTickCount();
		new id = random(testc);
	    if(IsHoldingExist("Players","Nick",HOLDING_NAME_INT,id))
	    {
	        if(OpenHolding("Players","Nick",HOLDING_MODE_READ,HOLDING_NAME_INT,id))
	        {
	            ineg = GetHoldingDataInt("integer");
			    flo = GetHoldingDataFloat("float");
			    GetHoldingDataStringEx("string",str,25);
				//printf("%d - [%d] [%f] [%s]",i,ineg,flo,str);
			    CloseHolding();
	        }
	    }
	    printf("[%d] '%s' speed: %d ticks",i,temp,GetTickCount() - start);
	}
	*/
	/*
	// write test in * rows
	new testc = 500;
	new start = GetTickCount();
	new temp[25];
	for(new i = 0;i < testc;i++)
	{
	    if(!IsHoldingExist("Players","Nick",HOLDING_NAME_INT,i)) AddHolding("Players","Nick",HOLDING_NAME_INT,i);
	}
	printf("Add speed: %d ticks",GetTickCount() - start);
	for(new i = 1;i <= 10;i++)
	{
		start = GetTickCount();
		new id = random(testc);
	    if(IsHoldingExist("Players","Nick",HOLDING_NAME_INT,id))
	    {
	        if(OpenHolding("Players","Nick",HOLDING_MODE_WRITE,HOLDING_NAME_INT,id))
	        {
			    SetHoldingDataInt("integer",random(1000));
			    SetHoldingDataFloat("float",float(random(1000)));
			    SetHoldingDataString("string",temp);
			    CloseHolding();
			}
	    }
	    printf("[%d] '%s' speed: %d ticks",i,temp,GetTickCount() - start);
	}
	*/
	/*
	// test different types
	if(!IsHoldingExist("Players","Nick",HOLDING_NAME_INT,9999)) AddHolding("Players","Nick",HOLDING_NAME_INT,9999);
	if(!IsHoldingExist("Players","Nick",HOLDING_NAME_FLOAT,654.5)) AddHolding("Players","Nick",HOLDING_NAME_FLOAT,654.5);
	if(!IsHoldingExist("Players","Nick",HOLDING_NAME_STRING,"Ololo")) AddHolding("Players","Nick",HOLDING_NAME_STRING,"Ololo");
    if(OpenHolding("Players","Nick",HOLDING_MODE_WRITE,HOLDING_NAME_INT,9999))
    {
        SetHoldingDataInt("integer",random(1000));
		SetHoldingDataFloat("float",float(random(1000)));
		SetHoldingDataString("string","Striiiing");
		CloseHolding();
    }
    if(OpenHolding("Players","Nick",HOLDING_MODE_WRITE,HOLDING_NAME_FLOAT,654.5))
    {
        SetHoldingDataInt("integer",random(1000));
		SetHoldingDataFloat("float",float(random(1000)));
		SetHoldingDataString("string","Striiiing");
		CloseHolding();
    }
    if(OpenHolding("Players","Nick",HOLDING_MODE_WRITE,HOLDING_NAME_STRING,"Ololo"))
    {
        SetHoldingDataInt("integer",random(1000));
		SetHoldingDataFloat("float",float(random(1000)));
		SetHoldingDataString("string","Striiiing");
		CloseHolding();
    }
	*/
	/*
    // test tables
    OpenHoldingTable("Players");
    do
    {
        printf("%s - [%d] [%f] [%s]",GetHoldingDataString("Nick"),GetHoldingDataInt("integer"),GetHoldingDataFloat("float"),GetHoldingDataString("string"));
    }
    while(NextHoldingTableRow());
    CloseHoldingTable();
	*/
	//printf("min: %d max: %d",GetHoldingDataByOrder("Players","Nick",HOLDING_ORDER_MINIMAL),GetHoldingDataByOrder("Players","Nick",HOLDING_ORDER_MAXIMAL));
#endif
	// try vehicles
#if defined core_vehicles_included
    Core_Vehicles_Init();
#endif
	// try debug
#if defined core_debug_included
	Debug(DEBUG_END,"ModeInit");
#endif
	// ok
    print("\"Criminal Syndicate 1.0\" gamemode's core test " VERSION " by 009 loaded.");
}

public OnGameModeExit()
{
// try holding
#if defined core_holding_included
	Core_Holding_Exit();
#endif
}

public OnPlayerConnect(playerid)
{
// try utils
#if defined core_utils_included
    Core_Utils_OnPlayerConnect(playerid);
#endif
// try pickups
#if defined core_pickups_included
    Core_Pickups_ResetStat(playerid);
#endif
// try icons
#if defined core_icons_included
    Core_Icons_ResetStat(playerid);
#endif
// try 3dtexts
#if defined core_3dtexts_included
    Core_3DText_ResetStat(playerid);
#endif
// try objects
#if defined core_objects_included
    Core_Objects_ResetStat(playerid);
#endif
// try camera
#if defined core_camera_included
    Core_Camera_ResetStat(playerid);
#endif
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
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	new idx;
	new cmd[20];
	
	new str[128];
	new Float:pos[9];
	
	new res;
	new Float:fres;
	
	new arg0;
	new arg1;
	new arg2;
	new arg3;
	new arg4;
	new arg5;
	new arg6;
	new Float:farg0;
	new Float:farg1;

	cmd = strtokex(cmdtext, idx);

#if defined core_utils_included
    if(!strcmp(cmd, "/utils"))
	{
	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "maxpl"))
		{
		    res = GetMaxPlayerId();
		    
		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "conex"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		
		    res = TogglePlayerControllableEx(playerid,bool:arg0);

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "iscon"))
		{
		    res = IsPlayerControllable(playerid);

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "helpbox"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    
		    res = ShowHelpBoxForPlayer(playerid,arg0,strtokex(cmdtext, idx));

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "cp"))
		{
		    res = GetPlayerClosestPlayer(playerid);

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "preanim"))
		{
		    res = PreLoadAnimation(playerid,strtokex(cmdtext, idx));

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "city"))
		{
		    res = GetPlayerCity(playerid);

		    format(str,sizeof(str),"utils '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	}
#endif

#if defined core_actions_included
    if(!strcmp(cmd, "/action"))
	{
	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "set"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		
		    res = SetPlayerAction(playerid,arg0);

		    format(str,sizeof(str),"actions '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	    if(!strcmp(cmd, "get"))
		{
		    res = GetPlayerAction(playerid);

		    format(str,sizeof(str),"actions '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	    if(!strcmp(cmd, "add"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));

		    res = AddActionSelectRow(strtokex(cmdtext, idx),arg0);

		    format(str,sizeof(str),"actions '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	    if(!strcmp(cmd, "show"))
		{
		    res = ShowActionSelecting(playerid);

		    format(str,sizeof(str),"actions '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	}
#endif

#if defined core_dialogs_included
    if(!strcmp(cmd, "/dialog"))
	{
	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "show"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
			new cap[sizeof(cmd)];
			new inf[sizeof(cmd)];
			new b1[sizeof(cmd)];
			new b2[sizeof(cmd)];
			cap = strtokex(cmdtext, idx);
			inf = strtokex(cmdtext, idx);
			b1 = strtokex(cmdtext, idx);
			b2 = strtokex(cmdtext, idx);

		    res = ShowPlayerModeDialog(playerid,arg0,arg1,cap,inf,b1,b2);

		    format(str,sizeof(str),"dialogs '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "hide"))
		{
		    res = HidePlayerModeDialog(playerid);

		    format(str,sizeof(str),"dialogs '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "setld"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
		    
		    res = SetPlayerModeDialogListData(playerid,arg0,arg1);

		    format(str,sizeof(str),"dialogs '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "getld"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));

		    res = GetPlayerModeDialogListData(playerid,arg0);

		    format(str,sizeof(str),"dialogs '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
		if(!strcmp(cmd, "getstyle"))
		{
		    res = GetPlayerModeDialogStyle(playerid);

		    format(str,sizeof(str),"dialogs '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
		}
	}
#endif

#if defined core_pickups_included
    if(!strcmp(cmd, "/pickup"))
	{
	    new pid;
	    
	    cmd = strtokex(cmdtext, idx);
	    
	    if(!strcmp(cmd, "create"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
		    arg2 = strval(strtokex(cmdtext, idx));
		    arg3 = strval(strtokex(cmdtext, idx));
		    
		    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		    
#if defined GetPlayerModeInterior
			res = CreateModePickup(arg0,arg1,pos[0],pos[1],pos[2],GetPlayerModeInterior(playerid),GetPlayerVirtualWorld(playerid),arg2,arg3);
#else
			res = CreateModePickup(arg0,arg1,pos[0],pos[1],pos[2],INVALID_MODE_INTERIOR_ID,GetPlayerVirtualWorld(playerid),arg2,arg3);
#endif

			format(str,sizeof(str),"pickup '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
		if(!strcmp(cmd, "destroy"))
		{
		    pid = strval(strtokex(cmdtext, idx));
		    
		    res = DestroyModePickup(pid);

			format(str,sizeof(str),"pickup '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
		if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);

	    	if(!strcmp(cmd, "pos"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    GetModePickupPos(pid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    
			    res = GetModePickupModeInterior(pid);
			    
			    format(str,sizeof(str),"interior: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    pid = strval(strtokex(cmdtext, idx));

			    res = GetModePickupVirtualWorld(pid);

			    format(str,sizeof(str),"virtual world: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "model"))
			{
			    pid = strval(strtokex(cmdtext, idx));

			    res = GetModePickupModel(pid);

			    format(str,sizeof(str),"model: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "type"))
			{
			    pid = strval(strtokex(cmdtext, idx));

			    res = GetModePickupType(pid);

			    format(str,sizeof(str),"type: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeex"))
			{
			    pid = strval(strtokex(cmdtext, idx));

			    res = GetModePickupTypeEx(pid);

			    format(str,sizeof(str),"typeex: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeexparam"))
			{
			    pid = strval(strtokex(cmdtext, idx));

			    res = GetModePickupTypeExParam(pid);

			    format(str,sizeof(str),"typeexparam: %d",res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
		if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

	    	if(!strcmp(cmd, "pos"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    pos[0] = floatstr(strtokex(cmdtext, idx));
			    pos[1] = floatstr(strtokex(cmdtext, idx));
			    pos[2] = floatstr(strtokex(cmdtext, idx));
			    
			    res = SetModePickupPos(pid,pos[0],pos[1],pos[2]);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModePickupModeInterior(pid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModePickupVirtualWorld(pid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "type"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModePickupType(pid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeex"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModePickupTypeEx(pid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeexparam"))
			{
			    pid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModePickupTypeExParam(pid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
		if(!strcmp(cmd, "on"))
		{
		    res = GetPlayerPickupOn(playerid);

			format(str,sizeof(str),"pickup '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
		if(!strcmp(cmd, "need"))
		{
		    pid = strval(strtokex(cmdtext, idx));
		    
		    res = IsModePickupNeedToShow(playerid,pid);

			format(str,sizeof(str),"pickup '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_icons_included
    if(!strcmp(cmd, "/icon"))
	{
	    new icid;

	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "create"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));

		    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);

#if defined GetPlayerModeInterior
			res = CreateModeIcon(arg0,arg1,pos[0],pos[1],pos[2],GetPlayerModeInterior(playerid),GetPlayerVirtualWorld(playerid));
#else
			res = CreateModeIcon(arg0,arg1,pos[0],pos[1],pos[2],INVALID_MODE_INTERIOR_ID,GetPlayerVirtualWorld(playerid));
#endif

			format(str,sizeof(str),"icon '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "destroy"))
		{
		    icid = strval(strtokex(cmdtext, idx));
		    
		    res = DestroyModeIcon(icid);

			format(str,sizeof(str),"icon '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);
		
		    if(!strcmp(cmd, "pos"))
			{
			    icid = strval(strtokex(cmdtext, idx));

			    res = GetModeIconPos(icid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    icid = strval(strtokex(cmdtext, idx));

			    res = GetModeIconModeInterior(icid);

			    format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    icid = strval(strtokex(cmdtext, idx));

			    res = GetModeIconVirtualWorld(icid);

			    format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "icon"))
			{
			    icid = strval(strtokex(cmdtext, idx));

			    res = GetModeIconIcon(icid);

			    format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "color"))
			{
			    icid = strval(strtokex(cmdtext, idx));

			    res = GetModeIconColor(icid);

			    format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
	    if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

		    if(!strcmp(cmd, "pos"))
			{
			    icid = strval(strtokex(cmdtext, idx));
			    pos[0] = floatstr(strtokex(cmdtext, idx));
			    pos[1] = floatstr(strtokex(cmdtext, idx));
			    pos[2] = floatstr(strtokex(cmdtext, idx));

			    res = SetModeIconPos(icid,pos[0],pos[1],pos[2]);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    icid = strval(strtokex(cmdtext, idx));
                arg0 = strval(strtokex(cmdtext, idx));
                
			    res = SetModeIconModeInterior(icid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    icid = strval(strtokex(cmdtext, idx));
                arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeIconVirtualWorld(icid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "icon"))
			{
			    icid = strval(strtokex(cmdtext, idx));
                arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeIconIcon(icid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "color"))
			{
			    icid = strval(strtokex(cmdtext, idx));
                arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeIconColor(icid,arg0);

			    format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
		if(!strcmp(cmd, "need"))
		{
		    icid = strval(strtokex(cmdtext, idx));

		    res = IsModeIconNeedToShow(playerid,icid);

			format(str,sizeof(str),"icon '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_3dtexts_included
    if(!strcmp(cmd, "/3dtext"))
	{
	    new d3id;

	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "create"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));

		    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);

#if defined GetPlayerModeInterior
			res = CreateMode3DText(strtokex(cmdtext, idx),arg0,pos[0],pos[1],pos[2],farg0,GetPlayerModeInterior(playerid),GetPlayerVirtualWorld(playerid),arg1);
#else
			res = CreateMode3DText(strtokex(cmdtext, idx),arg0,pos[0],pos[1],pos[2],farg0,INVALID_MODE_INTERIOR_ID,GetPlayerVirtualWorld(playerid),arg1);
#endif

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "destroy"))
		{
		    d3id = strval(strtokex(cmdtext, idx));
		    
			res = DestroyMode3DText(d3id);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);
		
		    if(!strcmp(cmd, "pos"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				res = GetMode3DTextPos(d3id,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				res = GetMode3DTextModeInterior(d3id);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				res = GetMode3DTextVirtualWorld(d3id);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "text"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				format(str,sizeof(str),"get '%s' result: %s",cmd,GetMode3DTextText(d3id));
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "color"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				res = GetMode3DTextColor(d3id);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "dd"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				fres = GetMode3DTextDrawDistance(d3id);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
		}
	    if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

		    if(!strcmp(cmd, "pos"))
			{
			    d3id = strval(strtokex(cmdtext, idx));
			    pos[0] = floatstr(strtokex(cmdtext, idx));
			    pos[1] = floatstr(strtokex(cmdtext, idx));
			    pos[2] = floatstr(strtokex(cmdtext, idx));

				res = SetMode3DTextPos(d3id,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    d3id = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

				res = SetMode3DTextModeInterior(d3id,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    d3id = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

				res = SetMode3DTextVirtualWorld(d3id,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "text"))
			{
			    d3id = strval(strtokex(cmdtext, idx));

				res = SetMode3DTextText(d3id,strtokex(cmdtext, idx));

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "color"))
			{
			    d3id = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

				res = SetMode3DTextColor(d3id,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "dd"))
			{
			    d3id = strval(strtokex(cmdtext, idx));
			    farg0 = floatstr(strtokex(cmdtext, idx));

				res = SetMode3DTextDrawDistance(d3id,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
		}
	    if(!strcmp(cmd, "atp"))
		{
		    d3id = strval(strtokex(cmdtext, idx));
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));

			res = AttachMode3DTextToPlayer(d3id,arg0,pos[0],pos[1],pos[2]);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "atv"))
		{
		    d3id = strval(strtokex(cmdtext, idx));
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));

			res = AttachMode3DTextToVehicle(d3id,arg0,pos[0],pos[1],pos[2]);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "dat"))
		{
		    d3id = strval(strtokex(cmdtext, idx));

			res = DeAttachMode3DText(d3id);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "at"))
		{
		    d3id = strval(strtokex(cmdtext, idx));

			res = IsMode3DTextAttached(d3id);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "need"))
		{
		    d3id = strval(strtokex(cmdtext, idx));

			res = IsMode3DTextNeedToShow(playerid,d3id);

			format(str,sizeof(str),"3dtext '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_objects_included
    if(!strcmp(cmd, "/object"))
	{
	    new oid;

	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "create"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
		    arg2 = strval(strtokex(cmdtext, idx));

		    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);

#if defined GetPlayerModeInterior
			res = CreateModeObject(arg0,pos[0],pos[1],pos[2],0.0,0.0,0.0,GetPlayerModeInterior(playerid),GetPlayerVirtualWorld(playerid),farg0,arg1,arg2);
#else
			res = CreateModeObject(arg0,pos[0],pos[1],pos[2],0.0,0.0,0.0,INVALID_MODE_INTERIOR_ID,GetPlayerVirtualWorld(playerid),farg0,arg1,arg2);
#endif

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "destroy"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = DestroyModeObject(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);
		
		    if(!strcmp(cmd, "pos"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectPos(oid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "rot"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectRot(oid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectModeInterior(oid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectVirtualWorld(oid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "type"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectType(oid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeparam"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    res = GetModeObjectTypeParam(oid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "health"))
			{
			    oid = strval(strtokex(cmdtext, idx));

			    fres = GetModeObjectHealth(oid);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
	    if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

		    if(!strcmp(cmd, "pos"))
			{
			    oid = strval(strtokex(cmdtext, idx));
				pos[0] = floatstr(strtokex(cmdtext, idx));
				pos[1] = floatstr(strtokex(cmdtext, idx));
				pos[2] = floatstr(strtokex(cmdtext, idx));

			    res = SetModeObjectPos(oid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "rot"))
			{
			    oid = strval(strtokex(cmdtext, idx));
				pos[0] = floatstr(strtokex(cmdtext, idx));
				pos[1] = floatstr(strtokex(cmdtext, idx));
				pos[2] = floatstr(strtokex(cmdtext, idx));

			    res = SetModeObjectRot(oid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "mi"))
			{
			    oid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeObjectModeInterior(oid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "vw"))
			{
			    oid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeObjectVirtualWorld(oid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "type"))
			{
			    oid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeObjectType(oid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "typeparam"))
			{
			    oid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeObjectTypeParam(oid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
			if(!strcmp(cmd, "health"))
			{
			    oid = strval(strtokex(cmdtext, idx));
			    farg0 = floatstr(strtokex(cmdtext, idx));

			    res = SetModeObjectHealth(oid,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
			}
	    }
	    if(!strcmp(cmd, "atp"))
		{
		    oid = strval(strtokex(cmdtext, idx));
			arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
			pos[3] = floatstr(strtokex(cmdtext, idx));
			pos[4] = floatstr(strtokex(cmdtext, idx));
			pos[5] = floatstr(strtokex(cmdtext, idx));

		    res = AttachModeObjectToPlayer(oid,arg0,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5]);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "dat"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = DeAttachModeObject(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "at"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = IsModeObjectAttached(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "pao"))
		{
		    res = GetPlayerAttachedModeObject(playerid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "pco"))
		{
		    res = GetPlayerClosestModeObject(playerid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "need"))
		{
		    oid = strval(strtokex(cmdtext, idx));
		    
		    res = IsModeObjectNeedToShow(playerid,oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "hide"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = HideModeObject(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "show"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = ShowModeObject(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "streamed"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = IsModeObjectStreamedIn(oid,playerid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "max"))
		{
		    res = GetMaxModeObjectId();

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "valid"))
		{
		    oid = strval(strtokex(cmdtext, idx));

		    res = IsValidModeObject(oid);

			format(str,sizeof(str),"object '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_interiors_included
    if(!strcmp(cmd, "/interior"))
	{
	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "set"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));

		    res = SetPlayerModeInterior(playerid,arg0);

			format(str,sizeof(str),"interior '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    res = GetPlayerModeInterior(playerid);

			format(str,sizeof(str),"interior '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "getexit"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));

		    res = GetModeInteriorExitPos(arg0,pos[0],pos[1],pos[2]);

			format(str,sizeof(str),"interior '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_camera_included
    if(!strcmp(cmd, "/camera"))
	{
	    cmd = strtokex(cmdtext, idx);

	    if(!strcmp(cmd, "move"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
			pos[3] = floatstr(strtokex(cmdtext, idx));
			pos[4] = floatstr(strtokex(cmdtext, idx));
			pos[5] = floatstr(strtokex(cmdtext, idx));
			pos[6] = floatstr(strtokex(cmdtext, idx));
			pos[7] = floatstr(strtokex(cmdtext, idx));
			pos[8] = floatstr(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));

		    res = MovePlayerCamera(playerid,arg0,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7],pos[8],farg0);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "moveex"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
			pos[3] = floatstr(strtokex(cmdtext, idx));
			pos[4] = floatstr(strtokex(cmdtext, idx));
			pos[5] = floatstr(strtokex(cmdtext, idx));
			pos[6] = floatstr(strtokex(cmdtext, idx));
			pos[7] = floatstr(strtokex(cmdtext, idx));
			pos[8] = floatstr(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));

		    res = MovePlayerCamera(playerid,arg0,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7],pos[8],farg0);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "moveapl"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));
		    farg1 = floatstr(strtokex(cmdtext, idx));
		    arg2 = strval(strtokex(cmdtext, idx));

		    res = MovePlayerCameraAroundPlayer(playerid,arg0,arg1,farg0,farg1,arg2);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "moveapx"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));
		    farg1 = floatstr(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));

		    res = MovePlayerCameraAroundXYZ(playerid,arg0,pos[0],pos[1],pos[2],farg0,farg1,arg1);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "moveapxex"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
		    farg0 = floatstr(strtokex(cmdtext, idx));
		    farg1 = floatstr(strtokex(cmdtext, idx));
			pos[3] = floatstr(strtokex(cmdtext, idx));
			pos[4] = floatstr(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));

		    res = MovePlayerCameraAroundXYZEx(playerid,arg0,pos[0],pos[1],pos[2],farg0,farg1,pos[3],pos[4],arg1);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);
		    
		    if(!strcmp(cmd, "ar"))
			{
			    fres = GetPlayerCameraAroundRadius(playerid);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "ac"))
			{
			    res = GetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "ad"))
			{
			    res = GetPlayerCameraAroundDirection(playerid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
	    }
	    if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

		    if(!strcmp(cmd, "ar"))
			{
		    	farg0 = floatstr(strtokex(cmdtext, idx));
		    
			    res = SetPlayerCameraAroundRadius(playerid,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "ac"))
			{
				pos[0] = floatstr(strtokex(cmdtext, idx));
				pos[1] = floatstr(strtokex(cmdtext, idx));
				pos[2] = floatstr(strtokex(cmdtext, idx));
			
			    res = SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "ad"))
			{
		    	arg0 = strval(strtokex(cmdtext, idx));
		    
			    res = SetPlayerCameraAroundDirection(playerid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
	    }
	    if(!strcmp(cmd, "stop"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));

		    res = StopPlayerCamera(playerid,bool:arg0);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "is"))
		{
		    res = IsPlayerCameraMoving(playerid);

			format(str,sizeof(str),"camera '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	}
#endif

#if defined core_vehicles_included
    if(!strcmp(cmd, "/vehicle"))
	{
	    cmd = strtokex(cmdtext, idx);

		new vid;

	    if(!strcmp(cmd, "create"))
		{
		    arg0 = strval(strtokex(cmdtext, idx));
			pos[0] = floatstr(strtokex(cmdtext, idx));
			pos[1] = floatstr(strtokex(cmdtext, idx));
			pos[2] = floatstr(strtokex(cmdtext, idx));
			pos[3] = floatstr(strtokex(cmdtext, idx));
		    arg1 = strval(strtokex(cmdtext, idx));
		    arg2 = strval(strtokex(cmdtext, idx));
		    arg3 = strval(strtokex(cmdtext, idx));
		    arg4 = strval(strtokex(cmdtext, idx));
		    arg5 = strval(strtokex(cmdtext, idx));
		    arg6 = strval(strtokex(cmdtext, idx));

		    res = CreateModeVehicle(arg0,pos[0],pos[1],pos[2],pos[3],arg1,arg2,arg3,arg4,arg5,arg6);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "destroy"))
		{
		    vid = strval(strtokex(cmdtext, idx));

		    res = DestroyModeVehicle(vid);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "get"))
		{
		    cmd = strtokex(cmdtext, idx);
		    
		    if(!strcmp(cmd, "pos"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehiclePos(vid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"get '%s' result: %f,%f,%f - %d",cmd,pos[0],pos[1],pos[2],res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "angle"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleAngle(vid,fres);

				format(str,sizeof(str),"get '%s' result: %f - %d",cmd,fres,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "health"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleHealth(vid,fres);

				format(str,sizeof(str),"get '%s' result: %f - %d",cmd,fres,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "tuning"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleTuning(vid,arg0);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "paintjob"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehiclePaintjob(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "color"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleColor(vid,arg0,arg1);

				format(str,sizeof(str),"get '%s' result: %d,%d - %d",cmd,arg0,arg1,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "keysize"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleKeysize(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "speedoinfo"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleSpeedoInfo(vid,arg0,arg1,arg2);

				format(str,sizeof(str),"get '%s' result: %d,%d,%d - %d",cmd,arg0,arg1,arg2,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "door"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleDoorStatus(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "radio"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleRadioStation(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "fuel"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    fres = GetModeVehicleFuel(vid);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "engine"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleEngineState(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "ml"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    fres = GetModeVehicleMaxLuggage(vid);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "lt"))
			{
			    vid = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleLuggageType(vid);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "type"))
			{
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleType(arg0);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "subtype"))
			{
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = GetModeVehicleSubType(arg0);

				format(str,sizeof(str),"get '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "maxfuel"))
			{
			    arg0 = strval(strtokex(cmdtext, idx));

			    fres = GetModeVehicleMaxFuel(arg0);

				format(str,sizeof(str),"get '%s' result: %f",cmd,fres);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
	    }
	    if(!strcmp(cmd, "set"))
		{
		    cmd = strtokex(cmdtext, idx);

		    if(!strcmp(cmd, "pos"))
			{
			    vid = strval(strtokex(cmdtext, idx));
				pos[0] = floatstr(strtokex(cmdtext, idx));
				pos[1] = floatstr(strtokex(cmdtext, idx));
				pos[2] = floatstr(strtokex(cmdtext, idx));

			    res = SetModeVehiclePos(vid,pos[0],pos[1],pos[2]);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "angle"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    farg0 = floatstr(strtokex(cmdtext, idx));

			    res = SetModeVehicleAngle(vid,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "health"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    farg0 = floatstr(strtokex(cmdtext, idx));

			    res = SetModeVehicleHealth(vid,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "tuning"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleTuning(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "paintjob"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehiclePaintjob(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "color"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));
			    arg1 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleColor(vid,arg0,arg1);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "keysize"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleKeysize(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "speedoinfo"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));
			    arg1 = strval(strtokex(cmdtext, idx));
			    arg2 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleSpeedoInfo(vid,arg0,arg1,arg2);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "door"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleDoorStatus(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "radio"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleRadioStation(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "fuel"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    farg0 = floatstr(strtokex(cmdtext, idx));

			    res = SetModeVehicleFuel(vid,farg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
		    if(!strcmp(cmd, "engine"))
			{
			    vid = strval(strtokex(cmdtext, idx));
			    arg0 = strval(strtokex(cmdtext, idx));

			    res = SetModeVehicleEngineState(vid,arg0);

				format(str,sizeof(str),"set '%s' result: %d",cmd,res);
				SendClientMessage(playerid,0xFFFFFFFF,str);
				return 1;
		    }
	    }
	    if(!strcmp(cmd, "gpcv"))
		{
		    res = GetPlayerClosestModeVehicle(playerid);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "ial"))
		{
			vid = strval(strtokex(cmdtext, idx));
			
		    res = IsPlayerAroundLuggageModeVehicl(playerid,vid);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "iad"))
		{
			vid = strval(strtokex(cmdtext, idx));

		    res = IsPlayerAroundDoorModeVehicle(playerid,vid);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "ia"))
		{
			vid = strval(strtokex(cmdtext, idx));

		    res = IsModeVehicleActive(playerid);

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
	    if(!strcmp(cmd, "count"))
		{
		    res = GetMaxModeVehicleId();

			format(str,sizeof(str),"vehicle '%s' result: %d",cmd,res);
			SendClientMessage(playerid,0xFFFFFFFF,str);
			return 1;
	    }
   }
#endif

	return 0;
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
	return 1;
}

#endif

#if defined core_camera_included

public OnPlayerCameraCompleteMoving(playerid,cameraid)
{
	return 1;
}

#endif

#if defined core_actions_included

public OnPlayerActionSelectCheck(playerid,actionid)
{
	return 1;
}

public OnPlayerActionSelect(playerid,actionid)
{
#if defined core_dialogs_included
	switch(actionid)
	{
	    case 0: ShowPlayerModeDialog(playerid,0,DIALOG_STYLE_MSGBOX,"info","","But1","But2");
	    case 1: SetPlayerModeDialogListData(playerid,0,1);
	}
#endif
	return 1;
}

#endif

#if defined core_dialogs_included

public OnModeDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	return 1;
}

#endif

#if defined core_pickups_included

public OnPlayerModePickupPickUp(playerid,pickupid)
{
	return 1;
}

#endif

// --------------------------------------------------
// stocks
// --------------------------------------------------
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

#if defined core_debug_included

stock testfunc1()
{
    Debug(DEBUG_START,"testfunc1");
	Debug(DEBUG_ACTION,"dont worry...");
	Debug(DEBUG_END,"testfunc1");
}

stock testfunc2()
{
    Debug(DEBUG_START,"testfunc2");
	Debug(DEBUG_ACTION,"be happy...");
	Debug(DEBUG_END,"testfunc2");
}

#endif
