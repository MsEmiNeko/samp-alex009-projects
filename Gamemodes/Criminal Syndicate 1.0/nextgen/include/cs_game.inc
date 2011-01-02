/*
*	Created:			04.10.10
*	Author:				009
*	Description:        "Criminal Syndicate 1.0" game modules
*/

#if defined _cs_game_included
  #endinput
#endif
#define _cs_game_included
#pragma library cs_game

// --------------------------------------------------
// includes
// --------------------------------------------------
// core
#include <cs_core>
// game modules
#tryinclude "../game/premise.p"
#tryinclude "../game/furniture.p"

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native Premise

native GetPlayerPremise(playerid);
native SetPlayerPremise(playerid,premiseid);
native GetPremiseDoorStatus(premiseid);
native SetPremiseDoorStatus(premiseid,status);
native GetPremiseKeysize(premiseid);
native SetPremiseKeysize(premiseid,keysize);
native GetPremiseEnterPos(premiseid,&Float:X,&Float:Y,&Float:Z);
native GetPlayerPremiseEnterOn(playerid);
native GetPlayerPremiseExitOn(playerid);

native
*/
