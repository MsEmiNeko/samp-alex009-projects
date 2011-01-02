/*
*	Created:			11.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Канистра
*/

#if defined _items_canister_included
	#endinput
#endif

#define _items_canister_included
#pragma library items_canister

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// statics
// --------------------------------------------------
static tmp;

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Сanister_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Сanister_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%.2f литра]",floatstr(var0));	
	Debug(DEBUG_END,"Сanister_BuildTypeListItems(reason: complete)");
	return 1;
}

Сanister_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Сanister_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true))
			{
				new Float:fuel = GetItemVarFloat(itemid,0);
				if((fuel > 0.0) && ((tmp = GetPlayerClosestModeVehicle(playerid)) != INVALID_MODE_VEHICLE_ID) && IsPlayerAroundLuggageModeVehicl(playerid,tmp) && (GetModeVehicleFuel(tmp) < GetModeVehicleMaxFuel(GetVehicleModel(tmp)))) format(dest,size,"Заправить транспорт\nВылить\nВыкинуть");
				else if(fuel > 0.0) format(dest,size,"Вылить\nВыкинуть");
				else format(dest,size,"Выкинуть");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Сanister_BuildItemActionsString(reason: complete)");
}

Сanister_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Сanister_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Заправить транспорт"))
	{
		Debug(DEBUG_ACTION,"Заправить транспорт");
		new Float:vehfuel,
			Float:maxfuel,
			Float:fuel;
		if((fuel = GetItemVarFloat(itemid,0) > 0.0) && ((tmp = GetPlayerClosestModeVehicle(playerid)) == INVALID_MODE_VEHICLE_ID) || !IsPlayerAroundLuggageModeVehicl(playerid,tmp) || ((vehfuel = GetModeVehicleFuel(tmp)) >= (maxfuel = GetModeVehicleMaxFuel(GetVehicleModel(tmp))))) {Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");return 0;}
		if((vehfuel + fuel) > maxfuel)
		{
			fuel = maxfuel - vehfuel;
			SetItemVarFloat(itemid,0,fuel);
			SetModeVehicleFuel(tmp,maxfuel);
		}
		else
		{
			SetItemVarFloat(itemid,0,0.0);
			SetModeVehicleFuel(tmp,(vehfuel + fuel));
		}
		Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Вылить"))
	{
		Debug(DEBUG_ACTION,"Вылить");
		SetItemVarFloat(itemid,0,0.0);
		Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Выкинуть"))
	{
		Debug(DEBUG_ACTION,"Выкинуть");
		ItemOwnerRemove(itemid);
		new Float:pos[4];
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		GetPlayerFacingAngle(playerid,pos[3]);
		MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
		SetItemPos(itemid,pos[0],pos[1],pos[2]);
		SetItemPremise(itemid,GetPlayerPremise(playerid));
		Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Забрать"))
	{
		Debug(DEBUG_ACTION,"Забрать");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Взять"))
	{
		Debug(DEBUG_ACTION,"Взять");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Сanister_OnPlayerUseItem(reason: complete)");
	return 0;
}