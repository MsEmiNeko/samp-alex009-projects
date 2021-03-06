/*
*	Created:			11.03.10
*	Author:				009
*	Last Modifed:		-
*	Description:		��������� �������
*/

#if defined _items_mobile_included
	#endinput
#endif

#define _items_mobile_included
#pragma library items_mobile

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum MobilePlayerInfo {
	pInterlocutorId,
	pActiveMobileItemId,
	pUsingMobileItemId,
	pSMSText[MAX_STRING],
	pSMSnumber
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static 
	Mobile_Player[MAX_PLAYERS][MobilePlayerInfo],
	tmp;

// --------------------------------------------------
// statics functions
// --------------------------------------------------
static 

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Mobile_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Mobile_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	if((tmp = strval(var0)) != INVALID_ITEM_ID) format(dest,size,"[%s]",GetNetworkName(tmp));
	Debug(DEBUG_END,"Mobile_BuildTypeListItems(reason: complete)");
	return 1;
}

Mobile_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Mobile_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true))
			{
				if(!GetItemVarInt(itemid,0)) format(dest,size,"�������� SIM\n��������\n�������");
				else if(Mobile_Player[playerid][pInterlocutorId] != INVALID_PLAYER_ID) format(dest,size,"��������\n��������\n��������\n�������");
				else format(dest,size,"���������\n�������� SMS\n�������� SMS\n�������� SIM\n��������\n�������");
			}
			else format(dest,size,"�������");
		}
		default: format(dest,size,"�����");
	}	
	Debug(DEBUG_END,"Mobile_BuildItemActionsString(reason: complete)");
}

Mobile_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Mobile_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"�������� SIM"))
			{
				Debug(DEBUG_ACTION,"�������� SIM");
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				format(query,sizeof(query),"SELECT * FROM "ITEMS_TABLE" WHERE `OwnerType`=%d AND `OwnerId`='%s' AND `Type`=%d",ITEM_OWNER_CHARACTER,oGetCharacterName(playerid),type);
				samp_mysql_query(query);
				samp_mysql_store_result();
				nullstr(DialogString);
				tmp = 0;
				new str[MAX_STRING],
					var0[100]; // �� ������ 100 ������ ����� �� ����� :)
				while(samp_mysql_fetch_row(result))
				{
					samp_mysql_get_field("id",str);
					SetPlayerModeDialogListData(playerid,tmp,strval(str));
					samp_mysql_get_field("Var_0",str);
					var0[tmp] = strval(str);
					tmp++;
				}
				for(new i = 0;i < tmp;i++) format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,GetNetworkName(var0[i]));
				ShowItemsListDialog(playerid,ITEM_DIALOG_MOBILE_SIM_SELECT,DialogString);
				Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"��������"))
			{
				Debug(DEBUG_ACTION,"��������");
				if(Mobile_Player[playerid][pInterlocutorId] == INVALID_PLAYER_ID) {Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");return 1;}
				if(!IsPlayerConnected(Mobile_Player[playerid][pInterlocutorId])) {Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");return 1;}
				if(GetPlayerAction(Mobile_Player[playerid][pInterlocutorId]) != ACTION_CALL) {Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");return 1;}
				tmp = GetItemVarInt(GetItemVarInt(itemid,0),0);
				new Float:pos[3];
				GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
				new sqid = GetSquareIdForXY(pos[0],pos[1]),
				if(!IsSquareHaveNetwork(sqid,tmp)) {Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");return 1;}
				GetPlayerPos(Mobile_Player[playerid][pInterlocutorId],pos[0],pos[1],pos[2]);
				sqid = GetSquareIdForXY(pos[0],pos[1]),
				if(!IsSquareHaveNetwork(sqid,tmp)) {Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");return 1;}
				SetPlayerAction(playerid,ACTION_TALKING);
				SetPlayerAction(Mobile_Player[playerid][pInterlocutorId],ACTION_TALKING);
				Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_MOBILE_SIM_SELECT:
		{
			tmp = GetItemsDialogSelectedListitem(playerid);
			ItemOwnerRemove(tmp);
			SetItemVarInt(itemid,0,tmp);
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
			Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Mobile_OnPlayerUseItem(reason: complete)");
	return 0;
}