/*
*	Created:			01.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Газета
*/

#if defined _items_newspaper_included
	#endinput
#endif

#define _items_newspaper_included
#pragma library items_newspaper

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Newspaper_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Newspaper_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s]",var0);	
	Debug(DEBUG_END,"Newspaper_BuildTypeListItems(reason: complete)");
	return 1;
}

Newspaper_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Newspaper_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) format(dest,size,"Прочитать\nВыкинуть\nПорвать");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Newspaper_BuildItemActionsString(reason: complete)");
}

Newspaper_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Newspaper_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Прочитать"))
			{
				Debug(DEBUG_ACTION,"Прочитать");
				ShowItemsMessageDialog(playerid,ITEM_DIALOG_NEWSPAPER_END,GetItemVarString(itemid,1));
				Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
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
				Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Порвать"))
			{
				Debug(DEBUG_ACTION,"Порвать");
				DestroyItem(itemid);
				Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_NEWSPAPER_END:
		{
			Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Newspaper_OnPlayerUseItem(reason: complete)");
	return 0;
}