/*
*	Created:			21.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Сигара
*/

#if defined _items_ciggy_included
	#endinput
#endif

#define _items_ciggy_included
#pragma library items_ciggy

// --------------------------------------------------
// defines
// --------------------------------------------------
#define MAX_CIGGY_SMOKE 8

// --------------------------------------------------
// statics
// --------------------------------------------------
static Ciggy_Player[MAX_PLAYERS];

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Ciggy_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Ciggy_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Ciggy_BuildTypeListItems(reason: complete)");
	return 1;
}

Ciggy_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Ciggy_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) format(dest,size,"Выкурить\nВыкинуть\nПорвать и выбросить");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Ciggy_BuildItemActionsString(reason: complete)");
}

Ciggy_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Ciggy_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Выкурить"))
	{
		Debug(DEBUG_ACTION,"Выкурить");
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_SMOKE_CIGGY);
		Ciggy_Player[playerid] = 0;
		Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
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
		Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Забрать"))
	{
		Debug(DEBUG_ACTION,"Забрать");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Взять"))
	{
		Debug(DEBUG_ACTION,"Взять");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Порвать и выбросить"))
	{
		Debug(DEBUG_ACTION,"Порвать и выбросить");
		DestroyItem(itemid);
		Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Ciggy_OnPlayerUseItem(reason: complete)");
	return 0;
}

Ciggy_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Ciggy_OnPlayerKeyStateChange(%d,%d,%d)",playerid,newkeys,oldkeys);
	if(newkeys & KEY_FIRE)
	{
		if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DRINK_CIGGY) {Debug(DEBUG_END,"Ciggy_OnPlayerKeyStateChange(reason: complete)");return 0;}
		Ciggy_Player[playerid]++;
		if(Ciggy_Player[playerid] == MAX_CIGGY_SMOKE) SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
	}
	Debug(DEBUG_END,"Ciggy_OnPlayerKeyStateChange(reason: complete)");
	return 1;
}