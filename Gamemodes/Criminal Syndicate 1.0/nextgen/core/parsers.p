/*
*	Created:			21.01.10
*	Author:				009
*	Description:		Парсеры для ускорения выбора действия
*/

#if defined core_parsers_included
	#endinput
#endif

#define core_parsers_included
#pragma library core_parsers

// --------------------------------------------------
// defines
// --------------------------------------------------
#define RegisterCmd(%1,%2,%3,%4,%5) if(!strcmp(%1,%2,true,%3) && ((%1[%3] == ' ') || (%1[%3] == 0))) return %4_Command(playerid,%5,%1[%3 + 1])
#define RegisterText(%1,%2,%3,%4)	if(%1[0] == %2) if(%3_Text(playerid,%4,%1[1])) return 0
#define RegisterDialog(%1,%2,%3,%4,%5,%6) case %6: return %5_Dialog(%1,%6,%2,%3,%4)

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native RegisterCmd(cmdtext[],command[],cmdlen,prefics,cmdid);
native RegisterText(text[],char,prefics,textid);
native RegisterDialog(playerid,response,listitem,inputtext,prefics,dialogid);
*/
