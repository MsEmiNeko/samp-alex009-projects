/*
*	Created:			15.01.10
*	Author:				009
*	Description:		Аналоговый спидометр(механический)
*						1 тип: есть спидометр и бензометр
*						2 тип: есть спидометр и бензометр, нумерация спидометра
*						3 тип: есть спидометр и бензометр, нумерация спидометра и бензометра
*						4 тип: есть спидометр и бензометр и "турбо"
*						5 тип: есть спидометр и бензометр и "турбо", нумерация спидометра
*						6 тип: есть спидометр и бензометр и "турбо", нумерация спидометра и бензометра
*						7 тип: есть спидометр и бензометр и "турбо", нумерация спидометра и бензина и "турбо"
*						8 тип: есть спидометр и бензометр и "турбо", нумерация спидометра и "турбо"
*/

#if defined _analog_included
  #endinput
#endif

#define _analog_included
#pragma library analog

// --------------------------------------------------
// defines
// --------------------------------------------------
#if defined INVALID_TEXT_DRAW
	#undef INVALID_TEXT_DRAW
#endif
#define INVALID_TEXT_DRAW Text:0xFFFF

// --------------------------------------------------
// enums
// --------------------------------------------------
// тип 1, тип 2, тип 3
enum E_SAT1
{
	sMaxSpeed,
	sColor,
	Float:sSpeedoPos[4],
	Float:sFuelPos[4]
};
// тип 4 , 5 , 6 , 7 , 8
enum E_SAT2
{
	sMaxSpeed,
	sColor,
	Float:sSpeedoPos[4],
	Float:sFuelPos[4],
	Float:sTurboPos[4]
};

// --------------------------------------------------
// news
// --------------------------------------------------
static
	SpeedoType1[][E_SAT1] =
	{
		{50,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}
	},
	SpeedoType2[][E_SAT1] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}
	},
	SpeedoType3[][E_SAT1] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}
	},
	SpeedoType4[][E_SAT2] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}
	},
	SpeedoType5[][E_SAT2] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}
	},
	SpeedoType6[][E_SAT2] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}
	},
	SpeedoType7[][E_SAT2] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}
	},
	SpeedoType8[][E_SAT2] =
	{
		{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
		{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}
	},
	// speedo circle TextDraws
	Text:SpeedoCircleTextType1[sizeof(SpeedoType1)][50],
	Text:SpeedoCircleTextType2[sizeof(SpeedoType2)][50],
	Text:SpeedoCircleTextType3[sizeof(SpeedoType3)][50],
	Text:SpeedoCircleTextType4[sizeof(SpeedoType4)][50],
	Text:SpeedoCircleTextType5[sizeof(SpeedoType5)][50],
	Text:SpeedoCircleTextType6[sizeof(SpeedoType6)][50],
	Text:SpeedoCircleTextType7[sizeof(SpeedoType7)][50],
	Text:SpeedoCircleTextType8[sizeof(SpeedoType8)][50],
	// fuel circle TextDraws
	Text:FuelCircleTextType1[sizeof(SpeedoType1)][10],
	Text:FuelCircleTextType2[sizeof(SpeedoType2)][10],
	Text:FuelCircleTextType3[sizeof(SpeedoType3)][10],
	Text:FuelCircleTextType4[sizeof(SpeedoType4)][10],
	Text:FuelCircleTextType5[sizeof(SpeedoType5)][10],
	Text:FuelCircleTextType6[sizeof(SpeedoType6)][10],
	Text:FuelCircleTextType7[sizeof(SpeedoType7)][10],
	Text:FuelCircleTextType8[sizeof(SpeedoType8)][10],
	// turbo circle TextDraws
	Text:TurboCircleTextType4[sizeof(SpeedoType4)][10],
	Text:TurboCircleTextType5[sizeof(SpeedoType5)][10],
	Text:TurboCircleTextType6[sizeof(SpeedoType6)][10],
	Text:TurboCircleTextType7[sizeof(SpeedoType7)][10],
	Text:TurboCircleTextType8[sizeof(SpeedoType8)][10],
	// speedo numerator
	Text:SpeedoNumeratorTextType2[sizeof(SpeedoType2)][10],
	Text:SpeedoNumeratorTextType3[sizeof(SpeedoType3)][10],
	Text:SpeedoNumeratorTextType5[sizeof(SpeedoType5)][10],
	Text:SpeedoNumeratorTextType6[sizeof(SpeedoType6)][10],
	Text:SpeedoNumeratorTextType7[sizeof(SpeedoType7)][10],
	Text:SpeedoNumeratorTextType8[sizeof(SpeedoType8)][10],
	// fuel numerator
	Text:FuelNumeratorTextType3[sizeof(SpeedoType3)][10],
	Text:FuelNumeratorTextType6[sizeof(SpeedoType6)][10],
	Text:FuelNumeratorTextType7[sizeof(SpeedoType7)][10],
	// turbo numerator
	Text:TurboNumeratorTextType7[sizeof(SpeedoType7)][3],
	Text:TurboNumeratorTextType8[sizeof(SpeedoType8)][3],
	// players indicators
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
native SpeedometerAnalogLoad();
native SpeedometerAnalogShow(playerid,type,speedoid);
native SpeedometerAnalogHide(playerid,type,speedoid);
native SpeedometerAnalogUpdate(playerid,type,speedoid,data[3]);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock SpeedometerAnalogLoad()
{
	new Float:Ang,
		Float:poX,
		Float:poY,
		Float:offs,
		tmp_s[4],
		tmp_i,
		Text:tid;
	// Создание текстов 1 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType1);speedoid++)
	{
		for(new i = 0;i <= (SpeedoType1[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType1[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType1[speedoid][sSpeedoPos][0] + (SpeedoType1[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType1[speedoid][sSpeedoPos][1] + (SpeedoType1[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType1[speedoid][sColor]);
			SpeedoCircleTextType1[speedoid][i] = tid;
		}
		offs = (360.0 - (SpeedoType1[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType1[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType1[speedoid][sFuelPos][0] + (SpeedoType1[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType1[speedoid][sFuelPos][1] + (SpeedoType1[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType1[speedoid][sColor]);
			FuelCircleTextType1[speedoid][i] = tid;
		}
	}
	// Создание текстов 2 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType2);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType2[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType2[speedoid][sSpeedoPos][0] + (SpeedoType2[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType2[speedoid][sSpeedoPos][1] + (SpeedoType2[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType2[speedoid][sColor]);
			SpeedoCircleTextType2[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType2[speedoid][sSpeedoPos][0] + ((SpeedoType2[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType2[speedoid][sSpeedoPos][1] + ((SpeedoType2[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType2[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType2[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		offs = (360.0 - (SpeedoType2[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType2[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType2[speedoid][sFuelPos][0] + (SpeedoType2[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType2[speedoid][sFuelPos][1] + (SpeedoType2[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType2[speedoid][sColor]);
			FuelCircleTextType2[speedoid][i] = tid;
		}
	}
	// Создание текстов 3 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType3);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType3[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType3[speedoid][sSpeedoPos][0] + (SpeedoType3[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType3[speedoid][sSpeedoPos][1] + (SpeedoType3[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType3[speedoid][sColor]);
			SpeedoCircleTextType3[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType3[speedoid][sSpeedoPos][0] + ((SpeedoType3[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType3[speedoid][sSpeedoPos][1] + ((SpeedoType3[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType3[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType3[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		tmp_i = 0;
		offs = (360.0 - (SpeedoType3[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType3[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType3[speedoid][sFuelPos][0] + (SpeedoType3[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType3[speedoid][sFuelPos][1] + (SpeedoType3[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType3[speedoid][sColor]);
			FuelCircleTextType3[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10:
			    {
			        poX = SpeedoType3[speedoid][sFuelPos][0] + ((SpeedoType3[speedoid][sFuelPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType3[speedoid][sFuelPos][1] + ((SpeedoType3[speedoid][sFuelPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType3[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					FuelNumeratorTextType3[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
	}
	// Создание текстов 4 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType4);speedoid++)
	{
		for(new i = 0;i <= (SpeedoType4[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType4[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType4[speedoid][sSpeedoPos][0] + (SpeedoType4[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType4[speedoid][sSpeedoPos][1] + (SpeedoType4[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType4[speedoid][sColor]);
			SpeedoCircleTextType4[speedoid][i] = tid;
		}
		offs = (360.0 - (SpeedoType4[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType4[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType4[speedoid][sFuelPos][0] + (SpeedoType4[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType4[speedoid][sFuelPos][1] + (SpeedoType4[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType4[speedoid][sColor]);
			FuelCircleTextType4[speedoid][i] = tid;
		}
		offs = (360.0 - (SpeedoType4[speedoid][sTurboPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType4[speedoid][sTurboPos][3] + (offs * float(i));
		    poX = SpeedoType4[speedoid][sTurboPos][0] + (SpeedoType4[speedoid][sTurboPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType4[speedoid][sTurboPos][1] + (SpeedoType4[speedoid][sTurboPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType4[speedoid][sColor]);
			TurboCircleTextType4[speedoid][i] = tid;
		}
	}
	// Создание текстов 5 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType5);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType5[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType5[speedoid][sSpeedoPos][0] + (SpeedoType5[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType5[speedoid][sSpeedoPos][1] + (SpeedoType5[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType5[speedoid][sColor]);
			SpeedoCircleTextType5[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType5[speedoid][sSpeedoPos][0] + ((SpeedoType5[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType5[speedoid][sSpeedoPos][1] + ((SpeedoType5[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType5[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType5[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		offs = (360.0 - (SpeedoType5[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType5[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType5[speedoid][sFuelPos][0] + (SpeedoType5[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType5[speedoid][sFuelPos][1] + (SpeedoType5[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType5[speedoid][sColor]);
			FuelCircleTextType5[speedoid][i] = tid;
		}
		offs = (360.0 - (SpeedoType5[speedoid][sTurboPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType5[speedoid][sTurboPos][3] + (offs * float(i));
		    poX = SpeedoType5[speedoid][sTurboPos][0] + (SpeedoType5[speedoid][sTurboPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType5[speedoid][sTurboPos][1] + (SpeedoType5[speedoid][sTurboPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType5[speedoid][sColor]);
			TurboCircleTextType5[speedoid][i] = tid;
		}
	}
	// Создание текстов 6 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType6);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType6[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType6[speedoid][sSpeedoPos][0] + (SpeedoType6[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType6[speedoid][sSpeedoPos][1] + (SpeedoType6[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType6[speedoid][sColor]);
			SpeedoCircleTextType6[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType6[speedoid][sSpeedoPos][0] + ((SpeedoType6[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType6[speedoid][sSpeedoPos][1] + ((SpeedoType6[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType6[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType6[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		tmp_i = 0;
		offs = (360.0 - (SpeedoType6[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType6[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType6[speedoid][sFuelPos][0] + (SpeedoType6[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType6[speedoid][sFuelPos][1] + (SpeedoType6[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType6[speedoid][sColor]);
			FuelCircleTextType6[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10:
			    {
			        poX = SpeedoType6[speedoid][sFuelPos][0] + ((SpeedoType6[speedoid][sFuelPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType6[speedoid][sFuelPos][1] + ((SpeedoType6[speedoid][sFuelPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType6[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					FuelNumeratorTextType6[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		offs = (360.0 - (SpeedoType6[speedoid][sTurboPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType6[speedoid][sTurboPos][3] + (offs * float(i));
		    poX = SpeedoType6[speedoid][sTurboPos][0] + (SpeedoType6[speedoid][sTurboPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType6[speedoid][sTurboPos][1] + (SpeedoType6[speedoid][sTurboPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType6[speedoid][sColor]);
			TurboCircleTextType6[speedoid][i] = tid;
		}
	}
	// Создание текстов 7 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType7);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType7[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType7[speedoid][sSpeedoPos][0] + (SpeedoType7[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType7[speedoid][sSpeedoPos][1] + (SpeedoType7[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
			SpeedoCircleTextType7[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType7[speedoid][sSpeedoPos][0] + ((SpeedoType7[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType7[speedoid][sSpeedoPos][1] + ((SpeedoType7[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType7[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		tmp_i = 0;
		offs = (360.0 - (SpeedoType7[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType7[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType7[speedoid][sFuelPos][0] + (SpeedoType7[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType7[speedoid][sFuelPos][1] + (SpeedoType7[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
			FuelCircleTextType7[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10:
			    {
			        poX = SpeedoType7[speedoid][sFuelPos][0] + ((SpeedoType7[speedoid][sFuelPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType7[speedoid][sFuelPos][1] + ((SpeedoType7[speedoid][sFuelPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					FuelNumeratorTextType7[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		tmp_i = 0;
		offs = (360.0 - (SpeedoType7[speedoid][sTurboPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType7[speedoid][sTurboPos][3] + (offs * float(i));
		    poX = SpeedoType7[speedoid][sTurboPos][0] + (SpeedoType7[speedoid][sTurboPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType7[speedoid][sTurboPos][1] + (SpeedoType7[speedoid][sTurboPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
			TurboCircleTextType7[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10:
			    {
			        poX = SpeedoType7[speedoid][sTurboPos][0] + ((SpeedoType7[speedoid][sTurboPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType7[speedoid][sTurboPos][1] + ((SpeedoType7[speedoid][sTurboPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType7[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					TurboNumeratorTextType7[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
	}
	// Создание текстов 8 типа
	for(new speedoid = 0;speedoid < sizeof(SpeedoType8);speedoid++)
	{
		tmp_i = 0;
		for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 10);i++)
		{
		    Ang = SpeedoType8[speedoid][sSpeedoPos][3] + (10.0 * float(i));
		    poX = SpeedoType8[speedoid][sSpeedoPos][0] + (SpeedoType8[speedoid][sSpeedoPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType8[speedoid][sSpeedoPos][1] + (SpeedoType8[speedoid][sSpeedoPos][2] * floatcos(-Ang, degrees));
			tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType8[speedoid][sColor]);
			SpeedoCircleTextType8[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10,15,20,25,30,35,40:
			    {
			        poX = SpeedoType8[speedoid][sSpeedoPos][0] + ((SpeedoType8[speedoid][sSpeedoPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType8[speedoid][sSpeedoPos][1] + ((SpeedoType8[speedoid][sSpeedoPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType8[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					SpeedoNumeratorTextType8[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
		offs = (360.0 - (SpeedoType8[speedoid][sFuelPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType8[speedoid][sFuelPos][3] + (offs * float(i));
		    poX = SpeedoType8[speedoid][sFuelPos][0] + (SpeedoType8[speedoid][sFuelPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType8[speedoid][sFuelPos][1] + (SpeedoType8[speedoid][sFuelPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType8[speedoid][sColor]);
			FuelCircleTextType8[speedoid][i] = tid;
		}
		tmp_i = 0;
		offs = (360.0 - (SpeedoType8[speedoid][sTurboPos][3] * 2)) / 10;
		for(new i = 0;i <= 10;i++)
		{
		    Ang = SpeedoType8[speedoid][sTurboPos][3] + (offs * float(i));
		    poX = SpeedoType8[speedoid][sTurboPos][0] + (SpeedoType8[speedoid][sTurboPos][2] * floatsin(-Ang, degrees));
			poY = SpeedoType8[speedoid][sTurboPos][1] + (SpeedoType8[speedoid][sTurboPos][2] * floatcos(-Ang, degrees));
            tid = TextDrawCreate(poX,poY,".");
            TextDrawSetShadow(tid , 0);
			TextDrawSetOutline(tid , 1);
			TextDrawColor(tid , SpeedoType8[speedoid][sColor]);
			TurboCircleTextType8[speedoid][i] = tid;
			switch(i)
			{
			    case 0,5,10:
			    {
			        poX = SpeedoType8[speedoid][sTurboPos][0] + ((SpeedoType8[speedoid][sTurboPos][2] - 20.0) * floatsin(-Ang, degrees));
					poY = SpeedoType8[speedoid][sTurboPos][1] + ((SpeedoType8[speedoid][sTurboPos][2] - 20.0) * floatcos(-Ang, degrees));
					valstr(tmp_s,(i * 10));
					tid = TextDrawCreate(poX,poY,tmp_s);
					TextDrawSetShadow(tid , 0);
					TextDrawSetOutline(tid , 1);
					TextDrawColor(tid , SpeedoType8[speedoid][sColor]);
					TextDrawFont(tid , 2);
					TextDrawAlignment(tid , 2);
					TurboNumeratorTextType8[speedoid][tmp_i] = tid;
					tmp_i++;
				}
			}
		}
	}
	// players info reset
	for(new playerid = 0;playerid < MAX_PLAYERS;playerid++)
	{
	    PlayerTextSpeed[playerid] = INVALID_TEXT_DRAW;
		PlayerTextFuel[playerid] = INVALID_TEXT_DRAW;
		PlayerTextTurbo[playerid] = INVALID_TEXT_DRAW;
	}
}

stock SpeedometerAnalogShow(playerid,type,speedoid)
{
	switch(type)
	{
		case 0:
		{
			for(new i = 0;i <= (SpeedoType1[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType1[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType1[speedoid][i]);
		}
		case 1:
		{
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType2[speedoid][i]);
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType2[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType2[speedoid][i]);
		}
		case 2:
		{
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType3[speedoid][i]);
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType3[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType3[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,FuelNumeratorTextType3[speedoid][i]);
		}
		case 3:
		{
			for(new i = 0;i <= (SpeedoType4[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType4[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType4[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,TurboCircleTextType4[speedoid][i]);
		}
		case 4:
		{
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType5[speedoid][i]);
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType5[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType5[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,TurboCircleTextType5[speedoid][i]);
		}
		case 5:
		{
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType6[speedoid][i]);
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType6[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType6[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,FuelNumeratorTextType6[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,TurboCircleTextType6[speedoid][i]);
		}
		case 6:
		{
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType7[speedoid][i]);
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType7[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType7[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,FuelNumeratorTextType7[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,TurboCircleTextType7[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,TurboNumeratorTextType7[speedoid][i]);
		}
		case 7:
		{
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,SpeedoCircleTextType8[speedoid][i]);
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,SpeedoNumeratorTextType8[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,FuelCircleTextType8[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,TurboCircleTextType8[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,TurboNumeratorTextType8[speedoid][i]);
		}
	}
}

stock SpeedometerAnalogHide(playerid,type,speedoid)
{
    TextDrawDestroy(PlayerTextSpeed[playerid]);
    TextDrawDestroy(PlayerTextFuel[playerid]);
    TextDrawDestroy(PlayerTextTurbo[playerid]);
    PlayerTextSpeed[playerid] = INVALID_TEXT_DRAW;
    PlayerTextFuel[playerid] = INVALID_TEXT_DRAW;
    PlayerTextTurbo[playerid] = INVALID_TEXT_DRAW;
	switch(type)
	{
		case 0:
		{
			for(new i = 0;i <= (SpeedoType1[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType1[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType1[speedoid][i]);
		}
		case 1:
		{
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType2[speedoid][i]);
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType2[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType2[speedoid][i]);
		}
		case 2:
		{
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType3[speedoid][i]);
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType3[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType3[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,FuelNumeratorTextType3[speedoid][i]);
		}
		case 3:
		{
			for(new i = 0;i <= (SpeedoType4[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType4[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType4[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,TurboCircleTextType4[speedoid][i]);
		}
		case 4:
		{
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType5[speedoid][i]);
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType5[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType5[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,TurboCircleTextType5[speedoid][i]);
		}
		case 5:
		{
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType6[speedoid][i]);
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType6[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType6[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,FuelNumeratorTextType6[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,TurboCircleTextType6[speedoid][i]);
		}
		case 6:
		{
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType7[speedoid][i]);
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType7[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType7[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,FuelNumeratorTextType7[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,TurboCircleTextType7[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,TurboNumeratorTextType7[speedoid][i]);
		}
		case 7:
		{
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,SpeedoCircleTextType8[speedoid][i]);
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,SpeedoNumeratorTextType8[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,FuelCircleTextType8[speedoid][i]);
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,TurboCircleTextType8[speedoid][i]);
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,TurboNumeratorTextType8[speedoid][i]);
		}
	}
}

stock SpeedometerAnalogUpdate(playerid,type,speedoid,data[3])
{
	switch(type)
	{
		case 0:
		{
			ShowIdentSpeed(playerid,SpeedoType1[speedoid][sSpeedoPos][3],SpeedoType1[speedoid][sSpeedoPos][0],SpeedoType1[speedoid][sSpeedoPos][1],SpeedoType1[speedoid][sSpeedoPos][2],SpeedoType1[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType1[speedoid][sFuelPos][3],SpeedoType1[speedoid][sFuelPos][0],SpeedoType1[speedoid][sFuelPos][1],SpeedoType1[speedoid][sFuelPos][2],SpeedoType1[speedoid][sColor],data[1]);
		}
		case 1:
		{
			ShowIdentSpeed(playerid,SpeedoType2[speedoid][sSpeedoPos][3],SpeedoType2[speedoid][sSpeedoPos][0],SpeedoType2[speedoid][sSpeedoPos][1],SpeedoType2[speedoid][sSpeedoPos][2],SpeedoType2[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType2[speedoid][sFuelPos][3],SpeedoType2[speedoid][sFuelPos][0],SpeedoType2[speedoid][sFuelPos][1],SpeedoType2[speedoid][sFuelPos][2],SpeedoType2[speedoid][sColor],data[1]);
		}
		case 2:
		{
			ShowIdentSpeed(playerid,SpeedoType3[speedoid][sSpeedoPos][3],SpeedoType3[speedoid][sSpeedoPos][0],SpeedoType3[speedoid][sSpeedoPos][1],SpeedoType3[speedoid][sSpeedoPos][2],SpeedoType3[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType3[speedoid][sFuelPos][3],SpeedoType3[speedoid][sFuelPos][0],SpeedoType3[speedoid][sFuelPos][1],SpeedoType3[speedoid][sFuelPos][2],SpeedoType3[speedoid][sColor],data[1]);
		}
		case 3:
		{
			ShowIdentSpeed(playerid,SpeedoType4[speedoid][sSpeedoPos][3],SpeedoType4[speedoid][sSpeedoPos][0],SpeedoType4[speedoid][sSpeedoPos][1],SpeedoType4[speedoid][sSpeedoPos][2],SpeedoType4[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType4[speedoid][sFuelPos][3],SpeedoType4[speedoid][sFuelPos][0],SpeedoType4[speedoid][sFuelPos][1],SpeedoType4[speedoid][sFuelPos][2],SpeedoType4[speedoid][sColor],data[1]);
			ShowIdentTurbo(playerid,SpeedoType4[speedoid][sTurboPos][3],SpeedoType4[speedoid][sTurboPos][0],SpeedoType4[speedoid][sTurboPos][1],SpeedoType4[speedoid][sTurboPos][2],SpeedoType4[speedoid][sColor],data[2]);
		}
		case 4:
		{
			ShowIdentSpeed(playerid,SpeedoType5[speedoid][sSpeedoPos][3],SpeedoType5[speedoid][sSpeedoPos][0],SpeedoType5[speedoid][sSpeedoPos][1],SpeedoType5[speedoid][sSpeedoPos][2],SpeedoType5[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType5[speedoid][sFuelPos][3],SpeedoType5[speedoid][sFuelPos][0],SpeedoType5[speedoid][sFuelPos][1],SpeedoType5[speedoid][sFuelPos][2],SpeedoType5[speedoid][sColor],data[1]);
			ShowIdentTurbo(playerid,SpeedoType5[speedoid][sTurboPos][3],SpeedoType5[speedoid][sTurboPos][0],SpeedoType5[speedoid][sTurboPos][1],SpeedoType5[speedoid][sTurboPos][2],SpeedoType5[speedoid][sColor],data[2]);
		}
		case 5:
		{
			ShowIdentSpeed(playerid,SpeedoType6[speedoid][sSpeedoPos][3],SpeedoType6[speedoid][sSpeedoPos][0],SpeedoType6[speedoid][sSpeedoPos][1],SpeedoType6[speedoid][sSpeedoPos][2],SpeedoType6[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType6[speedoid][sFuelPos][3],SpeedoType6[speedoid][sFuelPos][0],SpeedoType6[speedoid][sFuelPos][1],SpeedoType6[speedoid][sFuelPos][2],SpeedoType6[speedoid][sColor],data[1]);
			ShowIdentTurbo(playerid,SpeedoType6[speedoid][sTurboPos][3],SpeedoType6[speedoid][sTurboPos][0],SpeedoType6[speedoid][sTurboPos][1],SpeedoType6[speedoid][sTurboPos][2],SpeedoType6[speedoid][sColor],data[2]);
		}
		case 6:
		{
			ShowIdentSpeed(playerid,SpeedoType7[speedoid][sSpeedoPos][3],SpeedoType7[speedoid][sSpeedoPos][0],SpeedoType7[speedoid][sSpeedoPos][1],SpeedoType7[speedoid][sSpeedoPos][2],SpeedoType7[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType7[speedoid][sFuelPos][3],SpeedoType7[speedoid][sFuelPos][0],SpeedoType7[speedoid][sFuelPos][1],SpeedoType7[speedoid][sFuelPos][2],SpeedoType7[speedoid][sColor],data[1]);
			ShowIdentTurbo(playerid,SpeedoType7[speedoid][sTurboPos][3],SpeedoType7[speedoid][sTurboPos][0],SpeedoType7[speedoid][sTurboPos][1],SpeedoType7[speedoid][sTurboPos][2],SpeedoType7[speedoid][sColor],data[2]);
		}
		case 7:
		{
			ShowIdentSpeed(playerid,SpeedoType8[speedoid][sSpeedoPos][3],SpeedoType8[speedoid][sSpeedoPos][0],SpeedoType8[speedoid][sSpeedoPos][1],SpeedoType8[speedoid][sSpeedoPos][2],SpeedoType8[speedoid][sColor],data[0]);
			ShowIdentFuel(playerid,SpeedoType8[speedoid][sFuelPos][3],SpeedoType8[speedoid][sFuelPos][0],SpeedoType8[speedoid][sFuelPos][1],SpeedoType8[speedoid][sFuelPos][2],SpeedoType8[speedoid][sColor],data[1]);
			ShowIdentTurbo(playerid,SpeedoType8[speedoid][sTurboPos][3],SpeedoType8[speedoid][sTurboPos][0],SpeedoType8[speedoid][sTurboPos][1],SpeedoType8[speedoid][sTurboPos][2],SpeedoType8[speedoid][sColor],data[2]);
		}
	}
}

// --------------------------------------------------
// local utils
// --------------------------------------------------

static ShowIdentSpeed(playerid,Float:A,Float:X,Float:Y,Float:R,color,data)
{
	new Float:Ang,
		Float:poX,
		Float:poY,
		Text:tid;
	if((PlayerTextSpeed[playerid] == INVALID_TEXT_DRAW) || (PlayerDataSpeed[playerid] != data))
	{
		Ang = A + float(data);
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(PlayerTextSpeed[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextSpeed[playerid]);
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextSpeed[playerid] = tid;
		PlayerDataSpeed[playerid] = data;
	}
}

static ShowIdentFuel(playerid,Float:A,Float:X,Float:Y,Float:R,color,data)
{
	new Float:Ang,
		Float:offs,
		Float:poX,
		Float:poY,
		Text:tid;
	if((PlayerTextFuel[playerid] == INVALID_TEXT_DRAW) || (PlayerDataFuel[playerid] != data))
	{
		offs = (360.0 - (A * 2)) / 10;
		Ang = A + (offs * float(data));
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(PlayerTextFuel[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextFuel[playerid]);
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextFuel[playerid] = tid;
		PlayerDataFuel[playerid] = data;
	}
}

static ShowIdentTurbo(playerid,Float:A,Float:X,Float:Y,Float:R,color,data)
{
	new Float:Ang,
		Float:offs,
		Float:poX,
		Float:poY,
		Text:tid;
	if((PlayerTextTurbo[playerid] == INVALID_TEXT_DRAW) || (PlayerDataTurbo[playerid] != data))
	{
		offs = (360.0 - (A * 2)) / 10;
		Ang = A + (offs * float(data));
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(PlayerTextTurbo[playerid] != INVALID_TEXT_DRAW) TextDrawDestroy(PlayerTextTurbo[playerid]);
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		PlayerTextTurbo[playerid] = tid;
		PlayerDataTurbo[playerid] = data;
	}
}
