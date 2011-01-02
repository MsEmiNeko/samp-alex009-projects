/*
*	Created:			05.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Радио-передатчик
*/

#if defined _furnitures_transmitter_included
	#endinput
#endif

#define _furnitures_transmitter_included
#pragma library furnitures_transmitter

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum {
	TRANSMITTER_VAR_NONE,
	TRANSMITTER_VAR_REQ,
	TRANSMITTER_VAR_ON
};
enum FurnitureTransmitterPlayerInfo {
	pMessage[MAX_STRING],
	pTimeOfLastMessage
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static 
	Transmitter_Player[MAX_PLAYERS][FurnitureTransmitterPlayerInfo],
	tmp,
	tmptime;

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward TransmitterUpdate(furnitureid);
forward OnRadioMessageRecived(sender,message[],networkid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public TransmitterUpdate(furnitureid)
{
	tmp = GetFurnitureModeObject(furnitureid);
	tmptime = GetTickCount();
	for(new i = 0;i <= GetMaxPlayer();i++)
	{
		if(IsPlayerRangeOfModeObject(i,5.0,tmp))
		{
			if((tmptime - Transmitter_Player[playerid][pTimeOfLastMessage]) < 1000)
			{
				Transmitter_Player[playerid][pTimeOfLastMessage] = 0;
				OnRadioMessageRecived(playerid,Transmitter_Player[playerid][pMessage],GetFurnitureVar(furnitureid,TRANSMITTER_VAR_REQ));
			}
		}
	}	
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Transmitter_Init()
{
	Debug(DEBUG_START,"Transmitter_Init()");
	AddActionSelectRow(RusToGame("Использовать~n~радио-передатчик"),ACTION_USE_TRANSMITTER);
	Debug(DEBUG_END,"Transmitter_Init(reason: complete)");
}

Transmitter_OnFurnitureActionC(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Transmitter_OnFurnitureActionC(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionC(reason: its not transmitter)");return 0;}
	if(actionid != ACTION_USE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionC(reason: any actionid)");return 0;}
	new Float:ang[3];
	GetModeObjectRot(modeobjectid,ang[0],ang[1],ang[2]);
	GetPlayerFacingAngle(playerid,ang[0]);
	ang[1] = ang[0] - ang[2];
	if(ang[1] < 0) ang[1] *= -1;
	if((ang[1] < 170.0) || (ang[1] > 190.0)) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionC(reason: face not see on transmitter)");return 0;}	
	Debug(DEBUG_END,"Transmitter_OnFurnitureActionC(reason: complete)");
	return 1;	
}

Transmitter_OnFurnitureActionS(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Transmitter_OnFurnitureActionS(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionS(reason: its not transmitter)");return 0;}
	if(actionid != ACTION_USE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionS(reason: any actionid)");return 0;}
	new Float:ang[3];
	GetModeObjectRot(modeobjectid,ang[0],ang[1],ang[2]);
	GetPlayerFacingAngle(playerid,ang[0]);
	ang[1] = ang[0] - ang[2];
	if(ang[1] < 0) ang[1] *= -1;
	if((ang[1] < 170.0) || (ang[1] > 190.0)) {Debug(DEBUG_END,"Transmitter_OnFurnitureActionS(reason: face not see on transmitter)");return 0;}	
	if(GetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON)) ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_ACTIONS,DIALOG_STYLE_LIST,"Радио-передатчик","Сменить частоту\nОстановить трансляцию","Выбрать","Выход");
	else ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_ACTIONS,DIALOG_STYLE_LIST,"Радио-передатчик","Сменить частоту\nНачать трансляцию","Выбрать","Выход");
	ShowHelpBoxForPlayer(playerid,HELPBOX_TRANSMITTER_ACTIONS,TRANSMITTER_INFO_ACTIONS);
	SetPlayerAction(playerid,ACTION_USE_TRANSMITTER);
	Debug(DEBUG_END,"Transmitter_OnFurnitureActionS(reason: complete)");
	return 1;
}

Transmitter_OnFurnitureDialogR(playerid,dialogid,response,listitem,inputtext[],furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Transmitter_OnFurnitureDialogR(%d,%d,%d,%d,'%s',%d,%d,%d)",playerid,dialogid,response,listitem,inputtext,furnitureid,type,modeobjectid);
	switch(dialogid)
	{
		case DIALOG_TRANSMITTER_NULL:
		{
			Debug(DEBUG_ACTION,"DIALOG_TRANSMITTER_NULL");
			SetPlayerAction(playerid,ACTION_NONE);
			Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
			return 1;
		}
		case DIALOG_TRANSMITTER_ACTIONS:
		{
			Debug(DEBUG_ACTION,"DIALOG_TRANSMITTER_ACTIONS");
			if(!response) 
			{
				SetPlayerAction(playerid,ACTION_NONE);
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
			if(!strcmp("Сменить частоту",inputtext))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,TRANSMITTER_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_REQ,DIALOG_STYLE_INPUT,"Радио-передатчик",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
			if(!strcmp("Начать трансляцию",inputtext))
			{
				format(DialogString,sizeof(DialogString),"Трансляция на частоте %d MHz начата",GetFurnitureVar(furnitureid,TRANSMITTER_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_NULL,DIALOG_STYLE_MSGBOX,"Радио-передатчик",DialogString,"Выход","Выход");
				SetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON,1);
				SetModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0,SetTimerEx("TransmitterUpdate",500,1,"d",furnitureid));
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
			if(!strcmp("Остановить трансляцию",inputtext))
			{
				ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_NULL,DIALOG_STYLE_MSGBOX,"Радио-передатчик","Трансляция остановлена","Выход","Выход");
				SetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON,0);
				KillTimer(GetModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0));
				DeleteModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0);
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
		}
		case DIALOG_TRANSMITTER_REQ:
		{
			Debug(DEBUG_ACTION,"DIALOG_TRANSMITTER_REQ");
			if(!response) 
			{
				if(GetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON)) ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_ACTIONS,DIALOG_STYLE_LIST,"Радио-передатчик","Сменить частоту\nОстановить трансляцию","Выбрать","Выход");
				else ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_ACTIONS,DIALOG_STYLE_LIST,"Радио-передатчик","Сменить частоту\nНачать трансляцию","Выбрать","Выход");
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
			tmp = strval(inputtext);
			if((tmp <= 0) || (tmp > 300))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,TRANSMITTER_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_REQ,DIALOG_STYLE_INPUT,"Радио-передатчик",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
				return 1;
			}
			SetFurnitureVar(furnitureid,TRANSMITTER_VAR_REQ,tmp);
			format(DialogString,sizeof(DialogString),"Частота изменена на %d MHz",tmp);
			ShowPlayerModeDialog(playerid,DIALOG_TRANSMITTER_NULL,DIALOG_STYLE_MSGBOX,"Радио-передатчик",DialogString,"Выход","Выход");
			Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Transmitter_OnFurnitureDialogR(reason: complete)");
	return 0;
}

Transmitter_OnPlayerMessage(playerid,message[],type,messagef[])
{
	format(Transmitter_Player[playerid][pMessage],MAX_STRING,message);
	Transmitter_Player[playerid][pTimeOfLastMessage] = GetTickCount();
}

Transmitter_OnFurnitureDeath(furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Transmitter_OnFurnitureDeath(%d,%d,%d)",furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureDeath(reason: its not transmitter)");return 0;}
	if(GetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON))
	{
		KillTimer(GetModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0));
		DeleteModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0);
	}
	Debug(DEBUG_END,"Transmitter_OnFurnitureDeath(reason: complete)");
	return 1;
}

Transmitter_OnFurnitureLoaded(furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Transmitter_OnFurnitureLoaded(%d,%d,%d)",furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_TRANSMITTER) {Debug(DEBUG_END,"Transmitter_OnFurnitureLoaded(reason: its not transmitter)");return 0;}
	if(GetFurnitureVar(furnitureid,TRANSMITTER_VAR_ON))
	{
		SetModePropertyInt(MODE_PROPERTY_FURNITURE_TRANSM,furnitureid,0,SetTimerEx("TransmitterUpdate",500,1,"d",furnitureid));
	}
	Debug(DEBUG_END,"Transmitter_OnFurnitureLoaded(reason: complete)");
	return 1;
}