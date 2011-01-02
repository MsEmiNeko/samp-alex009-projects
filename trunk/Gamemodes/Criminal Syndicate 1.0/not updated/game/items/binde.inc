/*
*	Created:			19.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Бинт
*/

#if defined _items_binde_included
	#endinput
#endif

#define _items_binde_included
#pragma library items_binde

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Binde_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Binde_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Binde_BuildTypeListItems(reason: complete)");
	return 1;
}

Binde_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Binde_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) 
			{
				format(dest,size,"Использовать\nВыкинуть\nПорвать");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}
	Debug(DEBUG_END,"Binde_BuildItemActionsString(reason: complete)");
}

Binde_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Binde_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Использовать"))
			{
				Debug(DEBUG_ACTION,"Использовать");
				new id;
				if(((id = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,id))) ShowItemsActionsDialog(playerid,ITEM_DIALOG_BINDE_USE_1,"Использовать на себе\nИспользовать на другом");
				else ShowItemsActionsDialog(playerid,ITEM_DIALOG_BINDE_USE_1,"Использовать на себе");
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
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
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Порвать"))
			{
				Debug(DEBUG_ACTION,"Порвать");
				DestroyItem(itemid);
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_BINDE_USE_1:
		{
			if(!strcmp(action,"Использовать на себе"))
			{
				Debug(DEBUG_ACTION,"Использовать на себе");
				PlayerAction(playerid,ACTION_BINDE);
				new Float:health;
				GetPlayerHealth(playerid,health);
				health += 10.0;
				if(health > 100.0) health = 100.0;
				SetPlayerHealth(playerid,health);
				DestroyItem(itemid);
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Использовать на другом"))
			{
				Debug(DEBUG_ACTION,"Использовать на другом");
				new id;
				if(((id = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,id)))
				{
					PlayerAction(id,ACTION_BINDE);
					new Float:health;
					GetPlayerHealth(id,health);
					health += 10.0;
					if(health > 100.0) health = 100.0;
					SetPlayerHealth(id,health);
					DestroyItem(itemid);
				}
				Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
	}
	Debug(DEBUG_END,"Binde_OnPlayerUseItem(reason: complete)");
	return 0;
}