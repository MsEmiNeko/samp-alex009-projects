/*
*	Created:			01.06.10
*	Author:				009
*	Description:		Camera editor
*/

// --------------------------------------------------
// includes
// --------------------------------------------------
#include <a_samp>

// --------------------------------------------------
// defines
// --------------------------------------------------
#define VERSION         			"1.0"
#define GetPlayersCount()           pcount
#define START_SPEED                 0.1
#define SPEED_UP                    0.01
#define MAX_STRING                  128

// --------------------------------------------------
// news
// --------------------------------------------------
new pcount;
new Float:CurrentCameraPos[MAX_PLAYERS][3];
new Float:CurrentCameraVector[MAX_PLAYERS][3];
new Float:CurrentSpeed[MAX_PLAYERS];
new IsEditorUsed[MAX_PLAYERS char];
new tid;
new stmp[MAX_STRING];
new IsSaveUsed[MAX_PLAYERS char];

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward CE_Update();

// --------------------------------------------------
// publics
// --------------------------------------------------
public OnFilterScriptInit()
{
    print("Camera editor " VERSION " by 009 loaded.");
    tid = SetTimer("CE_Update",10,1);
}

public OnFilterScriptExit()
{
    print("Camera editor " VERSION " by 009 unloaded.");
	KillTimer(tid);
}

public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid)) return;
	// counter
    if(pcount < playerid) pcount = playerid;
    // null data
    IsEditorUsed{playerid} = 0;
    for(new i = 0;i < 3;i++)
    {
    	CurrentCameraPos[playerid][i] = 0.0;
    	CurrentCameraVector[playerid][i] = 0.0;
    }
    CurrentSpeed[playerid] = START_SPEED;
    IsSaveUsed{playerid} = 0;
}

public OnPlayerDisconnect(playerid,reason)
{
	if(IsPlayerNPC(playerid)) return;
	// counter
    if(pcount == playerid)
	{
		do pcount--;
		while((IsPlayerNPC(playerid) || (IsPlayerConnected(pcount) == 0)) && (pcount > 0));
	}
}

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	if(newkeys & KEY_LOOK_BEHIND)
	{
        if(IsEditorUsed{playerid})
        {
            // leave specate
        	TogglePlayerSpectating(playerid,false);
        	// on pos
        	SetPlayerPos(playerid,CurrentCameraPos[playerid][0],CurrentCameraPos[playerid][1],CurrentCameraPos[playerid][2]);
        	// flag
        	IsEditorUsed{playerid} = 0;
        }
        else
        {
            // get camera pos
            GetPlayerCameraPos(playerid,CurrentCameraPos[playerid][0],CurrentCameraPos[playerid][1],CurrentCameraPos[playerid][2]);
            GetPlayerCameraFrontVector(playerid,CurrentCameraVector[playerid][0],CurrentCameraVector[playerid][1],CurrentCameraVector[playerid][2]);
            // check vector and pos
            if((CurrentCameraVector[playerid][0] == 0.0) && (CurrentCameraVector[playerid][1] == 0.0) && (CurrentCameraVector[playerid][2] == 0.0))
            {
                GetPlayerPos(playerid,CurrentCameraPos[playerid][0],CurrentCameraPos[playerid][1],CurrentCameraPos[playerid][2]);
                CurrentCameraVector[playerid][0] = 1.0;
            }
            // go in specate
        	TogglePlayerSpectating(playerid,true);
        	// set camera
        	SetPlayerCameraPos(playerid,CurrentCameraPos[playerid][0],CurrentCameraPos[playerid][1],CurrentCameraPos[playerid][2]);
        	SetPlayerCameraLookAt(playerid,(CurrentCameraPos[playerid][0] + CurrentCameraVector[playerid][0]),(CurrentCameraPos[playerid][1] + CurrentCameraVector[playerid][1]),(CurrentCameraPos[playerid][2] + CurrentCameraVector[playerid][2]));
			// speed
			CurrentSpeed[playerid] = START_SPEED;
			// flag
        	IsEditorUsed{playerid} = 1;
        }
	}
}

public CE_Update()
{
	// all players
	for(new i = 0;i <= GetPlayersCount();i++)
	{
	    if(!IsPlayerConnected(i)) continue;
	    if(IsPlayerNPC(i)) continue;
	    if(!IsEditorUsed{i}) continue;
	    // check keys
		static ud,lr,k,ip;
		GetPlayerKeys(i,k,ud,lr);
		// null
		ip = 0;
		// speed control
		if(k & KEY_ANALOG_LEFT) CurrentSpeed[i] += SPEED_UP;
		else if(k & KEY_ANALOG_RIGHT) CurrentSpeed[i] -= SPEED_UP;
		// show coords & save
		if(k & KEY_WALK)
		{
		    if(!IsSaveUsed{i})
		    {
			    new File:save = fopen("CameraEditor.txt",io_append);
			    format(stmp,sizeof(stmp),"SetPlayerCameraPos(playerid,%f,%f,%f);\r\n",CurrentCameraPos[i][0],CurrentCameraPos[i][1],CurrentCameraPos[i][2]);
				SendClientMessage(i,0xFFFFFFFF,stmp);
				fwrite(save,stmp);
				format(stmp,sizeof(stmp),"SetPlayerCameraLookAt(playerid,%f,%f,%f);\r\n",(CurrentCameraPos[i][0] + CurrentCameraVector[i][0]),(CurrentCameraPos[i][1] + CurrentCameraVector[i][1]),(CurrentCameraPos[i][2] + CurrentCameraVector[i][2]));
				SendClientMessage(i,0xFFFFFFFF,stmp);
				fwrite(save,stmp);
				fclose(save);
				IsSaveUsed{i} = 1;
			}
		}
		else if(IsSaveUsed{i}) IsSaveUsed{i} = 0;
		// front
		if(ud == KEY_UP)
		{
			// moving by vector
			CurrentCameraPos[i][0] += (CurrentSpeed[i] * CurrentCameraVector[i][0]);
			CurrentCameraPos[i][1] += (CurrentSpeed[i] * CurrentCameraVector[i][1]);
			CurrentCameraPos[i][2] += (CurrentSpeed[i] * CurrentCameraVector[i][2]);
			// is pressed
			ip = 1;
		}
		else if(ud == KEY_DOWN) // back
		{
			// moving by vector
			CurrentCameraPos[i][0] -= (CurrentSpeed[i] * CurrentCameraVector[i][0]);
			CurrentCameraPos[i][1] -= (CurrentSpeed[i] * CurrentCameraVector[i][1]);
			CurrentCameraPos[i][2] -= (CurrentSpeed[i] * CurrentCameraVector[i][2]);
			// is pressed
			ip = 1;
		}
		// rotate left
		if(lr == KEY_LEFT)
		{
		    // rotate vector around Z
			RotateVectorAroundVector(CurrentCameraVector[i][0],CurrentCameraVector[i][1],CurrentCameraVector[i][2],0.0,0.0,1.0,CurrentSpeed[i]);
			// is pressed
			ip = 1;
		}
		else if(lr == KEY_RIGHT) // rotate right
		{
		    // rotate vector around Z
			RotateVectorAroundVector(CurrentCameraVector[i][0],CurrentCameraVector[i][1],CurrentCameraVector[i][2],0.0,0.0,1.0,-CurrentSpeed[i]);
			// is pressed
			ip = 1;
		}
		// rotate up
		if(k == KEY_SPRINT)
		{
		    // change vector
			VectorZControl(CurrentCameraVector[i][0],CurrentCameraVector[i][1],CurrentCameraVector[i][2],(CurrentSpeed[i] / 50));
			// is pressed
			ip = 1;
		}
		else if(k == KEY_CROUCH) // rotate down
		{
		    // change vector
			VectorZControl(CurrentCameraVector[i][0],CurrentCameraVector[i][1],CurrentCameraVector[i][2],-(CurrentSpeed[i] / 50));
			// is pressed
			ip = 1;
		}
		
		if(!ip) continue;
		
	    // set camera
		SetPlayerCameraPos(i,CurrentCameraPos[i][0],CurrentCameraPos[i][1],CurrentCameraPos[i][2]);
       	SetPlayerCameraLookAt(i,(CurrentCameraPos[i][0] + CurrentCameraVector[i][0]),(CurrentCameraPos[i][1] + CurrentCameraVector[i][1]),(CurrentCameraPos[i][2] + CurrentCameraVector[i][2]));
	}
}

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock RotateVectorAroundVector(&Float:vx,&Float:vy,&Float:vz,Float:rx,Float:ry,Float:rz,Float:angle)
{
	static Float:cosTheta;
	static Float:sinTheta;
	static Float:temp_vec[3];
	
	cosTheta = floatcos(angle,grades);
    sinTheta = floatsin(angle,grades);
    
	// Найдем новую позицию X для вращаемой точки
	temp_vec[0] = (cosTheta + (1 - cosTheta) * rx * rx) * vx;
	temp_vec[0] += ((1 - cosTheta) * rx * ry - rz * sinTheta) * vy;
	temp_vec[0] += ((1 - cosTheta) * rx * rz + ry * sinTheta) * vz;

	// Найдем позицию Y
	temp_vec[1]  = ((1 - cosTheta) * rx * ry + rz * sinTheta) * vx;
	temp_vec[1] += (cosTheta + (1 - cosTheta) * ry * ry) * vy;
	temp_vec[1] += ((1 - cosTheta) * ry * rz - rx * sinTheta) * vz;

	// И позицию Z
	temp_vec[2]  = ((1 - cosTheta) * rx * rz - ry * sinTheta) * vx;
	temp_vec[2] += ((1 - cosTheta) * ry * rz + rx * sinTheta) * vy;
	temp_vec[2] += (cosTheta + (1 - cosTheta) * rz * rz) * vz;
	
	// set new value
	vx = temp_vec[0];
	vy = temp_vec[1];
	vz = temp_vec[2];
}

stock VectorZControl(&Float:vx,&Float:vy,&Float:vz,Float:value)
{
	static Float:len;
	// change vector
	vz += value;
	// check max
	if((vz >= 0.99) || (vz <= -0.99))
	{
		vz -= value;
		return;
	}
	// change to 1.0 len
	len = floatsqroot((vx * vx) + (vy * vy) + (vz * vz));
	vx /= len;
	vy /= len;
	vz /= len;
}
