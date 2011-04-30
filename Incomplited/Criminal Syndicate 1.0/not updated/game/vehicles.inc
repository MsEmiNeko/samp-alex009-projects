/*
*	Created:			10.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Транспорт
*/

#if defined _vehicles_included
	#endinput
#endif

#define _vehicles_included
#pragma library vehicles

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// defines
// --------------------------------------------------
#define VEHICLE_TOGGLE_ENGINE_KEY 512
#define VEHICLE_TOGGLE_ENGINE_TEXT "~k~~TOGGLE_SUBMISSIONS~"
#define VEHICLE_RADIO_TEXT "~k~~VEHICLE_MOUSELOOK~"

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native IsVehicleHaveRadio(model);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock IsVehicleHaveRadio(model)
{
	Debug(DEBUG_START,"IsVehicleHaveRadio(%d)",model);
	if(model < 400 || model > 612) 
	{
		Debug(DEBUG_END,"IsVehicleHaveRadio(reason: error)");
		print("[WARNING] Vehicles -> IsVehicleHaveRadio (incorrect model)");
		return 0;
	}
	switch(GetModeVehicleSubType(model))
	{
		case 
			VEHICLE_SUBTYPE_RCCAR,
			VEHICLE_SUBTYPE_RCBIKE,
			VEHICLE_SUBTYPE_RCPLANE,
			VEHICLE_SUBTYPE_RCHELI,
			VEHICLE_SUBTYPE_BIKE,
			VEHICLE_SUBTYPE_QUAD,
			VEHICLE_SUBTYPE_CARGO,
			VEHICLE_SUBTYPE_PASSANGER,
			VEHICLE_SUBTYPE_CARGO_T,
			VEHICLE_SUBTYPE_PASSANGER_T: {Debug(DEBUG_END,"IsVehicleHaveRadio(reason: complete)");return 0;}
		default: {Debug(DEBUG_END,"IsVehicleHaveRadio(reason: complete)");return 1;}
	}
	Debug(DEBUG_END,"IsVehicleHaveRadio(reason: complete)");
	return 0;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Vehicles_OnGameModeInit()
{
	Debug(DEBUG_START,"Vehicles_OnGameModeInit()");
	AddActionSelectRow(RusToGame("Сменить~n~частоту~n~радио"),ACTION_CHANGE_RADIO_REQ);
	print("Vehicles system loaded.");
	Debug(DEBUG_END,"Vehicles_OnGameModeInit(reason: complete)");
}

Vehicles_OnPlayerStateChange(playerid, newstate, oldstate)
{
	Debug(DEBUG_START,"Vehicles_OnPlayerStateChange(%d,%d,%d)",playerid,newstate,oldstate);
	if(newstate != PLAYER_STATE_DRIVER) {Debug(DEBUG_END,"Vehicles_OnPlayerStateChange(reason: complete)");return;}
	ShowHelpBoxForPlayer(playerid,helpboxid,"Используйте "VEHICLE_RADIO_TEXT" чтобы ~n~сменить радио станцию.~n~Используйте "VEHICLE_TOGGLE_ENGINE_TEXT"  чтобы ~n~запустить двигатель");
	Debug(DEBUG_END,"Vehicles_OnPlayerStateChange(reason: complete)");
	return;
}

Vehicles_OnPlayerActionCheck(playerid,actionid)
{
	Debug(DEBUG_START,"Vehicles_OnPlayerActionCheck(%d,%d)",playerid,actionid);
	if(!IsPlayerInAnyVehicle(playerid)) {Debug(DEBUG_END,"Vehicles_OnPlayerActionCheck(reason: complete)");return 0;}
	switch(actionid)
	{
		case ACTION_CHANGE_RADIO_REQ:
		{
			Debug(DEBUG_ACTION,"ACTION_CHANGE_RADIO_REQ");
			if(!IsVehicleHaveRadio(GetVehicleModel(GetPlayerVehicleID(playerid)))) {Debug(DEBUG_END,"Vehicles_OnPlayerActionCheck(reason: complete)");return 0;}
			return 1;
		}
	}
	Debug(DEBUG_END,"Vehicles_OnPlayerActionCheck(reason: complete)");
	return 0;
}

Vehicles_OnPlayerActionSelect(playerid,actionid)
{
	Debug(DEBUG_START,"Vehicles_OnPlayerActionSelect(%d,%d)",playerid,actionid);
	if(!IsPlayerInAnyVehicle(playerid)) {Debug(DEBUG_END,"Vehicles_OnPlayerActionCheck(reason: complete)");return 0;}
	switch(actionid)
	{
		case ACTION_CHANGE_RADIO_REQ:
		{
			Debug(DEBUG_ACTION,"ACTION_CHANGE_RADIO_REQ");
			if(!IsVehicleHaveRadio(GetVehicleModel(GetPlayerVehicleID(playerid)))) {Debug(DEBUG_END,"Vehicles_OnPlayerActionCheck(reason: complete)");return 0;}
			DialogString = "Ввести свою\n";
			new Float:pos[3];
			GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
			new tmp = GetSquareIdForXY(pos[0],pos[1]),
				li = 1;
			for(new i = 1;i <= 300;i++)
			{
				if(!IsSquareHaveNetwork(tmp,i)) continue;
				format(DialogString,sizeof(DialogString),"%s%d MHz\n",DialogString,i);
				SetPlayerModeDialogListData(playerid,li,i);
				li++;
			}
			ShowPlayerModeDialog(playerid,DIALOG_VEHICLE_RADIO,DIALOG_STYLE_LIST,"Радио-станции",DialogString,"Выбрать","Выход");
			return 1;
		}
	}
	Debug(DEBUG_END,"Vehicles_OnPlayerActionSelect(reason: complete)");
	return 0;
}

Vehicles_OnModeDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	Debug(DEBUG_START,"Vehicles_OnModeDialogResponse(%d,%d,%d,%d,'%s')",playerid,dialogid,response,listitem,inputtext);
	switch(dialogid)
	{
		case DIALOG_VEHICLE_RADIO:
		{
			Debug(DEBUG_ACTION,"DIALOG_VEHICLE_RADIO");
			if(!response) {Debug(DEBUG_END,"Vehicles_OnModeDialogResponse(reason: complete)");return 1;}
			if(listitem == 0) ShowPlayerModeDialog(playerid,DIALOG_VEHICLE_RADIO_2,DIALOG_STYLE_INPUT,"Радио-станция","Введите частоту радио-станции","Готово","Выход");
			else SetModeVehicleRadioStation(GetPlayerVehicleID(playerid),GetPlayerModeDialogListData(playerid,listitem));
			Debug(DEBUG_END,"Vehicles_OnModeDialogResponse(reason: complete)");
			return 1;
		}
		case DIALOG_VEHICLE_RADIO_2:
		{
			Debug(DEBUG_ACTION,"DIALOG_VEHICLE_RADIO_2");
			if(!response) {Debug(DEBUG_END,"Vehicles_OnModeDialogResponse(reason: complete)");return 1;}
			SetModeVehicleRadioStation(GetPlayerVehicleID(playerid),strval(inputtext));
			Debug(DEBUG_END,"Vehicles_OnModeDialogResponse(reason: complete)");
			return 1;			
		}
	}
	Debug(DEBUG_END,"Vehicles_OnModeDialogResponse(reason: complete)");
	return 0;	
}

Vehicles_OnRadioMessageRecived(message[],networkid) 
{
	Debug(DEBUG_START,"Vehicles_OnRadioMessageRecived('%s',%d)",message,networkid);
	new sqid,
		Float:pos[3];
	for(new i = 0;i <= GetModeVehiclesCount();i++)
	{
		if(!IsModeVehicleActive(i)) continue;
		GetModeVehiclePos(i,pos[0],pos[1],pos[2]);
		if(!IsSquareHaveNetwork((sqid = GetSquareIdForXY(pos[0],pos[1])),networkid)) continue;
		for(new p = 0;p <= GetMaxPlayer();p++)
		{
			if(!IsPlayerConnected(p)) continue;
			if(!IsPlayerRangeOfPoint(p,VEHICLE_RADIO_DISTANCE,pos[0],pos[1],pos[2])) continue;
			ModeMessage(p,MODE_MESSAGE_RADIO,message);
		}	
	}
	Debug(DEBUG_END,"Vehicles_OnRadioMessageRecived(reason: complete)");
	return;
}

Vehicle_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Vehicle_OnPlayerKeyStateChange(%d,%d,%d)",playerid,newkeys,oldkeys);
	new vehicleid = GetPlayerVehicleID(playerid)
	if((vehicleid != INVALID_VEHICLE_ID) && (newkeys & VEHICLE_TOGGLE_ENGINE_KEY))
	{
		if(!GetModeVehicleEngineState(vehicleid))
		{
			Debug(DEBUG_ACTION,"Engine control");		
			new Float:fuel = GetModeVehicleFuel(vehicleid),
				Float:health;
			GetVehicleHealth(vehicleid,health);
			if((fuel > 5.0) && (health > 900.0)) SetModeVehicleEngineState(vehicleid,true);
			else if((fuel > 5.0) && (health > 500.0) && (random(10) > 5)) SetModeVehicleEngineState(vehicleid,true);
			else if((fuel > 5.0) && (health > 300.0) && (random(10) > 3)) SetModeVehicleEngineState(vehicleid,true);
			else if((fuel > 1.0) && (health > 500.0) && (random(15) > 10)) SetModeVehicleEngineState(vehicleid,true);
			else if((fuel > 1.0) && (health > 300.0) && (random(30) > 25)) SetModeVehicleEngineState(vehicleid,true);
		}
		else SetModeVehicleEngineState(vehicleid,false);
	}
	Debug(DEBUG_END,"Vehicle_OnPlayerKeyStateChange(reason: complete)");
}