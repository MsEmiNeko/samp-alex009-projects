/*
*	Created:			19.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Наркотики
*/

#if defined _items_drugs_included
	#endinput
#endif

#define _items_drugs_included
#pragma library items_drugs

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Drugs_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Drugs_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s доз]",var0);
	Debug(DEBUG_END,"Drugs_BuildTypeListItems(reason: complete)");
	return 1;
}

Drugs_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Drugs_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
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
	Debug(DEBUG_END,"Drugs_BuildItemActionsString(reason: complete)");
}

Drugs_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Drugs_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Использовать"))
			{
				Debug(DEBUG_ACTION,"Использовать");
				PlayerAction(playerid,ACTION_DRUGS);
				SetPlayerDrunkLevel(playerid,50_000);
				new count = GetItemVarInt(itemid,0);
				if(count == 1) DestroyItem(itemid);
				else SetItemVarInt(itemid,0,count - 1);				
				Debug(DEBUG_END,"Drugs_OnPlayerUseItem(reason: complete)");
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
				Debug(DEBUG_END,"Drugs_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Drugs_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Drugs_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
	}
	Debug(DEBUG_END,"Drugs_OnPlayerUseItem(reason: complete)");
	return 0;
}

Drugs_OnPlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Drugs_OnPlayerUpdate(%d)",playerid);
	if(GetPlayerDrunkLevel(playerid) < 10_000) {Debug(DEBUG_END,"Drugs_OnPlayerUpdate(reason: complete)");return 1;}	
	SetPlayerDrunkLevel(playerid,(GetPlayerDrunkLevel(playerid) - 1));
	new Float:health;
	GetPlayerHealth(playerid,health);
	SetPlayerHealth(playerid,(health - 0.1));
	Debug(DEBUG_END,"Drugs_OnPlayerUpdate(reason: complete)");
	return 1;
}