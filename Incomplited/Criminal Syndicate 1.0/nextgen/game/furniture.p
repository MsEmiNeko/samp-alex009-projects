/*
*	Created:			10.10.09
*	Author:				009
*	Description:		Функции создания и работы с параметрами мебели (уникальные действия отдельных едениц мебели в ресурсах, папка furnitures)
*/

#if defined game_furniture_included
	#endinput
#endif

#define game_furniture_included
#pragma library game_furniture

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../headers/enums.h"
#tryinclude "../headers/defines.h"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define INFO_SLOW_MOVE		"For moving use:~n~~k~~PED_JUMPING~ - up~n~~k~~PED_SPRINT~ - down~n~~k~~GO_FORWARD~ - front~n~~k~~GO_BACK~ - back~n~~k~~GO_LEFT~ - left~n~~k~~GO_RIGHT~ - right~n~~k~~PED_FIREWEAPON~ - move camera front~n~~k~~PED_LOCK_TARGET~ - move camera back~n~~k~~SNEAK_ABOUT~ - change move type~n~~k~~PED_DUCK~ - move angles"
#define INFO_FAST_MOVE		"For moving use:~n~~k~~SNEAK_ABOUT~ - change move type"
#define INFO_ANGLE_MOVE		"For moving use:~n~~k~~PED_JUMPING~ - z+~n~~k~~PED_SPRINT~ - z-~n~~k~~GO_FORWARD~ - x+~n~~k~~GO_BACK~ - x-~n~~k~~GO_LEFT~ - y+~n~~k~~GO_RIGHT~ - y-~n~~k~~PED_FIREWEAPON~ - move camera front~n~~k~~PED_LOCK_TARGET~ - move camera back~n~~k~~SNEAK_ABOUT~ - change move type~n~~k~~PED_DUCK~ - move pos"
#define MAX_FURNITURE_VARS	2
#define MAX_FURNITURES      MAX_MODE_OBJECTS

// --------------------------------------------------
// enums
// --------------------------------------------------
enum
{
	MOVING_TYPE_NONE,
	MOVING_TYPE_SLOW,
	MOVING_TYPE_FAST,
	MOVING_TYPE_ANGLE
};
enum
{
    SHOP_COUNTER,
    SHOP_TABLE,
    LIGHTS,
    OFFICE_COMP_TABLE,
    OFFICE_TABLE,
    OFFICE_CHAIR,
    SPECIAL,
    SAFE,
    LETTER_BOX,
    SOFA,
    ARMCHAIR,
    TABLE,
    TV,
    AUDIO,
	VIDEOGAME,
	BED,
	CABINET,
	CHEST,
	DRESSER,
	KITCHEN_TABLE,
	KITCHEN_TABLE_EX,
	REFRIDGERATOR
};
enum
{
	ANIM_TYPE_CARRY = 1,
	ANIM_TYPE_PUSH
};
enum FurnitureInfo
{
	fModel,
	fGroup,
	Float:fAttachCoords[3],
	fAnimType,
	Float:fHealth,
	Float:fMass,
	Float:fSize,
	Float:fMaxLuggageMass,
	fName[40]
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static 
	// furnitures
	Furniture[][FurnitureInfo] = {
		{1987,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 1)"},
		{1988,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 1)"},
		{1983,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 1)"},
		{2536,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Левая часть прилавка (Тип 2)"},
		{2537,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Правая часть прилавка (Тип 2)"},
		{2535,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Центральная часть прилавка (Тип 2)"},
		{1991,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Левая часть прилавка (Тип 3)"},
		{1996,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Правая часть прилавка (Тип 3)"},
		{1981,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,20.000000,"Центральная часть прилавка (Тип 3)"},
		{2540,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 4)"},
		{2538,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 4)"},
		{2539,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 4)"},
		{1994,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,10.000000,"Левая часть прилавка (Тип 5)"},
		{1995,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,10.000000,"Правая часть прилавка (Тип 5)"},
		{1993,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,10.000000,"Центральная часть прилавка (Тип 5)"},
		{2542,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 6)"},
		{2871,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 6)"},
		{2541,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 6)"},
		{2544,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 7)"},
		{2545,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 7)"},
		{2543,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 7)"},
		{2551,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 8)"},
		{2550,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 8)"},
		{2546,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 8)"},
		{2549,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 9)"},
		{2547,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 9)"},
		{2548,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 9)"},
		{2553,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 10)"},
		{2552,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 10)"},
		{2554,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 10)"},
		{2555,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Левая часть прилавка (Тип 11)"},
		{2557,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Правая часть прилавка (Тип 11)"},
		{2554,SHOP_COUNTER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,15.000000,"Центральная часть прилавка (Тип 11)"},
		{1984,SHOP_TABLE,{-0.900000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Стол с кассой"},
		{1893,LIGHTS,{-0.600000,0.399999,1.000000},ANIM_TYPE_CARRY,100.000000,1.000000,2.000000,0.000000,"Подвесная лампа"},
		{2165,OFFICE_COMP_TABLE,{-0.500000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,5.000000,"Офисный стол с компьютером (Тип 1)"},
		{2181,OFFICE_COMP_TABLE,{-0.500000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,10.000000,"Офисный стол с компьютером (Тип 2)"},
		{1999,OFFICE_COMP_TABLE,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,5.000000,"Офисный стол с компьютером (Тип 3)"},
		{1998,OFFICE_COMP_TABLE,{-0.700000,0.099999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.099999,5.000000,"Офисный стол с компьютером (Тип 4)"},
		{2172,OFFICE_COMP_TABLE,{-0.500000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,5.000000,"Офисный стол с компьютером (Тип 5)"},
		{2174,OFFICE_TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,10.000000,"Офисный стол"},
		{1714,OFFICE_CHAIR,{-0.100000,0.699999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.699999,0.000000,"Офисный стул (Тип 1)"},
		{1715,OFFICE_CHAIR,{0.000000,0.799999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.799999,0.000000,"Офисный стул (Тип 2)"},
		{1722,OFFICE_CHAIR,{-0.100000,0.199999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.199999,0.000000,"Офисный стул (Тип 3)"},
		{1721,OFFICE_CHAIR,{0.000000,0.299999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.299999,0.000000,"Офисный стул (Тип 4)"},
		{1806,OFFICE_CHAIR,{0.000000,0.299999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.299999,0.000000,"Офисный стул (Тип 5)"},
		{2309,OFFICE_CHAIR,{0.000000,0.199999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.199999,0.000000,"Офисный стул (Тип 6)"},
		{2002,SPECIAL,{0.000000,0.599999,-1.000000},ANIM_TYPE_PUSH,100.000000,10.000000,1.599999,0.000000,"Автомат с водой"},
		{2007,SAFE,{0.000000,0.699999,-1.000000},ANIM_TYPE_PUSH,100.000000,15.000000,1.699999,30.000000,"Средний сейф"},
		{2065,LETTER_BOX,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,20.000000,"Ящик для бумаг (Тип 1)"},
		{2066,LETTER_BOX,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,20.000000,"Ящик для бумаг (Тип 2)"},
		{2067,LETTER_BOX,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,20.000000,"Ящик для бумаг (Тип 3)"},
		{1763,SOFA,{-0.600000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,0.000000,"Диван (Тип 1)"},
		{1764,SOFA,{-1.000000,1.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.099999,0.000000,"Диван (Тип 2)"},
		{1768,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 3)"},
		{1757,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 4)"},
		{1766,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 5)"},
		{1760,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 6)"},
		{1726,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 7)"},
		{1702,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 8)"},
		{2290,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 9)"},
		{1761,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 10)"},
		{1723,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 11)"},
		{1713,SOFA,{-0.800000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 12)"},
		{1703,SOFA,{-1.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Диван (Тип 13)"},
		{1759,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 1)"},
		{1765,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 2)"},
		{1769,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 3)"},
		{1758,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 4)"},
		{1767,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 5)"},
		{1755,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 6)"},
		{1727,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 7)"},
		{1705,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 8)"},
		{2291,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 9)"},
		{1762,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 10)"},
		{1724,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 11)"},
		{1708,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 12)"},
		{1704,ARMCHAIR,{-0.400000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Кресло (Тип 13)"},
		{2313,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 1)"},
		{2311,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 2)"},
		{2314,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 3)"},
		{2315,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 4)"},
		{2319,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 5)"},
		{2321,TABLE,{-0.600000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под TV (Тип 6)"},
		{2318,TV,{-0.100000,0.399999,0.600000},ANIM_TYPE_CARRY,100.000000,5.000000,1.600000,0.000000,"Телевизор (Тип 1)"},
		{2312,TV,{-0.100000,0.399999,0.700000},ANIM_TYPE_CARRY,100.000000,5.000000,1.700000,0.000000,"Телевизор (Тип 2)"},
		{2317,TV,{-0.100000,0.399999,0.600000},ANIM_TYPE_CARRY,100.000000,5.000000,1.600000,0.000000,"Телевизор (Тип 3)"},
		{2316,TV,{-0.100000,0.499999,0.700000},ANIM_TYPE_CARRY,100.000000,5.000000,1.700000,0.000000,"Телевизор (Тип 4)"},
		{2320,TV,{-0.100000,0.399999,0.600000},ANIM_TYPE_CARRY,100.000000,5.000000,1.600000,0.000000,"Телевизор (Тип 5)"},
		{2322,TV,{-0.100000,0.399999,0.600000},ANIM_TYPE_CARRY,100.000000,5.000000,1.600000,0.000000,"Телевизор (Тип 6)"},
		{1821,TABLE,{-0.500000,-0.100000,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.300000,0.000000,"Кофейный столик (Тип 1)"},
		{1815,TABLE,{-0.600000,0.199999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Кофейный столик (Тип 2)"},
		{1820,TABLE,{-0.500000,0.099999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.099999,0.000000,"Кофейный столик (Тип 4)"},
		{1816,TABLE,{-0.500000,0.099999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.099999,0.000000,"Кофейный столик (Тип 3)"},
		{1813,TABLE,{-0.500000,0.099999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.099999,0.000000,"Кофейный столик (Тип 5)"},
		{2234,TABLE,{-0.500000,-0.000000,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,0.999999,0.000000,"Кофейный столик (Тип 6)"},
		{1814,TABLE,{-0.500000,-0.000000,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.300000,0.000000,"Кофейный столик (Тип 7)"},
		{1817,TABLE,{-0.500000,-0.000000,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.300000,0.000000,"Кофейный столик (Тип 8)"},
		{2082,TABLE,{-0.600000,0.099999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.099999,0.000000,"Кофейный столик (Тип 9)"},
		{2083,TABLE,{-0.500000,-0.000000,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Кофейный столик (Тип 10)"},
		{1823,TABLE,{-0.600000,0.099999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.099999,0.000000,"Кофейный столик (Тип 11)"},
		{2235,TABLE,{-0.600000,-0.100000,0.100000},ANIM_TYPE_CARRY,100.000000,5.000000,1.100000,0.000000,"Кофейный столик (Тип 12)"},
		{2236,TABLE,{-0.500000,-0.000000,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.000000,0.000000,"Кофейный столик (Тип 13)"},
		{1818,TABLE,{-0.500000,0.399999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Кофейный столик (Тип 14)"},
		{2081,TABLE,{-0.500000,0.099999,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.300000,0.000000,"Кофейный столик (Тип 15)"},
		{1819,TABLE,{-0.600000,0.199999,0.000000},ANIM_TYPE_CARRY,100.000000,5.000000,1.199999,0.000000,"Кофейный столик (Тип 16)"},
		{2126,TABLE,{-0.500000,0.299999,-0.099999},ANIM_TYPE_CARRY,100.000000,5.000000,1.299999,0.000000,"Кофейный столик (Тип 17)"},
		{1822,TABLE,{-0.500000,0.199999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Кофейный столик (Тип 18)"},
		{2024,TABLE,{-0.500000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,0.000000,"Кофейный столик (Тип 19)"},
		{2023,LIGHTS,{0.000000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,0.000000,"Торшер (Тип 1)"},
		{2069,LIGHTS,{0.000000,0.799999,-0.899999},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,0.000000,"Торшер (Тип 2)"},
		{2108,LIGHTS,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,0.000000,"Торшер (Тип 3)"},
		{2239,LIGHTS,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,0.000000,"Торшер (Тип 4)"},
		{2346,TABLE,{-0.500000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,0.000000,"Подставка под электорнику"},
		{2103,AUDIO,{0.000000,0.399999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Музыкальный центр (Тип 1)"},
		{2102,AUDIO,{0.000000,0.399999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Музыкальный центр (Тип 2)"},
		{2226,AUDIO,{-0.100000,0.399999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Музыкальный центр (Тип 3)"},
		{1809,AUDIO,{-0.100000,0.299999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Музыкальный центр (Тип 4)"},
		{2101,AUDIO,{0.000000,0.399999,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.399999,0.000000,"Музыкальный центр (Тип 5)"},
		{1783,VIDEOGAME,{0.000000,0.399999,0.500000},ANIM_TYPE_CARRY,100.000000,5.000000,1.500000,0.000000,"Приставка (Тип 1)"},
		{1719,VIDEOGAME,{0.000000,0.299999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Приставка (Тип 2)"},
		{2028,VIDEOGAME,{0.000000,0.399999,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,0.000000,"Приставка (Тип 3)"},
		{1793,BED,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,0.000000,"Кровать (Тип 1)"},
		{1794,BED,{-0.400000,-0.500000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.600000,0.000000,"Кровать (Тип 2)"},
		{1700,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 3)"},
		{1799,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 4)"},
		{2301,BED,{-0.400000,-0.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.999999,0.000000,"Кровать (Тип 5)"},
		{1745,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 6)"},
		{1798,BED,{-0.400000,-0.200000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.799999,0.000000,"Кровать (Тип 7)"},
		{1797,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 8)"},
		{2090,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 9)"},
		{2299,BED,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,0.000000,"Кровать (Тип 10)"},
		{1740,CABINET,{0.000000,-0.700000,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,10.000000,"Тумбочка (Тип 1)"},
		{2306,CABINET,{0.000000,-0.700000,0.200000},ANIM_TYPE_CARRY,100.000000,5.000000,1.200000,10.000000,"Тумбочка (Тип 2)"},
		{2095,CABINET,{0.000000,-0.700000,0.400000},ANIM_TYPE_CARRY,100.000000,5.000000,1.400000,10.000000,"Тумбочка (Тип 3)"},
		{2328,CABINET,{0.000000,-0.600000,0.300000},ANIM_TYPE_CARRY,100.000000,5.000000,1.300000,10.000000,"Тумбочка (Тип 4)"},
		{1743,CHEST,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,20.000000,"Комод (Тип 1)"},
		{2094,CHEST,{-0.400000,-0.300000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.699999,20.000000,"Комод (Тип 2)"},
		{1741,CHEST,{-0.400000,-0.200000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.799999,20.000000,"Комод (Тип 3)"},
		{2323,CHEST,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,20.000000,"Комод (Тип 4)"},
		{2088,DRESSER,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,40.000000,"Шкаф (Тип 1)"},
		{2307,DRESSER,{-0.400000,-0.200000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.799999,40.000000,"Шкаф (Тип 2)"},
		{2330,DRESSER,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,40.000000,"Шкаф (Тип 3)"},
		{2329,DRESSER,{-0.400000,-0.100000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,0.899999,40.000000,"Шкаф (Тип 4)"},
		{2128,DRESSER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,50.000000,"Шкаф (Тип 5)"},
		{2140,DRESSER,{0.000000,1.000000,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,2.000000,50.000000,"Шкаф (Тип 6)"},
		{2158,DRESSER,{0.000000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Шкаф (Тип 7)"},
		{2141,DRESSER,{0.000000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Шкаф (Тип 8)"},
		{2129,KITCHEN_TABLE,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 1)"},
		{2137,KITCHEN_TABLE,{0.100000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 2)"},
		{2334,KITCHEN_TABLE,{0.000000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,30.000000,"Кухонный шкаф (Тип 3)"},
		{2134,KITCHEN_TABLE,{0.100000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,30.000000,"Кухонный шкаф (Тип 4)"},
		{2139,KITCHEN_TABLE,{0.100000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 5)"},
		{2130,KITCHEN_TABLE_EX,{-0.400000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Кухонный шкаф (Тип 6)"},
		{2136,KITCHEN_TABLE_EX,{-0.500000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 7)"},
		{2336,KITCHEN_TABLE_EX,{-0.500000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 8)"},
		{2132,KITCHEN_TABLE_EX,{-0.500000,0.799999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.799999,50.000000,"Кухонный шкаф (Тип 9)"},
		{2127,REFRIDGERATOR,{-0.300000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Холодильник (Тип 1)"},
		{2147,REFRIDGERATOR,{0.000000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Холодильник (Тип 2)"},
		{2131,REFRIDGERATOR,{-0.400000,0.899999,-1.000000},ANIM_TYPE_PUSH,100.000000,5.000000,1.899999,50.000000,"Холодильник (Тип 3)"}
	},
	// players
	PlayerMoveFurnitureType[MAX_PLAYERS char],
	PlayerMoveType[MAX_PLAYERS char],
	PlayerMoveObjectId[MAX_PLAYERS],
	inttmp[32];

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native CreateFurniture(type,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ,premise);
native GetFurnitureType(furnitureid);
native Float:GetFurnitureMaxLuggage(furnitureid);
native GetFurnitureModeObject(furnitureid);
native Float:GetFurnituresMassForVehicle(vehicleid);
native SetFurnitureVar(furnitureid,varid,value);
native GetFurnitureVar(furnitureid,varid);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock CreateFurniture(type,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ,vw)
{
	Debug(DEBUG_START,"CreateFurniture(%d,%f,%f,%f,%f,%f,%f,%d)",type,X,Y,Z,rX,rY,rZ,vw);
	new furnitureid = GetHoldingDataByOrder("Furniture","Fid",HOLDING_ORDER_MAXIMAL) + 1,
		obj;
	Debug(DEBUG_ACTION,"convert");
	AddHolding("Furniture","Fid",HOLDING_NAME_INT,furnitureid);
	if(OpenHolding("Furniture","Fid",HOLDING_MODE_WRITE,HOLDING_NAME_INT,furnitureid))
	{
		SetHoldingDataInt("Type",type);
		SetHoldingDataFloat("X",X);
		SetHoldingDataFloat("Y",Y);
		SetHoldingDataFloat("Z",Z);
		SetHoldingDataFloat("rX",rX);
		SetHoldingDataFloat("rY",rY);
		SetHoldingDataFloat("rZ",rZ);
		SetHoldingDataInt("VirtualWorld",vw);
		SetHoldingDataFloat("Health",Furniture[type][fHealth]);
		SetHoldingDataInt("VehicleId",INVALID_MODE_VEHICLE_ID);
		new tmp[5];
		for(new i = 0;i < MAX_FURNITURE_VARS;i++)
		{
		    format(tmp,sizeof(tmp),"Var%d",i);
		    SetHoldingDataInt(tmp,0);
		}
		Debug(DEBUG_ACTION,"create object");
		obj = CreateModeObject(Furniture[type][fModel],X,Y,Z,rX,rY,rZ,255,vw,Furniture[type][fHealth],MODE_OBJECT_TYPE_FURNITURE,furnitureid);
		CloseHolding();
	}
	CallRemoteFunction("OnFurnitureCreated","ddd",furnitureid,type,obj);
	Debug(DEBUG_END,"CreateFurniture(reason: complete)");
	return furnitureid;
}

stock DestroyFurniture(furnitureid)
{
	Debug(DEBUG_START,"DestroyFurniture(%d)",furnitureid);
	CallRemoteFunction("OnFurnitureDestroyed","ddd",furnitureid,GetFurnitureType(furnitureid));
	DeleteHolding("Furniture","Fid",HOLDING_NAME_INT,furnitureid);
	Debug(DEBUG_ACTION,"destroy object");
	for(new i = 0;i <= GetMaxModeObjectId();i++)
	{
	    if(!IsValidModeObject(i)) continue;
	    if(GetModeObjectType(i) != MODE_OBJECT_TYPE_FURNITURE) continue;
	    if(GetModeObjectTypeParam(i) != furnitureid) continue;
	    
	    DestroyModeObject(i);
	    break;
	}
	Debug(DEBUG_END,"DestroyFurniture(reason: complete)");
	return 1;
}

stock GetFurnitureType(furnitureid)
{
	Debug(DEBUG_START,"GetFurnitureType(%d)",furnitureid);
	new res;
	if(OpenHolding("Furniture","Fid",HOLDING_MODE_READ,HOLDING_NAME_INT,furnitureid))
	{
		res = GetHoldingDataInt("Type");
		CloseHolding();
	}
	Debug(DEBUG_END,"GetFurnitureType(reason: complete)");
	return res;
}

stock Float:GetFurnitureMaxLuggage(furnitureid)
{
	Debug(DEBUG_START,"GetFurnitureMaxLuggage(%d)",furnitureid);
	new res = GetFurnitureType(furnitureid);
	Debug(DEBUG_END,"GetFurnitureMaxLuggage(reason: complete)");
	return Furniture[res][fMaxLuggageMass];
}

stock Float:GetFurnituresMassForVehicle(vehicleid)
{
    Debug(DEBUG_START,"GetFurnituresMassForVehicle(%d)",vehicleid);
    new Float:mas;
    if(OpenHoldingTable("Furniture"))
    {
    	do
    	{
     	   if(GetHoldingDataInt("VehicleId") == vehicleid)
     	   {
     	       mas += Furniture[GetHoldingDataInt("Type")][fMass];
     	   }
    	}
    	while(NextHoldingTableRow());
    	CloseHoldingTable();
	}
	Debug(DEBUG_END,"GetFurnituresMassForVehicle(reason: complete)");
	return mas;
}

stock SetFurnitureVar(furnitureid,varid,value)
{
	Debug(DEBUG_START,"SetFurnitureVar(%d,%d,%d)",furnitureid,varid,value);
	if(OpenHolding("Furniture","Fid",HOLDING_MODE_WRITE,HOLDING_NAME_INT,furnitureid))
	{
		format(inttmp,sizeof(inttmp),"Var%d",varid);
		SetHoldingDataInt(inttmp,value);
		CloseHolding();
	}
	Debug(DEBUG_END,"SetFurnitureVar(reason: complete)");
	return 1;
}

stock GetFurnitureVar(furnitureid,varid)
{
	Debug(DEBUG_START,"GetFurnitureVar(%d,%d)",furnitureid,varid);
	new res;
	if(OpenHolding("Furniture","Fid",HOLDING_MODE_READ,HOLDING_NAME_INT,furnitureid))
	{
		format(inttmp,sizeof(inttmp),"Var%d",varid);
		res = GetHoldingDataInt(inttmp);
		CloseHolding();
	}
	Debug(DEBUG_END,"GetFurnitureVar(reason: complete)");
	return res;
}

stock IsValidFurniture(furnitureid)
{
	Debug(DEBUG_SMALL,"IsValidFurniture(%d)",furnitureid);
	return IsHoldingExist("Furniture","Fid",HOLDING_NAME_INT,furnitureid);
}

stock SetCurrentFurnitureVehicle(furnitureid,vehicleid)
{
	Debug(DEBUG_START,"SetCurrentFurnitureVehicle(%d,%d)",furnitureid,vehicleid);
    if(OpenHolding("Furniture","Fid",HOLDING_MODE_WRITE,HOLDING_NAME_INT,furnitureid))
	{
		SetHoldingDataInt("VehicleId",vehicleid);
		CloseHolding();
	}
	Debug(DEBUG_END,"SetCurrentFurnitureVehicle(reason: complete)");
}

stock GetFurnitureModeObject(furnitureid)
{
    Debug(DEBUG_START,"GetFurnitureModeObject(%d)",furnitureid);
    new ret;
    for(new i = 0;i <= GetMaxModeObjectId();i++)
	{
	    if(!IsValidModeObject(i)) continue;
	    if(GetModeObjectType(i) != MODE_OBJECT_TYPE_FURNITURE) continue;
	    if(GetModeObjectTypeParam(i) != furnitureid) continue;

	    ret = i;
	    break;
	}
	Debug(DEBUG_END,"GetFurnitureModeObject(reason: complete)");
	return ret;
}

// --------------------------------------------------
// static functions
// --------------------------------------------------
static stock CheckAction(playerid,furnitureid,type,group,modeobject,actionid)
{
	/*
	switch(group)
	{
	    case SHOP_COUNTER: return ShopCounter_CheckAction(playerid,furnitureid,type,group,modeobject,actionid);
	}
	*/
	return 0;
}

static stock SelectAction(playerid,furnitureid,type,group,modeobject,actionid)
{
	/*
	switch(group)
	{
	    case SHOP_COUNTER: return ShopCounter_SelectAction(playerid,furnitureid,type,group,modeobject,actionid);
	}
	*/
	return 0;
}

static stock DialogSelect(playerid,dialogid,response,listitem,inputtext[],furnitureid,type,group,modeobject)
{
	/*
	switch(group)
	{
	    case SHOP_COUNTER: return ShopCounter_DialogSelect(playerid,dialogid,response,listitem,inputtext,furnitureid,type,group,modeobject);
	}
	*/
	return 0;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Furniture_Init()
{
	Debug(DEBUG_START,"Furniture_Init()");
	AddActionSelectRow(RusToGame("Передвинуть~n~мебель"),ACTION_MOVE_FURNITURE);
	AddActionSelectRow(RusToGame("Погрузить~n~в~n~транспорт"),ACTION_PUT_FURNITURE_IN_VEH);
	AddActionSelectRow(RusToGame("Забрать~n~мебель~n~из~n~транспорта"),ACTION_GET_FURNITURE_FROM_VEH);
	Debug(DEBUG_ACTION,"create vars");
	new fid,
		type,
		vw,
		Float:X,
		Float:Y,
		Float:Z,
		Float:rX,
		Float:rY,
		Float:rZ,
		Float:Health;
    Debug(DEBUG_ACTION,"load furnitures from base");
    if(OpenHoldingTable("Furniture"))
    {
	    do
	    {
	        fid = GetHoldingDataInt("Fid");
	        type = GetHoldingDataInt("Type");
			X = GetHoldingDataFloat("X");
			Y = GetHoldingDataFloat("Y");
			Z = GetHoldingDataFloat("Z");
			rX = GetHoldingDataFloat("rX");
			rY = GetHoldingDataFloat("rY");
			rZ = GetHoldingDataFloat("rZ");
			vw = GetHoldingDataInt("VirtualWorld");
			Health = GetHoldingDataFloat("Health");
			new obj = CreateModeObject(Furniture[type][fModel],X,Y,Z,rX,rY,rZ,255,vw,Furniture[type][fHealth],MODE_OBJECT_TYPE_FURNITURE,fid);
			SetModeObjectHealth(obj,Health);
	   		if(GetHoldingDataInt("VehicleId") != INVALID_MODE_VEHICLE_ID) HideModeObject(obj);
            CallRemoteFunction("OnFurnitureLoaded","ddd",fid,type,obj);
	    }
	    while(NextHoldingTableRow());
	    CloseHoldingTable();
	}
	print("[GAME] Furniture system loaded.");
	Debug(DEBUG_END,"Furniture_Init(reason: complete)");
}

Furniture_PlayerActionCheck(playerid,actionid)
{
	Debug(DEBUG_START,"Furniture_PlayerActionCheck(%d,%d)",playerid,actionid);
	switch(actionid)
	{
		case ACTION_MOVE_FURNITURE:
		{
			Debug(DEBUG_ACTION,"ACTION_MOVE_FURNITURE");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player have action)");return 0;}
			new modeobject = GetPlayerClosestModeObject(playerid);
			if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: havent closest object)");return 0;}
			if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: closest object attached)");return 0;}
			if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: object not furniture)");return 0;}
			new type = GetFurnitureType(GetModeObjectTypeParam(modeobject));
			if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: object not in range)");return 0;}
			Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: complete)");
			return 1;
		}
		case ACTION_PUT_FURNITURE_IN_VEH:
		{
			Debug(DEBUG_ACTION,"ACTION_PUT_FURNITURE_IN_VEH");
			if(GetPlayerAction(playerid) != ACTION_MOVE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player not moving furniture)");return 0;}
			new modeobject = GetPlayerAttachedModeObject(playerid);
			if(modeobject == INVALID_MODE_OBJECT_ID) 
			{
				print("[ERROR] Furniture -> Furniture_PlayerActionCheck (player action \"move furniture\" & not attached object");
				Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player not attaching object)");
				return 0;
			}
			if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: object not furniture)");return 0;}
			Debug(DEBUG_ACTION,"Find closest vehicle");
			new modevehicle = GetPlayerClosestModeVehicle(playerid);
			if(modevehicle == INVALID_MODE_VEHICLE_ID) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: havent closest vehicle)");return 0;}
			if(!IsPlayerAroundLuggageModeVehicl(playerid,modevehicle)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player not around luggage)");return 0;}
			if(GetModeVehicleLuggageType(modevehicle) != LUGGAGE_BIG) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: small vehicle's luggage)");return 0;}
			Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: complete)");
			return 1;
		}
		case ACTION_GET_FURNITURE_FROM_VEH:
		{
			Debug(DEBUG_ACTION,"ACTION_GET_FURNITURE_FROM_VEH");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player have action)");return 0;}
			Debug(DEBUG_ACTION,"Find closest vehicle");
			new modevehicle = GetPlayerClosestModeVehicle(playerid);
			if(modevehicle == INVALID_MODE_VEHICLE_ID) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: havent closest vehicle)");return 0;}
			if(!IsPlayerAroundLuggageModeVehicl(playerid,modevehicle)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: player not around luggage)");return 0;}
			if(GetModeVehicleLuggageType(modevehicle) != LUGGAGE_BIG) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: small vehicle's luggage)");return 0;}
			new st = 0;
			if(OpenHoldingTable("Furniture"))
			{
			    do
			    {
			        if(GetHoldingDataInt("VehicleId") == modevehicle)
					{
						st = 1;
						break;
					}
			    }
			    while(NextHoldingTableRow());
			    CloseHoldingTable();
			}
			if(st == 0) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: vehicle havent luggage)");return 0;}
			Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_ACTION,"Check furnitures actions");
	new modeobject = GetPlayerClosestModeObject(playerid);
	if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: havent closest object)");return 0;}
	if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: closest object attached)");return 0;}
	if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: object not furniture)");return 0;}
	new fid = GetModeObjectTypeParam(modeobject);
	new type = GetFurnitureType(fid);
	if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: object not in range)");return 0;}
	if(CheckAction(playerid,fid,type,Furniture[type][fGroup],modeobject,actionid)) {Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: complete)");return 1;}
	Debug(DEBUG_END,"Furniture_PlayerActionCheck(reason: complete)");
	return 0;
}

Furniture_PlayerActionSelect(playerid,actionid)
{
	Debug(DEBUG_START,"Furniture_PlayerActionSelect(%d,%d)",playerid,actionid);
	switch(actionid)
	{
		case ACTION_MOVE_FURNITURE: 
		{
			Debug(DEBUG_ACTION,"ACTION_MOVE_FURNITURE");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: player have action)");return 0;}
			new modeobject = GetPlayerClosestModeObject(playerid);
			if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: havent closest object)");return 0;}
			if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: closest object attached)");return 0;}
			if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: object not furniture)");return 0;}
			new type = GetFurnitureType(GetModeObjectTypeParam(modeobject));
			if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: object not in range)");return 0;}
			ShowPlayerModeDialog(playerid,DIALOG_FURNITURE_MOVING,DIALOG_STYLE_LIST,"Передвинуть мебель","Переместить на большое расстояние\nНемного подвинуть","Выбрать","Отмена");
			Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: complete)");
			return 1;
		}
		case ACTION_PUT_FURNITURE_IN_VEH:
		{
			Debug(DEBUG_ACTION,"ACTION_PUT_FURNITURE_IN_VEH");
			if(GetPlayerAction(playerid) != ACTION_MOVE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: player not moving furniture)");return 0;}
			new modeobject = GetPlayerAttachedModeObject(playerid);
			if(modeobject == INVALID_MODE_OBJECT_ID) 
			{
				print("[ERROR] Furniture -> Furniture_PlayerActionSelect (player action \"move furniture\" & not attached object");
				Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: player not attaching object)");
				return 0;
			}
			if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: object not furniture)");return 0;}
			Debug(DEBUG_ACTION,"Find closest vehicle");
			new modevehicle = GetPlayerClosestModeVehicle(playerid);
			if(modevehicle == INVALID_MODE_VEHICLE_ID) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: havent closest vehicle)");return 0;}
			if(!IsPlayerAroundLuggageModeVehicl(playerid,modevehicle)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: player not around luggage)");return 0;}
			if(GetModeVehicleLuggageType(modevehicle) != LUGGAGE_BIG) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: small vehicle's luggage)");return 0;}
			Debug(DEBUG_ACTION,"get full luggage's mass");
			new type = GetFurnitureType(GetModeObjectTypeParam(modeobject)),
				Float:luggagemass = Furniture[type][fMass] + GetFurnituresMassForVehicle(modevehicle);
			if(luggagemass > GetModeVehicleMaxLuggage(modevehicle)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: small vehicle's luggage)");return 0;}
			Debug(DEBUG_ACTION,"put furniture");
			DeAttachModeObject(modeobject);
			HideModeObject(modeobject);
			SetCurrentFurnitureVehicle(GetModeObjectTypeParam(modeobject),modevehicle);
			SetPlayerAction(playerid,ACTION_NONE);
			Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: complete)");
			return 1;
		}
		case ACTION_GET_FURNITURE_FROM_VEH:
		{
			Debug(DEBUG_ACTION,"ACTION_GET_FURNITURE_FROM_VEH");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: player have action)");return 0;}
			Debug(DEBUG_ACTION,"Find closest vehicle");
			new modevehicle = GetPlayerClosestModeVehicle(playerid);
			if(modevehicle == INVALID_MODE_VEHICLE_ID) {Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: havent closest vehicle)");return 0;}
			if(!IsPlayerAroundLuggageModeVehicl(playerid,modevehicle)) {Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: player not around luggage)");return 0;}
			if(GetModeVehicleLuggageType(modevehicle) != LUGGAGE_BIG) {Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: small vehicle's luggage)");return 0;}
            new li = 0;
            nullstr(DialogString);
			if(OpenHoldingTable("Furniture"))
			{
			    do
			    {
			        if(GetHoldingDataInt("VehicleId") == modevehicle)
					{
					    strcat(DialogString,Furniture[GetHoldingDataInt("Type")][fName]);
					    strcat(DialogString,"\n");
					    SetPlayerModeDialogListData(playerid,li,GetHoldingDataInt("Fid"));
					    li++;
						break;
					}
			    }
			    while(NextHoldingTableRow());
			    CloseHoldingTable();
			}
			if(li == 0) {Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: vehicle havent luggage)");return 0;}
			ShowPlayerModeDialog(playerid,DIALOG_FURNITURE_IN_VEHICLE,DIALOG_STYLE_LIST,"Забрать мебель",DialogString,"Выбрать","Отмена");
			Debug(DEBUG_END,"Furniture_OnPlayerActionCheck(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_ACTION,"Check furnitures actions");
	new modeobject = GetPlayerClosestModeObject(playerid);
	if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: havent closest object)");return 0;}
	if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: closest object attached)");return 0;}
	if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: object not furniture)");return 0;}
	new fid = GetModeObjectTypeParam(modeobject);
	new type = GetFurnitureType(fid);
	if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: object not in range)");return 0;}
	if(SelectAction(playerid,fid,type,Furniture[type][fGroup],modeobject,actionid)) {Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: complete)");return 1;}
	Debug(DEBUG_END,"Furniture_PlayerActionSelect(reason: complete)");
	return 0;
}

Furniture_ModeDialogResponse(playerid,dialogid,response,listitem,inputtext[])
{
	#pragma unused inputtext
	Debug(DEBUG_START,"Furniture_ModeDialogResponse(%d,%d,%d,%d)",playerid,dialogid,response,listitem);

	if(!response)
	{
	    Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: canceled)");
		return 1;
	}

	switch(dialogid)
	{
		case DIALOG_FURNITURE_MOVING:
		{
			Debug(DEBUG_ACTION,"DIALOG_FURNITURE_MOVING");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: player have action)");return 0;}
			new modeobject = GetPlayerClosestModeObject(playerid);
			if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: havent closest object)");return 0;}
			if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: closest object attached)");return 0;}
			if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: object not furniture)");return 0;}
			new fid = GetModeObjectTypeParam(modeobject);
			new type = GetFurnitureType(fid);
			if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: object not in range)");return 0;}
			Debug(DEBUG_ACTION,"move object");
			switch(listitem)
			{
				case 0: // Быстрое перемещение
				{
					AttachModeObjectToPlayer(modeobject,playerid,Furniture[type][fAttachCoords][0],Furniture[type][fAttachCoords][1],Furniture[type][fAttachCoords][2],0.0,0.0,0.0);
					PlayerMoveType{playerid} = MOVING_TYPE_FAST;
					ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_FAST_MOVING,INFO_FAST_MOVE);
				}
				case 1: // Медленное перемещение
				{
					new Float:pos[4];
					GetModeObjectRot(modeobject,pos[0],pos[1],pos[3]);
					GetModeObjectPos(modeobject,pos[0],pos[1],pos[2]);
					MovePlayerCameraAroundXYZEx(playerid,MODE_CAMERA_FURNITURE_MOVING,pos[0],pos[1],pos[2],Furniture[type][fSize] + 2.5,0.5,(pos[3] - 90.0),(pos[3] + 90.0),DIRECTION_RIGHT);
					PlayerMoveType{playerid} = MOVING_TYPE_SLOW;
					ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_SLOW_MOVING,INFO_SLOW_MOVE);
					TogglePlayerControllableEx(playerid,false);
				}
			}
			PlayerMoveFurnitureType{playerid} = type;
			PlayerMoveObjectId[playerid] = modeobject;
			SetPlayerAction(playerid,ACTION_MOVE_FURNITURE);
			Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: complete)");
			return 1;
		}
		case DIALOG_FURNITURE_IN_VEHICLE:
		{
			Debug(DEBUG_ACTION,"DIALOG_FURNITURE_IN_VEHICLE");
			if(GetPlayerAction(playerid) != ACTION_NONE) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: player have action)");return 0;}
			Debug(DEBUG_ACTION,"Find closest vehicle");
			new modevehicle = GetPlayerClosestModeVehicle(playerid);
			if(modevehicle == INVALID_MODE_VEHICLE_ID) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: havent closest vehicle)");return 0;}
			if(!IsPlayerAroundLuggageModeVehicl(playerid,modevehicle)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: player not around luggage)");return 0;}
			if(GetModeVehicleLuggageType(modevehicle) != LUGGAGE_BIG) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: small vehicle's luggage)");return 0;}
			Debug(DEBUG_ACTION,"Get furniture");
			new furniture = GetPlayerModeDialogListData(playerid,listitem),
				modeobject = GetFurnitureModeObject(furniture),
				type = GetFurnitureType(furniture);
			ShowModeObject(modeobject);
			AttachModeObjectToPlayer(modeobject,playerid,Furniture[type][fAttachCoords][0],Furniture[type][fAttachCoords][1],Furniture[type][fAttachCoords][2],0.0,0.0,0.0);
			PlayerMoveFurnitureType{playerid} = type;
			PlayerMoveType{playerid} = MOVING_TYPE_FAST;
			PlayerMoveObjectId[playerid] = modeobject;
			ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_FAST_MOVING,INFO_FAST_MOVE);
			SetPlayerAction(playerid,ACTION_MOVE_FURNITURE);
			Debug(DEBUG_ACTION,"Update data");
			SetCurrentFurnitureVehicle(GetModeObjectTypeParam(modeobject),INVALID_MODE_VEHICLE_ID);
			SetPlayerAction(playerid,ACTION_NONE);
			Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: complete)");
			return 1;
		}
	}
	Debug(DEBUG_ACTION,"Check furnitures dialogs");
	new modeobject = GetPlayerClosestModeObject(playerid);
	if(modeobject == INVALID_MODE_OBJECT_ID) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: havent closest object)");return 0;}
	if(IsModeObjectAttached(modeobject)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: closest object attached)");return 0;}
	if(GetModeObjectType(modeobject) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: object not furniture)");return 0;}
	new fid = GetModeObjectTypeParam(modeobject);
	new type = GetFurnitureType(fid);
	if(!IsPlayerRangeOfModeObject(playerid,Furniture[type][fSize],modeobject)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: object not in range)");return 0;}
	if(DialogSelect(playerid,dialogid,response,listitem,inputtext,fid,type,Furniture[type][fGroup],modeobject)) {Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: complete)");return 1;}
	Debug(DEBUG_END,"Furniture_ModeDialogResponse(reason: complete)");
	return 0;
}

Furniture_PlayerUpdate(playerid)
{
	Debug(DEBUG_START,"Furniture_PlayerUpdate(%d)",playerid);
	if(GetPlayerAction(playerid) != ACTION_MOVE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: player not move furniture)");return 1;}
	new keys[3];
	GetPlayerKeys(playerid,keys[0],keys[1],keys[2]);
	switch(PlayerMoveType{playerid})
	{
		case MOVING_TYPE_SLOW:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_SLOW");
			new Float:pos[3];
			switch(keys[0]) // вверх вниз
			{
				case KEY_JUMP:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[2] += 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_SPRINT:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[2] -= 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
			switch(keys[1]) // вперед назад
			{
				case KEY_UP:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[0] += 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_DOWN:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[0] -= 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
			switch(keys[2]) // лево право
			{
				case KEY_LEFT:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[1] += 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_RIGHT:
				{
					GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[1] -= 0.1;
					SetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					SetPlayerCameraAroundCenter(playerid,pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
		}
		case MOVING_TYPE_FAST:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_FAST");
			if((keys[1] & KEY_UP) || (keys[1] & KEY_DOWN) || (keys[2] & KEY_LEFT) || (keys[2] & KEY_RIGHT))
			{
				switch(Furniture[ PlayerMoveFurnitureType{playerid} ][fAnimType])
				{
					case ANIM_TYPE_CARRY: ApplyAnimation(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1,FORCE_SYNC_ALL);
					case ANIM_TYPE_PUSH: ApplyAnimation(playerid,"CHAINSAW","CSAW_3",4.1,0,1,1,1,1,FORCE_SYNC_ALL);
				}
				Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
				return 1;
			}
		}
		case MOVING_TYPE_ANGLE:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_ANGLE");
			new Float:pos[3];
			switch(keys[0]) // вверх вниз
			{
				case KEY_JUMP:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[2] += 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_SPRINT:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[2] -= 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
			switch(keys[1]) // вперед назад
			{
				case KEY_UP:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[0] += 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_DOWN:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[0] -= 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
			switch(keys[2]) // лево право
			{
				case KEY_LEFT:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[1] += 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
				case KEY_RIGHT:
				{
					GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					pos[1] -= 1.0;
					SetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
					Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
					return 1;
				}
			}
		}
	}
	Debug(DEBUG_END,"Furniture_PlayerUpdate(reason: complete)");
	return 1;
}

Furniture_PlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Furniture_PlayerKeyStateChange(%d,%d,%d)",playerid,newkeys,oldkeys);
	if(GetPlayerAction(playerid) != ACTION_MOVE_FURNITURE) {Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: player not move furniture)");return 1;}
	switch(PlayerMoveType{playerid})
	{
		case MOVING_TYPE_SLOW:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_SLOW");
			if(newkeys & KEY_FIRE)
			{
				SetPlayerCameraAroundRadius(playerid,(GetPlayerCameraAroundRadius(playerid) + 0.5));
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_HANDBRAKE)
			{
				SetPlayerCameraAroundRadius(playerid,(GetPlayerCameraAroundRadius(playerid) - 0.5));
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_WALK)
			{
				Debug(DEBUG_ACTION,"stop moving");
				TogglePlayerControllableEx(playerid,true);
				SetPlayerAction(playerid,ACTION_NONE);
				StopPlayerCamera(playerid,true);
				Debug(DEBUG_ACTION,"save info");
				new Float:Pos[6];
				GetModeObjectPos(PlayerMoveObjectId[playerid],Pos[0],Pos[1],Pos[2]);
				GetModeObjectRot(PlayerMoveObjectId[playerid],Pos[3],Pos[4],Pos[5]);
                if(OpenHolding("Furniture","Fid",HOLDING_MODE_WRITE,HOLDING_NAME_INT,GetModeObjectTypeParam(PlayerMoveObjectId[playerid])))
				{
					SetHoldingDataFloat("X",Pos[0]);
					SetHoldingDataFloat("Y",Pos[1]);
					SetHoldingDataFloat("Z",Pos[2]);
					SetHoldingDataFloat("rX",Pos[3]);
					SetHoldingDataFloat("rY",Pos[4]);
					SetHoldingDataFloat("rZ",Pos[5]);
					SetHoldingDataInt("VirtualWorld",GetModeObjectVirtualWorld(PlayerMoveObjectId[playerid]));
					CloseHolding();
				}
				Debug(DEBUG_ACTION,"clear data");
				PlayerMoveFurnitureType{playerid} = 0;
				PlayerMoveObjectId[playerid] = INVALID_MODE_OBJECT_ID;
				PlayerMoveType{playerid} = MOVING_TYPE_NONE;
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_CROUCH)
			{
				PlayerMoveType{playerid} = MOVING_TYPE_ANGLE;
				ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_ANGLE_MOVING,INFO_ANGLE_MOVE);
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
		}
		case MOVING_TYPE_FAST:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_FAST");
			if(newkeys & KEY_WALK)
			{
				DeAttachModeObject(PlayerMoveObjectId[playerid]);
				new Float:pos[4];
				GetModeObjectRot(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[3]);
				GetModeObjectPos(PlayerMoveObjectId[playerid],pos[0],pos[1],pos[2]);
				pos[3] -= 180.0;
				MovePlayerCameraAroundXYZEx(playerid,MODE_CAMERA_FURNITURE_MOVING,pos[0],pos[1],pos[2],Furniture[ PlayerMoveFurnitureType{playerid} ][fSize] + 2.5,0.5,(pos[3] - 90.0),(pos[3] + 90.0),DIRECTION_RIGHT);
				PlayerMoveType{playerid} = MOVING_TYPE_SLOW;
				ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_SLOW_MOVING,INFO_SLOW_MOVE);
				TogglePlayerControllableEx(playerid,false);
				ClearAnimations(playerid,FORCE_SYNC_ALL);
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
		}
		case MOVING_TYPE_ANGLE:
		{
			Debug(DEBUG_ACTION,"MOVING_TYPE_ANGLE");
			if(newkeys & KEY_FIRE)
			{
				SetPlayerCameraAroundRadius(playerid,(GetPlayerCameraAroundRadius(playerid) + 0.5));
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_HANDBRAKE)
			{
				SetPlayerCameraAroundRadius(playerid,(GetPlayerCameraAroundRadius(playerid) - 0.5));
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_WALK)
			{
				Debug(DEBUG_ACTION,"stop moving");
				TogglePlayerControllableEx(playerid,true);
				SetPlayerAction(playerid,ACTION_NONE);
				StopPlayerCamera(playerid,true);
				Debug(DEBUG_ACTION,"save info");
				new Float:Pos[6];
				GetModeObjectPos(PlayerMoveObjectId[playerid],Pos[0],Pos[1],Pos[2]);
				GetModeObjectRot(PlayerMoveObjectId[playerid],Pos[3],Pos[4],Pos[5]);
				if(OpenHolding("Furniture","Fid",HOLDING_MODE_WRITE,HOLDING_NAME_INT,GetModeObjectTypeParam(PlayerMoveObjectId[playerid])))
				{
					SetHoldingDataFloat("X",Pos[0]);
					SetHoldingDataFloat("Y",Pos[1]);
					SetHoldingDataFloat("Z",Pos[2]);
					SetHoldingDataFloat("rX",Pos[3]);
					SetHoldingDataFloat("rY",Pos[4]);
					SetHoldingDataFloat("rZ",Pos[5]);
					SetHoldingDataInt("VirtualWorld",GetModeObjectVirtualWorld(PlayerMoveObjectId[playerid]));
					CloseHolding();
				}
				Debug(DEBUG_ACTION,"clear data");
				PlayerMoveFurnitureType{playerid} = 0;
				PlayerMoveObjectId[playerid] = INVALID_MODE_OBJECT_ID;
				PlayerMoveType{playerid} = MOVING_TYPE_NONE;
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
			if(newkeys & KEY_CROUCH)
			{
				PlayerMoveType{playerid} = MOVING_TYPE_SLOW;
				ShowHelpBoxForPlayer(playerid,HELPBOX_FURNITURE_SLOW_MOVING,INFO_SLOW_MOVE);
				Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
				return 1;
			}
		}
	}
	Debug(DEBUG_END,"Furniture_PlayerKeyStateChange(reason: complete)");
	return 0;
}

Furniture_PlayerCCMoving(playerid,cameraid)
{
	Debug(DEBUG_START,"Furniture_PlayerCCMoving(%d,%d)",playerid,cameraid);
	if(cameraid != MODE_CAMERA_FURNITURE_MOVING) {Debug(DEBUG_END,"Furniture_PlayerCCMoving(reason: camera not from moving)");return 0;}
	switch(GetPlayerCameraAroundDirection(playerid))
	{
		case DIRECTION_LEFT: SetPlayerCameraAroundDirection(playerid,DIRECTION_RIGHT);
		case DIRECTION_RIGHT: SetPlayerCameraAroundDirection(playerid,DIRECTION_LEFT);
	}
	Debug(DEBUG_END,"Furniture_PlayerCCMoving(reason: complete)");
	return 1;
}

Furniture_ModeObjectDeath(objectid)
{
	Debug(DEBUG_START,"Furniture_ModeObjectDeath(%d)",objectid);
	if(GetModeObjectType(objectid) != MODE_OBJECT_TYPE_FURNITURE) {Debug(DEBUG_END,"Furniture_ModeObjectDeath(reason: object not furniture)");return 0;}
	new furnitureid = GetModeObjectTypeParam(objectid);
	new type = GetFurnitureType(furnitureid);
	Debug(DEBUG_ACTION,"delete furniture from base");
	DeleteHolding("Furniture","Fid",HOLDING_NAME_INT,furnitureid);
	CallRemoteFunction("OnFurnitureDeath","ddd",furnitureid,type,objectid);
	DestroyModeObject(objectid);
	Debug(DEBUG_END,"Furniture_ModeObjectDeath(reason: complete)");
	return 1;
}
