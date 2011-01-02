/*
*	Created:			01.06.10
*	Author:				009
*	Description:        Invisible
*/

// --------------------------------------------------
// includes
// --------------------------------------------------
#include <a_samp>

// --------------------------------------------------
// defines
// --------------------------------------------------
#define VERSION		"1.0"
#define INVISE_KEY    	KEY_WALK

// --------------------------------------------------
// news
// --------------------------------------------------
new InviseStage[MAX_PLAYERS char];
new Float:PlayerPos[MAX_PLAYERS][3];

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnFilterScriptInit()
{
	print("Invisible " VERSION " by 009 loaded.");
}

public OnFilterScriptExit()
{
	print("Invisible " VERSION " by 009 unloaded.");
}

public OnPlayerConnect(playerid)
{
	InviseStage{playerid} = 0;
}

public OnPlayerUpdate(playerid)
{
	switch(InviseStage{playerid})
	{
		case 0: return 1;
		case 1:
		{
			SetPlayerPos(playerid,PlayerPos[playerid][0],PlayerPos[playerid][1],PlayerPos[playerid][2]);
			InviseStage{playerid} = 2;
			return 0;
		}
		case 2: return 0;
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	if(newkeys & INVISE_KEY)
	{
		if(!InviseStage{playerid})
		{
			GetPlayerPos(playerid,PlayerPos[playerid][0],PlayerPos[playerid][1],PlayerPos[playerid][2]);
			SetPlayerPos(playerid,3000.0,3000.0,3000.0);
			InviseStage{playerid} = 1;
		}
		else
		{
			InviseStage{playerid} = 0;
		}
	}
}
