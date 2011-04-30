/*
*	Created:			08.11.09
*	Author:				009
*	Description:		Функции упрощения работы с интерьерами игры, создание выходов из интерьеров
*/

#if defined core_interiors_included
	#endinput
#endif

#define core_interiors_included
#pragma library core_interiors

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/headers/enums.h"
#tryinclude "../core/headers/defines.h"
#tryinclude "../core/pickups.p"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define ENTER_EXIT_PICKUP			1559
#define MAX_MODE_INTERIOR_OBJECTS   500

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// enums
// --------------------------------------------------
enum ModeInteriorsInfo
{
	gInterior,
	Float:gExit[4]
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	ModeInteriors[][ModeInteriorsInfo] = {
		{17,{-25.906459,-187.665069,1003.546875,358.724365}}, // Mode interior 1 [0] - 24/7
		{10,{6.051540,-31.119470,1003.549438,357.213836}}, // Mode interior 2 [1] - 24/7
		{18,{-30.890455,-91.431327,1003.546875,359.463348}}, // Mode interior 3 [2] - 24/7
		{16,{-25.976287,-140.677963,1003.546875,359.206207}}, // Mode interior 4 [3] - 24/7
		{4,{-27.606212,-31.048669,1003.557250,358.869567}}, // Mode interior 5 [4] - 24/7
		{6,{-27.426736,-57.533832,1003.546875,359.239074}}, // Mode interior 6 [5] - 24/7
		{1,{285.350311,-41.360557,1001.515625,356.812011}}, // Mode interior 7 [6] - Ammunation
		{4,{285.652038,-86.349815,1001.522888,355.928192}}, // Mode interior 8 [7] - Ammunation
		{6,{296.842742,-111.636672,1001.515625,353.533905}}, // Mode interior 9 [8] - Ammunation
		{7,{315.769958,-142.899368,999.601562,353.646331}}, // Mode interior 10 [9] - Ammunation
		{6,{316.282043,-169.450531,999.601013,359.319213}}, // Mode interior 11 [10] - Ammunation
		{3,{235.272872,1187.074340,1080.257812,356.265441}}, // Mode interior 12 [11] - A House
		{2,{226.487701,1240.006469,1082.140625,88.129158}}, // Mode interior 13 [12] - A House
		{1,{223.118255,1287.502075,1082.140625,357.294464}}, // Mode interior 14 [13] - A House
		{7,{225.727935,1022.066955,1084.015869,356.780242}}, // Mode interior 15 [14] - A House
		{15,{295.171813,1472.709594,1080.257812,356.008850}}, // Mode interior 16 [15] - A House
		{15,{327.968048,1478.024536,1084.437500,352.697937}}, // Mode interior 17 [16] - A House
		{15,{387.064758,1471.884765,1080.187500,83.341156}}, // Mode interior 18 [17] - A House
		{15,{376.816772,1417.333129,1081.328125,81.943138}}, // Mode interior 19 [18] - A House
		{2,{491.085571,1398.730712,1080.257812,356.458526}}, // Mode interior 20 [19] - A House
		{2,{447.039947,1397.279052,1084.304687,356.828094}}, // Mode interior 21 [20] - A House
		{5,{226.470260,1114.215454,1080.993774,263.903045}}, // Mode interior 22 [21] - A House
		{4,{261.048736,1284.693603,1080.257812,353.484954}}, // Mode interior 23 [22] - A House
		{4,{222.121307,1140.587890,1082.609375,2.853431}}, // Mode interior 24 [23] - A House
		{10,{24.053901,1340.450561,1084.375000,355.076171}}, // Mode interior 25 [24] - A House
		{5,{22.908340,1403.583740,1084.429687,356.989013}}, // Mode interior 26 [25] - A House
		{5,{140.321777,1366.331176,1083.859375,354.594787}}, // Mode interior 27 [26] - A House
		{6,{234.178421,1064.016235,1084.211791,345.049957}}, // Mode interior 28 [27] - A House
		{6,{-68.807296,1351.302490,1080.210937,358.579589}}, // Mode interior 29 [28] - A House
		{8,{-42.596492,1405.589965,1084.429687,358.032501}}, // Mode interior 30 [29] - A House
		{9,{83.010536,1322.681274,1083.866210,2.788770}}, // Mode interior 31 [30] - A House
		{9,{260.746887,1237.819213,1084.257812,349.998229}}, // Mode interior 32 [31] - A House
		{15,{2214.782714,-1150.498535,1025.796875,261.090087}}, // Mode interior 33 [32] - The Jefferson Motel
		{3,{834.479125,7.325429,1004.187011,83.194633}}, // Mode interior 34 [33] - The Off track Betting
		{1,{964.770446,2160.093505,1011.030273,87.983749}}, // Mode interior 35 [34] - The Sindacco Meat Processing Plant
		{6,{-2240.438232,128.317138,1035.421020,269.461669}}, // Mode interior 36 [35] - Zero's RC Shop
		{10,{2018.956298,1017.849487,996.875000,83.224388}}, // Mode interior 37 [36] - The Four Dragons
		{1,{2233.996826,1714.486206,1012.382812,177.594787}}, // Mode interior 38 [37] - Calligula's
		{1,{-2158.696777,642.956726,1052.375000,178.637695}}, // Mode interior 39 [38] - Woozie's Office
		{12,{1133.017456,-15.474257,1000.679687,8.295166}}, // Mode interior 40 [39] - Redsands West Casino
		{15,{207.625015,-111.078872,1005.132812,358.058044}}, // Mode interior 41 [40] - Binco
		{14,{204.399047,-168.577636,1000.523437,353.816619}}, // Mode interior 42 [41] - Didier Sachs
		{3,{206.932373,-140.102844,1003.507812,357.029571}}, // Mode interior 43 [42] - ProLaps
		{1,{203.780456,-50.315147,1001.804687,352.755218}}, // Mode interior 44 [43] - SubUrban
		{5,{227.261459,-8.183994,1002.210937,84.651779}}, // Mode interior 45 [44] - Victim
		{18,{161.342498,-96.791046,1001.804687,357.623931}}, // Mode interior 46 [45] - Zip
		{17,{493.390411,-24.405584,1000.679687,352.722930}}, // Mode interior 47 [46] - The Dance Club
		{11,{501.923950,-68.195831,998.757812,178.587493}}, // Mode interior 48 [47] - Shithole Bar
		{18,{-228.798904,1401.251708,27.765625,269.824493}}, // Mode interior 49 [48] - Lil' Probe Inn
		{4,{459.968780,-88.565185,999.554687,82.271842}}, // Mode interior 50 [49] - Jay's Diner
		{10,{363.057525,-75.039283,1001.507812,303.889648}}, // Mode interior 51 [50] - Burger Shot
		{9,{364.789337,-11.426133,1001.851562,351.002532}}, // Mode interior 52 [51] - Cluckin' Bell
		{5,{372.371551,-133.413833,1001.492187,0.145432}}, // Mode interior 53 [52] - Well Stacked Pizza
		{17,{377.173004,-193.122329,1000.640136,353.364471}}, // Mode interior 54 [53] - Rusty Brown's Donuts
		{1,{243.971572,304.929931,999.148437,262.609436}}, // Mode interior 55 [54] - Denise Robinson's Bedroom
		{2,{266.909301,304.938812,999.148437,265.340942}}, // Mode interior 56 [55] - Katie Zhan's Bedroom
		{6,{343.848571,305.005645,999.148437,267.637298}}, // Mode interior 57 [56] - Millie Perkins's Bedroom
		{17,{-959.551330,1955.300292,9.000000,172.205551}}, // Mode interior 58 [57] - The Sherman Dam
		{3,{390.196136,173.883148,1008.382812,87.347656}}, // Mode interior 59 [58] - The Planning Department
		{5,{772.232116,-5.029723,1000.728576,359.099304}}, // Mode interior 60 [59] - The Ganton Gym
		{6,{774.179077,-49.880123,1000.585937,359.211700}}, // Mode interior 61 [60] - The Cobra Gym
		{7,{773.911926,-78.440017,1000.662231,1.171320}}, // Mode interior 62 [61] - Below The Belt Gym
		{5,{1260.977783,-785.419250,1091.906250,268.503326}}, // Mode interior 63 [62] - Madd Dogg's Mansion
		{3,{2496.022705,-1692.390014,1014.742187,177.088699}}, // Mode interior 64 [63] - Carl's Mums House
		{2,{2468.362304,-1698.312622,1013.507812,81.946876}}, // Mode interior 65 [64] - Ryder's House
		{2,{2541.951171,-1303.960693,1025.070312,262.251068}}, // Mode interior 66 [65] - Big Smokes Crack Palace
		{3,{1212.214965,-26.393075,1000.953125,177.729858}}, // Mode interior 67 [66] - The Big Spread Ranch
		{6,{744.507873,1436.619384,1102.703125,351.140777}}, // Mode interior 68 [67] - Fanny Batter's Whore House
		{2,{1204.774658,-13.578839,1000.921875,358.403686}}, // Mode interior 69 [68] - The World Class Topless Girls Stripclub
		{3,{-2636.610107,1403.121459,906.460937,1.616546}}, // Mode interior 70 [69] - Jizzy's Pleasure Dome
		{8,{2807.526855,-1173.935546,1025.570312,357.262603}}, // Mode interior 71 [70] - Colonel Furburgher's House
		{5,{318.537445,1115.183837,1083.882812,352.988342}}, // Mode interior 72 [71] - The Crack Den
		{18,{1309.829833,4.386286,1002.492187,92.965980}}, // Mode interior 73 [72] - A Warehouse
		{12,{2324.457275,-1149.015258,1050.710083,358.708007}}, // Mode interior 74 [73] - A Safehouse
		{2,{411.500061,-22.898862,1001.804687,358.193725}}, // Mode interior 75 [74] - Old Reece's Hair and Facial Studio
		{3,{418.702728,-83.916366,1001.804687,1.696582}}, // Mode interior 76 [75] - Gay Gordo's Barber Shop
		{12,{412.027404,-54.152118,1001.898437,358.932739}}, // Mode interior 77 [76] - Mascila's Unisex Hair Salon
		{16,{-204.369140,-27.068975,1002.273437,359.928924}}, // Mode interior 78 [77] - A Tattoo Parlour
		{17,{-204.438430,-8.413149,1002.273437,358.418426}}, // Mode interior 79 [78] - Hemlock's Tattoo Parlour
		{6,{246.878005,63.077476,1003.640625,353.887023}}, // Mode interior 80 [79] - The Los Santos Police Department
		{10,{246.452423,107.982009,1003.218750,358.643249}}, // Mode interior 81 [80] - The San Fierro Police Department
		{3,{288.814453,167.803253,1007.171875,356.506103}}, // Mode interior 82 [81] - The Los Vagos Police Department
		{3,{1494.333374,1304.027465,1093.289062,357.871887}}, // Mode interior 83 [82] - Cycle School
		{3,{-2029.715942,-119.080795,1035.171875,358.241455}}, // Mode interior 84 [83] - Automobile School
		{10,{422.128814,2536.441894,10.000000,87.598487}} // Mode interior 85 [84] - Plane School
	},
	IsPlayerInModeInterior[MAX_PLAYERS char],
	CurrentPlayerModeInterior[MAX_PLAYERS char],
	Float:LastPlayerPosition[MAX_PLAYERS][4],
	LastPlayerInterior[MAX_PLAYERS char],
	// interior objects
	ModeInteriorGameId[MAX_PLAYERS][MAX_MODE_INTERIOR_OBJECTS],
	ModeInteriorObjects[MAX_PLAYERS];

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native SetPlayerModeInterior(playerid,modeinteriorid);
native GetPlayerModeInterior(playerid);
native GetModeInteriorExitPos(modeinteriorid,&Float:X,&Float:Y,&Float:Z);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock SetPlayerModeInterior(playerid,modeinteriorid)
{
	Debug(DEBUG_START,"SetPlayerModeInterior(%d,%d)",playerid,modeinteriorid);
	if((modeinteriorid < 0) || (modeinteriorid > sizeof(ModeInteriors)))
	{
		Debug(DEBUG_END,"SetPlayerModeInterior(reason: error)");
		printf("[ERROR] Core -> Interiors -> SetPlayerModeInterior (invalid mode interior - %d)",modeinteriorid);
		return 0;
	}
	Debug(DEBUG_ACTION,"set data");
	if(IsPlayerInModeInterior{playerid})
	{
	    if(modeinteriorid == 0)
	    {
	        Debug(DEBUG_ACTION,"exit from interior");
	        SetPlayerInterior(playerid,LastPlayerInterior{playerid});
	        IsPlayerInModeInterior{playerid} = 0;
        	Debug(DEBUG_ACTION,"hide interior objects");
        	HideInteriorObjects(playerid);
        	Debug(DEBUG_ACTION,"tp to world");
            CurrentPlayerModeInterior{playerid} = modeinteriorid;
            SetPlayerPos(playerid,LastPlayerPosition[playerid][0],LastPlayerPosition[playerid][1],LastPlayerPosition[playerid][2]);
			SetPlayerFacingAngle(playerid,(LastPlayerPosition[playerid][3] - 180.0)); // -180.0 для поворота игрока назад иммитируя выход из помещения(предполагается что игрок был повёрнут лицом к двери во время входа)
	    }
	}
	else if(modeinteriorid != 0)
	{
	    CurrentPlayerModeInterior{playerid} = modeinteriorid;
	    Debug(DEBUG_ACTION,"enter in interior");
		modeinteriorid--; // "Поправка нуля" иды интерьеров передаются в функцию с прибавленой единицой,для того чтобы использовать ид 0 для возвращения в мир
		IsPlayerInModeInterior{playerid} = 1;
		GetPlayerPos(playerid,LastPlayerPosition[playerid][0],LastPlayerPosition[playerid][1],LastPlayerPosition[playerid][2]);
		GetPlayerFacingAngle(playerid,LastPlayerPosition[playerid][3]);
		LastPlayerInterior{playerid} = GetPlayerInterior(playerid);
        SetPlayerInterior(playerid,20);
        Debug(DEBUG_ACTION,"show interior objects");
        ShowInteriorObjects(playerid,ModeInteriors[modeinteriorid][gInterior]);
        Debug(DEBUG_ACTION,"tp to interior");
		SetPlayerPos(playerid,ModeInteriors[modeinteriorid][gExit][0],ModeInteriors[modeinteriorid][gExit][1],ModeInteriors[modeinteriorid][gExit][2]);
		SetPlayerFacingAngle(playerid,ModeInteriors[modeinteriorid][gExit][3]);
	}
	Debug(DEBUG_END,"SetPlayerModeInterior(reason: complete)");
	return 1;
}

stock GetPlayerModeInterior(playerid)
{
	Debug(DEBUG_SMALL,"GetPlayerModeInterior(%d)",playerid);
	return CurrentPlayerModeInterior{playerid};
}

stock GetModeInteriorExitPos(modeinteriorid,&Float:X,&Float:Y,&Float:Z)
{
	Debug(DEBUG_START,"GetModeInteriorExitPos(%d)",modeinteriorid);
	X = ModeInteriors[modeinteriorid][gExit][0];
	Y = ModeInteriors[modeinteriorid][gExit][1];
	Z = ModeInteriors[modeinteriorid][gExit][2];
	Debug(DEBUG_END,"GetModeInteriorExitPos(reason: complete)");	
	return 1;
}

// --------------------------------------------------
// local functions
// --------------------------------------------------
static stock ShowInteriorObjects(playerid,interiorid)
{
    Debug(DEBUG_START,"ShowInteriorObjects(%d,%d)",playerid,interiorid);
	new File:int_obj = fopen("interiors.txt",io_read),
	    line[128],
	    last_obj,
		idx,
		model,
		interior,
		Float:pos[6];
	if(int_obj)
	{
	    while(fread(int_obj,line))
	    {
			if(last_obj == MAX_MODE_INTERIOR_OBJECTS)
			{
				print("[ERROR] Core -> Interiors -> ShowInteriorObjects (objects not loaded, less slots)");
				break;
			}
			
	        idx = 0;
			model = strval(istrtok(line,idx,','));
			interior = strval(istrtok(line,idx,','));
			
			if(interior != interiorid) continue;
			
			pos[0] = floatstr(istrtok(line,idx,','));
			pos[1] = floatstr(istrtok(line,idx,','));
			pos[2] = floatstr(istrtok(line,idx,','));
			pos[3] = floatstr(istrtok(line,idx,','));
			pos[4] = floatstr(istrtok(line,idx,','));
			pos[5] = floatstr(istrtok(line,idx,','));
			
            ModeInteriorGameId[playerid][last_obj] = CreatePlayerObject(playerid,model,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5]);
			last_obj++;
	    }
	    ModeInteriorObjects[playerid] = last_obj;
        Debug(DEBUG_ACTION,"loaded %d objects",ModeInteriorObjects[playerid]);
	    fclose(int_obj);
	}
	Debug(DEBUG_END,"ShowInteriorObjects(reason: complete)");
}

static stock HideInteriorObjects(playerid)
{
	for(new i = 0;i < ModeInteriorObjects[playerid];i++)
	{
		DestroyPlayerObject(playerid,ModeInteriorGameId[playerid][i]);
	}
}

static stock istrtok(const string[], &index,sep=',')
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= sep))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > sep) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Interiors_Init()
{
	Debug(DEBUG_START,"Core_Interiors_Init()");
	Debug(DEBUG_ACTION,"create exit pickups");
	for(new id = 0;id < sizeof(ModeInteriors);id++)
	{
#if defined CreateModePickup
		CreateModePickup(ENTER_EXIT_PICKUP,42,ModeInteriors[id][gExit][0],ModeInteriors[id][gExit][1],ModeInteriors[id][gExit][2],id + 1,INVALID_VIRTUAL_WORLD_ID,PICKUP_MODE_INTERIOR,id);
#else
        CreatePickup(ENTER_EXIT_PICKUP,42,ModeInteriors[id][gExit][0],ModeInteriors[id][gExit][1],ModeInteriors[id][gExit][2],INVALID_VIRTUAL_WORLD_ID);
#endif
	}
	print("[CORE] Interiors load complete.");
	Debug(DEBUG_END,"Core_Interiors_Init(reason: complete)");
}
