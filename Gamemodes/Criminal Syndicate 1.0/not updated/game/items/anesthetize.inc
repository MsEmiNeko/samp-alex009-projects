/*
*	Created:			19.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Обезболивающие
*/

#if defined _items_anesthetize_included
	#endinput
#endif

#define _items_anesthetize_included
#pragma library items_anesthetize

// --------------------------------------------------
// defines
// --------------------------------------------------
#define ANESTHETIZE_TIME 360000

// --------------------------------------------------
// statics
// --------------------------------------------------
static tmp;

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward AnesthetizeComplete(playerid,Float:health);

// --------------------------------------------------
// publics
// --------------------------------------------------
public AnesthetizeComplete(playerid,Float:health)
{
	SetPlayerDrunkLevel(playerid,0);
	SetPlayerHealth(playerid,health);	
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Anesthetize_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Anesthetize_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s мл]",var0);
	Debug(DEBUG_END,"Anesthetize_BuildTypeListItems(reason: complete)");
	return 1;
}

Anesthetize_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Anesthetize_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) format(dest,size,"Использовать\nВыкинуть\nРазбить");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}
	Debug(DEBUG_END,"Anesthetize_BuildItemActionsString(reason: complete)");
}

Anesthetize_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Anesthetize_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Использовать"))
			{
				Debug(DEBUG_ACTION,"Использовать");
				if(((tmp = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,tmp))) ShowItemsListDialog(playerid,ITEM_DIALOG_ANESTHETIZE_USE_1,"Использовать на себе\nИспользовать на другом");
				else ShowItemsListDialog(playerid,ITEM_DIALOG_ANESTHETIZE_USE_1,"Использовать на себе");
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
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
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Разбить"))
			{
				Debug(DEBUG_ACTION,"Разбить");
				DestroyItem(itemid);
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_ANESTHETIZE_USE_1:
		{
			if(!strcmp(action,"Использовать на себе"))
			{
				Debug(DEBUG_ACTION,"Использовать на себе");
				PlayerAction(playerid,ACTION_ANESTHETIZE);
				new Float:health;
				GetPlayerHealth(playerid,health);
				SetTimerEx("AnesthetizeComplete",ANESTHETIZE_TIME,0,"df",playerid,health);
				health += 50.0;
				if(health > 150.0) health = 150.0;
				SetPlayerHealth(playerid,health);
				SetPlayerDrunkLevel(playerid,5000);
				new count = GetItemVarInt(itemid,0);
				if(count == 1) DestroyItem(itemid);
				else SetItemVarInt(itemid,0,count - 1);
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Использовать на другом"))
			{
				Debug(DEBUG_ACTION,"Использовать на другом");
				if(((tmp = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,tmp)))
				{
					PlayerAction(tmp,ACTION_ANESTHETIZE);
					new Float:health;
					GetPlayerHealth(tmp,health);
					SetTimerEx("AnesthetizeComplete",ANESTHETIZE_TIME,0,"df",tmp,health);
					health += 50.0;
					if(health > 150.0) health = 150.0;
					SetPlayerHealth(tmp,health);
					SetPlayerDrunkLevel(tmp,5000);
					new count = GetItemVarInt(itemid,0);
					if(count == 1) DestroyItem(itemid);
					else SetItemVarInt(itemid,0,count - 1);
				}
				Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
	}
	Debug(DEBUG_END,"Anesthetize_OnPlayerUseItem(reason: complete)");
	return 0;
}