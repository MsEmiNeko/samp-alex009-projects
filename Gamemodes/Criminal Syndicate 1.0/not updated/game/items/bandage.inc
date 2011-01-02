/*
*	Created:			05.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Повязка
*/

#if defined _items_bandage_included
	#endinput
#endif

#define _items_bandage_included
#pragma library items_bandage

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
Bandage_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Bandage_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Bandage_BuildTypeListItems(reason: complete)");
	return 1;
}

Bandage_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Bandage_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) 
			{
				if(((tmp = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) && (GetCharacterVarInt(tmp,"BandageItemId") == INVALID_ITEM_ID)) format(dest,size,"Использовать\nВыкинуть\nРазорвать");
				else format(dest,size,"Выкинуть\nРазорвать");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Bandage_BuildItemActionsString(reason: complete)");
}

Bandage_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Bandage_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Использовать"))
	{
		Debug(DEBUG_ACTION,"Использовать");
		if(((tmp = GetPlayerClosestPlayer(playerid)) == INVALID_PLAYER_ID) || (!IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) || (GetCharacterVarInt(tmp,"BandageItemId") != INVALID_ITEM_ID)) {Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");return 1;}
		ItemOwnerRemove(itemid);
		SetCharacterVarInt(tmp,"BandageItemId",itemid);
		SetPlayerCameraPos(tmp, -127.9947,2258.2878,28.5071);
		SetPlayerCameraLookAt(tmp, -127.9947,2258.2878,20.5071);
		Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
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
		Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Забрать"))
	{
		Debug(DEBUG_ACTION,"Забрать");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Взять"))
	{
		Debug(DEBUG_ACTION,"Взять");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Разорвать"))
	{
		Debug(DEBUG_ACTION,"Разорвать");
		DestroyItem(itemid);
		Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Bandage_OnPlayerUseItem(reason: complete)");
	return 0;
}

Bandage_OnItemsSystemLoaded()
{
	Debug(DEBUG_START,"Bandage_OnItemsSystemLoaded()");
	AddActionSelectRow(RusToGame("Снять повязку"),ACTION_TAKE_BANDAGE);
	Debug(DEBUG_END,"Bandage_OnItemsSystemLoaded(reason: complete)");
}

Bandage_OnPlayerActionCheck(playerid,actionid)
{
	Debug(DEBUG_START,"Bandage_OnPlayerActionCheck(%d,%d)",playerid,actionid);
	switch(actionid)
	{
		case ACTION_TAKE_BANDAGE:
		{
			if(((tmp = GetPlayerClosestPlayer(playerid)) == INVALID_PLAYER_ID) || (!IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) || (GetCharacterVarInt(tmp,"BandageItemId") == INVALID_ITEM_ID)) {Debug(DEBUG_END,"Bandage_OnPlayerActionCheck(reason: complete)");return 0;}
			return 1;
		}
	}
	Debug(DEBUG_END,"Bandage_OnPlayerActionCheck(reason: complete)");
	return 0;
}

Bandage_OnPlayerActionSelect(playerid,actionid)
{
	Debug(DEBUG_START,"Bandage_OnPlayerActionSelect(%d,%d)",playerid,actionid);
	switch(actionid)
	{
		case ACTION_TAKE_BANDAGE:
		{
			new bandageitemid;
			if(((tmp = GetPlayerClosestPlayer(playerid)) == INVALID_PLAYER_ID) || (!IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) || ((bandageitemid = GetCharacterVarInt(tmp,"BandageItemId")) == INVALID_ITEM_ID)) {Debug(DEBUG_END,"Bandage_OnPlayerActionSelect(reason: complete)");return 0;}
			if(!SetItemOwner(bandageitemid,ITEM_OWNER_CHARACTER,playerid))
			{
				ItemOwnerRemove(bandageitemid);
				new Float:pos[4];
				GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
				GetPlayerFacingAngle(playerid,pos[3]);
				MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
				SetItemPos(bandageitemid,pos[0],pos[1],pos[2]);
				SetItemPremise(bandageitemid,GetPlayerPremise(playerid));
			}
			PlayerMessage(playerid,MESSAGE_ACTION,"снял повязку с %s",oGetCharacterName(tmp));
			Debug(DEBUG_END,"Bandage_OnPlayerActionSelect(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Bandage_OnPlayerActionSelect(reason: complete)");
	return 0;
}