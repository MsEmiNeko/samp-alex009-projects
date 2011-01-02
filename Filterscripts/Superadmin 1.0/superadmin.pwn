/*
*	Created:			02.07.10
*	Author:				009
*	Description:		Superman - admin
*/

// --------------------------------------------------
// includes
// --------------------------------------------------
#include <a_samp>

// --------------------------------------------------
// defines
// --------------------------------------------------
#define VERSION         "1.0"

// --------------------------------------------------
// news
// --------------------------------------------------
new Float:speed[MAX_PLAYERS],
	bool:fly[MAX_PLAYERS];

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnFilterScriptInit()
{
	print("SuperAdmin " VERSION " by 009 loaded");
}

public OnFilterScriptExit()
{
	print("SuperAdmin " VERSION " by 009 unloaded");
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerAdmin(playerid))
	{
		new k,w,j;
		GetPlayerKeys(playerid,k,w,j);
		if(k & KEY_FIRE)
		{
		    if(!fly[playerid])
			{
			    fly[playerid] = true;
			    speed[playerid] = 1.0;
			}
			if(w == KEY_UP) speed[playerid] += 0.1;
			else if(w == KEY_DOWN) speed[playerid] -= 0.1;
		    // speed
		    new Float:x,Float:y,Float:z;
			GetPlayerCameraFrontVector(playerid,x,y,z);
			SetPlayerVelocity(playerid,x * speed[playerid],y * speed[playerid],z * speed[playerid]);
			// angle
			z = atan2(y,x) + 270.0;
			if(z >= 360.0) z -= 360.0;
			SetPlayerFacingAngle(playerid,z);
			// anim
			ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel",4.1,1,1,1,1,1);
			// health
			SetPlayerHealth(playerid,999.0);
		}
		else if(fly[playerid])
		{
		    fly[playerid] = false;
		    SetPlayerHealth(playerid,150.0);
		}
	}
	return 1;
}
