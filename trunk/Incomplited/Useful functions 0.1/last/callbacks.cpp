/*
*	Created:			15.05.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// core
#include "math.h"
#include <malloc.h>
#include <stdio.h>
// plugin
#include "os.h"
#include "main.h"
#include "hooks.h"
// samp data
#include "samp structs.h"
#include "samp defines.h"

extern AMX*			gAMX;

extern DWORD		OPSP_DisableCheckAdmin1;
extern DWORD		OPSP_DisableCheckAdmin2;
extern DWORD		OPSP_GotoCallback_start;
extern DWORD		OPSP_GotoCallback_end;

/*

	0х47EFAD - он сет поинт
	
	0x47E669 -> 0x47E684 - disable check by admin

	0x47E6EE - go to my func
*/

void Install_OPSP_Callback()
{
	_asm
	{
		push esp
		push eax
		push ebp
		push ecx
		push edx

		mov ecx, [esp + 1Ch]
		mov edx, [esp + 20h]
		mov eax, [esp + 24h]
		mov ebp, [esp + 44h]
	}
	
	float x,y,z;
	int	playerid;
	_asm
	{
		mov x, ecx
		mov y, edx
		mov z, eax
		mov playerid, ebp
	}

	cell ret;
	int find_idx;

	amx_FindPublic(gAMX,"OnPlayerSetPoint",&find_idx);
	amx_Push(gAMX,(cell)amx_ftoc(z));
	amx_Push(gAMX,(cell)amx_ftoc(y));
	amx_Push(gAMX,(cell)amx_ftoc(x));
	amx_Push(gAMX,(cell)playerid);
	amx_Exec(gAMX, &ret, find_idx);

	_asm
	{
		pop edx
		pop ecx
		pop ebp
		pop eax
		pop esp
	}
}
49D3FB
void Return_OPSP_Callback() {}

void CallbacksOnAMXLoad(AMX *amx)
{
	// OnPlayerSetPoint(playerid,Float:X,Float:Y,Float:Z);
	JmpHook(OPSP_DisableCheckAdmin1,OPSP_DisableCheckAdmin2);
	JmpHook(OPSP_GotoCallback_start,((DWORD)(Install_OPSP_Callback) + 0x8));
	JmpHook((DWORD)(Return_OPSP_Callback),OPSP_GotoCallback_end);
}