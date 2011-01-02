/*
*	Created:			17.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		
*/

#if defined _items_  _included
	#endinput
#endif

#define _items_  _included
#pragma library items_

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum

// --------------------------------------------------
// statics
// --------------------------------------------------
static

// --------------------------------------------------
// statics functions
// --------------------------------------------------
static 

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
 _BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Weapons_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size," ",var0);	
	Debug(DEBUG_END,"Weapons_BuildTypeListItems(reason: complete)");
	return 1;
}

 _BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Weapons_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) format(dest,size,"Убрать\nВыкинуть");
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Weapons_BuildItemActionsString(reason: complete)");
}

 _OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Weapons_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Взять в руки"))
	{
		Debug(DEBUG_ACTION,"Взять в руки");

		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
	return 0;
}