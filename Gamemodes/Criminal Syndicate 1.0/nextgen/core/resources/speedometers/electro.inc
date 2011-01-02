/*
*	Created:			17.01.10
*	Author:				009
*	Description:		Электронный спидометр
*						1 тип: есть спидометр и бензометр, в виде цифр
*						2 тип: есть спидометр и бензометр, в виде строки символов ( |||||| либо ______ )
*						3 тип: есть спидометр и бензометр и "турбо", в виде цифр
*						4 тип: есть спидометр и бензометр и "турбо", в виде строки символов ( |||||| либо ______ )
*/

#if defined _electro_included
  #endinput
#endif

#define _electro_included
#pragma library electro

// --------------------------------------------------
// defines
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
// тип 1, тип 2
enum E_SET1
{
	Float:sBackground[4],
	sBackgroundColor,
	Float:sSpeedoPos[2],
	sSpeedoColor,
	Float:sFuelPos[2],
	sFuelColor,
	sTextStyle
};
// тип 3, тип 4
enum E_SET2
{
	Float:sBackground[4],
	sBackgroundColor,
	Float:sSpeedoPos[2],
	sSpeedoColor,
	Float:sFuelPos[2],
	sFuelColor,
	Float:sTurboPos[2],
	sTurboColor,
	sTextStyle
};

// --------------------------------------------------
// news
// --------------------------------------------------
static
	SpeedoType1[][E_SET1] =
	{
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,1},
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,2}
	},
	SpeedoType2[][E_SET1] =
	{
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,'_'},
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,'|'}
	},
	SpeedoType3[][E_SET2] =
	{
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,{160.0,400.0},0x33AAFFFF,1},
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,{160.0,400.0},0x33AAFFFF,2}
	},
	SpeedoType4[][E_SET2] =
	{
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,{160.0,400.0},0x33AAFFFF,'_'},
		{{460.0,375.0,150.0,5.0},0xFFFF00AA,{160.0,380.0},0x33AAFFFF,{160.0,390.0},0x33AAFFFF,{160.0,400.0},0x33AAFFFF,'|'}
	},
	// BackGround TextDraws
	Text:SpeedoTextType1[sizeof(SpeedoType1)],
	Text:SpeedoTextType2[sizeof(SpeedoType2)],
	Text:SpeedoTextType3[sizeof(SpeedoType3)],
	Text:SpeedoTextType4[sizeof(SpeedoType4)],
	// players identificators
	// speed
	Text:PlayerTextSpeed[MAX_PLAYERS],
	PlayerDataSpeed[MAX_PLAYERS],
	// fuel
	Text:PlayerTextFuel[MAX_PLAYERS],
	PlayerDataFuel[MAX_PLAYERS],
	// turbo
	Text:PlayerTextTurbo[MAX_PLAYERS],
	PlayerDataTurbo[MAX_PLAYERS];

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native SpeedometerElectroLoad();
native SpeedometerElectroShow(playerid,type,speedoid);
native SpeedometerElectroHide(playerid,type,speedoid);
native SpeedometerElectroUpdate(playerid,type,speedoid,data[3]);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock SpeedometerElectroLoad()
{
	new Text:tid;
	// Создание текстов 1 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType1);speedoid++)
	{
		tid = TextDrawCreate(SpeedoType1[speedoid][sBackground][0],SpeedoType1[speedoid][sBackground][1],"_");
		TextDrawUseBox(tid,1);
		TextDrawTextSize(tid,SpeedoType1[speedoid][sBackground][2],0.0);
		TextDrawLetterSize(tid,0.0,SpeedoType1[speedoid][sBackground][3]);
		TextDrawBoxColor(tid,SpeedoType1[speedoid][sBackgroundColor]);
		SpeedoTextType1[speedoid] = tid; // bg
	}
	// Создание текстов 2 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType2);speedoid++)
	{
		tid = TextDrawCreate(SpeedoType2[speedoid][sBackground][0],SpeedoType2[speedoid][sBackground][1],"_");
		TextDrawUseBox(tid,1);
		TextDrawTextSize(tid,SpeedoType2[speedoid][sBackground][2],0.0);
		TextDrawLetterSize(tid,0.0,SpeedoType2[speedoid][sBackground][3]);
		TextDrawBoxColor(tid,SpeedoType2[speedoid][sBackgroundColor]);
		SpeedoTextType2[speedoid] = tid; // bg
	}
	// Создание текстов 3 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType3);speedoid++)
	{
		tid = TextDrawCreate(SpeedoType3[speedoid][sBackground][0],SpeedoType3[speedoid][sBackground][1],"_");
		TextDrawUseBox(tid,1);
		TextDrawTextSize(tid,SpeedoType3[speedoid][sBackground][2],0.0);
		TextDrawLetterSize(tid,0.0,SpeedoType3[speedoid][sBackground][3]);
		TextDrawBoxColor(tid,SpeedoType3[speedoid][sBackgroundColor]);
		SpeedoTextType3[speedoid] = tid; // bg
	}
	// Создание текстов 4 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType4);speedoid++)
	{
		tid = TextDrawCreate(SpeedoType4[speedoid][sBackground][0],SpeedoType4[speedoid][sBackground][1],"_");
		TextDrawUseBox(tid,1);
		TextDrawTextSize(tid,SpeedoType4[speedoid][sBackground][2],0.0);
		TextDrawLetterSize(tid,0.0,SpeedoType4[speedoid][sBackground][3]);
		TextDrawBoxColor(tid,SpeedoType4[speedoid][sBackgroundColor]);
		SpeedoTextType4[speedoid] = tid; // bg
	}
	// players info reset
	for(new playerid = 0;playerid < MAX_PLAYERS;playerid++)
	{
	    PlayerTextSpeed[playerid] = INVALID_TEXT_DRAW;
		PlayerTextFuel[playerid] = INVALID_TEXT_DRAW;
		PlayerTextTurbo[playerid] = INVALID_TEXT_DRAW;
	}
}

stock SpeedometerElectroShow(playerid,type,speedoid)
{
	switch(type)
	{
		case 0: TextDrawShowForPlayer(playerid,SpeedoTextType1[speedoid]);
		case 1: TextDrawShowForPlayer(playerid,SpeedoTextType2[speedoid]);
		case 2: TextDrawShowForPlayer(playerid,SpeedoTextType3[speedoid]);
		case 3: TextDrawShowForPlayer(playerid,SpeedoTextType4[speedoid]);
	}
}

stock SpeedometerElectroHide(playerid,type,speedoid)
{
    TextDrawDestroy(PlayerTextSpeed[playerid]);
    TextDrawDestroy(PlayerTextFuel[playerid]);
    TextDrawDestroy(PlayerTextTurbo[playerid]);
    PlayerTextSpeed[playerid] = INVALID_TEXT_DRAW;
    PlayerTextFuel[playerid] = INVALID_TEXT_DRAW;
    PlayerTextTurbo[playerid] = INVALID_TEXT_DRAW;
	switch(type)
	{
		case 0: TextDrawHideForPlayer(playerid,SpeedoTextType1[speedoid]);
		case 1: TextDrawHideForPlayer(playerid,SpeedoTextType2[speedoid]);
		case 2: TextDrawHideForPlayer(playerid,SpeedoTextType3[speedoid]);
		case 3: TextDrawHideForPlayer(playerid,SpeedoTextType4[speedoid]);
	}
}

stock SpeedometerElectroUpdate(playerid,type,speedoid,data[3])
{
	switch(type)
	{
		case 0:
		{
			ShowIdentSpeed(playerid,0,SpeedoType1[speedoid][sSpeedoPos][0],SpeedoType1[speedoid][sSpeedoPos][1],SpeedoType1[speedoid][sSpeedoColor],SpeedoType1[speedoid][sTextStyle],data[0]);
			ShowIdentFuel(playerid,0,SpeedoType1[speedoid][sFuelPos][0],SpeedoType1[speedoid][sFuelPos][1],SpeedoType1[speedoid][sFuelColor],SpeedoType1[speedoid][sTextStyle],data[1]);
		}
		case 1:
		{
			ShowIdentSpeed(playerid,1,SpeedoType2[speedoid][sSpeedoPos][0],SpeedoType2[speedoid][sSpeedoPos][1],SpeedoType2[speedoid][sSpeedoColor],SpeedoType2[speedoid][sTextStyle],data[0]);
			ShowIdentFuel(playerid,1,SpeedoType2[speedoid][sFuelPos][0],SpeedoType2[speedoid][sFuelPos][1],SpeedoType2[speedoid][sFuelColor],SpeedoType2[speedoid][sTextStyle],data[1]);
		}
		case 2:
		{
			ShowIdentSpeed(playerid,0,SpeedoType3[speedoid][sSpeedoPos][0],SpeedoType3[speedoid][sSpeedoPos][1],SpeedoType3[speedoid][sSpeedoColor],SpeedoType3[speedoid][sTextStyle],data[0]);
			ShowIdentFuel(playerid,0,SpeedoType3[speedoid][sFuelPos][0],SpeedoType3[speedoid][sFuelPos][1],SpeedoType3[speedoid][sFuelColor],SpeedoType3[speedoid][sTextStyle],data[1]);
			ShowIdentTurbo(playerid,0,SpeedoType3[speedoid][sTurboPos][0],SpeedoType3[speedoid][sTurboPos][1],SpeedoType3[speedoid][sTurboColor],SpeedoType3[speedoid][sTextStyle],data[2]);
		
		}
		case 3:
		{
			ShowIdentSpeed(playerid,1,SpeedoType4[speedoid][sSpeedoPos][0],SpeedoType4[speedoid][sSpeedoPos][1],SpeedoType4[speedoid][sSpeedoColor],SpeedoType4[speedoid][sTextStyle],data[0]);
			ShowIdentFuel(playerid,1,SpeedoType4[speedoid][sFuelPos][0],SpeedoType4[speedoid][sFuelPos][1],SpeedoType4[speedoid][sFuelColor],SpeedoType4[speedoid][sTextStyle],data[1]);
			ShowIdentTurbo(playerid,1,SpeedoType4[speedoid][sTurboPos][0],SpeedoType4[speedoid][sTurboPos][1],SpeedoType4[speedoid][sTurboColor],SpeedoType4[speedoid][sTextStyle],data[2]);
		}
	}
}

// --------------------------------------------------
// local utils
// --------------------------------------------------
static ShowIdentSpeed(playerid,type,Float:X,Float:Y,color,style,data)
{
	if((PlayerTextSpeed[playerid] == INVALID_TEXT_DRAW) || (PlayerDataSpeed[playerid] != data))
	{
		new val[40],
			Text:tid;
		switch(type)
		{
			case 0: valstr(val,data);
			case 1: {for(new i = 0;i < (data / 10);i++) format(val,sizeof(val),"%s%c",val,style);}
		}
		if(PlayerTextSpeed[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextSpeed[playerid]);
		tid = TextDrawCreate(X,Y,val);
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawFont(tid, style);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextSpeed[playerid] = tid;
		PlayerDataSpeed[playerid] = data;
	}
}

static ShowIdentFuel(playerid,type,Float:X,Float:Y,color,style,data)
{
	if((PlayerTextFuel[playerid] == INVALID_TEXT_DRAW) || (PlayerDataFuel[playerid] != data))
	{
		new val[40],
			Text:tid;
		switch(type)
		{
			case 0: valstr(val,(data * 10));
			case 1: {for(new i = 0;i < data;i++) format(val,sizeof(val),"%s%c",val,style);}
		}
		if(PlayerTextFuel[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextFuel[playerid]);
		tid = TextDrawCreate(X,Y,val);
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawFont(tid, style);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextFuel[playerid] = tid;
		PlayerDataFuel[playerid] = data;
	}
}

static ShowIdentTurbo(playerid,type,Float:X,Float:Y,color,style,data)
{
	if((PlayerTextTurbo[playerid] == INVALID_TEXT_DRAW) || (PlayerDataTurbo[playerid] != data))
	{
		new val[40],
			Text:tid;
		switch(type)
		{
			case 0: valstr(val,(data * 10));
			case 1: {for(new i = 0;i < data;i++) format(val,sizeof(val),"%s%c",val,style);}
		}
		if(PlayerTextTurbo[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextTurbo[playerid]);
		tid = TextDrawCreate(X,Y,val);
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawFont(tid, style);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextTurbo[playerid] = tid;
		PlayerDataTurbo[playerid] = data;
	}
}
