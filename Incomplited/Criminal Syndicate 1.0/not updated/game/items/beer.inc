/*
*	Created:			21.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Пиво
*/

#if defined _items_beer_included
	#endinput
#endif

#define _items_beer_included
#pragma library items_beer

// --------------------------------------------------
// defines
// --------------------------------------------------
#define MAX_BEER_DRINK 5

// --------------------------------------------------
// statics
// --------------------------------------------------
static Beer_Player[MAX_PLAYERS];

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Beer_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Beer_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Beer_BuildTypeListItems(reason: complete)");
	return 1;
}

Beer_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Beer_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) format(dest,size,"Выпить\nВыкинуть\nРазбить");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Beer_BuildItemActionsString(reason: complete)");
}

Beer_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Beer_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Выпить"))
	{
		Debug(DEBUG_ACTION,"Выпить");
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_BEER);
		Beer_Player[playerid] = 0;
		Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
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
		Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Забрать"))
	{
		Debug(DEBUG_ACTION,"Забрать");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Взять"))
	{
		Debug(DEBUG_ACTION,"Взять");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Разбить"))
	{
		Debug(DEBUG_ACTION,"Разбить");
		DestroyItem(itemid);
		Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Beer_OnPlayerUseItem(reason: complete)");
	return 0;
}

Beer_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Beer_OnPlayerKeyStateChange(%d,%d,%d)",playerid,newkeys,oldkeys);
	if(newkeys & KEY_FIRE)
	{
		if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DRINK_BEER) {Debug(DEBUG_END,"Beer_OnPlayerKeyStateChange(reason: complete)");return 0;}
		Beer_Player[playerid]++;
		if(Beer_Player[playerid] == MAX_BEER_DRINK) SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
	}
	Debug(DEBUG_END,"Beer_OnPlayerKeyStateChange(reason: complete)");
	return 1;
}