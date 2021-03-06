/*
*	Created:			12.08.09
*	Aurthor:			009
*	Last Modifed:		05.09.09
*
*	05.09.09:
*	1.������� MAX_PLAYERS �� GetMaxPlayer() � ������
*/

#if defined _gps_included
	#endinput
#endif

#define _gps_included
#pragma library gps

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward GPS_OnGameModeInit();
forward GPS_OnPlayerSpawn(playerid);
forward GPS_OnPlayerDisconnect(playerid,reason);
forward GPS_OnPlayerLogin(playerid);
forward GPS_OnPlayerCommandText(playerid, text[]);
forward NewPlayerGPSid(playerid);
forward DeleteActorFromGPS(playerid);
forward UpdatePlayerMarker(playerid);
// --------------------------------------------------
// publics
// --------------------------------------------------

public GPS_OnGameModeInit()
{
	print("GPS system loaded.");
}

public GPS_OnPlayerSpawn(playerid)
{
	SetTimerEx("UpdatePlayerMarker",200,0,"d",playerid);
}

public GPS_OnPlayerDisconnect(playerid,reason)
{
	for(new id = 0;id < GetMaxPlayer();id++)
	{
		if(!IsPlayerConnected(id)) continue;
		Player[id][pShowenPlayers][playerid] = false;
	}
}

public UpdatePlayerMarker(playerid)
{
	for(new id = 0;id < GetMaxPlayer();id++)
	{
		if(!IsPlayerConnected(id)) continue;
		if(Player[playerid][pShowenPlayers][id] == true) SetPlayerMarkerForPlayer(playerid,id,COLOUR_PLAYER);
		if(Player[id][pShowenPlayers][playerid] == true) SetPlayerMarkerForPlayer(id,playerid,COLOUR_PLAYER);
	}
}

public GPS_OnPlayerLogin(playerid)
{
	MySQL_LoadGPSInfoForPlayer(playerid);
	MySQL_LoadGPSInfoForOthers(playerid);
}

public GPS_OnPlayerCommandText(playerid, text[])
{
	new idx;
	new cmd[20],tmp[MAX_STRING];
	cmd = strtok(text," ",idx);

	if(!strcmp(cmd,"/gps",true))
	{
		cmd = strtok(text," ",idx);
		if(!strcmp(cmd,"add",true))
		{
			new gpsid = strval(strtok(text," ",idx));
			for(new id = 0;id < GetMaxPlayer();id++)
			{
				if(!IsPlayerConnected(id)) continue;
				if(Player[id][pGPSid] != gpsid) continue;
				Player[playerid][pShowenPlayers][id] = true;
				SetPlayerMarkerForPlayer(playerid,id,COLOUR_PLAYER);
			}
			return MySQL_AddGPSInfo(playerid,gpsid);
		}
		if(!strcmp(cmd,"del",true))
		{
			new gpsid = strval(strtok(text," ",idx));
			for(new id = 0;id < GetMaxPlayer();id++)
			{
				if(!IsPlayerConnected(id)) continue;
				if(Player[id][pGPSid] != gpsid) continue;
				Player[playerid][pShowenPlayers][id] = false;
				SetPlayerMarkerForPlayer(playerid,id,(COLOUR_PLAYER & 0xFFFFFF00));
			}
			return MySQL_DeleteGPSInfo(playerid,gpsid);
		}
		if(!strcmp(cmd,"help",true))
		{
			format(tmp,sizeof(tmp),"*%s -> ������ -> GPS",GAMEMODE_NAME);
			SendMessage(playerid,COLOUR_GZ,tmp);
			SendMessage(playerid,COLOUR_GZ,"*������� ����� - ����� GPS,GPS ��������� ������ GPS ���� �����,� ��� ������ ����� ���������� �� ����� GPS");
			SendMessage(playerid,COLOUR_GZ,"*��� �� ��� GPS ����� ���������� GPS-id, �� ������ �������� ����� ���� GPS-id � �� ������ �������� ��� � ���� GPS");
			SendMessage(playerid,COLOUR_GZ,"*�������� '/gps add <gps-id>' ����� ���� �� ����� ������ ��� �� ���� GPS,��� �� ����� ������� ����������� gps-id");
			SendMessage(playerid,COLOUR_GZ,"*�� ������ GPS �������� '/gps del <gps-id>'");	
			return 1;
		}
	}
	return 0;
}

public NewPlayerGPSid()
{
	new randGPSid = 1000 + random(8999);
	while(MySQL_FindGPSid(randGPSid)) randGPSid = 1000 + random(8999);
	return randGPSid;
}

public DeleteActorFromGPS(playerid)
{
	for(new id = 0;id < GetMaxPlayer();id++)
	{
		if(!IsPlayerConnected(id)) continue;
		Player[id][pShowenPlayers][playerid] = false;
		SetPlayerMarkerForPlayer(id,playerid,(COLOUR_PLAYER & 0xFFFFFF00));
		Player[playerid][pShowenPlayers][id] = false;
		SetPlayerMarkerForPlayer(playerid,id,(COLOUR_PLAYER & 0xFFFFFF00));
	}
	MySQL_DeleteGPSinfo(playerid);
}