/*
*	Created:			02.03.09
*	Aurthor:			009
*	Last Modifed:		17.09.09
*	
*	17.09.09:
*	1.Смерть полностью обрабатывается в Player_OnPlayerDeath
*
*	14.09.09:
*	1.ModeInteriors не связаны с player.inc
*
*	13.09.09:
*	1.Регистрация перенесена из base.inc сюда
*	2.Добавлен PlayerMessage
*
*	05.09.09:
*	1.MAX_PLAYERS в циклах заменён на GetMaxPlayer()
*	
*/

#if defined _player_included
#endinput
#endif

#define _player_included
#pragma library player
#include "base"
#include "utils"

// --------------------------------------------------
// enums
// --------------------------------------------------
enum PlayerInfo {
//Base
	bool:pRegister,
	bool:pJailed,
	bool:pWeaponLicense,
	bool:pShowStreamedCP,
	bool:pBlockCMD,
	pCreateCharStep,
	Float:pDeathPos[3],
	Float:pHealth,
	pDeathOnBox,
	pDeathTime,
	pName[MAX_PLAYER_NAME],
	pActor[MAX_PLAYER_NAME],
	pSkin,
	pSkinType,
	pBirthday[MAX_STRING],
	pLocate[MAX_STRING],
	pMoney,
	pBankAccount,
	pBankCode,
	pSpawn[10],
	pInBlackList,
	pMenuAction,
	pTimeInGame,
	pPower,
	pDeaths,
	pKills,
	pStatus,
	pGPSid,
	pNumber,
	pWeapons[MAX_WEAPONS],
	pEnterText,
	pShowedCheckPoint,
	pSelectedMenuRow,
	pOldClass,
//Work inc
	pSpecate,
	pWork,
	pWorkScore,
	pWorkProfit,
	pWorkInfo,
	pYad,
	pPrison,
	pPrisonTime,
	bool:pArrested,
//Race inc
	pRaceId,
	pRaceCp,
	pRacesGone,
	pRacesWon,
//Business inc
	pAutoBuy,
	pAutoBuyInfo[4],
	pClotchBuy,
	pClotchBuyInfo[4],
//Houses inc
	pGhost[MAX_PLAYER_NAME],
//Icon streamer inc
	bool:pIcons[32],
//Pickup streamer inc
	pLastPickup,
//Phone inc.
	bool:pUsePhone,
	pIncomingCall,
	pPhoneAnswer,
	pCall,
//Sport Clubs inc
	bool:pOnBox,
	pFightScore,
	pFightSkill,
	pFightStyle,
	pFightHit,
	pFightDelay,
	pFightAnim,
//Walk Styles inc
	pWalkTime,
	pWalkStyle,
//Licenses inc
	bool:pLicenses[MAX_LICENSED],
	bool:pLicenseTest,
	pLicenseTestInfo[5],
//Part Time Job inc
	pPartTimeJobId,
	pPartTimeJobTime,
	pPartTimeJobInfo[7],
	Text:pPartTimeJobText,
	pDrugs,
//GPS inc
	bool:pShowenPlayers[MAX_PLAYERS],
//Vehicles inc
	pEnterCode
}

// --------------------------------------------------
// news
// --------------------------------------------------
new ENCRYPTION_KEY[MAX_STRING] = "_C)2^K¬RPXjwE8b;:p{Df+=Q3(O*vgu9ZH[!1tuLe0->?zhSF<xVzm]$4%5a`Jdny¦IUW@G7s6&l:k;i~ YsoMЈ.cBq#|}NrT8A,.";
new Player[MAX_PLAYERS][PlayerInfo];
new PlayerCheck;
new PlayerIP[MAX_PLAYERS][64];
new bool:NoneRequestSpawn[MAX_PLAYERS];

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward Player_OnPlayerDisconnect(playerid,reason);
forward Player_OnPlayerConnect(playerid);
forward Player_OnPlayerDeath(playerid,killerid,reason);
forward Player_ResetStat(playerid);
forward Player_OnPlayerRequestClass(playerid,classid);
forward Player_OnPlayerSpawn(playerid);
forward Player_OnPlayerUpdate(playerid);
forward Player_OnPlayerCommandText(playerid,text[]);
forward Player_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
forward Player_Check();
forward Player_OnPlayerSave(playerid);
forward Player_OnPlayerRequestClass(playerid,classid);
forward Player_OnPlayerRequestSpawn(playerid);
forward PlayerSay(playerid,text[]);
forward PlayerShout(playerid,text[]);
forward PlayerOOC(playerid,text[]);
forward IsPlayerMan(playerid);
forward IsPlayerWoman(playerid);
forward IsPlayerRegistered(playerid);
forward DeleteActorFromWorld(playerid);
forward DownPlayer(playerid);
forward SyncMoney(playerid);
forward UpdatePlayerScore(playerid);
forward oSetPlayerMoney(playerid,money);
forward oGivePlayerMoney(playerid,money,bool:showtext);
forward oGetPlayerMoney(playerid);
forward GivePlayerOwnedWeapons(playerid);
forward SetWeaponsFromDBString(playerid,dbstring[]);
forward MoveSelecting(playerid,leftright);
forward DropPlayerWeapons(playerid);
forward DeletePickup(pickupid);
forward GetWeaponModel(weaponid);

// --------------------------------------------------
// publics
// --------------------------------------------------

public Player_OnPlayerDisconnect(playerid,reason)
{
	if(IsPlayerCameraMoving(playerid)) StopPlayerCamera(playerid,false);
	if(IsPlayerRegistered(playerid) && (RegisterStep[playerid] == 0)) OnPlayerSave(playerid);
	ResetStat(playerid);
	return 1;
}

public Player_OnPlayerConnect(playerid)
{
	MovePlayerCameraPosEx(playerid,-2681.423095,2073.361328,55.812500,-2681.623291,1941.962524,62.112403,-2681.590576,1933.939697,217.273895,1.0);
	ResetStat(playerid);
	GetPlayerIp(playerid,PlayerIP[playerid],64);
	ModeMessage(playerid,MODE_MESSAGE_OOC,"Здравствуйте %s,мы приветствуем вас на RolePlay сервере ОАО Сибирьтелеком",oGetPlayerName(playerid));
	ModeMessage(playerid,MODE_MESSAGE_OOC,"На сервере установлен мод %s,это новый,не имеющий аналогов мод,написанный с нуля.",GAMEMODE_NAME);
	ModeMessage(playerid,MODE_MESSAGE_OOC,"Просим не нарушать правила сервера(написаны на форуме и в обучении)");
	ModeMessage(playerid,MODE_MESSAGE_OOC,"При нарушении правил администрация примет меры");
	if(MySQL_FindPlayer(playerid)) ModeMessage(playerid,MODE_MESSAGE_OOC,"Ваш ник зарегестрирован,введите '/login <пароль>'");
	else ModeMessage(playerid,MODE_MESSAGE_OOC,"Ваш ник не зарегестрирован,введите '/register <пароль>'");
	return 1;
}

public Player_OnPlayerDeath(playerid,killerid,reason)
{
	if(Player[playerid][pOnBox] == true) return 1; // Если погиб на боксе то обработка в другом инклуде,этот паблик обрываем
	Player[playerid][pDeaths]++; // добавляем смерть для отчёта админу
	if(killerid != INVALID_PLAYER_ID) Player[killerid][pKills]++; // добавляем килл для отчёта админу если игрока убил ктото
	/* Решаем что же с ним будет,умер или жив
	Для начала проверим смертельна ли причина (утонул,упал с высоты) */
	switch(reason)
	{
		case 49,53,54,255: /* причина - взрыв в авто,падение,автомобиль,сгорел... */
		{
			SetPlayerCameraPos(playerid, -127.9947,2258.2878,28.5071); // ставим камеру в чёрную зону
			SetPlayerCameraLookAt(playerid, -127.9947,2258.2878,20.5071); // ставим камеру в чёрную зону
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Ваш персонаж погиб...Предлагаем создать нового персонажа"); // Выводим сообщение о гибели
			ForceClassSelection(playerid); // возвращаем игрока в стадию создания персонажа
			return 1;
		}
	}
	/* Если мы тут то это значит что причина не обязательно смертельна,проверим его удачу 
	выставим уровни требуемой удачи в зависимости от оружия убийцы */
	new l_os; // первое ограничение
	new l_ts; // второе ограничение
	switch(reason) // расставляем ограничения...
	{
		case 0,1,2,3,5,6,7,10,11,12,13,14,41,42: // если рукопашное то ставим большую вероятность на хороший исход
		{
			l_os = 40;
			l_ts = 80;
		}
		default: // если огнестрельное... 40% - смерть...
		{
			l_os = 20;
			l_ts = 60;
		}
	}
	new luck = random(100); // берём число из 100...
	if(luck <= l_os) // если удача входит в первое ограничение...мы выжили и валяемся 2 минуты...
	{
		ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы получили ранения,ждите скорую помощь либо лежите 2 минуты для восстановления сил..."); // Выводим сообщение о полученом уроне
		new Float:X,
			Float:Y,
			Float:Z,
			Float:A,
			MInt,
			Int,
			VW;
		GetPlayerPos(playerid,X,Y,Z); // снимаем координаты смерти
		GetPlayerFacingAngle(playerid,A); // снимаем угол поворота смерти
		MInt = GetPlayerModeInterior(playerid); // снимаем интерьер мода смерти
		Int = GetPlayerInterior(playerid); // снимаем интерьер игры смерти
		VW = GetPlayerVirtualWorld(playerid); // снимаем интерьер игры смерти
		SetPlayerHealth(playerid,1.0); // ставим жизнь на единицу,чтобы небыло бага постоянной смерти
		SetPlayerPos(playerid,X,Y,Z); // ставим игрока на координаты смерти,чтобы если он был в транспорте его высунуло...
		SpawnPlayer(playerid); // спавним игрока...
		SetPlayerHealth(playerid,1.0); // ставим жизнь на единицу
		SetPlayerModeInterior(playerid,MInt); // возвращаем в прежний интерьер мода
		SetPlayerInterior(playerid,Int); // возвращаем в прежний интерьер
		SetPlayerVirtualWorld(playerid,VW); // возвращаем в прежний виртуальный мир
		SetPlayerPos(playerid,X,Y,Z); // ставим на координаты смерти...
		SetPlayerFacingAngle(playerid,A); // Ставим прежний угол поворота
		Player[playerid][pDeathTime] = 120; // ставим время 120 секунд - 60*2 - 2 минуты
		SetPlayerCameraPos(playerid, -127.9947,2258.2878,28.5071); // ставим камеру в чёрную зону
		SetPlayerCameraLookAt(playerid, -127.9947,2258.2878,20.5071); // ставим камеру в чёрную зону
		DownPlayer(playerid); // включаем анимацию...
	}
	else if(luck <= l_ts) // если удача входит во второе ограничение...мы выжили и валяемся 5 минут...
	{
		ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы получили ранения,ждите скорую помощь либо лежите 5 минут для восстановления сил..."); // Выводим сообщение о полученом уроне
		new Float:X,
			Float:Y,
			Float:Z,
			Float:A,
			MInt,
			Int,
			VW;
		GetPlayerPos(playerid,X,Y,Z); // снимаем координаты смерти
		GetPlayerFacingAngle(playerid,A); // снимаем угол поворота смерти
		MInt = GetPlayerModeInterior(playerid); // снимаем интерьер мода смерти
		Int = GetPlayerInterior(playerid); // снимаем интерьер игры смерти
		VW = GetPlayerVirtualWorld(playerid); // снимаем интерьер игры смерти
		SetPlayerHealth(playerid,1.0); // ставим жизнь на единицу,чтобы небыло бага постоянной смерти
		SetPlayerPos(playerid,X,Y,Z); // ставим игрока на координаты смерти,чтобы если он был в транспорте его высунуло...
		SpawnPlayer(playerid); // спавним игрока...
		SetPlayerHealth(playerid,1.0); // ставим жизнь на единицу
		SetPlayerModeInterior(playerid,MInt); // возвращаем в прежний интерьер мода
		SetPlayerInterior(playerid,Int); // возвращаем в прежний интерьер
		SetPlayerVirtualWorld(playerid,VW); // возвращаем в прежний виртуальный мир
		SetPlayerPos(playerid,X,Y,Z); // ставим на координаты смерти...
		SetPlayerFacingAngle(playerid,A); // Ставим прежний угол поворота
		Player[playerid][pDeathTime] = 300; // ставим время 300 секунд - 60*5 - 5 минут
		SetPlayerCameraPos(playerid, -127.9947,2258.2878,28.5071); // ставим камеру в чёрную зону
		SetPlayerCameraLookAt(playerid, -127.9947,2258.2878,20.5071); // ставим камеру в чёрную зону
		DownPlayer(playerid); // включаем анимацию...
	}
	else if(luck > l_ts)
	{
		SetPlayerCameraPos(playerid, -127.9947,2258.2878,28.5071); // ставим камеру в чёрную зону
		SetPlayerCameraLookAt(playerid, -127.9947,2258.2878,20.5071); // ставим камеру в чёрную зону
		ModeMessage(playerid,MODE_MESSAGE_OOC,"Ваш персонаж погиб...Предлагаем создать нового персонажа"); // Выводим сообщение о гибели
		DeleteActorFromWorld(playerid); // Удаляем персонажа отовсюду
		ResetStat(playerid); // обнуляем статистику игрока
		MySQL_RecreateAccount(playerid); // пересоздаём аккаунт
		ForceClassSelection(playerid); // возвращаем игрока в стадию создания персонажа
	}
	return 1;	
}

public Player_ResetStat(playerid)
{
	if(Player[playerid][pRegister] == false) Player[playerid][pName] = oGetPlayerName(playerid);
	Player[playerid][pRegister] = false;
	format(Player[playerid][pActor],MAX_PLAYER_NAME,"");
	Player[playerid][pSkin] = 101;
	Player[playerid][pSkinType] = 1;
	Player[playerid][pJailed] = false;
	Player[playerid][pDeath] = false;
	Player[playerid][pBlockCMD] = false;
	Player[playerid][pDeathTime] = 0;
	Player[playerid][pCreateCharStep] = CREATE_CHAR_SLEEP;
	Player[playerid][pDeathOnBox] = 0;
	Player[playerid][pOldClass] = 0;
	Player[playerid][pHealth] = 100.0;
	oSetPlayerMoney(playerid,START_MONEY);
	Player[playerid][pBankAccount] = 0;
	format(Player[playerid][pSpawn],10,"None");
	format(Player[playerid][pLocate],MAX_STRING,"");
	format(Player[playerid][pBirthday],MAX_STRING,"");
	format(PlayerIP[playerid],64,"");
	Player[playerid][pInBlackList] = 0;
	Player[playerid][pTimeInGame] = 0;
	Player[playerid][pDeaths] = 0;
	Player[playerid][pKills] = 0;
	Player[playerid][pStatus] = 0;
	Player[playerid][pGPSid] = 0;
	Player[playerid][pNumber] = 0;
	for(new i = 0;i < MAX_WEAPONS;i++) Player[playerid][pWeapons][i] = 0;
	Player[playerid][pWeaponLicense] = false;
	Player[playerid][pMoneyUpdateDelay] = 0;
	Player[playerid][pHealthUpdateDelay] = 0;
	Player[playerid][pEnterText] = 0;
	Player[playerid][pShowStreamedCP] = true;
	Player[playerid][pShowedCheckPoint] = -1;
	format(Player[playerid][pGang],MAX_PLAYER_NAME,"");
	Player[playerid][pGangStatus] = nullstr;
	Player[playerid][pGangId] = 0;
	Player[playerid][pInviteInGang] = 0;
	for(new i = 0;i < GANG_PRIVELEGES_ALL;i++) Player[playerid][pGangPrivileges][i] = false;
	Player[playerid][pSpecate] = INVALID_PLAYER_ID;
	Player[playerid][pWork] = 0;
	Player[playerid][pWorkScore] = 0;
	Player[playerid][pWorkProfit] = 0;
	Player[playerid][pYad] = 0;
	Player[playerid][pPrison] = 0;
	Player[playerid][pPrisonTime] = 0;
	Player[playerid][pArrested] = false;
	Player[playerid][pRaceId] = 0;
	Player[playerid][pRaceCp] = 0;
	Player[playerid][pRacesGone] = 0;
	Player[playerid][pRacesWon] = 0;
	Player[playerid][pAutoBuy] = 0;
	for(new i = 0;i < 3;i++) Player[playerid][pAutoBuyInfo][i] = 0;
	Player[playerid][pClotchBuy] = 0;
	for(new i = 0;i < 3;i++) Player[playerid][pClotchBuyInfo][i] = 0;
	format(Player[playerid][pGhost],MAX_PLAYER_NAME,"");
	for(new i = 0; i < 32; i++) Player[playerid][pIcons][i] = false;
	Player[playerid][pLastPickup] = 0;
	Player[playerid][pGangZone] = 0;
	Player[playerid][pGetZoneId] = 0;
	Player[playerid][pGangZoneFreez] = 0;
	Player[playerid][pGetZoneTimerId] = -1;
	Player[playerid][pUsePhone] = false;
	Player[playerid][pIncomingCall] = INVALID_PLAYER_ID;
	Player[playerid][pPhoneAnswer] = -1;
	Player[playerid][pCall] = INVALID_PLAYER_ID;
	Player[playerid][pFightScore] = 0;
	Player[playerid][pFightSkill] = 0;
	Player[playerid][pFightStyle] = 0;
	Player[playerid][pFightHit] = 0;
	Player[playerid][pFightDelay] = 0;
	Player[playerid][pFightAnim] = 0;
	Player[playerid][pWalkTime] = 0;
	Player[playerid][pWalkStyle] = 0;
	for(new i = 0;i < LICENSE_ALL;i++) Player[playerid][pLicenses][i] = false;
	Player[playerid][pLicenseTest] = false;
	for(new i = 0; i < 5; i++) Player[playerid][pLicenseTestInfo][i] = 0;
	Player[playerid][pPartTimeJobId] = 0;
	Player[playerid][pPartTimeJobTime] = 0;
	for(new i = 0; i < 7; i++) Player[playerid][pPartTimeJobInfo][i] = -1;
	Player[playerid][pDrugs] = 0;
	for(new i = 0; i < MAX_PLAYERS; i++) Player[playerid][pShowenPlayers][i] = false;
	Player[playerid][pEnterCode] = 0;
	return 1;
}

public Player_OnPlayerRequestClass(playerid,classid)
{
	SetPlayerColor(playerid,COLOUR_PLAYER);
	SetPlayerSkin(playerid,Player[playerid][pSkin]);
	/* если персонажа нет, и игрок зареган, и шаг реги на 0 */
	if(!strlen(Player[playerid][pActor]) && IsPlayerRegistered(playerid) && (Player[playerid][pCreateCharStep] == CREATE_CHAR_SLEEP)) CreateCharacter(playerid,CREATE_CHAR_START);
}

public Player_OnPlayerSpawn(playerid)
{
	SetPlayerColor(playerid,(COLOUR_PLAYER & 0xFFFFFF00)); // Ставим цвет игрока на прозрачный...
	GivePlayerOwnedWeapons(playerid); // Даём оружие которое было у игрока...
	SetPlayerHealth(playerid,Player[playerid][pHealth]); // Ставим жизнь на сохранённую...
	oSetPlayerMoney(playerid,Player[playerid][pMoney]); // Даём деньги игрока...
	SetPlayerSkin(playerid,Player[playerid][pSkin]); // ставим скин игрока...
	if(strcmp(Player[playerid][pSpawn],"None",true)) // Если у игрока есть спавн...
	{
		if(House_OnPlayerSpawn(playerid)) return 1; // Спавн в доме выполнен успешно
		if(GangHouses_OnPlayerSpawn(playerid)) return 1; // Спавн в ганг хаусе выполнен успешно
	}
	SetPlayerModeInterior(playerid,0);
	SetPlayerVirtualWorld(playerid,0);
	SetPlayerInterior(playerid,0);
	return 1;
}

public Player_OnPlayerUpdate(playerid)
{
	SyncMoney(playerid);
    if(oGetPlayerHealth(playerid) != Player[playerid][pHealth]) OnPlayerHealthChange(playerid,Player[playerid][pHealth],oGetPlayerHealth(playerid));
    Player[playerid][pHealth] = oGetPlayerHealth(playerid);
	/* Сохраняем всё оружие что у нас есть... */
	new weap_id,weap_ammo;
	for(new i = 0; i < 13; i++)
	{
	    GetPlayerWeaponData(playerid,i,weap_id,weap_ammo);
	    if(Player[playerid][pWeapons][weap_id] > weap_ammo) Player[playerid][pWeapons][weap_id] = weap_ammo;
		else 
		{
			if(weap_ammo > 900) GivePlayerWeapon(playerid,weap_id,-weap_ammo); /* если патронов больше 900 то это скорей всего чит,тихонько забираем оружие... */
			else Player[playerid][pWeapons][weap_id] = weap_ammo;
		}
	}
}

public Player_OnPlayerCommandText(playerid,text[])
{
	new idx,cmd[20];
	cmd = strtok(text," ",idx);
	if(!strcmp(cmd,"/register",true))
	{
		cmd = strtok(text," ",idx);
		if(!strlen(cmd)) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы не ввели пароль");
		if(IsPlayerRegistered(playerid)) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы зарегестрированы");
		if(!MySQL_CreatePlayer(playerid,cmd)) return 1;
		StopPlayerCamera(playerid,false);
		CreateCharacter(playerid,CREATE_CHAR_SHOW_HELP);
		return 1;
	}
	if(!strcmp(cmd,"/login",true))
	{
		cmd = strtok(text," ",idx);
		if(!strlen(cmd)) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы не ввели пароль");
		if(IsPlayerRegistered(playerid)) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы зарегестрированы");
		MySQL_LoadPlayer(playerid,cmd);
		return 1;
	}
	return 0;
}

public Player_OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{	
	if(newkeys == KEY_ACTION) OnPlayerPressEnterExitKey(playerid);
}

public Player_Check()
{
	PlayerCheck++;
	if(PlayerCheck == 60)
	{
		for(new i = 0;i < GetMaxPlayer();i++) 
		{
			if(!IsPlayerConnected(i)) continue;
			Player[i][pTimeInGame]++;
			UpdatePlayerScore(i);
		}
		PlayerCheck = 0;
	}
}

public Player_OnPlayerSave(playerid)
{
	MySQL_SavePlayer(playerid);
	return 1;
}

public Player_OnPlayerRequestClass(playerid,classid)
{
	switch(Player[playerid][pOldClass])
	{
		case 0: 
		{
			Player[playerid][pOldClass] = classid;
			if(classid == 1) MoveSelecting(playerid,KEY_RIGHT);
			else MoveSelecting(playerid,KEY_LEFT);
		}
		case 1: 
		{
			Player[playerid][pOldClass] = classid;
			if(classid == 2) MoveSelecting(playerid,KEY_RIGHT);
			else MoveSelecting(playerid,KEY_LEFT);
		}
		case 2: 
		{
			Player[playerid][pOldClass] = classid;
			if(classid == 0) MoveSelecting(playerid,KEY_RIGHT);
			else MoveSelecting(playerid,KEY_LEFT);
		}
	}
}

public Player_OnPlayerRequestSpawn(playerid)
{
	switch(Player[playerid][pCreateCharStep])
	{
		case CREATE_CHAR_SLEEP: return IsPlayerRegistered(playerid);
		case CREATE_CHAR_SELECT_WALK: return CreateCharacter(playerid,CREATE_CHAR_SELECT_WALK);
	}
	return 0;
}

/* ------------------------------------------------------------------- *
	Player chat
* ------------------------------------------------------------------- */

public PlayerSay(playerid,text[])
{
	PlayerMessage(playerid,text,MESSAGE_SAY);
	return 1;
}

public PlayerShout(playerid,text[])
{
	if(text[0] == '#')
	{
		strdel(text,0,1);
		PlayerMessage(playerid,text,MESSAGE_SCREAM);
		return 1;
	}
	return 0;
}

public PlayerOOC(playerid,text[])
{
	if(text[0] == '*')
	{
		strdel(text,0,1);
		PlayerMessage(playerid,text,MESSAGE_OOC);
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------- *
	Is... functions
* ------------------------------------------------------------------- */

public IsPlayerMan(playerid)
{
	if(Player[playerid][pSkinType] == 1 || Player[playerid][pSkinType] == 3) return 1;
	return 0;
}

public IsPlayerWoman(playerid)
{
	if(Player[playerid][pSkinType] == 2 || Player[playerid][pSkinType] == 4) return 1;
	return 0;
}

public IsPlayerRegistered(playerid)
{
	if(Player[playerid][pRegister] == false) return 0;
	return 1;
}

/* ------------------------------------------------------------------- *
	Added functions
* ------------------------------------------------------------------- */

public DeleteActorFromWorld(playerid)
{
	DeleteActorFromHouses(playerid);
	DeleteActorFromBusiness(playerid);
	DeleteActorFromGPS(playerid);
	DeleteActorFromBank(playerid);
}

public DownPlayer(playerid)
{
	if(Player[playerid][pDeathTime] > 0)
	{
		ApplyAnimation(playerid,"CRACK","crckdeth2",4.0,1,0,0,0,-1); 
		Player[playerid][pDeathTime]--;
		SetTimerEx("DownPlayer",500,0,"d",playerid);
	}
	else
	{
		ClearAnimations(playerid);
		SetCameraBehindPlayer(playerid);
		Player[playerid][pBlockCMD] = false;
	}
}

public SyncMoney(playerid)
{
	new clientmoney = GetPlayerMoney(playerid);
	if(clientmoney == Player[playerid][pMoney]) return;
	if(clientmoney > Player[playerid][pMoney]) oSetPlayerMoney(playerid,Player[playerid][pMoney]);
	return;
}

public UpdatePlayerScore(playerid)
{
	SetPlayerScore(playerid,Player[playerid][pTimeInGame]/60);
}

public oSetPlayerMoney(playerid,money)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,money);
	Player[playerid][pMoney] = money;
	return 1;
}

public oGivePlayerMoney(playerid,money,bool:showtext)
{
	if(money == 0) return 0;
	new string[MAX_STRING];
	if(money < 0)
	{
		if(showtext == true) ModeMessage(playerid,MODE_MESSAGE_OOC,"Bы потеряли %d$",-money);
		oSetPlayerMoney(playerid,Player[playerid][pMoney]+money);
		return 1;
	}
	else if((Player[playerid][pMoney] + money) > MAX_MONEY)
	{
		if(showtext == true) ModeMessage(playerid,MODE_MESSAGE_OOC,"Bы получили %d$,но у вас максимальное количество денег!Положите деньги в банк",money);
		oSetPlayerMoney(playerid,MAX_MONEY);
		return 1;
	}
	else 
	{
		if(showtext == true) ModeMessage(playerid,MODE_MESSAGE_OOC,"Bы получили %d$",money);
		oSetPlayerMoney(playerid,MAX_MONEY);
		return 1;
	}
	return 0;
}

public oGetPlayerMoney(playerid)
{
	return Player[playerid][pMoney];
}

public GivePlayerOwnedWeapons(playerid)
{
	ResetPlayerWeapons(playerid);
	for(new weapon = 1;weapon < MAX_WEAPONS;weapon++) 
	{
		if(Player[playerid][pWeapons][weapon] > 0) GivePlayerWeapon(playerid,weapon,Player[playerid][pWeapons][weapon]);
	}
	return 1;
}

public SetWeaponsFromDBString(playerid,dbstring[])
{
	new idx;
	for(new weapon = 0;weapon < MAX_WEAPONS;weapon++) Player[playerid][pWeapons][weapon] = strval(strtok(dbstring,"/",idx));
	return 1;
}

public MoveSelecting(playerid,leftright)
{
	if(Player[playerid][pCreateCharStep] == CREATE_CHAR_SELECT_WALK)
	{
		switch(leftright)
		{
			case KEY_LEFT:
			{
				if(GetPlayerWalkingStyle(playerid) > 0) SetPlayerWalkingStyle(playerid,GetPlayerWalkingStyle(playerid)-1);
				else SetPlayerWalkingStyle(playerid,13);
				ApplyAnimation(playerid,"PED",WalkStyle[GetPlayerWalkingStyle(playerid)-1],4.1,1,1,1,1,1);
			}
			case KEY_RIGHT:
			{
				if(GetPlayerWalkingStyle(playerid) < 13) SetPlayerWalkingStyle(playerid,GetPlayerWalkingStyle(playerid)+1);
				else SetPlayerWalkingStyle(playerid,0);
				ApplyAnimation(playerid,"PED",WalkStyle[GetPlayerWalkingStyle(playerid)-1],4.1,1,1,1,1,1);
			}
		}
	}
}

/* ------------------------------------------------------------------- *
	Player Drops
* ------------------------------------------------------------------- */

public DropPlayerWeapons(playerid)
{
    new playerweapons[13][2];
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid, x, y, z);

	for(new i = 0;i < 13;i++)
	{
    	GetPlayerWeaponData(playerid, i, playerweapons[i][0], playerweapons[i][1]);
    	new wmodel = GetWeaponModel(playerweapons[i][0]);
    	new Float:X = x + (random(3) - random(3));
    	new Float:Y = y + (random(3) - random(3));
    	if(playerweapons[i][1] != 0) 
		{
			if(wmodel!=-1) SetTimerEx("DeletePickup", 10000, false, "d",CreatePickup(wmodel, 3, X, Y, z));
		}
	}
	return 1;
}

public DeletePickup(pickupid)
{
	return DestroyPickup(pickupid);
}

public GetWeaponModel(weaponid)
{
	new wmodel;
	switch(weaponid)
	{
	    case 1: wmodel=331; case 2: wmodel=333; case 3: wmodel=334;
		case 4: wmodel=335; case 5: wmodel=336; case 6: wmodel=337;
		case 7: wmodel=338; case 8: wmodel=339; case 9: wmodel=341;
		case 10: wmodel=321; case 11: wmodel=322; case 12: wmodel=323;
		case 13: wmodel=324; case 14: wmodel=325; case 15: wmodel=326;
		case 16: wmodel=342; case 17: wmodel=343; case 18: wmodel=344;
		case 22: wmodel=346; case 23: wmodel=347; case 24: wmodel=348;
		case 25: wmodel=349; case 26: wmodel=350; case 27: wmodel=351;
		case 28: wmodel=352; case 29: wmodel=353; case 30: wmodel=355;
		case 31: wmodel=356; case 32: wmodel=372; case 33: wmodel=357;
		case 34: wmodel=358; case 35: wmodel=359; case 36: wmodel=360;
		case 37: wmodel=361; case 38: wmodel=362; case 39: wmodel=363;
		case 41: wmodel=365; case 42: wmodel=366; case 46: wmodel=371;
	}
	if(wmodel < 300) return -1;
	return wmodel;
}

// --------------------------------------------------
// stocks
// --------------------------------------------------

stock CreateCharacter(playerid,step,{Float,_}:...)
{
	switch(step)
	{
		case CREATE_CHAR_SHOW_HELP:
		{
			Player[playerid][pCreateCharStep] = CREATE_CHAR_SHOW_HELP;
			PlayerHelper(playerid,0);
			return 1;
		}
		case CREATE_CHAR_START:
		{
			StopPlayerCamera(playerid,false);
			TextDrawHideForPlayer(playerid,BlackScreen[4]);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Введите имя и фамилию своего персонажа.Пример: Vasya Pupkin");
			MovePlayerCameraAroundXYZ(playerid,200.0,1546.385986,-1355.594238,329.470397);
			Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_NAME;
			return 1;
		}
		case CREATE_CHAR_ENTER_NAME:
		{
			new k = 0;
			new chars;
			new arg_line[MAX_STRING];
			chars = getarg(3,k);
			while(chars != 0)
			{
				chars = getarg(3,k);
				if(chars != 0)
				{
					format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
					k++;
				}
			}
			format(Player[playerid][pActor],MAX_PLAYER_NAME,arg_line);
			SetPlayerName(playerid,arg_line);
			ModeMessage(playerid,MODE_MESSAGE_IC,"Здравствуйте %s,я заполню ваш паспорт.Какой у вас пол?",arg_line);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Введите М или Ж");
			Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_SEX;
			return 1;
		}
		case CREATE_CHAR_ENTER_SEX:
		{
			new k = 0;
			new chars;
			new arg_line[MAX_STRING];
			chars = getarg(3,k);
			while(chars != 0)
			{
				chars = getarg(3,k);
				if(chars != 0)
				{
					format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
					k++;
				}
			}
			if(!strcmp(arg_line,"М",true) || !strcmp(arg_line,"M",true))
			{
				Player[playerid][pSkinType] = 1;
				Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_SKIN;
				ModeMessage(playerid,MODE_MESSAGE_IC,"Мужчина,это хорошо...Ваш цвет кожи?");
				ModeMessage(playerid,MODE_MESSAGE_OOC,"Введите Белый или Черный");
			}
			if(!strcmp(arg_line,"Ж",true))
			{
				Player[playerid][pSkinType] = 3;
				Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_SKIN;
				ModeMessage(playerid,MODE_MESSAGE_IC,"Женщина,это хорошо...Ваш цвет кожи?");
				ModeMessage(playerid,MODE_MESSAGE_OOC,"Введите Белый или Черный");
			}
			return 1;
		}
		case CREATE_CHAR_ENTER_SKIN:
		{
			new k = 0;
			new chars;
			new arg_line[MAX_STRING];
			chars = getarg(3,k);
			while(chars != 0)
			{
				chars = getarg(3,k);
				if(chars != 0)
				{
					format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
					k++;
				}
			}
			if(!strcmp(arg_line,"белый",true))
			{
				if(Player[playerid][pSkinType] == 1) Player[playerid][pSkin] = 101;
				else Player[playerid][pSkin] = 169;
				Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_AGE;
				ModeMessage(playerid,MODE_MESSAGE_IC,"И так вы белый.Год вашего рождения?");
				ModeMessage(playerid,MODE_MESSAGE_OOC,"Пример: 01.05.1990");
			}
			if(!strcmp(arg_line,"черный",true))
			{
				if(Player[playerid][pSkinType] == 1) {Player[playerid][pSkinType] = 2;Player[playerid][pSkin] = 19;}
				else {Player[playerid][pSkinType] = 4;Player[playerid][pSkin] = 13;}
				Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_AGE;
				ModeMessage(playerid,MODE_MESSAGE_IC,"И так вы черный.Год вашего рождения?");
				ModeMessage(playerid,MODE_MESSAGE_OOC,"Пример: 01.05.1990");
			}
			return 1;
		}
		case CREATE_CHAR_ENTER_AGE:
		{
			new k = 0;
			new chars;
			new arg_line[MAX_STRING];
			chars = getarg(3,k);
			while(chars != 0)
			{
				chars = getarg(3,k);
				if(chars != 0)
				{
					format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
					k++;
				}
			}
			new data[3][20],idx;
			format(data[0],20,strtok(arg_line,".",idx));
			format(data[1],20,strtok(arg_line,".",idx));
			format(data[2],20,strtok(arg_line,".",idx));
			if(strval(data[0]) > 31 || strval(data[0]) < 0) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Не верный день");
			if(strval(data[1]) > 12 || strval(data[1]) < 0) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Не верный месяц");
			if(strval(data[2]) > 2005 || strval(data[2]) < 1940) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Не верный год");
			new nowdata[3];
			new years;
			new bool:IsBirthDay;
			getdate(nowdata[0],nowdata[1],nowdata[2]);
			if(nowdata[1] > strval(data[1])) {years = nowdata[0] - strval(data[2]);}
			else if(nowdata[1] < strval(data[1])) {years = nowdata[0] - strval(data[2]) - 1;}
			else
			{
				if(nowdata[2] > strval(data[0])) {years = nowdata[0] - strval(data[2]);}
				else if(nowdata[2] < strval(data[0])) {years = nowdata[0] - strval(data[2]) - 1;}
				else {years = nowdata[0] - strval(data[2]);IsBirthDay = true;}
			}
			if(IsBirthDay == true) ModeMessage(playerid,MODE_MESSAGE_IC,"Поздравляю с днём рождения!Счастья вам и здоровья!%d прекрасный возраст!Ну продолжим...Где вы родились?",years);
			else ModeMessage(playerid,MODE_MESSAGE_IC,"Вам %d лет...Где вы родились?",years);
			format(Player[playerid][pBirthday],MAX_STRING,"%s.%s.%s",data[0],data[1],data[2]);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Пример: Россия,Кемерово");
			Player[playerid][pCreateCharStep] = CREATE_CHAR_ENTER_LOCATE;
			return 1;
		}
		case CREATE_CHAR_ENTER_LOCATE:
		{
			new k = 0;
			new chars;
			new arg_line[MAX_STRING];
			chars = getarg(3,k);
			while(chars != 0)
			{
				chars = getarg(3,k);
				if(chars != 0)
				{
					format(arg_line,sizeof(arg_line),"%s%c",arg_line,chars);
					k++;
				}
			}
			if(strlen(text) > 30) return ModeMessage(playerid,MODE_MESSAGE_OOC,"Неверная длина");
			ModeMessage(playerid,MODE_MESSAGE_IC,"Так и запишем: %s.Удачи в нашем штате!",arg_line);
			format(Player[playerid][pLocate],MAX_STRING,arg_line);
			
			StopPlayerCamera(playerid,false);
			ClearAnimations(playerid);
			MovePlayerCameraPosEx(playerid,-2484.081787,-270.037841,40.557163,-2484.081787,-287.238891,40.557163,-2480.077880,-285.438781,40.557163,3.0);
			SetPlayerPos(playerid,-2480.077880,-285.438781,40.557163);
			SetPlayerFacingAngle(playerid,88.979431);
			SetPlayerFightingStyle(playerid,1);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Выберите свой стиль боя,после регистрации изменить его будет нельзя.Нажмите SHIFT когда закончите выбор");			
			Player[playerid][pCreateCharStep] = CREATE_CHAR_SELECT_FIGHT;
			return 1;
		}
		case CREATE_CHAR_SELECT_FIGHT:
		{
			StopPlayerCamera(playerid,false);
			ClearAnimations(playerid);
			etPlayerPos(playerid,837.798645,-2051.708007,12.867187);
			SetPlayerFacingAngle(playerid,359.448150);
			MovePlayerCameraAroundXYZ(playerid,7,837.798645,-2051.708007,12.867187);
			SetPlayerWalkingStyle(playerid,1);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Выберите свой стиль ходьбы,после регистрации изменить его будет нельзя.Нажмите SHIFT когда закончите выбор");			
			Player[playerid][pCreateCharStep] = CREATE_CHAR_SELECT_WALK;
			return 1;
		}
		case CREATE_CHAR_SELECT_WALK:
		{
			RegisterStep[playerid] = CREATE_CHAR_NONE;
			Player[playerid][pNumber] = random(89999) + 10000;
			Player[playerid][pNumber] = NewPlayerPhoneNumber();
			Player[playerid][pGPSid] = NewPlayerGPSid();
			Player[playerid][pBankAccount] = NewPlayerBankAccount();
			Player[playerid][pBankCode] = random(9999) + 1000;
			MySQL_AddBankAccount(Player[playerid][pBankAccount],Player[playerid][pBankCode]);
			PlayerSave(playerid);
			ModeMessage(playerid,MODE_MESSAGE_IC,"Ваш телефонный номер: %d ,ваш GPSid: %d, лицевой счёт в банке: %d, пароль счёта: %d",Player[playerid][pNumber],Player[playerid][pGPSid],Player[playerid][pBankAccount],Player[playerid][pBankCode]);
			Player[playerid][pBlockCMD] = false;
			StopPlayerCamera(playerid,true);
			SpawnPlayer(playerid);
			return 1;
		}
	}
	return 0;
}

stock PlayerHelper(playerid,time)
{
	if(!IsPlayerConnected(playerid)) return 0;
	new tmp[MAX_STRING];
	switch(time)
	{
		case 0:
		{
			StopPlayerCamera(playerid,false);
			MovePlayerCameraAroundXYZ(playerid,2000.0,0.0,0.0,-140.0);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"На сервере установлен мод %s,это новый,не имеющий аналогов мод,написанный с нуля.",GAMEMODE_NAME);			
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Жанр мода - RolePlay - ролевая игра,вы должны вжиться в роль жителя штата");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"San Andreas.Можно выбрать любой путь жизни своего персонажа - от уличного гонщика,");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"до главы ФБР.");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"%s имеет много уникальных особенностей,с которыми раньше вы могли не сталкиваться,поэтому",GAMEMODE_NAME);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"вам опишутся они в подробностях управления");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 20:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Для начала - транспортные средства(ТС).Вы можете водить любое ТС,вне");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"зависимости ваше ли оно и есть ли у вас лицензия на управления им(до встречи с органами правопорядка...)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Но ТС закрывают,для закрытия использую пароль(аналог ключей...), к примеру командой '/lock 1234'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"вы закроете ТС в котором находитесь,и никто не сможет в него сесть не введя '/unlock 1234'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Когда хотите сесть в ТС,вам нужно ввести '/unlock <код>' и после этого садится в ТС,чтобы открыть ТС");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"нужно ввести '/unlock <код>' сидя в ТС");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"ТС никуда не перемещаются \"сами по себе\",даже после рестарта сервера они на том же месте где и были");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"(кроме статических - полицейские и т.п.)");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");		
		}
		case 40:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - система GPS.");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Игровой радар - экран GPS,GPS принимает данные GPS сети штата,и все важные места отмечаются на вашем GPS");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Так же ваш GPS имеет уникальный GPS-id, вы можете сообщить другу свой GPS-id и он сможет добавить вас в свой GPS");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"командой '/gps add <gps-id>' после чего он будет видеть вас на своём GPS,так же можно удалить определённый gps-id");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"из своего GPS командой '/gps del <gps-id>'");	
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 60:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - мобильные телефоны");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"У вас есть мобильный телефон,вы можете звонить/отправлять смс и добавлять/удалять записи из телефонной книжки");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы можете сообщить свой телефон другу и он сможет добавить его в телефонную книжку командой '/pb add <номер> <имя>'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"после чего сможет найти ваш номер в своей книжке(команда '/pb <страница>'),телефонную книжку можно использовать для хранения");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"любых записей(главное что 1 параметр - цифра, 2 параметр - что угодно),так же можно удалить запись командой '/pb del <номер>'");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Для того чтобы звонить человеку нужно набрать команду '/call <номер>' или отправить смс командой '/sms <номер> <текст>'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Также есть определённые номера городских служб,подробнее в команде '/pnumbers'");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 80:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - счёт в банке");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы имеете собственный счёт в банке,для управления счётом нужно знать номер счёта и пароль доступа");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы можете использовать банкоматы либо прийти в банк и там снять/положить деньги");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"На чекпоинте нужно ввести '/bank menu' и появится меню с выбором: снять/положить деньги на счёт");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Выбираете нужное действие и пишите в чат номер счёта,пароль,сумму через пробел,пример: 12345 1234 100");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"12345 - номер счёта");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"1234 - пароль");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"100 - сумма денег");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы можете сообщить другу номер счёта и пароль,он сможет использовать ваш счёт,но это крайне не рекомендуется");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"в связи с тем что могут обмануть и ограбить");
		}
		case 100:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - уличные гонки");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы можете устраивать уличные гонки(хотя правоохранительные органы будут не рады такому) и получать деньги");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Заранее созданных трасс...нет.чтобы устроить гонку вам нужно приехать к желаемому месту старта и ввести '/race build <ставка>'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"далее приехать к месту финиша и ввести '/race apply'...гонка создана,вам сообщается GPS-id канала гонки,он нужен");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Для приглашения противников,вы сообщаете им GPS-id, они вводят '/race join <gps-id>' и едут к указанному на GPS месту старта");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"когда все собирутся организатор гонки вводит '/race start',у всех участников забирается ставка,и начинается отсчёт");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"тот кто прибудет первым получает все деньги(ставка * количество гонщиокв) по прибытию последнего гонщика гонка удалится");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 120:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - спортивные залы");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В спортивных залах можно повысить силу удара(нажимать \"спринт\" на красном коврике)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"либо устроить поединок(нажать \"огонь\" на пикапе красных человечков),проиграв поединок вы не умрёте");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"а только потеряете сознание");
			SendMessage(playerid,COLOUR_HELPER," ");	
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 140:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - смерть");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Игровая смерть вполне может стать смертью вашего персонажа...");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"При смерти вы имеете 40\% вероятность что угрозы для жизни не будет(выжили!ура!)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"40\% вероятность что вы \"чудом выжили\"(ещёб чуть чуть...и...)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"и 20\% вероятность летального исхода...что будет означать создание нового персонажа");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Конечно создав нового персонажа вы потеряете весь прогресс что был у прошлого");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"поэтому старайтесь не подвергать себя опасности");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 160:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - недвижимость");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Есть 2 типа недвижимости - личные дома и бизнесы");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Купить дом сразу - проблема,т.к. цены в штате не маленькие,поэтому");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"советуем взять комнату в аренду у кого нибудь,либо снять номер в отеле");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"арендную плату устанавливает владелец дома,так же он может запретить аренду либо");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"выселить арендатора");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 180:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Бизнесы в свою очередь разделяются на 5 типов");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Автомагазин,Гостиница,Магазин одежды,Магазин оружия,тюнинг-салон");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В автомагазине можно купить ТС");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В гостинице арендовать комнату");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В магазине одежды купить одежду");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В магазине оружия купить оружие");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В тюнинг салоне тюнинговать своё ТС");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"За бизнесы снимается налог,поэтому если бизнес не приносит дохода советуется его продать");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 200:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Следующее - банды");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Любой может основать свою банду и вступить в войну за территории,т.к. все города штата");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Разделены на территории,не советуется проникать на территорию другой банды - вас могут убить");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Банды могут покупать дома банд - гангхаусы,это большие сооружения с хорошей защитой,но и стоят много");
			SendMessage(playerid,COLOUR_HELPER," ");	
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 220:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Основные особенности описаны,так же есть другие ,но не новые черты мода как работы,подработки,");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"сервис такси и межгородских самолётов и некоторые \"сюрпризы\" которые будет интересно найти");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"А теперь прочтите основы ролевой игры");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");	
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 240:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Чат:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Чат разделяется на IC(In character - разговоры персонажей) и OOC(Out Of Character - разговоры игроков,всё что не относится");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"к роли)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В IC чате запрещены смайлы,розговоры не касающиеся роли");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В ООС чате можно всё кроме матов оскарблений и прочего");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Префиксы чатов:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Обычный чат(Vasya_Pupkin сказал: траляля) - нет префикса (траляля)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Крик(Vasya_Pupkin крикнул: траляля) - # (#траляля)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"OOC чат((Vasya_Pupkin сказал: траляля)) - * (*траляля)");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Me чат(Vasya_Pupkin упал) - /me (/me упал)");
		}
		case 260:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Игра:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Старайтесь поступать так,как поступили бы в жизни");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"И не злитесь на часть игроков именуемых \"noobs\" за их идиотизм,просто сообщите администрации о них");
			SendMessage(playerid,COLOUR_HELPER," ");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Вы не можете убивать без причины - так в жизни не поступают,решиться на убийство трудно,считайте что");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"человечек из игры это настоящий и подумайте - смогли бы вы убить человека?");
			SendMessage(playerid,COLOUR_HELPER," ");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Администрация следит за действиями игроков,при необходимости выносит предупреждения,в крайнем случае - бан");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 280:
		{
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Некоторая помощь:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Все белые конусы работают при нажатии кнопка \"действие\"");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"В основном это входы и выходы из домов и прочего");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Команды помощи:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"'/help' , '/bank help' , '/biz help' , '/gang help' , '/gh help' , '/gz help' , '/gps help'");	
			ModeMessage(playerid,MODE_MESSAGE_OOC,"'/h help' , '/l help' , '/ptj help' , '/p help' , '/race help' , '/job help'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Списки команд:");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"'/commands' , '/biz commands' , '/gang commands' , '/gh commands' , '/h commands' , '/ptj commands'");
			ModeMessage(playerid,MODE_MESSAGE_OOC,"'/p commands' , '/race commands' , '/job commands'");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 300:
		{
			StopPlayerCamera(playerid,false);
			MovePlayerCameraPosEx(playerid,-894.255676,-1112.811279,106.216537,-1218.666381,-780.352844,67.471176,-1218.666381,-780.352844,67.471176,2.0);
			ModeMessage(playerid,MODE_MESSAGE_OOC,"Сейчас вы перейдёте на этап создания персонажа");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
			SendMessage(playerid,COLOUR_HELPER," ");
		}
		case 320:
		{
			MySQL_EndShowedHelp(playerid);
			return CreateCharacter(playerid,CREATE_CHAR_START);
		}
	}
	time++;
	SetTimerEx("PlayerHelper",1000,0,"dd",playerid,time);
	return 1;
}