/*
*	Created:			10.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		�������
*/

#if defined _items_multi_key_included
	#endinput
#endif

#define _items_multi_key_included
#pragma library items_multi_key

// --------------------------------------------------
// defines
// --------------------------------------------------


// --------------------------------------------------
// statics
// --------------------------------------------------
static checkobj;

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
MultiKey_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"MultiKey_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s]",var0);
	Debug(DEBUG_END,"MultiKey_BuildTypeListItems(reason: complete)");
	return;
}

MultiKey_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"MultiKey_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true))
			{
				if(((checkobj = GetPlayerClosestModeVehicle(playerid)) != INVALID_MODE_VEHICLE_ID) && IsPlayerAroundDoorModeVehicle(playerid,checkobj)) 
				{
					if(GetModeVehicleKeysize(checkobj) == GetItemVarInt(itemid,1))
					{
						if(!GetModeVehicleDoorStatus(checkobj)) format(dest,size,"������� ���������\n��������");
						else format(dest,size,"������� ���������\n��������");
					}
				}
				if(((checkobj = GetPlayerPremiseEnterOn(playerid)) != 0) || ((checkobj = GetPlayerPremiseExitOn(playerid)) != 0))
				{
					if(GetPremiseKeysize(checkobj) == GetItemVarInt(itemid,1))
					{
						if(!GetPremiseDoorStatus(checkobj)) format(dest,size,"������� ���������\n��������");
						else format(dest,size,"������� ���������\n��������");
					}
				}
				if(((checkobj = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,checkobj)))
				{
					new handcuffsitem = GetCharacterVarInt(tmp,"HandcuffsItemId");
					if(GetItemVarInt(handcuffsitem,0) == GetItemVarInt(itemid,1)) format(dest,size,"����� ���������\n��������");
				}
			}
			else format(dest,size,"�������");
		}
		default: format(dest,size,"�����");
	}	
	Debug(DEBUG_END,"MultiKey_BuildItemActionsString(reason: complete)");
}

MultiKey_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"MultiKey_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"������� ���������"))
	{
		Debug(DEBUG_ACTION,"������� ���������");
		if(((checkobj = GetPlayerClosestModeVehicle(playerid)) != INVALID_MODE_VEHICLE_ID) && IsPlayerAroundDoorModeVehicle(playerid,checkobj)) 
		{
			if(GetModeVehicleKeysize(checkobj) != GetItemVarInt(itemid,1)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			if(GetModeVehicleDoorStatus(checkobj)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			PlayerMessage(playerid,MESSAGE_ACTION,"��������� � �����");
			new luck = random(200),
				skill;
			if(luck < (100 + 1 * (skill = GetCharacterVarInt(playerid,"RobSkill"))))
			{
				SetModeVehicleDoorStatus(checkobj,1);
				SetCharacterVarInt(playerid,"RobSkill",(skill + 1));
			}
			else if(luck < (180 - 1 * skill))
			{
				DestroyItem(itemid);
				PlayerMessage(playerid,MESSAGE_ACTION,"������ �����");
			}
			Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	if(!strcmp(action,"������� ���������"))
	{
		Debug(DEBUG_ACTION,"������� ���������");
		if(((checkobj = GetPlayerClosestModeVehicle(playerid)) != INVALID_MODE_VEHICLE_ID) && IsPlayerAroundDoorModeVehicle(playerid,checkobj)) 
		{
			if(GetModeVehicleKeysize(checkobj) != GetItemVarInt(itemid,1)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			if(!GetModeVehicleDoorStatus(checkobj)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			PlayerMessage(playerid,MESSAGE_ACTION,"��������� � �����");
			new luck = random(200),
				skill;
			if(luck < (100 + 1 * (skill = GetCharacterVarInt(playerid,"RobSkill"))))
			{
				SetModeVehicleDoorStatus(checkobj,0);
				SetCharacterVarInt(playerid,"RobSkill",(skill + 1));
			}
			else if(luck < (180 - 1 * skill))
			{
				DestroyItem(itemid);
				PlayerMessage(playerid,MESSAGE_ACTION,"������ �����");
			}
			Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	if(!strcmp(action,"������� ���������"))
	{
		Debug(DEBUG_ACTION,"������� ���������");
		if(((checkobj = GetPlayerPremiseEnterOn(playerid)) != 0) || ((checkobj = GetPlayerPremiseExitOn(playerid)) != 0))
		{
			if(GetPremiseKeysize(checkobj) != GetItemVarInt(itemid,1)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			if(GetPremiseDoorStatus(checkobj)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			PlayerMessage(playerid,MESSAGE_ACTION,"��������� � �����");
			new luck = random(200),
				skill;
			if(luck < (100 + 1 * (skill = GetCharacterVarInt(playerid,"RobSkill"))))
			{
				SetPremiseDoorStatus(checkobj,1);
				SetCharacterVarInt(playerid,"RobSkill",(skill + 1));
			}
			else if(luck < (180 - 1 * skill))
			{
				DestroyItem(itemid);
				PlayerMessage(playerid,MESSAGE_ACTION,"������ �����");
			}
			Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	if(!strcmp(action,"������� ���������"))
	{
		Debug(DEBUG_ACTION,"������� ���������");
		if(((checkobj = GetPlayerPremiseEnterOn(playerid)) != 0) || ((checkobj = GetPlayerPremiseExitOn(playerid)) != 0))
		{
			if(GetPremiseKeysize(checkobj) != GetItemVarInt(itemid,1)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			if(!GetPremiseDoorStatus(checkobj)) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			PlayerMessage(playerid,MESSAGE_ACTION,"��������� � �����");
			new luck = random(200),
				skill;
			if(luck < (100 + 1 * (skill = GetCharacterVarInt(playerid,"RobSkill"))))
			{
				SetPremiseDoorStatus(checkobj,0);
				SetCharacterVarInt(playerid,"RobSkill",(skill + 1));
			}
			else if(luck < (180 - 1 * skill))
			{
				DestroyItem(itemid);
				PlayerMessage(playerid,MESSAGE_ACTION,"������ �����");
			}
			Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	if(!strcmp(action,"����� ���������"))
	{
		Debug(DEBUG_ACTION,"����� ���������");
		if(((checkobj = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,checkobj)))
		{
			new handcuffsitem = GetCharacterVarInt(checkobj,"HandcuffsItemId");
			if(GetItemVarInt(handcuffsitem,0) == INVALID_ITEM_ID) {Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");return 0;}
			PlayerMessage(playerid,MESSAGE_ACTION,"��������� � �����");
			new luck = random(200),
				skill;
			if(luck < (100 + 1 * (skill = GetCharacterVarInt(playerid,"RobSkill"))))
			{
				SetPlayerAction(checkobj,ACTION_NONE);
				if(!SetItemOwner(handcuffsitem,ITEM_OWNER_CHARACTER,playerid))
				{
					ItemOwnerRemove(handcuffsitem);
					new Float:pos[4];
					GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
					GetPlayerFacingAngle(playerid,pos[3]);
					MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
					SetItemPos(handcuffsitem,pos[0],pos[1],pos[2]);
					SetItemPremise(handcuffsitem,GetPlayerPremise(playerid));
				}
				SetItemVarInt(handcuffsitem,0,0);
				SetCharacterVarInt(playerid,"RobSkill",(skill + 1));
			}
			else if(luck < (180 - 1 * skill))
			{
				DestroyItem(itemid);
				PlayerMessage(playerid,MESSAGE_ACTION,"������ �����");
			}
			Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
			return 1;
		}
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
		Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�������"))
	{
		Debug(DEBUG_ACTION,"�������");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�����"))
	{
		Debug(DEBUG_ACTION,"�����");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"MultiKey_OnPlayerUseItem(reason: complete)");
	return 0;
}