/*
*	Created:			28.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		GPS
*/

#if defined _items_gps_included
	#endinput
#endif

#define _items_gps_included
#pragma library items_gps

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum GPSPlayerInfo {
	bool:pShowedPoint,
	pSelectedPoint,
	pPointCity,
	pPointName[MAX_POINT_NAME]
};
enum CitysPointsInfo {
	cpName[MAX_POINT_NAME],
	Float:cpCoords[3]
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static 
	Gps_Player[MAX_PLAYERS][GPSPlayerInfo],
	LS_Points[][CitysPointsInfo] = {
		{"Test point",0.0,0.0,0.0},
	},
	SF_Points[][CitysPointsInfo] = {
		{"Test point",0.0,0.0,0.0},
	},
	LV_Points[][CitysPointsInfo] = {
		{"Test point",0.0,0.0,0.0},
	};

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Gps_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Gps_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Gps_BuildTypeListItems(reason: complete)");
	return 1;
}

Gps_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Gps_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER:
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) 
			{
				if(!Gps_Player[playerid][pShowedPoint]) format(dest,size,"Список моих точек\nСписок городских точек\nВыкинуть\nСломать");
				else format(dest,size,"Убрать цель\nСписок моих точек\nСписок городских точек\nВыкинуть\nСломать");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}
	Debug(DEBUG_END,"Gps_BuildItemActionsString(reason: complete)");
}

Gps_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Gps_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	switch(itemdialogid)
	{
		case 0:
		{
			if(!strcmp(action,"Список моих точек"))
			{
				Debug(DEBUG_ACTION,"Список моих точек");
				nullstr(DialogString);
				new tmp[128],
					listid;
				format(query,sizeof(query),"SELECT * FROM `Gps_data` WHERE `ItemId`=%d",itemid);
				samp_mysql_query(query);
				samp_mysql_store_result();
				while(samp_mysql_fetch_row(result)) 
				{
					samp_mysql_get_field("Name",tmp);
					format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,tmp);
					samp_mysql_get_field("id",tmp);
					SetPlayerModeDialogListData(playerid,listid,strval(tmp));
					listid++;
				}
				ShowItemsListDialog(playerid,ITEM_DIALOG_GPS_MY_POINTS,DialogString);
				Gps_Player[playerid][pPointCity] = 3;
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Список городских точек"))
			{
				Debug(DEBUG_ACTION,"Список городских точек");
				nullstr(DialogString);
				new listid;
				switch(GetPlayerCity(playerid))
				{
					case -1: // Not in city
					{
						ShowItemsMessageDialog(playerid,ITEM_DIALOG_GPS_END,"Нет сигнала");
						Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
						return 0;
					}
					case 0: // LS
					{
						for(new i = 0;i < sizeof(LS_Points);i++)
						{
							format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,LS_Points[i][cpName]);
							SetPlayerModeDialogListData(playerid,listid,i);
							listid++;
						}
						Gps_Player[playerid][pPointCity] = 0;
					}
					case 1: // SF
					{
						for(new i = 0;i < sizeof(SF_Points);i++)
						{
							format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,SF_Points[i][cpName]);
							SetPlayerModeDialogListData(playerid,listid,i);
							listid++;
						}
						Gps_Player[playerid][pPointCity] = 1;
					}
					case 2: // LV
					{
						for(new i = 0;i < sizeof(LV_Points);i++)
						{
							format(DialogString,sizeof(DialogString),"%s%s\n",DialogString,LV_Points[i][cpName]);
							SetPlayerModeDialogListData(playerid,listid,i);
							listid++;
						}
						Gps_Player[playerid][pPointCity] = 2;
					}
				}
				ShowItemsListDialog(playerid,ITEM_DIALOG_GPS_CITY_POINTS,DialogString);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Убрать цель"))
			{
				Debug(DEBUG_ACTION,"Убрать цель");
				Gps_Player[playerid][pShowedPoint] = false;
				DisablePlayerCheckpoint(playerid);
				ShowItemsMessageDialog(playerid,ITEM_DIALOG_GPS_END,"Цель убрана");
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Выкинуть"))
			{
				Debug(DEBUG_ACTION,"Выкинуть");
				ItemOwnerRemove(itemid);
				new Float:pos[4];
				GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
				GetPlayerFacingAngle(playerid,pos[3]);
				MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
				SetItemPos(itemid,pos[0],pos[1],pos[2]);
				SetItemPremise(itemid,GetPlayerPremise(playerid));
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Забрать"))
			{
				Debug(DEBUG_ACTION,"Забрать");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Взять"))
			{
				Debug(DEBUG_ACTION,"Взять");
				SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 1;
			}
			if(!strcmp(action,"Сломать"))
			{
				Debug(DEBUG_ACTION,"Сломать");
				DestroyItem(itemid);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 1;
			}
		}
		case ITEM_DIALOG_GPS_END:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_END");
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 1;
		}
		case ITEM_DIALOG_GPS_MY_POINTS:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_MY_POINTS");
			Gps_Player[playerid][pSelectedPoint] = GetPlayerModeDialogListData(playerid,GetItemsDialogSelectedListitem(playerid));
			ShowItemsListDialog(playerid,ITEM_DIALOG_GPS_POINT_ACTIONS,"Выставить цель\nКоординаты точки\nДобавить точку по координатам\nДобавить точку по текущему местоположению\nУдалить точку");
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 1;
		}
		case ITEM_DIALOG_GPS_CITY_POINTS:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_CITY_POINTS");
			Gps_Player[playerid][pSelectedPoint] = GetPlayerModeDialogListData(playerid,GetItemsDialogSelectedListitem(playerid));
			ShowItemsListDialog(playerid,ITEM_DIALOG_GPS_POINT_ACTIONS,"Выставить цель\nКоординаты точки");
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 1;
		}
		case ITEM_DIALOG_GPS_POINT_ACTIONS:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_POINT_ACTIONS");
			if(!strcmp(action,"Выставить цель"))
			{
				Debug(DEBUG_ACTION,"Выставить цель");
				switch(Gps_Player[playerid][pPointCity])
				{
					case 0: // LS
					{
						SetPlayerCheckpoint(playerid,LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2],0.0);
						format(DialogString,sizeof(DialogString),"'%s' зафиксировано",LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName]);						
					}
					case 1: // SF
					{
						SetPlayerCheckpoint(playerid,SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2],0.0);
						format(DialogString,sizeof(DialogString),"'%s' зафиксировано",SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName]);						
					}
					case 2: // LV
					{
						SetPlayerCheckpoint(playerid,LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2],0.0);
						format(DialogString,sizeof(DialogString),"'%s' зафиксировано",LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName]);						
					}
					case 3: // My points
					{
						new tmp[128],
							Float:X,
							Float:Y,
							Float:Z;
						format(query,sizeof(query),"SELECT * FROM `Gps_data` WHERE `ItemId`=%d",itemid);
						samp_mysql_query(query);
						samp_mysql_store_result();
						samp_mysql_fetch_row(result);
						samp_mysql_get_field("X",tmp);
						X = floatstr(tmp);
						samp_mysql_get_field("Y",tmp);
						Y = floatstr(tmp);
						samp_mysql_get_field("Z",tmp);
						Z = floatstr(tmp);
						samp_mysql_get_field("Name",tmp);
						SetPlayerCheckpoint(playerid,X,Y,Z,0.0);
						format(DialogString,sizeof(DialogString),"'%s' зафиксировано",tmp);
					}
				}
				Gps_Player[playerid][pShowedPoint] = true;
				ShowItemsMessageDialog(playerid,ITEM_DIALOG_GPS_END,DialogString);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Координаты точки"))
			{
				Debug(DEBUG_ACTION,"Координаты точки");
				switch(Gps_Player[playerid][pPointCity])
				{
					case 0: // LS
					{
						format(DialogString,sizeof(DialogString),"'%s' - %f,%f,%f",LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName],LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],LS_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2]);						
					}
					case 1: // SF
					{
						format(DialogString,sizeof(DialogString),"'%s' - %f,%f,%f",SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName],SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],SF_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2]);						
					}
					case 2: // LV
					{
						format(DialogString,sizeof(DialogString),"'%s' - %f,%f,%f",LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpName],LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][0],LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][1],LV_Points[ Gps_Player[playerid][pSelectedPoint] ][cpCoords][2]);						
					}
					case 3: // My points
					{
						new tmp[128],
							Float:X,
							Float:Y,
							Float:Z;
						format(query,sizeof(query),"SELECT * FROM `Gps_data` WHERE `ItemId`=%d",itemid);
						samp_mysql_query(query);
						samp_mysql_store_result();
						samp_mysql_fetch_row(result);
						samp_mysql_get_field("X",tmp);
						X = floatstr(tmp);
						samp_mysql_get_field("Y",tmp);
						Y = floatstr(tmp);
						samp_mysql_get_field("Z",tmp);
						Z = floatstr(tmp);
						samp_mysql_get_field("Name",tmp);
						format(DialogString,sizeof(DialogString),"'%s' - %f,%f,%f",tmp,X,Y,Z);
					}
				}
				ShowItemsMessageDialog(playerid,ITEM_DIALOG_GPS_END,DialogString);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Добавить точку по координатам"))
			{
				Debug(DEBUG_ACTION,"Добавить точку по координатам");
				ShowItemsInputDialog(playerid,ITEM_DIALOG_GPS_POINT_BY_COORD_1,"Введите название точки:");
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Добавить точку по текущему местоположению"))
			{
				Debug(DEBUG_ACTION,"Добавить точку по текущему местоположению");	
				ShowItemsInputDialog(playerid,ITEM_DIALOG_GPS_POINT_BY_POS,"Введите название точки:");
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
			if(!strcmp(action,"Удалить точку"))
			{
				Debug(DEBUG_ACTION,"Удалить точку");	
				format(query,sizeof(query),"DELETE FROM `Gps_data` WHERE `ItemId`=%d AND `id`=%d",itemid,Gps_Player[playerid][pSelectedPoint]);
				samp_mysql_query(query);
				Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
				return 0;
			}
		}
		case ITEM_DIALOG_GPS_POINT_BY_COORD_1:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_POINT_BY_COORD_1");
			format(Gps_Player[playerid][pPointName],MAX_POINT_NAME,action);
			ShowItemsInputDialog(playerid,ITEM_DIALOG_GPS_POINT_BY_COORD_2,"Введите координаты(через запятую X,Y,Z):");
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 0;
		}
		case ITEM_DIALOG_GPS_POINT_BY_COORD_2:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_POINT_BY_COORD_2");
			new idx,
				Float:X = floatstr(strtok(action,',',idx)),
				Float:Y = floatstr(strtok(action,',',idx)),
				Float:Z = floatstr(strtok(action,',',idx));
			format(query,sizeof(query),"INSERT INTO `Gps_data` (`ItemId`,`Name`,`X`,`Y`,`Z`) VALUES (%d,'%s',%f,%f,%f)",itemid,Gps_Player[playerid][pPointName],X,Y,Z);
			samp_mysql_query(query);
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 1;
		}
		case ITEM_DIALOG_GPS_POINT_BY_POS:
		{
			Debug(DEBUG_ACTION,"ITEM_DIALOG_GPS_POINT_BY_POS");
			new Float:X,
				Float:Y,
				Float:Z,
				tmp;
			if((tmp = GetPlayerPremise(playerid)) != 0) GetPlayerPos(playerid,X,Y,Z);
			else GetPremiseEnterPos(tmp,X,Y,Z);
			format(query,sizeof(query),"INSERT INTO `Gps_data` (`ItemId`,`Name`,`X`,`Y`,`Z`) VALUES (%d,'%s',%f,%f,%f)",itemid,action,X,Y,Z);
			samp_mysql_query(query);
			Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
			return 1;
		}
	}	
	Debug(DEBUG_END,"Gps_OnPlayerUseItem(reason: complete)");
	return 0;
}