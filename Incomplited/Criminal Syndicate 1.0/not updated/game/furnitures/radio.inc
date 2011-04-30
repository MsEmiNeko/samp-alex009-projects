/*
*	Created:			12.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Радио приёмник
*/

#if defined _furnitures_radio_included
	#endinput
#endif

#define _furnitures_radio_included
#pragma library furnitures_radio

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum {
	RADIO_VAR_NONE,
	RADIO_VAR_REQ,
	RADIO_VAR_ON
};

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Radio_Init()
{
	Debug(DEBUG_START,"Radio_Init()");
	AddActionSelectRow(RusToGame("Использовать~n~радио-приёмник"),ACTION_USE_RADIO);
	Debug(DEBUG_END,"Radio_Init(reason: complete)");
}

Radio_OnFurnitureActionCheck(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Radio_OnFurnitureActionCheck(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_RADIO) {Debug(DEBUG_END,"Radio_OnFurnitureActionCheck(reason: its not radio)");return 0;}
	if(actionid != ACTION_USE_RADIO) {Debug(DEBUG_END,"Radio_OnFurnitureActionCheck(reason: any actionid)");return 0;}
	Debug(DEBUG_END,"Radio_OnFurnitureActionCheck(reason: complete)");
	return 1;	
}

Radio_OnFurnitureActionSelect(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Radio_OnFurnitureActionSelect(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_RADIO) {Debug(DEBUG_END,"Radio_OnFurnitureActionSelect(reason: its not radio)");return 0;}
	if(actionid != ACTION_USE_RADIO) {Debug(DEBUG_END,"Radio_OnFurnitureActionSelect(reason: any actionid)");return 0;}
	if(GetFurnitureVar(furnitureid,RADIO_VAR_ON)) ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВыключить радио","Выбрать","Выход");
	else ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВключить радио","Выбрать","Выход");
	ShowHelpBoxForPlayer(playerid,HELPBOX_RADIO_ACTIONS,RADIO_INFO_ACTIONS);
	SetPlayerAction(playerid,ACTION_USE_RADIO);
	Debug(DEBUG_END,"Radio_OnFurnitureActionSelect(reason: complete)");
	return 1;
}

Radio_OnFurnitureDialogRespose(playerid,dialogid,response,listitem,inputtext[],furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Radio_OnFurnitureDialogRespose(%d,%d,%d,%d,'%s',%d,%d,%d)",playerid,dialogid,response,listitem,inputtext,furnitureid,type,modeobjectid);
	switch(dialogid)
	{
		case DIALOG_RADIO_NULL:
		{
			Debug(DEBUG_ACTION,"DIALOG_RADIO_NULL");
			SetPlayerAction(playerid,ACTION_NONE);
			Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
			return 1;
		}
		case DIALOG_RADIO_ACTIONS:
		{
			Debug(DEBUG_ACTION,"DIALOG_RADIO_NULL");
			if(!response) 
			{
				SetPlayerAction(playerid,ACTION_NONE);
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			if(!strcmp("Сменить частоту",inputtext))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,RADIO_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_RADIO_REQ,DIALOG_STYLE_INPUT,"Радио-приёмник",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			if(!strcmp("Поиск доступных частот",inputtext))
			{
				new tmp = GetModeObjectVirtualWorld(modeobjectid),
					Float:pos[3],
					li;
				if(tmp != 0) GetPremiseEnterPos(tmp,pos[0],pos[1],pos[2]);
				else GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
				tmp = GetSquareIdForXY(pos[0],pos[1]);
				nullstr(DialogString);
				for(new i = 1;i <= 300;i++)
				{
					if(!IsSquareHaveNetwork(tmp,i)) continue;
					format(DialogString,sizeof(DialogString),"%s%d MHz\n",DialogString,i);
					SetPlayerModeDialogListData(playerid,li,i);
					li++;
				}
				if(li == 0) ShowPlayerModeDialog(playerid,DIALOG_RADIO_NULL,DIALOG_STYLE_MSGBOX,"Радио-приёмник","Нет связи","Выход","Выход");
				else ShowPlayerModeDialog(playerid,DIALOG_RADIO_FIND_REQ,DIALOG_STYLE_LIST,"Радио-приёмник",DialogString,"Выбрать","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			if(!strcmp("Включить радио",inputtext))
			{
				SetFurnitureVar(furnitureid,RADIO_VAR_ON,1);
				ShowPlayerModeDialog(playerid,DIALOG_RADIO_NULL,DIALOG_STYLE_MSGBOX,"Радио-приёмник","Радио включено","Выход","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			if(!strcmp("Выключить радио",inputtext))
			{
				SetFurnitureVar(furnitureid,RADIO_VAR_ON,0);
				ShowPlayerModeDialog(playerid,DIALOG_RADIO_NULL,DIALOG_STYLE_MSGBOX,"Радио-приёмник","Радио выключено","Выход","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
		}
		case DIALOG_RADIO_REQ:
		{
			Debug(DEBUG_ACTION,"DIALOG_RADIO_REQ");
			if(!response) 
			{
				if(GetFurnitureVar(furnitureid,RADIO_VAR_ON)) ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВыключить радио","Выбрать","Выход");
				else ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВключить радио","Выбрать","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			new tmp = strval(inputtext);
			if((tmp <= 0) || (tmp > 300))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,RADIO_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_RADIO_REQ,DIALOG_STYLE_INPUT,"Радио-приёмник",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			SetFurnitureVar(furnitureid,RADIO_VAR_REQ,tmp);
			format(DialogString,sizeof(DialogString),"Частота изменена на %d MHz",tmp);
			ShowPlayerModeDialog(playerid,DIALOG_RADIO_NULL,DIALOG_STYLE_MSGBOX,"Радио-приёмник",DialogString,"Выход","Выход");
			Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
			return 1;
		}
		case DIALOG_RADIO_FIND_REQ:
		{
			Debug(DEBUG_ACTION,"DIALOG_RADIO_FIND_REQ");
			if(!response) 
			{
				if(GetFurnitureVar(furnitureid,RADIO_VAR_ON)) ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВыключить радио","Выбрать","Выход");
				else ShowPlayerModeDialog(playerid,DIALOG_RADIO_ACTIONS,DIALOG_STYLE_LIST,"Радио-приёмник","Сменить частоту\nПоиск доступных частот\nВключить радио","Выбрать","Выход");
				Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			new tmp = GetPlayerModeDialogListData(playerid,li);
			SetFurnitureVar(furnitureid,RADIO_VAR_REQ,tmp);
			format(DialogString,sizeof(DialogString),"Частота изменена на %d MHz",tmp);
			ShowPlayerModeDialog(playerid,DIALOG_RADIO_NULL,DIALOG_STYLE_MSGBOX,"Радио-приёмник",DialogString,"Выход","Выход");
			Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Radio_OnFurnitureDialogRespose(reason: complete)");
	return 0;
}

Radio_OnRadioMessageRecived(message[],networkid) 
{
	Debug(DEBUG_START,"Radio_OnRadioMessageRecived('%s',%d)",message,networkid);
	new furnitureid,
		tmp,
		sqid,
		Float:pos[3];
	forfurnituresbytype(FURNITURE_TYPE_RADIO)
	{
		furnitureid = strval(result);
		if(!GetFurnitureVar(furnitureid,RADIO_VAR_ON)) continue;
		tmp = GetModeObjectVirtualWorld(modeobjectid);
		if(tmp != 0) GetPremiseEnterPos(tmp,pos[0],pos[1],pos[2]);
		else GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
		sqid = GetSquareIdForXY(pos[0],pos[1]);
		if(!IsSquareHaveNetwork(sqid,networkid)) continue;
		GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
		for(new i = 0;i <= GetMaxPlayer();i++)
		{
			if(!IsPlayerConnected(i)) continue;
			if(!IsPlayerRangeOfPoint(i,RADIO_DISTANCE,pos[0],pos[1],pos[2])) continue;
			if(GetPlayerVirtualWorld(i) != tmp) continue;
			ModeMessage(i,MODE_MESSAGE_RADIO,message);
		}
	}
	Debug(DEBUG_END,"Radio_OnRadioMessageRecived(reason: complete)");
	return 1;
}