/*
*	Created:			04.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Рация
*/

#if defined _items_portable_radio_transmitter_included
	#endinput
#endif

#define _items_portable_radio_transmitter_included
#pragma library items_portable_radio_transmitter

// --------------------------------------------------
// includes
// --------------------------------------------------

// --------------------------------------------------
// enums
// --------------------------------------------------
enum PRTPlayerInfo {
	bool:pActiveRadio,
	pRadioFrequency
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static Prt_Player[MAX_PLAYERS][PRTPlayerInfo];
	
// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Prt_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Prt_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	format(dest,size,"[%s MHz]",var0);	
	Debug(DEBUG_END,"Prt_BuildTypeListItems(reason: complete)");
	return 1;
}

Prt_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Prt_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) 
			{
				if(Prt_Player[playerid][pActiveRadio]) format(dest,size,"Выключить\nСменить частоту\nВыкинуть\nСломать");
				else format(dest,size,"Включить\nСменить частоту\nВыкинуть\nСломать");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Prt_BuildItemActionsString(reason: complete)");
}

Prt_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Prt_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Включить"))
			{
				Debug(DEBUG_ACTION,"Включить");
				Prt_Player[playerid][pActiveRadio] = true;
				Prt_Player[playerid][pRadioFrequency] = GetItemVarInt(itemid,0);
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Выключить"))
			{
				Debug(DEBUG_ACTION,"Выключить");
				Prt_Player[playerid][pActiveRadio] = false;
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Сменить частоту"))
			{
				Debug(DEBUG_ACTION,"Сменить частоту");
				ShowItemsInputDialog(playerid,ITEM_DIALOG_PRT_FREQUENCY,"Введите новую частоту:");
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 0;
			}			
			if(!strcmp(action,"Выкинуть"))
			{
				Debug(DEBUG_ACTION,"Выкинуть");
				Prt_Player[playerid][pActiveRadio] = false;
				ItemOwnerRemove(itemid);
				new Float:pos[4];
				GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
				GetPlayerFacingAngle(playerid,pos[3]);
				MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
				SetItemPos(itemid,pos[0],pos[1],pos[2]);
				SetItemPremise(itemid,GetPlayerPremise(playerid));
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Сломать"))
			{
				Debug(DEBUG_ACTION,"Сломать");
				Prt_Player[playerid][pActiveRadio] = false;
				DestroyItem(itemid);
				Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_PRT_FREQUENCY:
		{
			new fq = strval(action);
			SetItemVarInt(itemid,0,fq);
			Prt_Player[playerid][pRadioFrequency] = fq;
			Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Prt_OnPlayerUseItem(reason: complete)");
	return 0;
}

Ptr_OnPlayerText(playerid,text[])
{
	Debug(DEBUG_START,"Ptr_OnPlayerText(%d,'%s')",playerid,text);
	if(!Prt_Player[playerid][pActiveRadio]) {Debug(DEBUG_END,"Ptr_OnPlayerText(reason: complete)");return 1;}
	PlayerMessage(playerid,PLAYER_MESSAGE_PRT,text);
	Debug(DEBUG_END,"Ptr_OnPlayerText(reason: complete)");
	return 1;
}

Prt_OnPlayerMessage(playerid,message[],type,formated[])
{
	Debug(DEBUG_START,"Prt_OnPlayerMessage(%d,'%s',%d,'%s')",playerid,message,type,formated);
	static bool:tmp[MAX_PLAYERS];
	for(new i = 0;i <= GetMaxPlayer();i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(!Prt_Player[i][pActiveRadio]) continue;
		if(!IsPlayerInRangeOfPlayer(playerid,PTR_DISTANCE,i)) continue;
		if(Prt_Player[i][pRadioFrequency] != networkid) continue;
		for(new j = 0;j <= GetMaxPlayer();j++)
		{
			if(!IsPlayerConnected(j)) continue;
			if(!IsPlayerInRangeOfPlayer(i,PRT_LISTEN_DISTANCE,j)) continue;
			if(tmp[j]) continue;
			SendClientMessage(j,PRT_MESSAGE_COLOR,formated);
			tmp[j] = true;
		}
	}
	Debug(DEBUG_END,"Prt_OnPlayerMessage(reason: complete)");
	return 1;
}