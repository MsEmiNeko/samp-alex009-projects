/*
*	Created:			09.01.10
*	Aurthor:			009
*	Last Modifed:		-
*/

#if defined _items_weapons_included
  #endinput
#endif

#define _items_weapons_included
#pragma library items_weapons

// --------------------------------------------------
// includes
// --------------------------------------------------
#include "mode_debug"
#include "items"

// --------------------------------------------------
// defines
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------

// --------------------------------------------------
// news
// --------------------------------------------------

// --------------------------------------------------
// forwards
// --------------------------------------------------

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native
*/

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------

	ITEM_TYPE_WEAPON_BAT,
	ITEM_TYPE_WEAPON_KNIFE,
	ITEM_TYPE_WEAPON_NIGHTSTICK,
	ITEM_TYPE_WEAPON_9MM,
	ITEM_TYPE_WEAPON_9MM_SIL,
	ITEM_TYPE_WEAPON_DEAGLE,
	ITEM_TYPE_WEAPON_SHOTGUN,
	ITEM_TYPE_WEAPON_SAWN,
	ITEM_TYPE_WEAPON_SPAS,
	ITEM_TYPE_WEAPON_UZI,
	ITEM_TYPE_WEAPON_TEK,
	ITEM_TYPE_WEAPON_MP5,
	ITEM_TYPE_WEAPON_AK47,
	ITEM_TYPE_WEAPON_M4,
	ITEM_TYPE_WEAPON_RIFLE,
	ITEM_TYPE_WEAPON_SNIPER,
	ITEM_TYPE_WEAPON_FLOWER,
	ITEM_TYPE_WEAPON_PHOTO,	

iWeapons_OnPlayerItemActionsCheck(playerid,itemid,dest[])
{
	Debug(DEBUG_START,"iWeapons_OnPlayerItemActionsCheck(%d,%d)",playerid,itemid);
	switch(itemid)
	{
		// Ручное оружие
		case
			ITEM_TYPE_WEAPON_BRASSKNUCKLE,
			ITEM_TYPE_WEAPON_GOLFCLUB,
			ITEM_TYPE_WEAPON_NITESTICK,
			ITEM_TYPE_WEAPON_BAT,
			ITEM_TIPE_WEAPON_SHOVEL,
			ITEM_TYPE_WEAPON_POOLSTICK:
			{
				format(DialogString,MAX_DIALOG_SIZE,"%sСломать\n",DialogString);
				Debug(DEBUG_END,"iWeapons_OnPlayerItemActionsCheck(reason: complete)");
				return 1;
			}
		// Холодное оружие
		case 
			ITEM_TYPE_WEAPON_KNIFE,
			ITEM_TYPE_WEAPON_KATANA:
			{
				format(DialogString,MAX_DIALOG_SIZE,"%s\n",DialogString);
				Debug(DEBUG_END,"iWeapons_OnPlayerItemActionsCheck(reason: complete)");
				return 1;
			}
			
			
			
			#define WEAPON_BRASSKNUCKLE				(1)
#define WEAPON_GOLFCLUB					(2)
#define WEAPON_NITESTICK				(3)
#define WEAPON_KNIFE					(4)
#define WEAPON_BAT						(5)
#define WEAPON_SHOVEL					(6)
#define WEAPON_POOLSTICK				(7)
#define WEAPON_KATANA					(8)
#define WEAPON_CHAINSAW					(9)
#define WEAPON_DILDO					(10)
#define WEAPON_DILDO2					(11)
#define WEAPON_VIBRATOR					(12)
#define WEAPON_VIBRATOR2				(13)
#define WEAPON_FLOWER					(14)
#define WEAPON_CANE						(15)
#define WEAPON_GRENADE					(16)
#define WEAPON_TEARGAS					(17)
#define WEAPON_MOLTOV					(18)
#define WEAPON_COLT45					(22)
#define WEAPON_SILENCED					(23)
#define WEAPON_DEAGLE					(24)
#define WEAPON_SHOTGUN					(25)
#define WEAPON_SAWEDOFF					(26)
#define WEAPON_SHOTGSPA					(27)
#define WEAPON_UZI						(28)
#define WEAPON_MP5						(29)
#define WEAPON_AK47						(30)
#define WEAPON_M4						(31)
#define WEAPON_TEC9						(32)
#define WEAPON_RIFLE					(33)
#define WEAPON_SNIPER					(34)
#define WEAPON_ROCKETLAUNCHER			(35)
#define WEAPON_HEATSEEKER				(36)
#define WEAPON_FLAMETHROWER				(37)
#define WEAPON_MINIGUN					(38)
#define WEAPON_SATCHEL					(39)
#define WEAPON_BOMB						(40)
#define WEAPON_SPRAYCAN					(41)
#define WEAPON_FIREEXTINGUISHER			(42)
#define WEAPON_CAMERA					(43)
#define WEAPON_PARACHUTE				(46)
#define WEAPON_VEHICLE					(49)
	}
	Debug(DEBUG_END,"iWeapons_OnPlayerItemActionsCheck(reason: complete)");
	return 0;
}



/*






stock Items_OnPlayerUpdate(playerid)
{
	if(Items_Player[playerid][pActiveWeaponType] != 0)
	{
		new slot,
			wid,
			wdata[2];
		if(Items_Player[playerid][pActiveWeaponCheck] != 0) 
		{
			
			switch(Items_Player[playerid][pActiveWeaponCheck])
			{
				case 0,1: 				slot=0;
				case 2,3,4,5,6,7,8,9:	slot=1;
				case 22,23,24:			slot=2;
				case 25,26,27:			slot=3;
				case 28,29,32:			slot=4;
				case 30,31:				slot=5;
				case 33,34:				slot=6;
				case 35,36,37,38:		slot=7;
				case 16,17,18,39:		slot=8;
				case 41,42,43:			slot=9;
				case 10,11,12,13,14,15: slot=10;
				case 44,45,46:			slot=11;
				case 40:				slot=12;
			}
			GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
			if(wdata[1] == 0) return 1;
			else Items_Player[playerid][pActiveWeaponCheck] = 0;
		}
		switch(Items_Player[playerid][pActiveWeaponType])
		{
			case ITEM_TYPE_WEAPON_BAT: wid = 5;
			case ITEM_TYPE_WEAPON_KNIFE: wid = 4;
			case ITEM_TYPE_WEAPON_NIGHTSTICK: wid = 3;
			case ITEM_TYPE_WEAPON_9MM: wid = 22;
			case ITEM_TYPE_WEAPON_9MM_SIL: wid = 23;
			case ITEM_TYPE_WEAPON_DEAGLE: wid = 24;
			case ITEM_TYPE_WEAPON_SHOTGUN: wid = 25;
			case ITEM_TYPE_WEAPON_SAWN: wid = 26;
			case ITEM_TYPE_WEAPON_SPAS: wid = 27;
			case ITEM_TYPE_WEAPON_UZI: wid = 28;
			case ITEM_TYPE_WEAPON_TEK: wid = 32;
			case ITEM_TYPE_WEAPON_MP5: wid = 29;
			case ITEM_TYPE_WEAPON_AK47: wid = 30;
			case ITEM_TYPE_WEAPON_M4: wid = 31;
			case ITEM_TYPE_WEAPON_RIFLE: wid = 33;
			case ITEM_TYPE_WEAPON_SNIPER: wid = 34;
			case ITEM_TYPE_WEAPON_PHOTO: wid = 43;
			case ITEM_TYPE_WEAPON_FLOWER: wid = 14;
		}
		if(GetPlayerWeapon(playerid) != wid)
		{
			Debug("[items.inc] Items_OnPlayerUpdate -> player try change weapon");
			switch(Items_Player[playerid][pActiveWeaponType])
			{
				case ITEM_TYPE_WEAPON_BAT,ITEM_TYPE_WEAPON_KNIFE,ITEM_TYPE_WEAPON_NIGHTSTICK: slot = 1;
				case ITEM_TYPE_WEAPON_9MM,ITEM_TYPE_WEAPON_9MM_SIL,ITEM_TYPE_WEAPON_DEAGLE: slot = 2;
				case ITEM_TYPE_WEAPON_SHOTGUN,ITEM_TYPE_WEAPON_SAWN,ITEM_TYPE_WEAPON_SPAS: slot = 3;
				case ITEM_TYPE_WEAPON_UZI,ITEM_TYPE_WEAPON_TEK,ITEM_TYPE_WEAPON_MP5: slot = 4;
				case ITEM_TYPE_WEAPON_AK47,ITEM_TYPE_WEAPON_M4: slot = 5;
				case ITEM_TYPE_WEAPON_RIFLE,ITEM_TYPE_WEAPON_SNIPER: slot = 6;
				case ITEM_TYPE_WEAPON_PHOTO: slot = 9;
				case ITEM_TYPE_WEAPON_FLOWER: slot = 10;
			}
			GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
			if(wdata[1] == 0) 
			{
				Debug("[items.inc] Items_OnPlayerUpdate -> ammo lost");
				MySQL_DeleteItem(Items_Player[playerid][pActiveWeaponItem]);
				DeletePlayerItem(playerid,Items_Player[playerid][pActiveWeaponItem]);
				Items_Player[playerid][pActiveWeaponType] = 0;
				Items_Player[playerid][pActiveWeaponItem] = 0;				
			}
			else 
			{
				Debug("[items.inc] Items_OnPlayerUpdate -> set our weapon");
				SetPlayerArmedWeapon(playerid,wid);
			}
		}
	}
	return 1;
}

stock Items_OnPlayerKeyStateChange(playerid,newkeys)
{
	if(Items_Player[playerid][pPressingFireCount] != 0)
	{
		if(newkeys != KEY_FIRE) return 0;
		Items_Player[playerid][pPressingFireCount]++;
		if(Items_Player[playerid][pPressingFireCount] == 5) 
		{
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
			Items_Player[playerid][pPressingFireCount] = 0;
		}
	}
	return 1;
}

stock Items_OnDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_ITEM_END:
		{
			for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
			SetPlayerAction(playerid,ACTION_NONE);
			return 1;
		}
		case DIALOG_ITEM_LAST:
		{
			if(!response)
			{
				new type = MySQL_GetItemType(Items_Player[playerid][pDialogSelectedItem]);
				ShowPlayerDialog(playerid,ItemsDialogs[type],DIALOG_STYLE_LIST,ItemsNames[type],ItemsActions[type],"Выбрать","Отмена");
				return 1;
			}
			for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
			SetPlayerAction(playerid,ACTION_NONE);
			return 1;
		}
		case DIALOG_ITEM_LIST:
		{
			if(!response)
			{
				for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
				SetPlayerAction(playerid,ACTION_NONE);
				return 1;
			}
			Items_Player[playerid][pDialogSelectedItem] = Items_Player[playerid][pDialogItemId][listitem];
			new type = MySQL_GetItemType(Items_Player[playerid][pDialogSelectedItem]);
			ShowPlayerDialog(playerid,DIALOG_ITEM_ACTIONS,DIALOG_STYLE_LIST,ItemsNames[type],ItemsActions[type],"Выбрать","Отмена");
			return 1;
		}
		case DIALOG_ITEM_KEY_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Измерить
				{
					new size[MAX_STRING];
					format(size,sizeof(size),MySQL_GetItemVar(Items_Player[playerid][pDialogSelectedItem],1));
					ModeMessage(playerid,MODE_MESSAGE_IC,"Размер ключа: %cx%c%cx%c%c",size[0],size[1],size[2],size[3],size[4]);
					ShowPlayerDialog(playerid,ItemsDialogs[ITEM_TYPE_KEY],DIALOG_STYLE_LIST,ItemsNames[ITEM_TYPE_KEY],ItemsActions[ITEM_TYPE_KEY],"Выбрать","Отмена");
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_KEY]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 2: // Сломать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"сломал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я сломал %s",ItemsNames[ITEM_TYPE_KEY]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_DOC_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Прочесть
				{
					ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,MySQL_GetItemVar(Items_Player[playerid][pDialogSelectedItem],0),MySQL_GetItemVar(Items_Player[playerid][pDialogSelectedItem],1),"Готово","Назад");
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_DOCUMENT]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 2: // Порвать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"порвал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я порвал %s",ItemsNames[ITEM_TYPE_DOCUMENT]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_MOB_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
					SetPlayerAction(playerid,ACTION_NONE);
					PlayerUseMobile(playerid,Items_Player[playerid][pDialogSelectedItem]);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_MOBILE]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 2: // Сломать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"сломал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я сломал %s",ItemsNames[ITEM_TYPE_MOBILE]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_NOTE_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Прочесть
				{
					if(!strlen(MySQL_GetNotesInItem(Items_Player[playerid][pDialogSelectedItem]))) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Записная книга","Записная книжка пуста","Готово","Назад");
					return ShowPlayerDialog(playerid,DIALOG_ITEM_NOTE_USE_1,DIALOG_STYLE_LIST,"Записная книга",MySQL_GetNotesInItem(Items_Player[playerid][pDialogSelectedItem]),"Прочесть","Назад");
				}
				case 1: // Добавить запись
				{
					Items_Player[playerid][pNotebookText][0] = '\0';
					ShowPlayerDialog(playerid,DIALOG_ITEM_NOTE_USE_2,DIALOG_STYLE_INPUT,"Записная книга","Наберите текст:","Следующая строка","Готово");
					return 1;
				}
				case 2: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_NOTEBOOK]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 3: // Порвать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"порвал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я порвал %s",ItemsNames[ITEM_TYPE_NOTEBOOK]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
		}
		case DIALOG_ITEM_ALCO_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Выпить
				{
					if(Items_Player[playerid][pActiveWeaponType] != 0)
					{
						new slot;
						switch(Items_Player[playerid][pActiveWeaponType])
						{
							case ITEM_TYPE_WEAPON_BAT,ITEM_TYPE_WEAPON_KNIFE,ITEM_TYPE_WEAPON_NIGHTSTICK: slot = 1;
							case ITEM_TYPE_WEAPON_9MM,ITEM_TYPE_WEAPON_9MM_SIL,ITEM_TYPE_WEAPON_DEAGLE: slot = 2;
							case ITEM_TYPE_WEAPON_SHOTGUN,ITEM_TYPE_WEAPON_SAWN,ITEM_TYPE_WEAPON_SPAS: slot = 3;
							case ITEM_TYPE_WEAPON_UZI,ITEM_TYPE_WEAPON_TEK,ITEM_TYPE_WEAPON_MP5: slot = 4;
							case ITEM_TYPE_WEAPON_AK47,ITEM_TYPE_WEAPON_M4: slot = 5;
							case ITEM_TYPE_WEAPON_RIFLE,ITEM_TYPE_WEAPON_SNIPER: slot = 6;
							case ITEM_TYPE_WEAPON_PHOTO: slot = 9;
							case ITEM_TYPE_WEAPON_FLOWER: slot = 10;
						}
						new wdata[2];
						GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
						SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",wdata[1]);
						ResetPlayerWeapons(playerid);
						Items_Player[playerid][pActiveWeaponType] = 0;
						Items_Player[playerid][pActiveWeaponItem] = 0;
					}
					switch(strval(GetItemVar(Items_Player[playerid][pDialogSelectedItem],0)))
					{
						case 0: // Пиво
						{
							SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_BEER);
						}
						case 1: // Вино
						{
							SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);
						}
						case 2: // Газировка
						{
							SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						}
					}
					Items_Player[playerid][pPressingFireCount] = 1;
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
					SetPlayerAction(playerid,ACTION_NONE);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_ALCO]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 2: // Разбить
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"разбил что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я разбил %s",ItemsNames[ITEM_TYPE_ALCO]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_SIGA_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Выкурить
				{
					if(Items_Player[playerid][pActiveWeaponType] != 0)
					{
						new slot;
						switch(Items_Player[playerid][pActiveWeaponType])
						{
							case ITEM_TYPE_WEAPON_BAT,ITEM_TYPE_WEAPON_KNIFE,ITEM_TYPE_WEAPON_NIGHTSTICK: slot = 1;
							case ITEM_TYPE_WEAPON_9MM,ITEM_TYPE_WEAPON_9MM_SIL,ITEM_TYPE_WEAPON_DEAGLE: slot = 2;
							case ITEM_TYPE_WEAPON_SHOTGUN,ITEM_TYPE_WEAPON_SAWN,ITEM_TYPE_WEAPON_SPAS: slot = 3;
							case ITEM_TYPE_WEAPON_UZI,ITEM_TYPE_WEAPON_TEK,ITEM_TYPE_WEAPON_MP5: slot = 4;
							case ITEM_TYPE_WEAPON_AK47,ITEM_TYPE_WEAPON_M4: slot = 5;
							case ITEM_TYPE_WEAPON_RIFLE,ITEM_TYPE_WEAPON_SNIPER: slot = 6;
							case ITEM_TYPE_WEAPON_PHOTO: slot = 9;
							case ITEM_TYPE_WEAPON_FLOWER: slot = 10;
						}
						new wdata[2];
						GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
						SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",wdata[1]);
						ResetPlayerWeapons(playerid);
						Items_Player[playerid][pActiveWeaponType] = 0;
						Items_Player[playerid][pActiveWeaponItem] = 0;
					}
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_SMOKE_CIGGY);
					Items_Player[playerid][pPressingFireCount] = 1;
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
					SetPlayerAction(playerid,ACTION_NONE);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_SIGA]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 2: // Сломать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"сломал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я сломал %s",ItemsNames[ITEM_TYPE_SIGA]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_MEDICALKIT_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					return ShowPlayerDialog(playerid,DIALOG_ITEM_MEDICALKIT_USE_1,DIALOG_STYLE_LIST,"Использовать...","На себе\nНа ближайшем персонаже","Выбрать","Отмена");
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_MEDICALKIT]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_HANDSCUFF_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					new Float:dist = 10.0,
						id = -1;
					for(new i = 0;i < GetMaxPlayer();i++)
					{
						if(!IsPlayerConnected(i)) continue;
						if(i == playerid) continue;
						if(!IsPlayerInRangeOfPlayer(playerid,5.0,i)) continue;
						new Float:d = GetDistancePlayertoPlayer(playerid,i);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}
					if(id == -1) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Возле вас никого нет","Готово","Назад");
					if(Items_Player[id][pIsHandcuffs] == true) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Вы не можете одевать наручники \n2 раза на одного и тогоже человека","Готово","Назад");
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					Items_Player[id][pIsHandcuffs] = true;
					MySQL_ChangePlayerVar(id,"Handcuffs","%d|%d",Items_Player[playerid][pDialogSelectedItem],strval(GetItemVar(Items_Player[playerid][pDialogSelectedItem],0)));
					SetPlayerAction(id,ACTION_ITEM_HANDCUFFS);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_HANDCUFFS]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_BANDAGE_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					new Float:dist = 10.0,
						id = -1;
					for(new i = 0;i < GetMaxPlayer();i++)
					{
						if(!IsPlayerConnected(i)) continue;
						if(i == playerid) continue;
						if(!IsPlayerInRangeOfPlayer(playerid,5.0,i)) continue;
						new Float:d = GetDistancePlayertoPlayer(playerid,i);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}
					if(id == -1) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Возле вас никого нет","Готово","Назад");
					if(Items_Player[id][pIsBandage] == true) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Вы не можете одевать повязку \n2 раза на одного и тогоже человека","Готово","Назад");
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					Items_Player[id][pIsBandage] = true;
					MySQL_ChangePlayerVar(id,"Bandage","%d",Items_Player[playerid][pDialogSelectedItem]);
					SetPlayerAction(id,ACTION_ITEM_BANDAGE);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_BANDAGE]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_MKEY_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					new Float:dist = 10.0,
						Float:pos[3],
						id,
						size,
						type,
						tmp[MAX_STRING],
						idx;
					// Вскрытие помещения
					id = 0;
					if(IsPlayerOnPickupType(playerid,PICKUP_PREMISE))
					{
						id = GetPlayerPickupParam(playerid);
						if(IsDoorClosed(id))
						{
							size = GetDoorKey(id);
							type = 1;
							goto act;
						}
					}
					else if(IsPlayerOnPickupType(playerid,PICKUP_MODE_INTERIOR))
					{
						id = GetPlayerCurrentPremise(playerid) - 1; // "Поправка 0"
						if(IsDoorClosed(id))
						{
							size = GetDoorKey(id);
							type = 1;
							goto act;
						}
					}
					// Вскрытие тачи
					id = -1;
					for(new i = 0;i < MAX_VEHICLES;i++)
					{
						if(!IsValidModeVehicle(i)) continue;
						GetVehiclePos(i,pos[0],pos[1],pos[2]);
						if(!IsPlayerInRangeOfPoint(playerid,5.0,pos[0],pos[1],pos[2])) continue;
						new Float:d = GetDistancePlayertoXYZ(playerid,pos[0],pos[1],pos[2]);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}
					if(id != -1)
					{
						if(IsModeVehicleClosed(id))
						{
							size = GetModeVehicleKey(id);
							type = 2;
							goto act;
						}
					}
					// Вскрытие наручников
					id = -1;
					for(new i = 0;i < GetMaxPlayer();i++)
					{
						if(!IsPlayerConnected(i)) continue;
						if(i == playerid) continue;
						if(!IsPlayerInRangeOfPlayer(playerid,5.0,i)) continue;
						new Float:d = GetDistancePlayertoPlayer(playerid,i);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}
					if(id != -1)
					{
						if(Items_Player[id][pIsHandcuffs] == true)
						{
							MySQL_GetPlayerVar(playerid,"Handcuffs",tmp);
							idx = strfind(tmp,"|");
							size = strval(tmp[idx+1]);
							type = 3;
							goto act;
						}
					}
					goto er;
					act:
					switch(strval(GetItemVar(Items_Player[playerid][pDialogSelectedItem],0)))
					{
						case 0: // малая
						{
							if(size >= 30000) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Отмычка не подходит к такому замку","Готово","Назад");
						}
						case 1: // средняя
						{
							if((size < 30000) || (size > 60000)) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Отмычка не подходит к такому замку","Готово","Назад");
						}
						case 2: // большая
						{
							if(size <= 60000) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Отмычка не подходит к такому замку","Готово","Назад");
						}
					}
					MySQL_GetPlayerVar(playerid,"RobSkill",tmp);
					new skill = strval(tmp);
					new luck = 10 + (5*skill);
					if(random(100) <= luck) // взлом удачен
					{
						switch(type)
						{
							case 1: // помещение
							{
								SetDoorStatus(id,0);
								PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"открыл дверь отмычкой");
								MySQL_ChangePlayerVar(playerid,"RobSkill","%d",(skill+1));
								for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
								SetPlayerAction(playerid,ACTION_NONE);
								return 1;
							}
							case 2: // машина
							{
								SetModeVehicleStatus(id,0);
								PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"открыл дверь отмычкой");
								MySQL_ChangePlayerVar(playerid,"RobSkill","%d",(skill+1));
								for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
								SetPlayerAction(playerid,ACTION_NONE);
								return 1;
							}
							case 3: // наручники
							{
								MySQL_GetPlayerVar(playerid,"Handcuffs",tmp);
								SetItemOwner(strval(strtok(tmp,"|",idx)),oGetPlayerName(playerid));
								MySQL_ChangePlayerVar(id,"Handcuffs","");
								PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"снял наручники отмычкой");
								MySQL_ChangePlayerVar(playerid,"RobSkill","%d",(skill+1));
								for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
								SetPlayerAction(playerid,ACTION_NONE);
								return 1;
							}
						}
					}
					else // неудача
					{
						if(random(100) >= luck) // отмычка сломана
						{
							DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
							MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
							PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"использовал отмычку ,но сломал её");
							for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
							SetPlayerAction(playerid,ACTION_NONE);
							return 1;
						}
						else
						{
							PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"использовал отмычку ,но ничего не получилось");
							for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
							SetPlayerAction(playerid,ACTION_NONE);
							return 1;
						}
					}
					er:
					ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Возле вас нет ничего для взлома","Готово","Назад");
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_MKEY]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_SIMCARD_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_SIMCARD]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 1: // Сломать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"сломал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я сломал %s",ItemsNames[ITEM_TYPE_SIMCARD]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_CANISTER_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					if(strval(GetItemVar(Items_Player[playerid][pDialogSelectedItem],0)) == 0) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Канистра пуста","Готово","Назад");
					new Float:dist = 10.0,
						Float:pos[3],
						id;
					for(new i = 0;i < MAX_VEHICLES;i++)
					{
						if(!IsValidModeVehicle(i)) continue;
						GetVehiclePos(i,pos[0],pos[1],pos[2]);
						if(!IsPlayerInRangeOfPoint(playerid,5.0,pos[0],pos[1],pos[2])) continue;
						new Float:d = GetDistancePlayertoXYZ(playerid,pos[0],pos[1],pos[2]);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}					
					if(id != -1)
					{
						if(!IsVehicleNeedFuel(GetVehicleModel(id))) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Этот транспорт не использует топливо","Готово","Назад");
						if(GetModeVehicleFuel(id) == GetModeVehicleMaxFuel(GetVehicleModel(id))) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Бак полон","Готово","Назад");
						if((GetModeVehicleFuel(id) + strval(GetItemVar(Items_Player[playerid][pActiveWeaponItem],0))) > GetModeVehicleMaxFuel(GetVehicleModel(id)))
						{
							new cfuel = strval(GetItemVar(Items_Player[playerid][pActiveWeaponItem],0));
							new lost = GetModeVehicleMaxFuel(GetVehicleModel(id)) - GetModeVehicleFuel(id);							
							SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",(cfuel - lost));
							SetModeVehicleFuel(id,GetModeVehicleMaxFuel(GetVehicleModel(id)));
							return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Транспорт заправлен","Готово","Назад");
						}
						else
						{
							new cfuel = strval(GetItemVar(Items_Player[playerid][pActiveWeaponItem],0));						
							SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"0");
							SetModeVehicleFuel(id,(GetModeVehicleFuel(id) + cfuel));
							return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Транспорт заправлен","Готово","Назад");
						}					
					}
					else return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Для использования канистры нужно быть около транспорта","Готово","Назад");
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_DOCUMENT]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_PRS_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					if(Items_Player[playerid][pIsPRS] == true)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						Items_Player[playerid][pIsPRS] = false;
						for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
						SetPlayerAction(playerid,ACTION_NONE);
						PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"убрал рацию");
					}
					else
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
						Items_Player[playerid][pIsPRS] = true;
						for(new i = 0;i < MAX_PLAYER_ITEMS;i++) Items_Player[playerid][pDialogItemId][i] = 0;
						SetPlayerAction(playerid,ACTION_NONE);
						PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"достал рацию");
					}
				}
				case 1: // Сменить канал
				{
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
					ShowPlayerDialog(playerid,DIALOG_ITEM_PRS_USE,DIALOG_STYLE_INPUT,"Рация","Введите канал:","Готово","Назад");
					return 1;
				}
				case 2: // Выкинуть
				{
					new Premise,
						Float:Pos[3];
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[ITEM_TYPE_PRS]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 3: // Сломать
				{
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"сломал что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я сломал %s",ItemsNames[ITEM_TYPE_PRS]);
					PlayerAction(playerid,ACTION_ITEM_DESTROY);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		case DIALOG_ITEM_WEAPON_ACTIONS:
		{
			if(!response)
			{
				if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
				ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				return 1;
			}
			switch(listitem)
			{
				case 0: // Использовать
				{
					new type = MySQL_GetItemType(Items_Player[playerid][pDialogSelectedItem]);
					if(Items_Player[playerid][pActiveWeaponType] == type)
					{
						new slot,
							wdata[2];
						switch(type)
						{
							case ITEM_TYPE_WEAPON_BAT,ITEM_TYPE_WEAPON_KNIFE,ITEM_TYPE_WEAPON_NIGHTSTICK: slot = 1;
							case ITEM_TYPE_WEAPON_9MM,ITEM_TYPE_WEAPON_9MM_SIL,ITEM_TYPE_WEAPON_DEAGLE: slot = 2;
							case ITEM_TYPE_WEAPON_SHOTGUN,ITEM_TYPE_WEAPON_SAWN,ITEM_TYPE_WEAPON_SPAS: slot = 3;
							case ITEM_TYPE_WEAPON_UZI,ITEM_TYPE_WEAPON_TEK,ITEM_TYPE_WEAPON_MP5: slot = 4;
							case ITEM_TYPE_WEAPON_AK47,ITEM_TYPE_WEAPON_M4: slot = 5;
							case ITEM_TYPE_WEAPON_RIFLE,ITEM_TYPE_WEAPON_SNIPER: slot = 6;
							case ITEM_TYPE_WEAPON_PHOTO: slot = 9;
							case ITEM_TYPE_WEAPON_FLOWER: slot = 10;
						}
						GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
						SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",wdata[1]);
						ResetPlayerWeapons(playerid);
						Items_Player[playerid][pActiveWeaponType] = 0;
						Items_Player[playerid][pActiveWeaponItem] = 0;
					}
					else
					{
						if(Items_Player[playerid][pActiveWeaponItem] != 0)
						{
							new slot,
								wdata[2];
							switch(type)
							{
								case ITEM_TYPE_WEAPON_BAT,ITEM_TYPE_WEAPON_KNIFE,ITEM_TYPE_WEAPON_NIGHTSTICK: slot = 1;
								case ITEM_TYPE_WEAPON_9MM,ITEM_TYPE_WEAPON_9MM_SIL,ITEM_TYPE_WEAPON_DEAGLE: slot = 2;
								case ITEM_TYPE_WEAPON_SHOTGUN,ITEM_TYPE_WEAPON_SAWN,ITEM_TYPE_WEAPON_SPAS: slot = 3;
								case ITEM_TYPE_WEAPON_UZI,ITEM_TYPE_WEAPON_TEK,ITEM_TYPE_WEAPON_MP5: slot = 4;
								case ITEM_TYPE_WEAPON_AK47,ITEM_TYPE_WEAPON_M4: slot = 5;
								case ITEM_TYPE_WEAPON_RIFLE,ITEM_TYPE_WEAPON_SNIPER: slot = 6;
								case ITEM_TYPE_WEAPON_PHOTO: slot = 9;
								case ITEM_TYPE_WEAPON_FLOWER: slot = 10;
							}
							GetPlayerWeaponData(playerid,slot,wdata[0],wdata[1]);
							SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",wdata[1]);
						}
						ResetPlayerWeapons(playerid);
						new wid;
						switch(type)
						{
							case ITEM_TYPE_WEAPON_BAT: wid = 5;
							case ITEM_TYPE_WEAPON_KNIFE: wid = 4;
							case ITEM_TYPE_WEAPON_NIGHTSTICK: wid = 3;
							case ITEM_TYPE_WEAPON_9MM: wid = 22;
							case ITEM_TYPE_WEAPON_9MM_SIL: wid = 23;
							case ITEM_TYPE_WEAPON_DEAGLE: wid = 24;
							case ITEM_TYPE_WEAPON_SHOTGUN: wid = 25;
							case ITEM_TYPE_WEAPON_SAWN: wid = 26;
							case ITEM_TYPE_WEAPON_SPAS: wid = 27;
							case ITEM_TYPE_WEAPON_UZI: wid = 28;
							case ITEM_TYPE_WEAPON_TEK: wid = 32;
							case ITEM_TYPE_WEAPON_MP5: wid = 29;
							case ITEM_TYPE_WEAPON_AK47: wid = 30;
							case ITEM_TYPE_WEAPON_M4: wid = 31;
							case ITEM_TYPE_WEAPON_RIFLE: wid = 33;
							case ITEM_TYPE_WEAPON_SNIPER: wid = 34;
							case ITEM_TYPE_WEAPON_PHOTO: wid = 43;
							case ITEM_TYPE_WEAPON_FLOWER: wid = 14;
						}
						GivePlayerWeapon(playerid,wid,strval(GetItemVar(Items_Player[playerid][pDialogSelectedItem],0)));
						Items_Player[playerid][pActiveWeaponType] = type;
						Items_Player[playerid][pActiveWeaponItem] = Items_Player[playerid][pDialogSelectedItem];
						Items_Player[playerid][pActiveWeaponCheck] = wid;
					}
					SetPlayerAction(playerid,ACTION_NONE);
					return 1;
				}
				case 1: // Выкинуть
				{
					new Premise,
						Float:Pos[3],
						mtype = MySQL_GetItemType(Items_Player[playerid][pDialogSelectedItem]);
					GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
					GetXYInFrontOfPlayer(playerid,Pos[0],Pos[1],2.0);
					Premise = GetPlayerCurrentPremise(playerid);
					SetItemPosition(Items_Player[playerid][pDialogSelectedItem],Pos[0],Pos[1],Pos[2],Premise);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"выкинул что-то");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я выкинул %s",ItemsNames[mtype]);
					PlayerAction(playerid,ACTION_ITEM_PUT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
			return 0;
		}
		// ITEM_TYPE_NOTEBOOK
		case DIALOG_ITEM_NOTE_USE_1:
		{
			if(!response) return ShowPlayerDialog(playerid,ItemsDialogs[ITEM_TYPE_NOTEBOOK],DIALOG_STYLE_LIST,ItemsNames[ITEM_TYPE_NOTEBOOK],ItemsActions[ITEM_TYPE_NOTEBOOK],"Выбрать","Отмена");
			return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Записная книга",MySQL_GetNoteFull(Items_Player[playerid][pDialogSelectedItem],strval(CutPartText(inputtext,'[',']'))),"Готово","Назад");
		}
		case DIALOG_ITEM_NOTE_USE_2:
		{
			format(Items_Player[playerid][pNotebookText],MAX_STRING,"%s%s\n",Items_Player[playerid][pNotebookText],inputtext);
			if(!response)
			{
				MySQL_AddNoteToItem(Items_Player[playerid][pDialogSelectedItem],Items_Player[playerid][pNotebookText]);
				return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Записная книга","Запись добавлена","Ok","Ok");
			}
			DialogString[0] = '\0';
			format(DialogString,sizeof(DialogString),"Наберите текст:\n%s",Items_Player[playerid][pNotebookText]);
			ShowPlayerDialog(playerid,DIALOG_ITEM_NOTE_USE_2,DIALOG_STYLE_INPUT,"Записная книга",DialogString,"Следующая строка","Готово");
		}
		// ITEM_TYPE_MEDICALKIT
		case DIALOG_ITEM_MEDICALKIT_USE_1:
		{
			if(!response) return ShowPlayerDialog(playerid,ItemsDialogs[ITEM_TYPE_MEDICALKIT],DIALOG_STYLE_LIST,ItemsNames[ITEM_TYPE_MEDICALKIT],ItemsActions[ITEM_TYPE_MEDICALKIT],"Выбрать","Отмена");
			switch(listitem)
			{
				case 0: // На себе
				{
					SetPlayerHealth(playerid,100.0);
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"использовал аптечку");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я использовал аптечку");
					PlayerAction(playerid,ACTION_ITEM_MEDICALKIT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
				case 1: // На ближайшем персонаже
				{
					new Float:dist = 10.0,
						id = -1;
					for(new i = 0;i < GetMaxPlayer();i++)
					{
						if(!IsPlayerConnected(i)) continue;
						if(i == playerid) continue;
						if(!IsPlayerInRangeOfPlayer(playerid,5.0,i)) continue;
						new Float:d = GetDistancePlayertoPlayer(playerid,i);
						if(d < dist)
						{
							dist = d;
							id = i;
						}
					}
					if(id == -1) return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Информация","Возле вас никого нет","Готово","Назад");
					SetPlayerHealth(id,100.0);
					MySQL_DeleteItem(Items_Player[playerid][pDialogSelectedItem]);
					DeletePlayerItem(playerid,Items_Player[playerid][pDialogSelectedItem]);
					PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"использовал аптечку");
					ModeMessage(playerid,MODE_MESSAGE_IC,"Я использовал аптечку");
					PlayerAction(playerid,ACTION_ITEM_MEDICALKIT);
					if(!IsPlayerHaveItems(oGetPlayerName(playerid))) return ShowPlayerDialog(playerid,DIALOG_ITEM_END,DIALOG_STYLE_MSGBOX,"Багаж","У вас нет никакого багажа","Ok","Ok");
					return ShowPlayerDialog(playerid,DIALOG_ITEMS_LIST,DIALOG_STYLE_LIST,"Багаж",PlayerItemsDialogStr(playerid,Items_Player[playerid][pDialogItemId]),"Выбрать","Отмена");
				}
			}
		}
		// ITEM_TYPE_PRS
		case DIALOG_ITEM_PRS_USE:
		{
			if(!response) return ShowPlayerDialog(playerid,ItemsDialogs[ITEM_TYPE_MOBILE],DIALOG_STYLE_LIST,ItemsNames[ITEM_TYPE_MOBILE],ItemsActions[ITEM_TYPE_MOBILE],"Выбрать","Отмена");
			SetItemVar(Items_Player[playerid][pActiveWeaponItem],0,"%d",strval(inputtext));
			return ShowPlayerDialog(playerid,DIALOG_ITEM_LAST,DIALOG_STYLE_MSGBOX,"Рация","Канал успешно сменён","Готово","Назад");
		}
	}
	return 0;
}

stock DeletePlayerItem(playerid,itemid)
{
	new items[MAX_PLAYER_ITEMS];
	MySQL_GetPlayerItems(oGetPlayerName(playerid),items);
	for(new i = 0;i < sizeof(items);i++)
	{
		if(items[i] == itemid) items[i] = 0;
	}
	MySQL_WritePlayerItems(oGetPlayerName(playerid),items);
}

stock PlayerItemsDialogStr(playerid,idsm[])
{
	new items[MAX_PLAYER_ITEMS],
		count,
		type;
	nullstr(DialogString);
	MySQL_GetPlayerItems(oGetPlayerName(playerid),items);
	for(new i = 0;i < sizeof(items);i++)
	{
		if(items[i] == 0) continue;
		idsm[count] = items[i];
		count++;
		type = MySQL_GetItemType(items[i]);
		switch(type)
		{
			case ITEM_TYPE_KEY,ITEM_TYPE_DOCUMENT: format(DialogString,sizeof(DialogString),"%s%s %s\n",DialogString,ItemsNames[type],MySQL_GetItemVar(items[i],0));
			case ITEM_TYPE_ALCO: 
			{
				switch(strval(GetItemVar(items[i],0)))
				{
					case 0: format(DialogString,sizeof(DialogString),"%s%s пива\n",DialogString,ItemsNames[type]);
					case 1: format(DialogString,sizeof(DialogString),"%s%s вина\n",DialogString,ItemsNames[type]);
					case 2: format(DialogString,sizeof(DialogString),"%s%s газировки\n",DialogString,ItemsNames[type]);
				}
			}
			case ITEM_TYPE_MKEY: 
			{
				switch(strval(GetItemVar(items[i],0)))
				{
					case 0: format(DialogString,sizeof(DialogString),"%s%s маленькая\n",DialogString,ItemsNames[type]);
					case 1: format(DialogString,sizeof(DialogString),"%s%s средняя\n",DialogString,ItemsNames[type]);
					case 2: format(DialogString,sizeof(DialogString),"%s%s большая\n",DialogString,ItemsNames[type]);
				}
			}
			case ITEM_TYPE_SIMCARD: 
			{
				format(DialogString,sizeof(DialogString),"%s%s %s\n",DialogString,ItemsNames[type],GetNetworkName(strval(GetItemVar(items[i],GSM_SIM_NETWORK_ID))));
			}
			default: format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,ItemsNames[type]);
		}
	}
	return DialogString;	
}

stock CreateItemForWorld(type,Float:X,Float:Y,Float:Z,premise,parstr[],{Float,_}:...)
{
	new itemid,
		tmp[MAX_STRING],
		Params[3][MAX_STRING],
		par_current,
		p_position,
		arg_current = 6,
		plen = strlen(parstr);
	do
	{
		switch(parstr[p_position])
		{
			case 'd':
			{
				format(Params[par_current],MAX_STRING,"%d",getarg(arg_current));
				arg_current++;
				par_current++;
			}
			case 's':
			{
				new k = 0;
				new chars;
				new arg_line[MAX_STRING];
				chars = getarg(arg_current,k);
				while(chars != 0)
				{
					chars = getarg(arg_current,k);
					if(chars != 0)
					{
						format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
						k++;
					}
				}
				format(Params[par_current],MAX_STRING,"%s",arg_line);
				arg_current++;
				par_current++;
			}
			case 'f':
			{
				format(Params[par_current],MAX_STRING,"%f",getarg(arg_current));
				arg_current++;
				par_current++;
			}
		}
	}
	while(++p_position < plen);
	itemid = MySQL_GetMaxItemId() + 1;
	format(tmp,sizeof(tmp),"%d/%f/%f/%f",premise,X,Y,Z);
	MySQL_AddItem(itemid,type,tmp,Params[0],Params[1],Params[2]);
	CreateModePickup(ItemsObjects[type],X,Y,Z,premise,PICKUP_ITEM,itemid);
	return itemid;
}

stock CreateItem(type,parstr[],{Float,_}:...)
{
	new itemid,
		Params[3][MAX_STRING],
		par_current,
		p_position,
		arg_current = 2,
		plen = strlen(parstr);
	do
	{
		switch(parstr[p_position])
		{
			case 'd':
			{
				format(Params[par_current],MAX_STRING,"%d",getarg(arg_current));
				arg_current++;
				par_current++;
			}
			case 's':
			{
				new k = 0;
				new chars;
				new arg_line[MAX_STRING];
				chars = getarg(arg_current,k);
				while(chars != 0)
				{
					chars = getarg(arg_current,k);
					if(chars != 0)
					{
						format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
						k++;
					}
				}
				format(Params[par_current],MAX_STRING,"%s",arg_line);
				arg_current++;
				par_current++;
			}
			case 'f':
			{
				format(Params[par_current],MAX_STRING,"%f",getarg(arg_current));
				arg_current++;
				par_current++;
			}
		}
	}
	while(++p_position < plen);
	itemid = MySQL_GetMaxItemId() + 1;
	MySQL_AddItem(itemid,type,"",Params[0],Params[1],Params[2]);
	return itemid;
}

stock SetItemVar(itemid,varid,varf[],{Float,_}:...)
{
	new str[MAX_STRING];
	new str_position;
	new mes_len = strlen(varf);
	new mes_position;
	new arg_current = 3;
	do
	{
		if(varf[mes_position] == '%')
		{
			switch(varf[mes_position+1])
			{
				case 'd':
				{
					format(str,sizeof(str),"%s%d",str,getarg(arg_current));
					mes_position++;
					arg_current++;
					str_position = strlen(str);
				}
				case 's':
				{
					new k = 0;
					new chars;
					new arg_line[MAX_STRING];
					chars = getarg(arg_current,k);
					while(chars != 0)
					{
						chars = getarg(arg_current,k);
						if(chars != 0)
						{
							format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
							k++;
						}
					}
					format(str,sizeof(str),"%s%s",str,arg_line);
					mes_position++;
					arg_current++;
					str_position = strlen(str);
				}
				case 'f':
				{
					format(str,sizeof(str),"%s%f",str,getarg(arg_current));
					mes_position++;
					arg_current++;
					str_position = strlen(str);
				}
			}
		}
		else
		{
			str[str_position] = varf[mes_position];
			str_position++;
		}
	}
	while(++mes_position < mes_len);
	return MySQL_SetItemVar(itemid,varid,str);
}

stock GetItemVar(itemid,varid)
{
	new res[MAX_STRING];
	format(res,sizeof(res),MySQL_GetItemVar(itemid,varid));
	return res;
}

*/