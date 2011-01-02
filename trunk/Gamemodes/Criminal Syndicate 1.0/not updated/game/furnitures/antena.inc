/*
*	Created:			12.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Антены передачи для радио сетей
*/

#if defined _furnitures_antena_included
	#endinput
#endif

#define _furnitures_antena_included
#pragma library furnitures_antena

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum {
	TRANSMITTER_VAR_NONE,
	TRANSMITTER_VAR_REQ
};

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Antena_Init()
{
	Debug(DEBUG_START,"Antena_Init()");
	AddActionSelectRow(RusToGame("Использовать~n~антену"),ACTION_USE_ANTENA);
	Debug(DEBUG_END,"Antena_Init(reason: complete)");
}

Antena_OnFurnitureActionCheck(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureActionCheck(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureActionCheck(reason: its not antena)");return 0;}
	if(actionid != ACTION_USE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureActionCheck(reason: any actionid)");return 0;}
	Debug(DEBUG_END,"Antena_OnFurnitureActionCheck(reason: complete)");
	return 1;	
}

Antena_OnFurnitureActionSelect(playerid,actionid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureActionSelect(%d,%d,%d,%d,%d)",playerid,actionid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureActionSelect(reason: its not antena)");return 0;}
	if(actionid != ACTION_USE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureActionSelect(reason: any actionid)");return 0;}
	ShowPlayerModeDialog(playerid,DIALOG_ANTENA_ACTIONS,DIALOG_STYLE_LIST,"Антена","Сменить частоту","Выбрать","Выход");
	ShowHelpBoxForPlayer(playerid,HELPBOX_ANTENA_ACTIONS,ANTENA_INFO_ACTIONS);
	SetPlayerAction(playerid,ACTION_USE_ANTENA);
	Debug(DEBUG_END,"Antena_OnFurnitureActionSelect(reason: complete)");
	return 1;
}

Antena_OnFurnitureDialogRespose(playerid,dialogid,response,listitem,inputtext[],furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureDialogRespose(%d,%d,%d,%d,'%s',%d,%d,%d)",playerid,dialogid,response,listitem,inputtext,furnitureid,type,modeobjectid);
	switch(dialogid)
	{
		case DIALOG_ANTENA_NULL:
		{
			Debug(DEBUG_ACTION,"DIALOG_ANTENA_NULL");
			SetPlayerAction(playerid,ACTION_NONE);
			Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
			return 1;
		}
		case DIALOG_ANTENA_ACTIONS:
		{
			Debug(DEBUG_ACTION,"DIALOG_ANTENA_ACTIONS");
			if(!response) 
			{
				SetPlayerAction(playerid,ACTION_NONE);
				Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			if(!strcmp("Сменить частоту",inputtext))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,ANTENA_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_ANTENA_REQ,DIALOG_STYLE_INPUT,"Антена",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
		}
		case DIALOG_ANTENA_REQ:
		{
			Debug(DEBUG_ACTION,"DIALOG_ANTENA_REQ");
			if(!response) 
			{
				ShowPlayerModeDialog(playerid,DIALOG_ANTENA_ACTIONS,DIALOG_STYLE_LIST,"Антена","Сменить частоту","Выбрать","Выход");
				Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			new tmp = strval(inputtext);
			if((tmp <= 0) || (tmp > 300))
			{
				format(DialogString,sizeof(DialogString),"Текущая частота: %d MHz\nВведите новую частоту:",GetFurnitureVar(furnitureid,ANTENA_VAR_REQ));
				ShowPlayerModeDialog(playerid,DIALOG_ANTENA_REQ,DIALOG_STYLE_INPUT,"Антена",DialogString,"Готово","Выход");
				Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
				return 1;
			}
			SetFurnitureVar(furnitureid,ANTENA_VAR_REQ,tmp);
			format(DialogString,sizeof(DialogString),"Частота изменена на %d MHz",tmp);
			ShowPlayerModeDialog(playerid,DIALOG_ANTENA_NULL,DIALOG_STYLE_MSGBOX,"Антена",DialogString,"Выход","Выход");
			Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_END,"Antena_OnFurnitureDialogRespose(reason: complete)");
	return 0;
}

Antena_OnFurnitureMovingStart(playerid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureMovingStart(%d,%d,%d,%d)",playerid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureMovingStart(reason: its not antena)");return 0;}
	new Float:pos[3];
	GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
	SetSquareRangeNetworkStatus(GetSquareIdForXY(pos[0],pos[1]),2,GetFurnitureVar(furnitureid,ANTENA_VAR_REQ),false);
	Debug(DEBUG_END,"Antena_OnFurnitureMovingStart(reason: complete)");
	return 1;
}

Antena_OnFurnitureMovingEnd(playerid,furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureMovingEnd(%d,%d,%d,%d)",playerid,furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureMovingEnd(reason: its not antena)");return 0;}
	new Float:pos[3];
	GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
	SetSquareRangeNetworkStatus(GetSquareIdForXY(pos[0],pos[1]),2,GetFurnitureVar(furnitureid,ANTENA_VAR_REQ),true);
	Debug(DEBUG_END,"Antena_OnFurnitureMovingEnd(reason: complete)");
	return 1;
}

Antena_OnFurnitureDeath(furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureDeath(%d,%d,%d)",furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureDeath(reason: its not antena)");return 0;}
	new Float:pos[3];
	GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
	SetSquareRangeNetworkStatus(GetSquareIdForXY(pos[0],pos[1]),2,GetFurnitureVar(furnitureid,ANTENA_VAR_REQ),false);
	Debug(DEBUG_END,"Antena_OnFurnitureDeath(reason: complete)");
	return 1;
}

Antena_OnFurnitureLoaded(furnitureid,type,modeobjectid)
{
	Debug(DEBUG_START,"Antena_OnFurnitureLoaded(%d,%d,%d)",furnitureid,type,modeobjectid);
	if(type != FURNITURE_TYPE_ANTENA) {Debug(DEBUG_END,"Antena_OnFurnitureLoaded(reason: its not antena)");return 0;}
	new Float:pos[3];
	GetModeObjectPos(modeobjectid,pos[0],pos[1],pos[2]);
	SetSquareRangeNetworkStatus(GetSquareIdForXY(pos[0],pos[1]),2,GetFurnitureVar(furnitureid,ANTENA_VAR_REQ),true);
	Debug(DEBUG_END,"Antena_OnFurnitureLoaded(reason: complete)");
	return 1;
}