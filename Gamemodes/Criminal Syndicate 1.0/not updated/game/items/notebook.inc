/*
*	Created:			26.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Блокнот
*/

#if defined _items_notebook_included
	#endinput
#endif

#define _items_notebook_included
#pragma library items_notebook

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Notebook_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Notebook_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	if(strlen(var0)) format(dest,size,"[%s]",var0);
	Debug(DEBUG_END,"Notebook_BuildTypeListItems(reason: complete)");
	return 1;
}

Notebook_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Notebook_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) format(dest,size,"Записать\nПрочитать\nВыкинуть\nПорвать");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Notebook_BuildItemActionsString(reason: complete)");
}

Notebook_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Notebook_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Записать"))
			{
				Debug(DEBUG_ACTION,"Записать");
				ShowItemsInputDialog(playerid,ITEM_DIALOG_NOTEBOOK_WRITE,"Введите текст для записи в блокнот:");
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Прочитать"))
			{
				Debug(DEBUG_ACTION,"Прочитать");
				nullstr(DialogString);
				format(query,sizeof(query),"SELECT `Content` FROM `Notebook_data` WHERE `ItemId`=%d",itemid);
				samp_mysql_query(query);
				samp_mysql_store_result();
				while(samp_mysql_fetch_row(result)) format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,result);
				ShowItemsMessageDialog(playerid,ITEM_DIALOG_NOTEBOOK_READ,DialogString);
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
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
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Порвать"))
			{
				Debug(DEBUG_ACTION,"Порвать");
				DestroyItem(itemid);
				Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_NOTEBOOK_WRITE:
		{
			format(query,sizeof(query),"INSERT INTO `Notebook_data` (`ItemId`,`Content`) VALUES (%d,'%s')",itemid,action);
			samp_mysql_query(query);
			Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
			return 1;
		}
		case ITEM_DIALOG_NOTEBOOK_READ:
		{
			Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Notebook_OnPlayerUseItem(reason: complete)");
	return 0;
}