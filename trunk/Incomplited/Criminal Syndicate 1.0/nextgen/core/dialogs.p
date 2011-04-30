/*
*	Created:			08.01.10
*	Author:				009
*	Description:		Функции упрощения работы с диалоговыми окнами 
*/

#if defined core_dialogs_included
	#endinput
#endif

#define core_dialogs_included
#pragma library core_dialogs

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// enums
// --------------------------------------------------

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	ShowedDialog[MAX_PLAYERS char], // in need more then 256 - delete 'char' word
	ShowedDialogStyle[MAX_PLAYERS char];

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward OnModeDialogResponse(playerid,dialogid,response,listitem,inputtext[]);

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	Debug(DEBUG_START,"OnDialogResponse(%d,%d,%d,%d,'%s')",playerid,dialogid,response,listitem,inputtext);
	ShowedDialog{playerid} = INVALID_MODE_DIALOG_ID;
	OnModeDialogResponse(playerid,dialogid,response,listitem,inputtext);
	Debug(DEBUG_END,"OnDialogResponse(reason: complete)");
}

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native ShowPlayerModeDialog(playerid,dialogid,style,caption[],info[],button1[],button2[]);
native HidePlayerModeDialog(playerid);
native SetPlayerModeDialogListData(playerid,listitem,data);
native GetPlayerModeDialogListData(playerid,listitem);
native GetPlayerModeDialogStyle(playerid);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock ShowPlayerModeDialog(playerid,dialogid,style,caption[],info[],button1[],button2[])
{
	Debug(DEBUG_START,"ShowModePlayerDialog(%d,%d,%d,'%s','%s','%s','%s')",playerid,dialogid,style,caption,info,button1,button2);
	if(!strlen(info))
	{
		format(info,10,"Null");
		if(style == DIALOG_STYLE_LIST) style = DIALOG_STYLE_MSGBOX;
	}
	ShowPlayerDialog(playerid,dialogid,style,caption,info,button1,button2);
	ShowedDialog{playerid} = dialogid;
	ShowedDialogStyle{playerid} = style;
	Debug(DEBUG_END,"ShowModePlayerDialog(reason: complete)");
	return 1;
}

stock HidePlayerModeDialog(playerid)
{
	Debug(DEBUG_START,"HideModePlayerDialog(%d)",playerid);
	ShowPlayerDialog(playerid,-1,0,"","","","");
	ShowedDialog{playerid} = INVALID_MODE_DIALOG_ID;
	Debug(DEBUG_END,"HideModePlayerDialog(reason: complete)");
	return 1;
}

stock GetPlayerModeDialogStyle(playerid)
{
	Debug(DEBUG_SMALL,"GetPlayerModeDialogStyle(%d)",playerid);
	return ShowedDialogStyle{playerid};
}

stock SetPlayerModeDialogListData(playerid,listitem,data)
{
	Debug(DEBUG_START,"SetModePlayerDialogListData(%d,%d,%d)",playerid,listitem,data);
	static name[20];
	format(name,sizeof(name),"ListData_%d",listitem);
	SetPVarInt(playerid,name,data);
	Debug(DEBUG_END,"SetModePlayerDialogListData(reason: complete)");
	return 1;
}

stock GetPlayerModeDialogListData(playerid,listitem)
{
	Debug(DEBUG_START,"GetModePlayerDialogListData(%d,%d)",playerid,listitem);
	static name[20];
	format(name,sizeof(name),"ListData_%d",listitem);
	Debug(DEBUG_END,"GetModePlayerDialogListData(reason: complete)");
	return GetPVarInt(playerid,name);
}
