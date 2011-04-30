/*
*	Created:			18.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Аптечка
*/

#if defined _items_medicalkit_included
	#endinput
#endif

#define _items_medicalkit_included
#pragma library items_medicalkit

// --------------------------------------------------
// defines
// --------------------------------------------------
#define HEAL_ME_ANIMATION "PED","LOLBOT",4.1,0,0,0,-1
#define HEAL_ANIMATION "MEDIC","CPR",4.1,0,0,0,-1
#define HEALED_ANIMATION "MB_CHASE","LOLBOT",4.1,0,0,0,-1
#define HEAL_TIME 30000

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward HealComplete(healingid,healedid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public HealComplete(healingid,healedid)
{
	Debug(DEBUG_START,"HealComplete(%d,%d)",healingid,healedid);
	switch(healedid)
	{
		case INVALID_PLAYER_ID:
		{
			SetPlayerAction(healingid,ACTION_NONE);
			ClearAnimations(healingid);
			SetPlayerHealth(healingid,100.0);
		}
		default:
		{
			SetPlayerAction(healingid,ACTION_NONE);
			ClearAnimations(healingid);
			SetPlayerAction(healedid,ACTION_NONE);
			ClearAnimations(healedid);
			SetPlayerHealth(healedid,100.0);
		}
	}
	Debug(DEBUG_END,"HealComplete(reason: complete)");
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
MedicalKit_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"MedicalKit_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s лекарств]",var0);
	Debug(DEBUG_END,"MedicalKit_BuildTypeListItems(reason: complete)");
	return 1;
}

MedicalKit_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"MedicalKit_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) 
			{
				format(dest,size,"Использовать\nВыкинуть");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}
	Debug(DEBUG_END,"MedicalKit_BuildItemActionsString(reason: complete)");
}

MedicalKit_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"MedicalKit_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Использовать"))
			{
				Debug(DEBUG_ACTION,"Использовать");
				new id;
				if(((id = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,id))) ShowItemsActionsDialog(playerid,ITEM_DIALOG_MEDICALKIT_USE_1,"Использовать на себе\nИспользовать на другом");
				else ShowItemsActionsDialog(playerid,ITEM_DIALOG_MEDICALKIT_USE_1,"Использовать на себе");
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 0;
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
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_MEDICALKIT_USE_1:
		{
			if(!strcmp(action,"Использовать на себе"))
			{
				Debug(DEBUG_ACTION,"Использовать на себе");
				new count = GetItemVarInt(itemid,0);
				if(count == 1) DestroyItem(itemid);
				else SetItemVarInt(itemid,0,count - 1);
				ApplyAnimation(playerid,HEAL_ME_ANIMATION);
				SetPlayerAction(playerid,ACTION_HEAL_ME);
				SetTimerEx("HealComplete",HEAL_TIME,0,"dd",playerid,INVALID_PLAYER_ID);
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Использовать на другом"))
			{
				Debug(DEBUG_ACTION,"Использовать на другом");
				new id;
				if(((id = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,id)))
				{
					new count = GetItemVarInt(itemid,0);
					if(count == 1) DestroyItem(itemid);
					else SetItemVarInt(itemid,0,count - 1);
					ApplyAnimation(playerid,HEAL_ANIMATION);
					SetPlayerAction(playerid,ACTION_HEAL);
					ApplyAnimation(id,HEALED_ANIMATION);
					SetPlayerAction(id,ACTION_HEALED);
					SetTimerEx("HealComplete",HEAL_TIME,0,"dd",playerid,id);
				}
				Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
	}
	Debug(DEBUG_END,"MedicalKit_OnPlayerUseItem(reason: complete)");
	return 0;
}