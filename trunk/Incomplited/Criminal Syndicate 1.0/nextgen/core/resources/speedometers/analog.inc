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
// includes
// --------------------------------------------------
#include "mode_property"

// --------------------------------------------------
// defines
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------
// тип 1, тип 2, тип 3
enum E_SAT1 {
	sMaxSpeed,
	sColor,
	Float:sSpeedoPos[4],
	Float:sFuelPos[4]
};
// тип 4 , 5 , 6 , 7 , 8
enum E_SAT2 {
	sMaxSpeed,
	sColor,
	Float:sSpeedoPos[4],
	Float:sFuelPos[4],
	Float:sTurboPos[4]
};

// --------------------------------------------------
// news
// --------------------------------------------------
static SpeedoType1[][E_SAT1] = {
	{50,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}
};
static SpeedoType2[][E_SAT1] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}	
};
static SpeedoType3[][E_SAT1] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0}}	
};
static SpeedoType4[][E_SAT2] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}	
};
static SpeedoType5[][E_SAT2] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}	
};
static SpeedoType6[][E_SAT2] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}	
};
static SpeedoType7[][E_SAT2] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}	
};
static SpeedoType8[][E_SAT2] = {
	{250,0x33AAFFFF,{320.0,400.0,75.0,55.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}},
	{300,0x33AAFFFF,{320.0,380.0,50.0,30.0},{200.0,430.0,30.0,55.0},{440.0,430.0,30.0,55.0}}	
};

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
			SetModePropertyInt("SAT1","SC",speedoid,i,int:tid);
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
			SetModePropertyInt("SAT1","FC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT2","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT2","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT2","FC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT3","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT3","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT3","FC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT3","FN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT4","SC",speedoid,i,int:tid);
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
			SetModePropertyInt("SAT4","FC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT4","TC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT5","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT5","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT5","FC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT5","TC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT6","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT6","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT6","FC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT6","FN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT6","TC",speedoid,i,int:tid);			
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
			SetModePropertyInt("SAT7","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT7","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT7","FC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT7","FN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT7","TC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT7","TN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT8","SC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT8","SN",speedoid,tmp_i,int:tid);
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
			SetModePropertyInt("SAT8","FC",speedoid,i,int:tid);
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
			SetModePropertyInt("SAT8","TC",speedoid,i,int:tid);
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
					SetModePropertyInt("SAT8","TN",speedoid,tmp_i,int:tid);
					tmp_i++;
				}
			}
		}
	}
}

stock SpeedometerAnalogShow(playerid,type,speedoid)
{
	switch(type)
	{
		case 0:
		{
			for(new i = 0;i <= (SpeedoType1[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT1","SC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT1","FC",speedoid,i));
		}
		case 1:
		{
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT2","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT2","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT2","FC",speedoid,i));
		}
		case 2:
		{
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT3","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT3","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT3","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT3","FN",speedoid,i));
		}
		case 3:
		{
			for(new i = 0;i <= (SpeedoType4[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT4","SC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT4","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT4","TC",speedoid,i));
		}
		case 4:
		{
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT5","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT5","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT5","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT5","TC",speedoid,i));
		}
		case 5:
		{
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT6","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT6","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT6","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT6","FN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT6","TC",speedoid,i));
		}
		case 6:
		{
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","FN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","TC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT7","TN",speedoid,i));
		}
		case 7:
		{
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 10);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT8","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 50);i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT8","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT8","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT8","TC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawShowForPlayer(playerid,Text:GetModePropertyInt("SAT8","TN",speedoid,i));
		}
	}
}

stock SpeedometerAnalogHide(playerid,type,speedoid)
{
	if(ExistModeProperty("SA","PIS",playerid,1)) {TextDrawDestroy(Text:GetModePropertyInt("SA","PIS",playerid,1));DeleteModeProperty("SA","PIS",playerid,1);}
	if(ExistModeProperty("SA","PIS",playerid,0)) DeleteModeProperty("SA","PIS",playerid,0);
	if(ExistModeProperty("SA","PIF",playerid,1)) {TextDrawDestroy(Text:GetModePropertyInt("SA","PIF",playerid,1));DeleteModeProperty("SA","PIF",playerid,1);}
	if(ExistModeProperty("SA","PIF",playerid,0)) DeleteModeProperty("SA","PIF",playerid,0);
	if(ExistModeProperty("SA","PIT",playerid,1)) {TextDrawDestroy(Text:GetModePropertyInt("SA","PIT",playerid,1));DeleteModeProperty("SA","PIT",playerid,1);}
	if(ExistModeProperty("SA","PIT",playerid,0)) DeleteModeProperty("SA","PIT",playerid,0);
	switch(type)
	{
		case 0:
		{
			for(new i = 0;i <= (SpeedoType1[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT1","SC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT1","FC",speedoid,i));
		}
		case 1:
		{
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT2","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType2[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT2","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT2","FC",speedoid,i));
		}
		case 2:
		{
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT3","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType3[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT3","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT3","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT3","FN",speedoid,i));
		}
		case 3:
		{
			for(new i = 0;i <= (SpeedoType4[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT4","SC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT4","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT4","TC",speedoid,i));
		}
		case 4:
		{
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT5","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType5[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT5","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT5","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT5","TC",speedoid,i));
		}
		case 5:
		{
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT6","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType6[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT6","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT6","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT6","FN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT6","TC",speedoid,i));
		}
		case 6:
		{
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType7[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","FC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","FN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","TC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT7","TN",speedoid,i));
		}
		case 7:
		{
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 10);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT8","SC",speedoid,i));
			for(new i = 0;i <= (SpeedoType8[speedoid][sMaxSpeed] / 50);i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT8","SN",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT8","FC",speedoid,i));
			for(new i = 0;i <= 10;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT8","TC",speedoid,i));
			for(new i = 0;i < 3;i++) TextDrawHideForPlayer(playerid,Text:GetModePropertyInt("SAT8","TN",speedoid,i));
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
	if((!ExistModeProperty("SA","PIS",playerid,0)) || (GetModePropertyInt("SA","PIS",playerid,0) != data))
	{
		Ang = A + float(data);
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(ExistModeProperty("SA","PIS",playerid,1))
		{
			TextDrawDestroy(Text:GetModePropertyInt("SA","PIS",playerid,1));
			DeleteModeProperty("SA","PIS",playerid,1);
		}
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		SetModePropertyInt("SA","PIS",playerid,1,int:tid);
		if(ExistModeProperty("SA","PIS",playerid,0)) DeleteModeProperty("SA","PIS",playerid,0);
		SetModePropertyInt("SA","PIS",playerid,0,data);
	}
}

static ShowIdentFuel(playerid,Float:A,Float:X,Float:Y,Float:R,color,data)
{
	new Float:Ang,
		Float:offs,
		Float:poX,
		Float:poY,
		Text:tid;
	if((!ExistModeProperty("SA","PIF",playerid,0)) || (GetModePropertyInt("SA","PIF",playerid,0) != data))
	{
		offs = (360.0 - (A * 2)) / 10;
		Ang = A + (offs * float(data));
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(ExistModeProperty("SA","PIF",playerid,1))
		{
			TextDrawDestroy(Text:GetModePropertyInt("SA","PIF",playerid,1));
			DeleteModeProperty("SA","PIF",playerid,1);
		}
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		SetModePropertyInt("SA","PIF",playerid,1,int:tid);
		if(ExistModeProperty("SA","PIF",playerid,0)) DeleteModeProperty("SA","PIF",playerid,0);
		SetModePropertyInt("SA","PIF",playerid,0,data);
	}
}

static ShowIdentTurbo(playerid,Float:A,Float:X,Float:Y,Float:R,color,data)
{
	new Float:Ang,
		Float:offs,
		Float:poX,
		Float:poY,
		Text:tid;
	if((!ExistModeProperty("SA","PIT",playerid,0)) || (GetModePropertyInt("SA","PIT",playerid,0) != data))
	{
		offs = (360.0 - (A * 2)) / 10;
		Ang = A + (offs * float(data));
		poX = X + ((R + 10.0) * floatsin(-Ang, degrees));
		poY = Y + ((R + 10.0) * floatcos(-Ang, degrees));
		if(ExistModeProperty("SA","PIT",playerid,1))
		{
			TextDrawDestroy(Text:GetModePropertyInt("SA","PIT",playerid,1));
			DeleteModeProperty("SA","PIT",playerid,1);
		}
		tid = TextDrawCreate(poX,poY,".");
		TextDrawSetShadow(tid , 0);
		TextDrawSetOutline(tid , 1);
		TextDrawColor(tid , color);
		TextDrawShowForPlayer(playerid,tid);
		SetModePropertyInt("SA","PIT",playerid,1,int:tid);
		if(ExistModeProperty("SA","PIT",playerid,0)) DeleteModeProperty("SA","PIT",playerid,0);
		SetModePropertyInt("SA","PIT",playerid,0,data);
	}
}
