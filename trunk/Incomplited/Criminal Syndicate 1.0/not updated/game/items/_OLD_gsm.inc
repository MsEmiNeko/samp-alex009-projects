/*
*	Created:			21.11.09
*	Aurthor:			009
*	Last Modifed:		-
*/

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+	ACTION_SELECT_GSM_TERMINAL
+	ACTION_SELECT_GSM_ANTENA
+
+	Терминал:
+	0 - ид сети
+	1 - используется ли сейчас
+	2 - ид обьекта в таблице
+
+	Антены:
+	0 - ид сети
+	1 - есть ли соединение с терминалом
+	2 - используется ли сейчас
+	3 - ид обьекта в таблице
+
+	Симка:
+	0 - номер
+	1 - счёт
+	2 - ид сети
+
+	Мобила:
+	0 - ид симки
+	
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#if defined _gsm_included
  #endinput
#endif

#define _gsm_included
#pragma library gsm

// --------------------------------------------------
// includes
// --------------------------------------------------
#include "items"
#include "active_objects"
#include "players_actions"
#include "action_select"
#include "objects_moving"
#include "premise"
#include "pcounter"

// --------------------------------------------------
// enums
// --------------------------------------------------
enum GSMPlayerInfo {
	pInterlocutorId,
	pActiveMobileItemId,
	pUsingMobileItemId,
	pSMSText[MAX_STRING],
	pSMSnumber
};

// --------------------------------------------------
// defines
// --------------------------------------------------
#define GSM_ANTENA_DISTANCE 1000.0
#define SIM_START_MONEY 100

// --------------------------------------------------
// news
// --------------------------------------------------
new GSM_Player[MAX_PLAYERS][GSMPlayerInfo];

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward IsPlayerInGSMZone(playerid,NetworkId);
forward PlayerUseMobile(playerid,mobileitemid);
forward CheckNetworkAntenes(networkid);
forward ResetAntenesStatusWithNetwork(networkid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public IsPlayerInGSMZone(playerid,NetworkId)
{
	new premise,
		Float:Pos[6],
		Float:Pos_pl[3];
	// если в помещении то берем координаты входа в помещение иначе - координаты игрока
	if(GetPlayerCurrentPremise(playerid) != 0) GetPremiseEnterPos(GetPlayerCurrentPremise(playerid),Pos_pl[0],Pos_pl[1],Pos_pl[2]);
	else GetPlayerPos(playerid,Pos_pl[0],Pos_pl[1],Pos_pl[2]);
	for(new i = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);i < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;i++)
	{
		if(!IsActiveObjectValid(i)) continue;
		// если зона не нашей сети то пропуск
		if(GetActiveObjectParam(i,GSM_ANTENA_NETWORK_ID) != NetworkId) continue;
		// если связи нет то пропуск
		if(GetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED) == 0) continue;
		// берем координаты для последующих проверок
		GetModeObjectPos(GetActiveObjectModeObjectId(i),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
		// если в помещении то берем координаты входа в помещение
		if(premise != 0) GetPremiseEnterPos(premise,Pos[0],Pos[1],Pos[2]);
		// если мы не в зоне то пропуск этой антены
		if(!IsPosInRangeOfPoint(Pos_pl[0],Pos_pl[1],Pos_pl[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
		return 1;
	}
	return 0;
}

public PlayerUseMobile(playerid,mobileitemid)
{
	GSM_Player[playerid][pUsingMobileItemId] = mobileitemid;
	// Есть ли симка
	if(strval(GetItemVar(mobileitemid,0)) == 0) return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"Мобильник","Вставить SIM","Готово","Назад");
	// Звонят ли игроку сейчас
	if((GSM_Player[playerid][pInterlocutorId] != INVALID_PLAYER_ID) && (GSM_Player[playerid][pActiveMobileItemId] == mobileitemid)) return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"Мобильник","Ответить","Готово","Назад");
	// Обычные действия
	return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"Мобильник","Позвонить\nПрочесть SMS\nНаписать SMS\nВытащить SIM","Готово","Назад");
}

public CheckNetworkAntenes(networkid)
{
	new premise,
		Float:Pos[6],
		Float:Pos_tmp[3],
		i,j;
	// Крутим все антены
	for(i = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);i < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;i++)
	{
		if(!IsActiveObjectValid(i)) continue;
		// если антену передвигают то пропуск
		if(IsObjectMoving(GetActiveObjectModeObjectId(i))) return 0;
		// если сеть не наша то пропускаем
		if(GetActiveObjectParam(i,GSM_ANTENA_NETWORK_ID) != networkid) continue;
		// если связь есть тоже пропускаем
		if(GetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED) == 1) continue;
		// берем координаты для последующих проверок
		GetModeObjectPos(GetActiveObjectModeObjectId(i),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
		// если в помещении то берем координаты входа в помещение
		if(premise != 0) GetPremiseEnterPos(premise,Pos[0],Pos[1],Pos[2]);
		// крутим все антены чтобы найти ту что в зоне этой
		for(j = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);j < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;j++)
		{
			if(!IsActiveObjectValid(j)) continue;
			// если антену передвигают то пропуск
			if(IsObjectMoving(GetActiveObjectModeObjectId(j))) return 0;
			// если сеть не наша то пропускаем
			if(GetActiveObjectParam(j,GSM_ANTENA_NETWORK_ID) != networkid) continue;
			// если связи нет тоже пропускаем
			if(GetActiveObjectParam(j,GSM_ANTENA_IS_CONNECTED) == 0) continue;
			// берем координаты для последующих проверок			
			GetModeObjectPos(GetActiveObjectModeObjectId(j),premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],Pos[3],Pos[4],Pos[5]);
			// если в помещении то берем координаты входа в помещение
			if(premise != 0) GetPremiseEnterPos(premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2]);
			// если антена не в зоне действия то пропускаем
			if(!IsPosInRangeOfPoint(Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
			// связь есть,сохраняем эти данные
			SetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED,1);
			return 1;
		}
		// антен со связью не найдено,ищем терминал
		for(j = GetActiveObjectsCount(ACTION_SELECT_GSM_TERMINAL,0);j < GetActiveObjectsCount(ACTION_SELECT_GSM_TERMINAL,1) + 1;j++)
		{
			if(!IsActiveObjectValid(j)) continue;
			// если терминал передвигают то пропуск
			if(IsObjectMoving(GetActiveObjectModeObjectId(j))) return 0;
			// если не наша сеть то пропускаем
			if(GetActiveObjectParam(j,GSM_TERMINAL_NETWORK_ID) != networkid) continue;
			// берем координаты для последующих проверок
			GetModeObjectPos(GetActiveObjectModeObjectId(j),premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],Pos[3],Pos[4],Pos[5]);
			// проверим в помещении ли терминал,если да то координаты перемещаем на координаты входа в помещение
			if(premise != 0) GetPremiseEnterPos(premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2]);
			// если терминал не в зоне действия то пропускаем
			if(!IsPosInRangeOfPoint(Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
			// связь есть,сохраняем эти данные
			SetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED,1);
			return 1;
		}
	}
	return 0;
}

public ResetAntenesStatusWithNetwork(networkid)
{
	for(new i = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);i < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;i++)
	{
		if(!IsActiveObjectValid(i)) continue;
		// если сеть не наша то пропускаем
		if(GetActiveObjectParam(i,GSM_ANTENA_NETWORK_ID) != networkid) continue;
		SetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED,0);
	}
	return 1;
}

// --------------------------------------------------
// stocks
// --------------------------------------------------

stock GSM_OnGameModeInit()
{
	AddActionSelectRow(RusToGame("Передвинуть~n~антену"),ACTION_SELECT_MOVE_ANTENA);
	AddActionSelectRow(RusToGame("Передвинуть~n~терминал"),ACTION_SELECT_MOVE_TERMINAL);
	AddActionSelectRow(RusToGame("Управление~n~терминалом"),ACTION_SELECT_TERMINAL_SETTINGS);
	AddActionSelectRow(RusToGame("Управление~n~антеной"),ACTION_SELECT_ANTENA_SETTINGS);
	print("GSM system loaded.");
}

stock GSM_OnPlayerActionSelectCheck(playerid,actionid)
{
	switch(actionid)
	{
		// перемещение антены
		case ACTION_SELECT_MOVE_ANTENA:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если игрок не у активного обьекта
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// если ао не антена
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_ANTENA) return 0;
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;	
			return 1;
		}
		// настройки антены
		case ACTION_SELECT_ANTENA_SETTINGS:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если игрок не у активного обьекта
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// если ао не терминал
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_ANTENA) return 0;
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;			
			return 1;
		}
		// перемещение терминала
		case ACTION_SELECT_MOVE_TERMINAL:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если игрок не у активного обьекта
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// если ао не терминал
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_TERMINAL) return 0;
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING) == 1) return 0;	
			return 1;
		}
		// настройки терминала
		case ACTION_SELECT_TERMINAL_SETTINGS:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если игрок не у активного обьекта
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// если ао не терминал
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_TERMINAL) return 0;
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING) == 1) return 0;			
			return 1;
		}
	}
	return 0;
}

stock GSM_OnPlayerActionSelect(playerid,actionid)
{
	switch(actionid)
	{
		// перемещение антены
		case ACTION_SELECT_MOVE_ANTENA: return ShowPlayerDialog(playerid,DIALOG_ANTENA_MOVING,DIALOG_STYLE_LIST,"Передвинуть антену","Переместить на большое расстояние\nНемного подвинуть","Выбрать","Отмена");
		// настройки антены
		case ACTION_SELECT_ANTENA_SETTINGS: 
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;
			// ставим статус "используется"
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_USING,1);
			return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"Управление антеной","Просмотр частоты радиоволн\nИзменение частоты радиоволн","Выбрать","Отмена");
		}
		// перемещение терминала
		case ACTION_SELECT_MOVE_TERMINAL: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_MOVING,DIALOG_STYLE_LIST,"Передвинуть терминал","Переместить на большое расстояние\nНемного подвинуть","Выбрать","Отмена");
		// настройки терминала
		case ACTION_SELECT_TERMINAL_SETTINGS: 
		{
			new aoid = GetPlayerActiveObject(playerid);
			// если ао перемещают
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// если ао используется
			if(GetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING) == 1) return 0;
			// ставим статус "используется"
			SetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING,1);
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт","Выбрать","Отмена");
		}
	}
	return 0;
}

stock GSM_OnPlayerText(playerid,text[])
{
	if(GetPlayerAction(playerid) != ACTION_GSM_TALKING) return 0;
	PlayerMessage(playerid,PLAYER_MESSAGE_GSM_ASK,text);
	PlayerMessage(GSM_Player[playerid][pInterlocutorId],PLAYER_MESSAGE_GSM_LISTEN,text);
	return 1;
}

stock GSM_OnDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	new string[MAX_STRING];
	switch(dialogid)
	{
		case DIALOG_ANTENA_MOVING:
		{
			if(!response) return 1;
			new networkid = GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID);
			// ставим отрицательный ид сети,чтобы данная антена не участвовала при обновлении сети
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID,-networkid);
			// обнуляем статусы антен
			ResetAntenesStatusWithNetwork(networkid);
			// ожидаем пока всем антенам что находятся в зоне действия выставится статус "связь"
			while(CheckNetworkAntenes(networkid)) {}
			switch(listitem)
			{
				// На большое расстояние
				case 0: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),false);
				// Миллимитраж позиции
				case 1: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),true);
			}
			return 0;
		}
		case DIALOG_TERMINAL_MOVING:
		{
			if(!response) return 1;
			switch(listitem)
			{
				// На большое расстояние
				case 0: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),false);
				// Миллимитраж позиции
				case 1: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),true);
			}
			return 0;
		}
		case DIALOG_ANTENA_SETTINGS_LAST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"Управление антеной","Просмотр частоты радиоволн\nИзменение частоты радиоволн","Выбрать","Отмена");
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_IS_USING,0);
			return 1;
		}
		case DIALOG_ANTENA_SETTINGS:
		{
			if(!response) 
			{
				SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_IS_USING,0);
				return 1;
			}
			switch(listitem)
			{
				// Просмотр частоты
				case 0: 
				{
					format(string,sizeof(string),"Частота радиоволн равна %dMHz",((GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID) + 43) * 10 ));
					return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"Управление антеной [Частота радиоволн]",string,"Готово","Назад");
				}
				// Изменение частоты
				case 1: return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS_MHZ,DIALOG_STYLE_INPUT,"Управление антеной [Частота радиоволн]","Введите новую частоту:","Готово","Назад");
			}
			return 0;
		}
		case DIALOG_ANTENA_SETTINGS_MHZ:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"Управление антеной","Просмотр частоты радиоволн\nИзменение частоты радиоволн","Выбрать","Отмена");
			new networkid = (strval(inputtext) / 10) - 43;
			if((networkid < 0) || (networkid > 100)) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"Управление антеной","Просмотр частоты радиоволн\nИзменение частоты радиоволн","Выбрать","Отмена");
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID,networkid);
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BASE_ID),UPDATE_AO_INFO_VAR,GSM_ANTENA_NETWORK_ID,networkid);			
			return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"Управление антеной","Просмотр частоты радиоволн\nИзменение частоты радиоволн","Выбрать","Отмена");
		}
		case DIALOG_TERMINAL_SETTINGS_LAST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_IS_USING,0);
			return 1;
		}
		case DIALOG_TERMINAL_SETTINGS:
		{
			if(!response) 
			{
				SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_IS_USING,0);
				return 1;
			}
			switch(listitem)
			{
				// Сетевые параметры
				case 0: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_1,DIALOG_STYLE_LIST,"Управление терминалом [Сетевые параметры]","Частота радиоволн\nНазвание сети\nЦена секунды разговора\nЦена 1 SMS сообщения","Выбрать","Отмена");
				// Штамповка SIM-карт
				case 1: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_2,DIALOG_STYLE_INPUT,"Управление терминалом [Штамповка SIM-карт]","Введите количество:","Штамповать","Отмена");
				// Забрать SIM-карты
				case 2:
				{
					new tmp_int;
					while(MySQL_GetBoxItem(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BOX_ID),tmp_int))
					{
						MySQL_DeleteItemFromBox(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BOX_ID),tmp_int);
						if(!SetItemOwner(tmp_int,oGetPlayerName(playerid)))
						{
							printf("[gsm.inc] -> OnDialogResponse -> DIALOG_TERMINAL_SETTINGS -> listitem 2 -> item %d not set to player %d",tmp_int,playerid);
						}
					}
				}
			}
			return 0;
		}
		case DIALOG_TERMINAL_SETTINGS_1:
		{
			if(!response) 
			{
				SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_IS_USING,0);
				return 1;
			}
			switch(listitem)
			{
				// Частота радиоволн
				case 0: 
				{
					format(string,sizeof(string),"Частота радиоволн равна %dMHz",((GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_NETWORK_ID) + 43) * 10 ));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"Управление терминалом [Частота радиоволн]",string,"Готово","Назад");
				}
				// Название сети
				case 1: 
				{
					format(string,sizeof(string),"Текущее название сети: %s\nВведите новое:",MySQL_GetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NNAME,DIALOG_STYLE_INPUT,"Управление терминалом [Название сети]",string,"Готово","Назад");
				}
				// Цена секунды разговора
				case 2:
				{
					format(string,sizeof(string),"Текущая цена секунды разговора: %d$\nВведите новую:",MySQL_GetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NCCOST,DIALOG_STYLE_INPUT,"Управление терминалом [Цена секунды разговора]",string,"Готово","Назад");
				}
				// Цена 1 смс
				case 3:
				{
					format(string,sizeof(string),"Текущая цена 1 SMS сообщения: %d$\nВведите новую:",MySQL_GetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NSCOST,DIALOG_STYLE_INPUT,"Управление терминалом [Цена 1 SMS сообщения]",string,"Готово","Назад");
				}
			}
			return 0;
		}
		case DIALOG_TERMINAL_SETTINGS_2:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 50)) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_2,DIALOG_STYLE_INPUT,"Управление терминалом [Штамповка SIM-карт]","Введите количество:","Штамповать","Отмена");
			new pnumber,
				tmp_int;
			for(new i = 0;i < strval(inputtext);i++)
			{
				pnumber = random(899999) + 100000;
				while(GetItemWhithVar(ITEM_TYPE_SIMCARD,GSM_SIM_NUMBER,inttostr(pnumber),tmp_int)) pnumber = random(899999) + 100000;
				tmp_int = CreateItem(ITEM_TYPE_SIMCARD,"ddd",pnumber,SIM_START_MONEY,GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID));
				MySQL_AddItemInBox(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BOX_ID),tmp_int);
			}
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
		}
		case DIALOG_TERMINAL_SETTINGS_NNAME:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
			if(!strlen(inputtext)) 
			{
				format(string,sizeof(string),"Текущее название сети: %s\nВведите новое:",MySQL_GetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NNAME,DIALOG_STYLE_INPUT,"Управление терминалом [Название сети]",string,"Готово","Назад");
			}
			MySQL_SetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),inputtext);
			format(string,sizeof(string),"Новое название сети: %s",inputtext);
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"Управление терминалом [Название сети]",string,"Готово","Назад");
		}
		case DIALOG_TERMINAL_SETTINGS_NCCOST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 100)) 
			{
				format(string,sizeof(string),"Текущая цена секунды разговора: %d$\nВведите новую:",MySQL_GetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NCCOST,DIALOG_STYLE_INPUT,"Управление терминалом [Цена секунды разговора]",string,"Готово","Назад");
			}
			MySQL_SetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),strval(inputtext));
			format(string,sizeof(string),"Новая цена секунды разговора: %d",strval(inputtext));
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"Управление терминалом [Цена секунды разговора]",string,"Готово","Назад");
		}
		case DIALOG_TERMINAL_SETTINGS_NSCOST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"Управление терминалом","Сетевые параметры\nШтамповка SIM-карт\nЗабрать SIM-карты","Выбрать","Отмена");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 100)) 
			{
				format(string,sizeof(string),"Текущая цена 1 SMS сообщения: %d$\nВведите новую:",MySQL_GetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NSCOST,DIALOG_STYLE_INPUT,"Управление терминалом [Цена 1 SMS сообщения]",string,"Готово","Назад");
			}
			MySQL_SetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),strval(inputtext));
			format(string,sizeof(string),"Новая цена 1 SMS сообщения: %d",strval(inputtext));
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"Управление терминалом [Цена 1 SMS сообщения]",string,"Готово","Назад");
		}
		case DIALOG_GSM_LAST:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			return 1;
		}
		case DIALOG_GSM_MOBILE_ACTIONS:
		{
			if(!response) return 1;
			if(!strcmp(inputtext,"Вставить SIM"))
			{
				new items[MAX_PLAYER_ITEMS],
					icount;
				nullstr(DialogString);
				GetPlayerItems(playerid,items);
				for(new i = 0;i < sizeof(items);i++)
				{
					if(items[i] == 0) continue;
					if(GetItemType(items[i]) != ITEM_TYPE_SIMCARD) continue;
					icount++;
					format(DialogString,sizeof(DialogString),"%s%s[%s]\n",DialogString,GetNetworkName(strval(GetItemVar(items[i],2))),GetItemVar(items[i],0));
				}
				if(icount == 0) return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","У вас нет SIM-карт","Готово","Назад");
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_SELECT_SIM,DIALOG_STYLE_LIST,"Мобильник",DialogString,"Выбрать","Назад");
			}
			else if(!strcmp(inputtext,"Ответить"))
			{
				if(GSM_Player[playerid][pInterlocutorId] == INVALID_PLAYER_ID) return 0;
				if(!IsPlayerConnected(GSM_Player[playerid][pInterlocutorId])) return 0; // Звонящий оффлайн
				if(GetPlayerAction(GSM_Player[playerid][pInterlocutorId]) != ACTION_GSM_CALLING) return 0; // Звонящий уже не звонит
				new NetworkId = strval(GetItemVar(strval(GetItemVar(GSM_Player[playerid][pActiveMobileItemId],0)),2));
				if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // Вы вне сети
				if(!IsPlayerInGSMZone(GSM_Player[playerid][pInterlocutorId],NetworkId)) return 0; // Звонящий вне сети
				SetPlayerAction(playerid,ACTION_GSM_TALKING);
				SetPlayerAction(GSM_Player[playerid][pInterlocutorId],ACTION_GSM_TALKING);
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return 1;
			}		
			else if(!strcmp(inputtext,"Позвонить"))
			{
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_CALL_NUMBER,DIALOG_STYLE_INPUT,"Мобильник","Наберите номер телефона:","Готово","Назад");
			}
			else if(!strcmp(inputtext,"Прочесть SMS"))
			{
			
			}
			else if(!strcmp(inputtext,"Написать SMS"))
			{
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_NUMBER,DIALOG_STYLE_INPUT,"Мобильник","Наберите номер телефона:","Готово","Назад");
			}
			else if(!strcmp(inputtext,"Вытащить SIM"))
			{
				SetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID,"0");				
				return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","SIM-карта вытащена","Готово","Назад");
			}
		}
		case DIALOG_GSM_SELECT_SIM:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			new simid;
			GetItemWhithVar(ITEM_TYPE_SIMCARD,GSM_SIM_NUMBER,CutPartText(inputtext,'[',']'),simid);
			SetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID,"%d",simid);
			return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","SIM-карта поставлена","Готово","Назад");
		}
		case DIALOG_GSM_CALL_NUMBER:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			new simid = strval(GetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID));
			// Отрицательный баланс
			if(strval(GetItemVar(simid,GSM_SIM_MONEY)) <= 0) return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","На вашем счету не хватает денег для совершения данного звонка","Готово","Назад");
			switch(CallToNumber(playerid,GSM_Player[playerid][pUsingMobileItemId],strval(inputtext)))
			{
				// Вы вне зоны действия сети
				case 0: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","Нет сети","Готово","Назад");
				// Такого номера не существует
				case 1: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","Вы неправильно набрали номер\nПовторите пожалуйста набор","Готово","Назад");
				// Абонент находится вне зоны действия сети
				case 2: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","Абонент находится вне зоны действия сети\nПопробуйте позвонить позднее","Готово","Назад");
				// Абонент находится вне зоны действия сети
				case 3: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","Телефон абонента занят","Готово","Назад");
				// Всё ок
				case 4: return 1;
			}
		}
		case DIALOG_GSM_WSMS_NUMBER:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			nullstr(GSM_Player[playerid][pSMSText]);
			GSM_Player[playerid][pSMSnumber] = strval(inputtext);
			return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_TEXT,DIALOG_STYLE_INPUT,"Мобильник","Введите текст:","Следующая строка","Отправить");
		}
		case DIALOG_GSM_WSMS_TEXT:
		{
			format(GSM_Player[playerid][pSMSText],MAX_STRING,"%s%s\n",GSM_Player[playerid][pSMSText],inputtext);
			if(!response)
			{
				SendSMSToNumber(playerid,GSM_Player[playerid][pUsingMobileItemId],GSM_Player[playerid][pSMSnumber],GSM_Player[playerid][pSMSText]);
				return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"Мобильник","Сообщение отправлено","Готово","Назад");				
			}
			format(DialogString,sizeof(DialogString),"Введите текст сообщения:\n%s",GSM_Player[playerid][pSMSText]);
			return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_TEXT,DIALOG_STYLE_INPUT,"Мобильник",DialogString,"Следующая строка","Отправить");
		}
	}
	return 0;
}

stock GSM_OnActiveObjectCreate(aoid,actionid)
{
	switch(actionid)
	{
		case ACTION_SELECT_GSM_TERMINAL:
		{
			new networkid = MySQL_GetMaxGSMNetworkId() + 1,
				boxid = MySQL_GetMaxBoxId() + 1,
				objectid = GetActiveObjectModeObjectId(aoid),
				premise,
				Float:Pos[6];
			// добавляем в базу новую сеть
			MySQL_AddGSMNetwork(networkid);
			// ставим терминалу ид сети
			SetActiveObjectParam(aoid,GSM_TERMINAL_NETWORK_ID,networkid);
			// ставим ид коробки для вещей
			SetActiveObjectParam(aoid,GSM_TERMINAL_BOX_ID,boxid);
			// ставим статус "не используется"
			SetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING,0);			
			GetModeObjectPos(objectid,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// добавляем данные в таблицу активных обьектов
			new aobaseid = MySQL_AddActiveObjectInfo(ACTION_SELECT_GSM_TERMINAL,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5],networkid,boxid);
			// записываем ид обьекта в базе в инфу обеькта
			SetActiveObjectParam(aoid,GSM_TERMINAL_BASE_ID,aobaseid);
			// обнуляем статусы антен
			ResetAntenesStatusWithNetwork(networkid);
			// ожидаем пока всем антенам что находятся в зоне действия выставится статус "связь"
			while(CheckNetworkAntenes(networkid)) {} 
			return 1;
		}
		case ACTION_SELECT_GSM_ANTENA:
		{
			new	premise,
				Float:Pos[6];
			GetModeObjectPos(GetActiveObjectModeObjectId(aoid),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ставим ид сети 0 - терминала на 0 нет и не будет
			SetActiveObjectParam(aoid,GSM_ANTENA_NETWORK_ID,0);
			// связи конечно же нет
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_CONNECTED,0);
			// не используется
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_USING,0);
			// добавляем данные в таблицу активных обьектов
			new aobaseid = MySQL_AddActiveObjectInfo(ACTION_SELECT_GSM_ANTENA,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// записываем ид обьекта в базе в инфу обеькта
			SetActiveObjectParam(aoid,GSM_ANTENA_BASE_ID,aobaseid);
			return 1;
		}
	}
	return 0;
}

stock GSM_OnActiveObjectMovingComplet(aobjectid)
{
	switch(GetActiveObjectAction(aobjectid))
	{
		case ACTION_SELECT_GSM_TERMINAL:
		{
			new networkid = GetActiveObjectParam(aobjectid,GSM_TERMINAL_NETWORK_ID),
				premise,
				Float:Pos[6];
			GetModeObjectPos(GetActiveObjectModeObjectId(aobjectid),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// обновляем координаты обьекта в таблице
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(aobjectid,GSM_TERMINAL_BASE_ID),UPDATE_AO_INFO_POS,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// обнуляем статусы антен
			ResetAntenesStatusWithNetwork(networkid);
			// ожидаем пока всем антенам что находятся в зоне действия выставится статус "связь"
			while(CheckNetworkAntenes(networkid)) {} 
			return 1;
		}
		case ACTION_SELECT_GSM_ANTENA:
		{
			new networkid = -GetActiveObjectParam(aobjectid,GSM_ANTENA_NETWORK_ID),
				premise,
				Float:Pos[6];
			GetModeObjectPos(GetActiveObjectModeObjectId(aobjectid),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// обновляем координаты обьекта в таблице
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(aobjectid,GSM_ANTENA_BASE_ID),UPDATE_AO_INFO_POS,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// возвращаем положительный ид сети
			SetActiveObjectParam(aobjectid,GSM_ANTENA_NETWORK_ID,networkid);
			// обнуляем статусы антен
			ResetAntenesStatusWithNetwork(networkid);
			// ожидаем пока всем антенам что находятся в зоне действия выставится статус "связь"
			while(CheckNetworkAntenes(networkid)) {} 
			return 1;
		}
	}
	return 0;
}

stock GetNetworkName(networkid)
{
	new res[MAX_STRING];
	format(res,sizeof(res),MySQL_GetGSMNetworkName(networkid));
	return res;
}

stock CallToNumber(playerid,mobileitemid,number)
{
	printf("CallToNumber(%d,%d,%d)",playerid,mobileitemid,number);
	new NetworkId = strval(GetItemVar(strval(GetItemVar(mobileitemid,0)),2));
	if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // Мы вне зоны действия сети
	// Связь есть,ищем номер абонента
	new to_simid,
		to_mobileid;
	if(!GetItemWhithVar(ITEM_TYPE_SIMCARD,0,inttostr(number),to_simid)) return 1; // такого номера нету
	if(!GetItemWhithVar(ITEM_TYPE_MOBILE,0,inttostr(to_simid),to_mobileid)) return 2; // Абонент вне зоны действия сети(по сути симка не используется)
	for(new pl = 0;pl < GetMaxPlayer();pl++)
	{
		if(!IsPlayerConnected(pl)) continue;
		if(pl == playerid) continue;
		if(!IsPlayerHaveItem(oGetPlayerName(pl),to_mobileid)) continue;
		// У игрока есть мобильник нужный нам
		if(!IsPlayerInGSMZone(pl,strval(GetItemVar(to_simid,2)))) return 2; // Абонент вне зоны действия сети(он реально вне зоны)
		// У цели сеть ловит, соединяем
		if(GetPlayerAction(pl) != ACTION_NONE) return 3; // Телефон цели занят
		SetPlayerAction(playerid,ACTION_GSM_CALLING);
		ModeMessage(pl,MODE_MESSAGE_IC,"[мобильник] Входящий звонок от %d",number);
		PlayerMessage(pl,PLAYER_MESSAGE_ACTION,"звонит мобильник");
		PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"достал мобильник и набрал номер");
		GSM_Player[playerid][pInterlocutorId] = pl;
		GSM_Player[pl][pInterlocutorId] = playerid;
		GSM_Player[playerid][pActiveMobileItemId] = mobileitemid;
		GSM_Player[pl][pActiveMobileItemId] = to_mobileid;
		return 4; // Всё ок
	}
	return 0; // Мы вне зоны действия сети
}

stock SendSMSToNumber(playerid,mobileitemid,number,text[])
{
	printf("SendSMSToNumber(%d,%d,%d,%s)",playerid,mobileitemid,number,text);
	new NetworkId = strval(GetItemVar(strval(GetItemVar(mobileitemid,0)),2));
	if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // Мы вне зоны действия сети
//	MySQL_SendSMS(strval(GetItemVar(strval(GetItemVar(mobileitemid,0)),0)),number,text);
	// Связь есть,ищем номер абонента
	new to_simid,
		to_mobileid;
	if(!GetItemWhithVar(ITEM_TYPE_SIMCARD,0,inttostr(number),to_simid)) return 1; // такого номера нету
	if(!GetItemWhithVar(ITEM_TYPE_MOBILE,0,inttostr(to_simid),to_mobileid)) return 1; // Абонент вне зоны действия сети(по сути симка не используется)
	for(new pl = 0;pl < GetMaxPlayer();pl++)
	{
		if(!IsPlayerConnected(pl)) continue;
		if(pl == playerid) continue;
		if(!IsPlayerHaveItem(oGetPlayerName(pl),to_mobileid)) continue;
		// У игрока есть мобильник нужный нам
		if(!IsPlayerInGSMZone(pl,strval(GetItemVar(to_simid,2)))) return 1;
		// У цели сеть ловит
		if(GetPlayerAction(pl) != ACTION_NONE) return 1; // Телефон цели занят		
		ModeMessage(pl,MODE_MESSAGE_IC,"[мобильник] Входящее сообщение от %d",number);
		return 1; // Всё ок
	}
	return 1; // Мы вне зоны действия сети
}