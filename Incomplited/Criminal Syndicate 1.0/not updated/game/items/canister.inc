/*
*	Created:			11.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		��������
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
�anister_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"�anister_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%.2f �����]",floatstr(var0));	
	Debug(DEBUG_END,"�anister_BuildTypeListItems(reason: complete)");
	return 1;
}

�anister_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"�anister_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true))
			{
				new Float:fuel = GetItemVarFloat(itemid,0);
				if((fuel > 0.0) && ((tmp = GetPlayerClosestModeVehicle(playerid)) != INVALID_MODE_VEHICLE_ID) && IsPlayerAroundLuggageModeVehicl(playerid,tmp) && (GetModeVehicleFuel(tmp) < GetModeVehicleMaxFuel(GetVehicleModel(tmp)))) format(dest,size,"��������� ���������\n������\n��������");
				else if(fuel > 0.0) format(dest,size,"������\n��������");
				else format(dest,size,"��������");
			}
			else format(dest,size,"�������");
		}
		default: format(dest,size,"�����");
	}	
	Debug(DEBUG_END,"�anister_BuildItemActionsString(reason: complete)");
}

�anister_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"�anister_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"��������� ���������"))
	{
		Debug(DEBUG_ACTION,"��������� ���������");
		new Float:vehfuel,
			Float:maxfuel,
			Float:fuel;
		if((fuel = GetItemVarFloat(itemid,0) > 0.0) && ((tmp = GetPlayerClosestModeVehicle(playerid)) == INVALID_MODE_VEHICLE_ID) || !IsPlayerAroundLuggageModeVehicl(playerid,tmp) || ((vehfuel = GetModeVehicleFuel(tmp)) >= (maxfuel = GetModeVehicleMaxFuel(GetVehicleModel(tmp))))) {Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");return 0;}
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
		Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"������"))
	{
		Debug(DEBUG_ACTION,"������");
		SetItemVarFloat(itemid,0,0.0);
		Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"��������"))
	{
		Debug(DEBUG_ACTION,"��������");
		ItemOwnerRemove(itemid);
		new Float:pos[4];
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		GetPlayerFacingAngle(playerid,pos[3]);
		MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
		SetItemPos(itemid,pos[0],pos[1],pos[2]);
		SetItemPremise(itemid,GetPlayerPremise(playerid));
		Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�������"))
	{
		Debug(DEBUG_ACTION,"�������");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�����"))
	{
		Debug(DEBUG_ACTION,"�����");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"�anister_OnPlayerUseItem(reason: complete)");
	return 0;
}