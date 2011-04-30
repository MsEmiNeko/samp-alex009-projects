/*
*	Created:			05.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:        Прилавки магазинов
*/

#if defined _furnitures_shop_counter_included
	#endinput
#endif

#define _furnitures_shop_counter_included
#pragma library furnitures_shop_counter

// --------------------------------------------------
// includes
// --------------------------------------------------


// --------------------------------------------------
// enums
// --------------------------------------------------


// --------------------------------------------------
// news
// --------------------------------------------------


// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native 
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock 

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
ShopCounter_Init()
{
    AddActionSelectRow(RusToGame("Передвинуть~n~мебель"),ACTION_MOVE_FURNITURE);
}

ShopCounter_CheckAction(playerid,furnitureid,type,group,modeobject,actionid)
{

	return 0;
}
