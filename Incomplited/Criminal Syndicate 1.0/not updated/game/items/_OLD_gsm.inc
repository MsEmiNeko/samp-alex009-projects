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
+	��������:
+	0 - �� ����
+	1 - ������������ �� ������
+	2 - �� ������� � �������
+
+	������:
+	0 - �� ����
+	1 - ���� �� ���������� � ����������
+	2 - ������������ �� ������
+	3 - �� ������� � �������
+
+	�����:
+	0 - �����
+	1 - ����
+	2 - �� ����
+
+	������:
+	0 - �� �����
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
	// ���� � ��������� �� ����� ���������� ����� � ��������� ����� - ���������� ������
	if(GetPlayerCurrentPremise(playerid) != 0) GetPremiseEnterPos(GetPlayerCurrentPremise(playerid),Pos_pl[0],Pos_pl[1],Pos_pl[2]);
	else GetPlayerPos(playerid,Pos_pl[0],Pos_pl[1],Pos_pl[2]);
	for(new i = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);i < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;i++)
	{
		if(!IsActiveObjectValid(i)) continue;
		// ���� ���� �� ����� ���� �� �������
		if(GetActiveObjectParam(i,GSM_ANTENA_NETWORK_ID) != NetworkId) continue;
		// ���� ����� ��� �� �������
		if(GetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED) == 0) continue;
		// ����� ���������� ��� ����������� ��������
		GetModeObjectPos(GetActiveObjectModeObjectId(i),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
		// ���� � ��������� �� ����� ���������� ����� � ���������
		if(premise != 0) GetPremiseEnterPos(premise,Pos[0],Pos[1],Pos[2]);
		// ���� �� �� � ���� �� ������� ���� ������
		if(!IsPosInRangeOfPoint(Pos_pl[0],Pos_pl[1],Pos_pl[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
		return 1;
	}
	return 0;
}

public PlayerUseMobile(playerid,mobileitemid)
{
	GSM_Player[playerid][pUsingMobileItemId] = mobileitemid;
	// ���� �� �����
	if(strval(GetItemVar(mobileitemid,0)) == 0) return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"���������","�������� SIM","������","�����");
	// ������ �� ������ ������
	if((GSM_Player[playerid][pInterlocutorId] != INVALID_PLAYER_ID) && (GSM_Player[playerid][pActiveMobileItemId] == mobileitemid)) return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"���������","��������","������","�����");
	// ������� ��������
	return ShowPlayerDialog(playerid,DIALOG_GSM_MOBILE_ACTIONS,DIALOG_STYLE_LIST,"���������","���������\n�������� SMS\n�������� SMS\n�������� SIM","������","�����");
}

public CheckNetworkAntenes(networkid)
{
	new premise,
		Float:Pos[6],
		Float:Pos_tmp[3],
		i,j;
	// ������ ��� ������
	for(i = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);i < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;i++)
	{
		if(!IsActiveObjectValid(i)) continue;
		// ���� ������ ����������� �� �������
		if(IsObjectMoving(GetActiveObjectModeObjectId(i))) return 0;
		// ���� ���� �� ���� �� ����������
		if(GetActiveObjectParam(i,GSM_ANTENA_NETWORK_ID) != networkid) continue;
		// ���� ����� ���� ���� ����������
		if(GetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED) == 1) continue;
		// ����� ���������� ��� ����������� ��������
		GetModeObjectPos(GetActiveObjectModeObjectId(i),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
		// ���� � ��������� �� ����� ���������� ����� � ���������
		if(premise != 0) GetPremiseEnterPos(premise,Pos[0],Pos[1],Pos[2]);
		// ������ ��� ������ ����� ����� �� ��� � ���� ����
		for(j = GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,0);j < GetActiveObjectsCount(ACTION_SELECT_GSM_ANTENA,1) + 1;j++)
		{
			if(!IsActiveObjectValid(j)) continue;
			// ���� ������ ����������� �� �������
			if(IsObjectMoving(GetActiveObjectModeObjectId(j))) return 0;
			// ���� ���� �� ���� �� ����������
			if(GetActiveObjectParam(j,GSM_ANTENA_NETWORK_ID) != networkid) continue;
			// ���� ����� ��� ���� ����������
			if(GetActiveObjectParam(j,GSM_ANTENA_IS_CONNECTED) == 0) continue;
			// ����� ���������� ��� ����������� ��������			
			GetModeObjectPos(GetActiveObjectModeObjectId(j),premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],Pos[3],Pos[4],Pos[5]);
			// ���� � ��������� �� ����� ���������� ����� � ���������
			if(premise != 0) GetPremiseEnterPos(premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2]);
			// ���� ������ �� � ���� �������� �� ����������
			if(!IsPosInRangeOfPoint(Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
			// ����� ����,��������� ��� ������
			SetActiveObjectParam(i,GSM_ANTENA_IS_CONNECTED,1);
			return 1;
		}
		// ����� �� ������ �� �������,���� ��������
		for(j = GetActiveObjectsCount(ACTION_SELECT_GSM_TERMINAL,0);j < GetActiveObjectsCount(ACTION_SELECT_GSM_TERMINAL,1) + 1;j++)
		{
			if(!IsActiveObjectValid(j)) continue;
			// ���� �������� ����������� �� �������
			if(IsObjectMoving(GetActiveObjectModeObjectId(j))) return 0;
			// ���� �� ���� ���� �� ����������
			if(GetActiveObjectParam(j,GSM_TERMINAL_NETWORK_ID) != networkid) continue;
			// ����� ���������� ��� ����������� ��������
			GetModeObjectPos(GetActiveObjectModeObjectId(j),premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],Pos[3],Pos[4],Pos[5]);
			// �������� � ��������� �� ��������,���� �� �� ���������� ���������� �� ���������� ����� � ���������
			if(premise != 0) GetPremiseEnterPos(premise,Pos_tmp[0],Pos_tmp[1],Pos_tmp[2]);
			// ���� �������� �� � ���� �������� �� ����������
			if(!IsPosInRangeOfPoint(Pos_tmp[0],Pos_tmp[1],Pos_tmp[2],GSM_ANTENA_DISTANCE,Pos[0],Pos[1],Pos[2])) continue;
			// ����� ����,��������� ��� ������
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
		// ���� ���� �� ���� �� ����������
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
	AddActionSelectRow(RusToGame("�����������~n~������"),ACTION_SELECT_MOVE_ANTENA);
	AddActionSelectRow(RusToGame("�����������~n~��������"),ACTION_SELECT_MOVE_TERMINAL);
	AddActionSelectRow(RusToGame("����������~n~����������"),ACTION_SELECT_TERMINAL_SETTINGS);
	AddActionSelectRow(RusToGame("����������~n~�������"),ACTION_SELECT_ANTENA_SETTINGS);
	print("GSM system loaded.");
}

stock GSM_OnPlayerActionSelectCheck(playerid,actionid)
{
	switch(actionid)
	{
		// ����������� ������
		case ACTION_SELECT_MOVE_ANTENA:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� ����� �� � ��������� �������
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// ���� �� �� ������
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_ANTENA) return 0;
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;	
			return 1;
		}
		// ��������� ������
		case ACTION_SELECT_ANTENA_SETTINGS:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� ����� �� � ��������� �������
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// ���� �� �� ��������
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_ANTENA) return 0;
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;			
			return 1;
		}
		// ����������� ���������
		case ACTION_SELECT_MOVE_TERMINAL:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� ����� �� � ��������� �������
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// ���� �� �� ��������
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_TERMINAL) return 0;
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
			if(GetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING) == 1) return 0;	
			return 1;
		}
		// ��������� ���������
		case ACTION_SELECT_TERMINAL_SETTINGS:
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� ����� �� � ��������� �������
			if(aoid == INVALID_ACTIVE_OBJECT_ID) return 0;
			// ���� �� �� ��������
			if(GetActiveObjectAction(aoid) != ACTION_SELECT_GSM_TERMINAL) return 0;
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
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
		// ����������� ������
		case ACTION_SELECT_MOVE_ANTENA: return ShowPlayerDialog(playerid,DIALOG_ANTENA_MOVING,DIALOG_STYLE_LIST,"����������� ������","����������� �� ������� ����������\n������� ���������","�������","������");
		// ��������� ������
		case ACTION_SELECT_ANTENA_SETTINGS: 
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
			if(GetActiveObjectParam(aoid,GSM_ANTENA_IS_USING) == 1) return 0;
			// ������ ������ "������������"
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_USING,1);
			return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"���������� �������","�������� ������� ���������\n��������� ������� ���������","�������","������");
		}
		// ����������� ���������
		case ACTION_SELECT_MOVE_TERMINAL: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_MOVING,DIALOG_STYLE_LIST,"����������� ��������","����������� �� ������� ����������\n������� ���������","�������","������");
		// ��������� ���������
		case ACTION_SELECT_TERMINAL_SETTINGS: 
		{
			new aoid = GetPlayerActiveObject(playerid);
			// ���� �� ����������
			if(IsObjectMoving(GetActiveObjectModeObjectId(aoid))) return 0;
			// ���� �� ������������
			if(GetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING) == 1) return 0;
			// ������ ������ "������������"
			SetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING,1);
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����","�������","������");
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
			// ������ ������������� �� ����,����� ������ ������ �� ����������� ��� ���������� ����
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID,-networkid);
			// �������� ������� �����
			ResetAntenesStatusWithNetwork(networkid);
			// ������� ���� ���� ������� ��� ��������� � ���� �������� ���������� ������ "�����"
			while(CheckNetworkAntenes(networkid)) {}
			switch(listitem)
			{
				// �� ������� ����������
				case 0: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),false);
				// ����������� �������
				case 1: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),true);
			}
			return 0;
		}
		case DIALOG_TERMINAL_MOVING:
		{
			if(!response) return 1;
			switch(listitem)
			{
				// �� ������� ����������
				case 0: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),false);
				// ����������� �������
				case 1: return PlayerMoveObject(playerid,GetPlayerModeObjectId(playerid),true);
			}
			return 0;
		}
		case DIALOG_ANTENA_SETTINGS_LAST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"���������� �������","�������� ������� ���������\n��������� ������� ���������","�������","������");
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
				// �������� �������
				case 0: 
				{
					format(string,sizeof(string),"������� ��������� ����� %dMHz",((GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID) + 43) * 10 ));
					return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"���������� ������� [������� ���������]",string,"������","�����");
				}
				// ��������� �������
				case 1: return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS_MHZ,DIALOG_STYLE_INPUT,"���������� ������� [������� ���������]","������� ����� �������:","������","�����");
			}
			return 0;
		}
		case DIALOG_ANTENA_SETTINGS_MHZ:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"���������� �������","�������� ������� ���������\n��������� ������� ���������","�������","������");
			new networkid = (strval(inputtext) / 10) - 43;
			if((networkid < 0) || (networkid > 100)) return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"���������� �������","�������� ������� ���������\n��������� ������� ���������","�������","������");
			SetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID,networkid);
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BASE_ID),UPDATE_AO_INFO_VAR,GSM_ANTENA_NETWORK_ID,networkid);			
			return ShowPlayerDialog(playerid,DIALOG_ANTENA_SETTINGS,DIALOG_STYLE_LIST,"���������� �������","�������� ������� ���������\n��������� ������� ���������","�������","������");
		}
		case DIALOG_TERMINAL_SETTINGS_LAST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
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
				// ������� ���������
				case 0: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_1,DIALOG_STYLE_LIST,"���������� ���������� [������� ���������]","������� ���������\n�������� ����\n���� ������� ���������\n���� 1 SMS ���������","�������","������");
				// ��������� SIM-����
				case 1: return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_2,DIALOG_STYLE_INPUT,"���������� ���������� [��������� SIM-����]","������� ����������:","����������","������");
				// ������� SIM-�����
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
				// ������� ���������
				case 0: 
				{
					format(string,sizeof(string),"������� ��������� ����� %dMHz",((GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_NETWORK_ID) + 43) * 10 ));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"���������� ���������� [������� ���������]",string,"������","�����");
				}
				// �������� ����
				case 1: 
				{
					format(string,sizeof(string),"������� �������� ����: %s\n������� �����:",MySQL_GetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NNAME,DIALOG_STYLE_INPUT,"���������� ���������� [�������� ����]",string,"������","�����");
				}
				// ���� ������� ���������
				case 2:
				{
					format(string,sizeof(string),"������� ���� ������� ���������: %d$\n������� �����:",MySQL_GetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NCCOST,DIALOG_STYLE_INPUT,"���������� ���������� [���� ������� ���������]",string,"������","�����");
				}
				// ���� 1 ���
				case 3:
				{
					format(string,sizeof(string),"������� ���� 1 SMS ���������: %d$\n������� �����:",MySQL_GetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
					return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NSCOST,DIALOG_STYLE_INPUT,"���������� ���������� [���� 1 SMS ���������]",string,"������","�����");
				}
			}
			return 0;
		}
		case DIALOG_TERMINAL_SETTINGS_2:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 50)) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_2,DIALOG_STYLE_INPUT,"���������� ���������� [��������� SIM-����]","������� ����������:","����������","������");
			new pnumber,
				tmp_int;
			for(new i = 0;i < strval(inputtext);i++)
			{
				pnumber = random(899999) + 100000;
				while(GetItemWhithVar(ITEM_TYPE_SIMCARD,GSM_SIM_NUMBER,inttostr(pnumber),tmp_int)) pnumber = random(899999) + 100000;
				tmp_int = CreateItem(ITEM_TYPE_SIMCARD,"ddd",pnumber,SIM_START_MONEY,GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_ANTENA_NETWORK_ID));
				MySQL_AddItemInBox(GetActiveObjectParam(GetPlayerActiveObject(playerid),GSM_TERMINAL_BOX_ID),tmp_int);
			}
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
		}
		case DIALOG_TERMINAL_SETTINGS_NNAME:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
			if(!strlen(inputtext)) 
			{
				format(string,sizeof(string),"������� �������� ����: %s\n������� �����:",MySQL_GetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NNAME,DIALOG_STYLE_INPUT,"���������� ���������� [�������� ����]",string,"������","�����");
			}
			MySQL_SetGSMNetworkName(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),inputtext);
			format(string,sizeof(string),"����� �������� ����: %s",inputtext);
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"���������� ���������� [�������� ����]",string,"������","�����");
		}
		case DIALOG_TERMINAL_SETTINGS_NCCOST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 100)) 
			{
				format(string,sizeof(string),"������� ���� ������� ���������: %d$\n������� �����:",MySQL_GetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NCCOST,DIALOG_STYLE_INPUT,"���������� ���������� [���� ������� ���������]",string,"������","�����");
			}
			MySQL_SetGSMNetworkCallCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),strval(inputtext));
			format(string,sizeof(string),"����� ���� ������� ���������: %d",strval(inputtext));
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"���������� ���������� [���� ������� ���������]",string,"������","�����");
		}
		case DIALOG_TERMINAL_SETTINGS_NSCOST:
		{
			if(!response) return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS,DIALOG_STYLE_LIST,"���������� ����������","������� ���������\n��������� SIM-����\n������� SIM-�����","�������","������");
			if((strlen(inputtext) == 0) || (strval(inputtext) < 0) || (strval(inputtext) > 100)) 
			{
				format(string,sizeof(string),"������� ���� 1 SMS ���������: %d$\n������� �����:",MySQL_GetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID)));
				return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_NSCOST,DIALOG_STYLE_INPUT,"���������� ���������� [���� 1 SMS ���������]",string,"������","�����");
			}
			MySQL_SetGSMNetworkSMSCost(GetActiveObjectParam( GetPlayerActiveObject(playerid) ,GSM_TERMINAL_NETWORK_ID),strval(inputtext));
			format(string,sizeof(string),"����� ���� 1 SMS ���������: %d",strval(inputtext));
			return ShowPlayerDialog(playerid,DIALOG_TERMINAL_SETTINGS_LAST,DIALOG_STYLE_MSGBOX,"���������� ���������� [���� 1 SMS ���������]",string,"������","�����");
		}
		case DIALOG_GSM_LAST:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			return 1;
		}
		case DIALOG_GSM_MOBILE_ACTIONS:
		{
			if(!response) return 1;
			if(!strcmp(inputtext,"�������� SIM"))
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
				if(icount == 0) return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","� ��� ��� SIM-����","������","�����");
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_SELECT_SIM,DIALOG_STYLE_LIST,"���������",DialogString,"�������","�����");
			}
			else if(!strcmp(inputtext,"��������"))
			{
				if(GSM_Player[playerid][pInterlocutorId] == INVALID_PLAYER_ID) return 0;
				if(!IsPlayerConnected(GSM_Player[playerid][pInterlocutorId])) return 0; // �������� �������
				if(GetPlayerAction(GSM_Player[playerid][pInterlocutorId]) != ACTION_GSM_CALLING) return 0; // �������� ��� �� ������
				new NetworkId = strval(GetItemVar(strval(GetItemVar(GSM_Player[playerid][pActiveMobileItemId],0)),2));
				if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // �� ��� ����
				if(!IsPlayerInGSMZone(GSM_Player[playerid][pInterlocutorId],NetworkId)) return 0; // �������� ��� ����
				SetPlayerAction(playerid,ACTION_GSM_TALKING);
				SetPlayerAction(GSM_Player[playerid][pInterlocutorId],ACTION_GSM_TALKING);
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return 1;
			}		
			else if(!strcmp(inputtext,"���������"))
			{
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_CALL_NUMBER,DIALOG_STYLE_INPUT,"���������","�������� ����� ��������:","������","�����");
			}
			else if(!strcmp(inputtext,"�������� SMS"))
			{
			
			}
			else if(!strcmp(inputtext,"�������� SMS"))
			{
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
				return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_NUMBER,DIALOG_STYLE_INPUT,"���������","�������� ����� ��������:","������","�����");
			}
			else if(!strcmp(inputtext,"�������� SIM"))
			{
				SetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID,"0");				
				return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","SIM-����� ��������","������","�����");
			}
		}
		case DIALOG_GSM_SELECT_SIM:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			new simid;
			GetItemWhithVar(ITEM_TYPE_SIMCARD,GSM_SIM_NUMBER,CutPartText(inputtext,'[',']'),simid);
			SetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID,"%d",simid);
			return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","SIM-����� ����������","������","�����");
		}
		case DIALOG_GSM_CALL_NUMBER:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			new simid = strval(GetItemVar(GSM_Player[playerid][pUsingMobileItemId],GSM_MOBILE_SIM_ID));
			// ������������� ������
			if(strval(GetItemVar(simid,GSM_SIM_MONEY)) <= 0) return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","�� ����� ����� �� ������� ����� ��� ���������� ������� ������","������","�����");
			switch(CallToNumber(playerid,GSM_Player[playerid][pUsingMobileItemId],strval(inputtext)))
			{
				// �� ��� ���� �������� ����
				case 0: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","��� ����","������","�����");
				// ������ ������ �� ����������
				case 1: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","�� ����������� ������� �����\n��������� ���������� �����","������","�����");
				// ������� ��������� ��� ���� �������� ����
				case 2: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","������� ��������� ��� ���� �������� ����\n���������� ��������� �������","������","�����");
				// ������� ��������� ��� ���� �������� ����
				case 3: return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","������� �������� �����","������","�����");
				// �� ��
				case 4: return 1;
			}
		}
		case DIALOG_GSM_WSMS_NUMBER:
		{
			if(!response) return PlayerUseMobile(playerid,GSM_Player[playerid][pUsingMobileItemId]);
			nullstr(GSM_Player[playerid][pSMSText]);
			GSM_Player[playerid][pSMSnumber] = strval(inputtext);
			return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_TEXT,DIALOG_STYLE_INPUT,"���������","������� �����:","��������� ������","���������");
		}
		case DIALOG_GSM_WSMS_TEXT:
		{
			format(GSM_Player[playerid][pSMSText],MAX_STRING,"%s%s\n",GSM_Player[playerid][pSMSText],inputtext);
			if(!response)
			{
				SendSMSToNumber(playerid,GSM_Player[playerid][pUsingMobileItemId],GSM_Player[playerid][pSMSnumber],GSM_Player[playerid][pSMSText]);
				return ShowPlayerDialog(playerid,DIALOG_GSM_LAST,DIALOG_STYLE_MSGBOX,"���������","��������� ����������","������","�����");				
			}
			format(DialogString,sizeof(DialogString),"������� ����� ���������:\n%s",GSM_Player[playerid][pSMSText]);
			return ShowPlayerDialog(playerid,DIALOG_GSM_WSMS_TEXT,DIALOG_STYLE_INPUT,"���������",DialogString,"��������� ������","���������");
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
			// ��������� � ���� ����� ����
			MySQL_AddGSMNetwork(networkid);
			// ������ ��������� �� ����
			SetActiveObjectParam(aoid,GSM_TERMINAL_NETWORK_ID,networkid);
			// ������ �� ������� ��� �����
			SetActiveObjectParam(aoid,GSM_TERMINAL_BOX_ID,boxid);
			// ������ ������ "�� ������������"
			SetActiveObjectParam(aoid,GSM_TERMINAL_IS_USING,0);			
			GetModeObjectPos(objectid,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ��������� ������ � ������� �������� ��������
			new aobaseid = MySQL_AddActiveObjectInfo(ACTION_SELECT_GSM_TERMINAL,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5],networkid,boxid);
			// ���������� �� ������� � ���� � ���� �������
			SetActiveObjectParam(aoid,GSM_TERMINAL_BASE_ID,aobaseid);
			// �������� ������� �����
			ResetAntenesStatusWithNetwork(networkid);
			// ������� ���� ���� ������� ��� ��������� � ���� �������� ���������� ������ "�����"
			while(CheckNetworkAntenes(networkid)) {} 
			return 1;
		}
		case ACTION_SELECT_GSM_ANTENA:
		{
			new	premise,
				Float:Pos[6];
			GetModeObjectPos(GetActiveObjectModeObjectId(aoid),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ������ �� ���� 0 - ��������� �� 0 ��� � �� �����
			SetActiveObjectParam(aoid,GSM_ANTENA_NETWORK_ID,0);
			// ����� ������� �� ���
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_CONNECTED,0);
			// �� ������������
			SetActiveObjectParam(aoid,GSM_ANTENA_IS_USING,0);
			// ��������� ������ � ������� �������� ��������
			new aobaseid = MySQL_AddActiveObjectInfo(ACTION_SELECT_GSM_ANTENA,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ���������� �� ������� � ���� � ���� �������
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
			// ��������� ���������� ������� � �������
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(aobjectid,GSM_TERMINAL_BASE_ID),UPDATE_AO_INFO_POS,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// �������� ������� �����
			ResetAntenesStatusWithNetwork(networkid);
			// ������� ���� ���� ������� ��� ��������� � ���� �������� ���������� ������ "�����"
			while(CheckNetworkAntenes(networkid)) {} 
			return 1;
		}
		case ACTION_SELECT_GSM_ANTENA:
		{
			new networkid = -GetActiveObjectParam(aobjectid,GSM_ANTENA_NETWORK_ID),
				premise,
				Float:Pos[6];
			GetModeObjectPos(GetActiveObjectModeObjectId(aobjectid),premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ��������� ���������� ������� � �������
			MySQL_UpdateActiveObjectInfo(GetActiveObjectParam(aobjectid,GSM_ANTENA_BASE_ID),UPDATE_AO_INFO_POS,premise,Pos[0],Pos[1],Pos[2],Pos[3],Pos[4],Pos[5]);
			// ���������� ������������� �� ����
			SetActiveObjectParam(aobjectid,GSM_ANTENA_NETWORK_ID,networkid);
			// �������� ������� �����
			ResetAntenesStatusWithNetwork(networkid);
			// ������� ���� ���� ������� ��� ��������� � ���� �������� ���������� ������ "�����"
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
	if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // �� ��� ���� �������� ����
	// ����� ����,���� ����� ��������
	new to_simid,
		to_mobileid;
	if(!GetItemWhithVar(ITEM_TYPE_SIMCARD,0,inttostr(number),to_simid)) return 1; // ������ ������ ����
	if(!GetItemWhithVar(ITEM_TYPE_MOBILE,0,inttostr(to_simid),to_mobileid)) return 2; // ������� ��� ���� �������� ����(�� ���� ����� �� ������������)
	for(new pl = 0;pl < GetMaxPlayer();pl++)
	{
		if(!IsPlayerConnected(pl)) continue;
		if(pl == playerid) continue;
		if(!IsPlayerHaveItem(oGetPlayerName(pl),to_mobileid)) continue;
		// � ������ ���� ��������� ������ ���
		if(!IsPlayerInGSMZone(pl,strval(GetItemVar(to_simid,2)))) return 2; // ������� ��� ���� �������� ����(�� ������� ��� ����)
		// � ���� ���� �����, ���������
		if(GetPlayerAction(pl) != ACTION_NONE) return 3; // ������� ���� �����
		SetPlayerAction(playerid,ACTION_GSM_CALLING);
		ModeMessage(pl,MODE_MESSAGE_IC,"[���������] �������� ������ �� %d",number);
		PlayerMessage(pl,PLAYER_MESSAGE_ACTION,"������ ���������");
		PlayerMessage(playerid,PLAYER_MESSAGE_ACTION,"������ ��������� � ������ �����");
		GSM_Player[playerid][pInterlocutorId] = pl;
		GSM_Player[pl][pInterlocutorId] = playerid;
		GSM_Player[playerid][pActiveMobileItemId] = mobileitemid;
		GSM_Player[pl][pActiveMobileItemId] = to_mobileid;
		return 4; // �� ��
	}
	return 0; // �� ��� ���� �������� ����
}

stock SendSMSToNumber(playerid,mobileitemid,number,text[])
{
	printf("SendSMSToNumber(%d,%d,%d,%s)",playerid,mobileitemid,number,text);
	new NetworkId = strval(GetItemVar(strval(GetItemVar(mobileitemid,0)),2));
	if(!IsPlayerInGSMZone(playerid,NetworkId)) return 0; // �� ��� ���� �������� ����
//	MySQL_SendSMS(strval(GetItemVar(strval(GetItemVar(mobileitemid,0)),0)),number,text);
	// ����� ����,���� ����� ��������
	new to_simid,
		to_mobileid;
	if(!GetItemWhithVar(ITEM_TYPE_SIMCARD,0,inttostr(number),to_simid)) return 1; // ������ ������ ����
	if(!GetItemWhithVar(ITEM_TYPE_MOBILE,0,inttostr(to_simid),to_mobileid)) return 1; // ������� ��� ���� �������� ����(�� ���� ����� �� ������������)
	for(new pl = 0;pl < GetMaxPlayer();pl++)
	{
		if(!IsPlayerConnected(pl)) continue;
		if(pl == playerid) continue;
		if(!IsPlayerHaveItem(oGetPlayerName(pl),to_mobileid)) continue;
		// � ������ ���� ��������� ������ ���
		if(!IsPlayerInGSMZone(pl,strval(GetItemVar(to_simid,2)))) return 1;
		// � ���� ���� �����
		if(GetPlayerAction(pl) != ACTION_NONE) return 1; // ������� ���� �����		
		ModeMessage(pl,MODE_MESSAGE_IC,"[���������] �������� ��������� �� %d",number);
		return 1; // �� ��
	}
	return 1; // �� ��� ���� �������� ����
}