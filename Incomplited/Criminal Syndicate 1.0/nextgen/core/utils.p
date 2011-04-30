/*
*	Created:			21.01.10
*	Author:				009
*	Description:		�������� ����-������� 
*/

#if defined core_utils_included
	#endinput
#endif

#define core_utils_included
#pragma library core_utils

// --------------------------------------------------
// defines
// --------------------------------------------------
#define GetDistanceBetweenCoords(%1,%2,%3,%4,%5,%6) floatsqroot((%4 - %1)*(%4 - %1) + (%5 - %2)*(%5 - %2) + (%6 - %3)*(%6 - %3))
#define MoveCoordsOnAngleByDistance(%1,%2,%3,%4) \
	%1 += (%4 * floatsin(-%3, degrees)); \
	%2 += (%4 * floatcos(-%3, degrees))
#define fixchars(%1) 			for(new charfixloop=0;charfixloop<strlen(%1);charfixloop++)if(%1[charfixloop]<0)%1[charfixloop]+=256
#define nullstr(%1) 			%1[0] = 0
#define HELP_BOX_SHOW_TIME      10_000

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
// news
// --------------------------------------------------
static
	MaxPlayerId,
	PlayerControllableState[MAX_PLAYERS char],
	IsHelpBoxShowed[MAX_PLAYERS char],
	HelpBoxTimer[MAX_PLAYERS],
	Text:HelpBoxTexts[MAX_PLAYERS][2],
	Float:Citys[][4] = {
		{44.60,-2892.90,2997.00,-768.00},
		{-2997.40,-1115.50,-1213.90,1659.60},
		{869.40,596.30,2997.00,2993.80}
	};

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward HidePlayerHelpBox(playerid);

// --------------------------------------------------
// publics
// --------------------------------------------------
public HidePlayerHelpBox(playerid)
{
	Debug(DEBUG_START,"HidePlayerHelpBox(%d)",playerid);
	TextDrawHideForPlayer(playerid,HelpBoxTexts[playerid][0]);
	TextDrawHideForPlayer(playerid,HelpBoxTexts[playerid][1]);
	TextDrawDestroy(HelpBoxTexts[playerid][0]);
	TextDrawDestroy(HelpBoxTexts[playerid][1]);
	IsHelpBoxShowed{playerid} = 0;
	KillTimer(HelpBoxTimer[playerid]);
	Debug(DEBUG_END,"HidePlayerHelpBox(reason: complete)");
}

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native StripNL(str[]);
native GetMaxPlayerId();
native GetDistanceBetweenCoords(Float:X1,Float:Y1,Float:Z1,Float:X2,Float:Y2,Float:Z2);
native TogglePlayerControllableEx(playerid,bool:toggle);
native IsPlayerControllable(playerid);
native MoveCoordsOnAngleByDistance(Float:X,Float:Y,Float:angle,Float:distance);
native ShowHelpBoxForPlayer(playerid,helpboxid,info[]);
native GetPlayerClosestPlayer(playerid);
native fixchars(string[]);
native nullstr(string[]);
native IsPlayerInRangeOfPlayer(playerid,Float:range,pid);
native PreLoadAnimation(playerid,animlib[]);
native GetPlayerCity(playerid);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock StripNL(str[]) // by Y_Less
{
	new l = strlen(str);
	while (l-- && str[l] <= ' ') str[l] = '\0';
}

stock GetMaxPlayerId()
{
	return MaxPlayerId;
}

stock GetPlayerClosestPlayer(playerid)
{
	Debug(DEBUG_START,"GetPlayerClosestPlayer(%d)",playerid);
	new pid = INVALID_PLAYER_ID,
		Float:distance = 69000.0,
		Float:tmp[7];
	GetPlayerPos(playerid,tmp[0],tmp[1],tmp[2]);
	for(new i = 0;i <= GetMaxPlayerId();i++)
	{
		if(i == playerid) continue;
		if(!IsPlayerConnected(i)) continue;
		if(!IsPlayerStreamedIn(i,playerid)) continue;
		GetPlayerPos(i,tmp[3],tmp[4],tmp[5]);
		tmp[6] = GetDistanceBetweenCoords(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]);
		if(distance < tmp[6]) continue;
		distance = tmp[6];
		pid = i;
	}
	Debug(DEBUG_END,"GetPlayerClosestPlayer(reason: complete)");
	return pid;
}

stock IsPlayerInRangeOfPlayer(playerid,Float:range,pid)
{
	Debug(DEBUG_START,"IsPlayerInRangeOfPlayer(%d,%f,%d)",playerid,range,pid);
	new Float:tmp[3];
	GetPlayerPos(pid,tmp[0],tmp[1],tmp[2]);
	Debug(DEBUG_END,"IsPlayerInRangeOfPlayer(reason: complete)");
	return IsPlayerInRangeOfPoint(playerid,range,tmp[0],tmp[1],tmp[2]);
}

stock PreLoadAnimation(playerid,animlib[])
{
	return ApplyAnimation(playerid,animlib,"",0.0,0,0,0,0,0);
}

stock GetPlayerCity(playerid)
{
	Debug(DEBUG_START,"GetPlayerCity(%d)",playerid);
	new Float:X,
		Float:Y,
		Float:Z;
	GetPlayerPos(playerid,X,Y,Z);
	for(new i = 0;i < sizeof(Citys);i++)
	{
		if((X > Citys[i][0]) && (X < Citys[i][2]) && (Y > Citys[i][1]) && (Y < Citys[i][3])) {Debug(DEBUG_END,"GetPlayerCity(reason: complete)");return i;}
	}
	Debug(DEBUG_END,"GetPlayerCity(reason: complete)");
	return -1;
}

stock IsPlayerControllable(playerid)
{
	return PlayerControllableState{playerid};
}

stock TogglePlayerControllableEx(playerid,bool:toggle)
{
	PlayerControllableState{playerid} = toggle;
	return TogglePlayerControllable(playerid,toggle);
}

stock ShowHelpBoxForPlayer(playerid,helpboxid,info[])
{
	Debug(DEBUG_START,"ShowHelpBoxForPlayer(%d,%d,'%s')",playerid,helpboxid,info);
	if(IsHelpBoxShowed{playerid} == 1) HidePlayerHelpBox(playerid);
	new Float:sizey = 1.0 + 1.5; // 1.0 - ������ � ����� ������� �� ����
	new pos;
	while((pos = strfind(info,"~n~",false,pos)) != -1)
	{
		sizey += 1.5;
		pos += 3;
	}
	HelpBoxTexts[playerid][0] = TextDrawCreate(15.0,100.0,"_");
	TextDrawUseBox(HelpBoxTexts[playerid][0],1);
	TextDrawTextSize(HelpBoxTexts[playerid][0],200.0,0.0);
	TextDrawLetterSize(HelpBoxTexts[playerid][0],0.0,sizey);
	TextDrawBoxColor(HelpBoxTexts[playerid][0],0x000000FF);
	HelpBoxTexts[playerid][1] = TextDrawCreate(15.5,100.5,info);
	TextDrawShowForPlayer(playerid,HelpBoxTexts[playerid][0]);
	TextDrawShowForPlayer(playerid,HelpBoxTexts[playerid][1]);
	IsHelpBoxShowed{playerid} = 1;
	HelpBoxTimer[playerid] = SetTimerEx("HidePlayerHelpBox",HELP_BOX_SHOW_TIME,0,"d",playerid);
	Debug(DEBUG_END,"ShowHelpBoxForPlayer(reason: complete)");
	return 1;
}

stock RusToGame(string[])
{
	new result[128];
	new maxl = strlen(string);
	maxl = (maxl > 128?128:maxl);
	for(new i; i < maxl; i++)
	{
		if(string[i] < 0) string[i] += 256;
		switch(string[i])
		{
			case '�': result[i] = 'a';
			case '�': result[i] = 'A';
			case '�':result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'e';
			case '�': result[i] = 'E';
			case '�': result[i] = 'e';
			case '�': result[i] = 'E';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'k';
			case '�': result[i] = 'K';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'M';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'o';
			case '�': result[i] = 'O';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'p';
			case '�': result[i] = 'P';
			case '�': result[i] = 'c';
			case '�': result[i] = 'C';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'y';
			case '�': result[i] = 'Y';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = 'x';
			case '�': result[i] = 'X';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			case '�': result[i] = '�';
			default: result[i] = string[i];
		}
	}
	return result;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Utils_OnPlayerConnect(playerid)
{
	Debug(DEBUG_START,"Core_Utils_OnPlayerConnect(%d)",playerid);
	if(MaxPlayerId < playerid) MaxPlayerId = playerid;
	Debug(DEBUG_END,"Core_Utils_OnPlayerConnect (reason: complete");
}

Core_Utils_OnPlayerDisconnect(playerid,reason)
{
	Debug(DEBUG_START,"Core_Utils_OnPlayerDisconnect(%d,%d)",playerid,reason);
	if(MaxPlayerId == playerid) 
	{
		do MaxPlayerId--;
		while((IsPlayerConnected(MaxPlayerId) == 0) && (MaxPlayerId > 0));
	}
	Debug(DEBUG_END,"Core_Utils_OnPlayerDisconnect (reason: complete");
}
