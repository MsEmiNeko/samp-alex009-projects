/*
*	Created:			17.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		Оружие
*/

#if defined _items_weapons_included
	#endinput
#endif

#define _items_weapons_included
#pragma library items_weapons

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
enum ItemsWeaponsPlayerInfo {
	pActiveWeaponItem,
	pActiveWeaponType,
	pActiveWeaponCheck
}
enum {
	WEAPON_TYPE_HAND,
	WEAPON_TYPE_SWORDS,
	WEAPON_TYPE_FIRE,
	WEAPON_TYPE_MISSILE,
	WEAPON_TYPE_SPECIAL_1,
	WEAPON_TYPE_SPECIAL_2
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static Weapons_Player[MAX_PLAYERS][ItemsWeaponsPlayerInfo];

// --------------------------------------------------
// statics functions
// --------------------------------------------------
static IsItemWeapon(type)
{
	switch(type)
	{
		case 
			ITEM_TYPE_BRASSKNUCKLE,
			ITEM_TYPE_GOLFCLUB,
			ITEM_TYPE_NITESTICK,
			ITEM_TYPE_KNIFE,
			ITEM_TYPE_BAT,
			ITEM_TYPE_SHOVEL,
			ITEM_TYPE_POOLSTICK,
			ITEM_TYPE_KATANA,
			ITEM_TYPE_CHAINSAW,
			ITEM_TYPE_DILDO,
			ITEM_TYPE_DILDO2,
			ITEM_TYPE_VIBRATOR,
			ITEM_TYPE_VIBRATOR2,
			ITEM_TYPE_FLOWER,
			ITEM_TYPE_CANE,
			ITEM_TYPE_GRENADE,
			ITEM_TYPE_TEARGAS,
			ITEM_TYPE_MOLTOV,
			ITEM_TYPE_COLT45,
			ITEM_TYPE_SILENCED,
			ITEM_TYPE_DEAGLE,
			ITEM_TYPE_SHOTGUN,
			ITEM_TYPE_SAWEDOFF,
			ITEM_TYPE_SHOTGSPA,
			ITEM_TYPE_UZI,
			ITEM_TYPE_MP5,
			ITEM_TYPE_AK47,
			ITEM_TYPE_M4,
			ITEM_TYPE_TEC9,
			ITEM_TYPE_RIFLE,
			ITEM_TYPE_SNIPER,
			ITEM_TYPE_ROCKETLAUNCHER,
			ITEM_TYPE_SATCHEL,
			ITEM_TYPE_BOMB,
			ITEM_TYPE_SPRAYCAN,
			ITEM_TYPE_FIREEXTINGUISHER,
			ITEM_TYPE_CAMERA,
			ITEM_TYPE_PARACHUTE: return 1;
		default: return 0;
	}
}
static GetItemWeaponType(type)
{
	switch(type)
	{
		case 
			ITEM_TYPE_BRASSKNUCKLE,
			ITEM_TYPE_GOLFCLUB,
			ITEM_TYPE_NITESTICK,
			ITEM_TYPE_BAT,
			ITEM_TYPE_SHOVEL,
			ITEM_TYPE_POOLSTICK,
			ITEM_TYPE_CANE: return WEAPON_TYPE_HAND;
		case 
			ITEM_TYPE_KNIFE,
			ITEM_TYPE_KATANA,
			ITEM_TYPE_CHAINSAW: return WEAPON_TYPE_SWORDS;
		case 
			ITEM_TYPE_COLT45,
			ITEM_TYPE_SILENCED,
			ITEM_TYPE_DEAGLE,
			ITEM_TYPE_SHOTGUN,
			ITEM_TYPE_SAWEDOFF,
			ITEM_TYPE_SHOTGSPA,
			ITEM_TYPE_UZI,
			ITEM_TYPE_MP5,
			ITEM_TYPE_AK47,
			ITEM_TYPE_M4,
			ITEM_TYPE_TEC9,
			ITEM_TYPE_RIFLE,
			ITEM_TYPE_SNIPER,
			ITEM_TYPE_ROCKETLAUNCHER: return WEAPON_TYPE_FIRE;
		case
			ITEM_TYPE_MOLTOV,
			ITEM_TYPE_BOMB,
			ITEM_TYPE_GRENADE,
			ITEM_TYPE_TEARGAS: return WEAPON_TYPE_MISSILE;
		case
			ITEM_TYPE_DILDO,
			ITEM_TYPE_DILDO2,
			ITEM_TYPE_VIBRATOR,
			ITEM_TYPE_VIBRATOR2,
			ITEM_TYPE_FLOWER,
			ITEM_TYPE_SATCHEL,
			ITEM_TYPE_PARACHUTE: return WEAPON_TYPE_SPECIAL_1;
		case
			ITEM_TYPE_SPRAYCAN,
			ITEM_TYPE_FIREEXTINGUISHER,
			ITEM_TYPE_CAMERA: return WEAPON_TYPE_SPECIAL_2;
		default: return -1;
	}
}
static GetItemWeaponSlot(type)
{
	switch(type)
	{
		case 
			ITEM_TYPE_BRASSKNUCKLE: return 0;
		case 
			ITEM_TYPE_GOLFCLUB,
			ITEM_TYPE_NITESTICK,
			ITEM_TYPE_KNIFE,
			ITEM_TYPE_BAT,
			ITEM_TYPE_SHOVEL,
			ITEM_TYPE_POOLSTICK,
			ITEM_TYPE_KATANA,
			ITEM_TYPE_CHAINSAW: return 1;
		case 
			ITEM_TYPE_COLT45,
			ITEM_TYPE_SILENCED,
			ITEM_TYPE_DEAGLE: return 2;
		case
			ITEM_TYPE_SHOTGUN,
			ITEM_TYPE_SAWEDOFF,
			ITEM_TYPE_SHOTGSPA: return 3;
		case
			ITEM_TYPE_UZI,
			ITEM_TYPE_MP5,
			ITEM_TYPE_TEC9: return 4;
		case 
			ITEM_TYPE_AK47,
			ITEM_TYPE_M4: return 5;
		case
			ITEM_TYPE_RIFLE,
			ITEM_TYPE_SNIPER: return 6;
		case
			ITEM_TYPE_ROCKETLAUNCHER: return 7;
		case
			ITEM_TYPE_GRENADE,
			ITEM_TYPE_TEARGAS,
			ITEM_TYPE_MOLTOV,
			ITEM_TYPE_SATCHEL: return 8;
		case
			ITEM_TYPE_SPRAYCAN,
			ITEM_TYPE_FIREEXTINGUISHER,
			ITEM_TYPE_CAMERA: return 9;
		case
			ITEM_TYPE_DILDO,
			ITEM_TYPE_DILDO2,
			ITEM_TYPE_VIBRATOR,
			ITEM_TYPE_VIBRATOR2,
			ITEM_TYPE_FLOWER,
			ITEM_TYPE_CANE: return 10;
		case 
			ITEM_TYPE_PARACHUTE: return 11;
		case 
			ITEM_TYPE_BOMB: return 12;
	}
	return -1;
}
static GetItemWeaponId(type)
{
	switch(type)
	{
		case ITEM_TYPE_BRASSKNUCKLE: return 1;
		case ITEM_TYPE_GOLFCLUB: return 2;
		case ITEM_TYPE_NITESTICK: return 3;
		case ITEM_TYPE_KNIFE: return 4;
		case ITEM_TYPE_BAT: return 5;
		case ITEM_TYPE_SHOVEL: return 6;
		case ITEM_TYPE_POOLSTICK: return 7;
		case ITEM_TYPE_KATANA: return 8;
		case ITEM_TYPE_CHAINSAW: return 9;
		case ITEM_TYPE_COLT45: return 22;
		case ITEM_TYPE_SILENCED: return 23;
		case ITEM_TYPE_DEAGLE: return 24;
		case ITEM_TYPE_SHOTGUN: return 25;
		case ITEM_TYPE_SAWEDOFF: return 26;
		case ITEM_TYPE_SHOTGSPA: return 27;
		case ITEM_TYPE_UZI: return 28;
		case ITEM_TYPE_MP5: return 29;
		case ITEM_TYPE_TEC9: return 32;
		case ITEM_TYPE_AK47: return 30;
		case ITEM_TYPE_M4: return 31;
		case ITEM_TYPE_RIFLE: return 33;
		case ITEM_TYPE_SNIPER: return 34;
		case ITEM_TYPE_ROCKETLAUNCHER: return 35;
		case ITEM_TYPE_GRENADE: return 16;
		case ITEM_TYPE_TEARGAS: return 17;
		case ITEM_TYPE_MOLTOV: return 18;
		case ITEM_TYPE_SATCHEL: return 39;
		case ITEM_TYPE_SPRAYCAN: return 41;
		case ITEM_TYPE_FIREEXTINGUISHER: return 42;
		case ITEM_TYPE_CAMERA: return 43;
		case ITEM_TYPE_DILDO: return 10;
		case ITEM_TYPE_DILDO2: return 11;
		case ITEM_TYPE_VIBRATOR: return 12;
		case ITEM_TYPE_VIBRATOR2: return 13;
		case ITEM_TYPE_FLOWER: return 14;
		case ITEM_TYPE_CANE: return 15;
		case ITEM_TYPE_BOMB: return 40;
		case ITEM_TYPE_PARACHUTE: return 46;
	}
	return 0;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Weapons_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Weapons_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	switch(GetItemWeaponType(type))
	{
		case WEAPON_TYPE_FIRE: format(dest,size,"[%s патронов]",var0);
		case WEAPON_TYPE_MISSILE: format(dest,size,"[%s штук]",var0);
	}
	Debug(DEBUG_END,"Weapons_BuildTypeListItems(reason: complete)");
	return 1;
}

Weapons_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Weapons_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(ownertype),true)) 
			{
				if(Weapons_Player[playerid][pActiveWeaponType] == type) format(dest,size,"Убрать");
				else format(dest,size,"Взять в руки\nВыкинуть");
			}
			else format(dest,size,"Забрать");
		}
		default: format(dest,size,"Взять");
	}	
	Debug(DEBUG_END,"Weapons_BuildItemActionsString(reason: complete)");
	return 1;
}

Weapons_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Weapons_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"Взять в руки"))
	{
		Debug(DEBUG_ACTION,"Взять в руки");
		if(Weapons_Player[playerid][pActiveWeaponType] == type)
		{
			new wdata[2];
			GetPlayerWeaponData(playerid,GetItemWeaponSlot(type),wdata[0],wdata[1]);
			SetItemVarInt(Weapons_Player[playerid][pActiveWeaponItem],0,wdata[1]);
			ResetPlayerWeapons(playerid);
			Weapons_Player[playerid][pActiveWeaponType] = 0;
			Weapons_Player[playerid][pActiveWeaponItem] = 0;
		}
		else
		{
			if(Weapons_Player[playerid][pActiveWeaponItem] != INVALID_ITEM_ID)
			{
				new wdata[2];
				GetPlayerWeaponData(playerid,GetItemWeaponSlot(Weapons_Player[playerid][pActiveWeaponType]),wdata[0],wdata[1]);
				SetItemVarInt(Weapons_Player[playerid][pActiveWeaponItem],0,wdata[1]);
			}
			ResetPlayerWeapons(playerid);
			new wid = GetItemWeaponId(type);
			GivePlayerWeapon(playerid,wid,GetItemVarInt(itemid,0)));
			Weapons_Player[playerid][pActiveWeaponType] = type;
			Weapons_Player[playerid][pActiveWeaponItem] = itemid;
			Weapons_Player[playerid][pActiveWeaponCheck] = wid;
		}
		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Убрать"))
	{
		Debug(DEBUG_ACTION,"Убрать");
		if(Weapons_Player[playerid][pActiveWeaponType] == type)
		{
			new wdata[2];
			GetPlayerWeaponData(playerid,GetItemWeaponSlot(type),wdata[0],wdata[1]);
			SetItemVarInt(Weapons_Player[playerid][pActiveWeaponItem],0,wdata[1]);
			ResetPlayerWeapons(playerid);
			Weapons_Player[playerid][pActiveWeaponType] = 0;
			Weapons_Player[playerid][pActiveWeaponItem] = 0;
		}
		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
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
		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Забрать"))
	{
		Debug(DEBUG_ACTION,"Забрать");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"Взять"))
	{
		Debug(DEBUG_ACTION,"Взять");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Weapons_OnPlayerUseItem(reason: complete)");
	return 0;
}

Weapons_OnPlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Weapons_OnPlayerUpdate(%d)",playerid);
	if(Weapons_Player[playerid][pActiveWeaponType] == 0) {Debug(DEBUG_END,"Weapons_OnPlayerUpdate(reason: complete)");return 1;}	
	if(Weapons_Player[playerid][pActiveWeaponCheck] == 0) {Debug(DEBUG_END,"Weapons_OnPlayerUpdate(reason: complete)");return 1;}	
	if(GetPlayerWeapon(playerid) == Weapons_Player[playerid][pActiveWeaponCheck]) {Debug(DEBUG_END,"Weapons_OnPlayerUpdate(reason: complete)");return 1;}
	new wdata[2];
	GetPlayerWeaponData(playerid,GetItemWeaponSlot(Weapons_Player[playerid][pActiveWeaponType]),wdata[0],wdata[1]);
	if(wdata[1] == 0) 
	{
		SetItemVarInt(Weapons_Player[playerid][pActiveWeaponItem],0,wdata[1]);
		ResetPlayerWeapons(playerid);
		Weapons_Player[playerid][pActiveWeaponType] = 0;
		Weapons_Player[playerid][pActiveWeaponItem] = 0;
	}
	else SetPlayerArmedWeapon(playerid,Weapons_Player[playerid][pActiveWeaponCheck]);
	Debug(DEBUG_END,"Weapons_OnPlayerUpdate(reason: complete)");
	return 1;
}