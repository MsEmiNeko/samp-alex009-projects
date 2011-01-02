/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// core
#include "os.h"
#include "math.h"
#include <malloc.h>

extern	int	LastUpdate;

// AntiSleepUpdate();
static cell AMX_NATIVE_CALL n_AntiSleepUpdate( AMX* amx, cell* params )
{
	LastUpdate = GetTickCount();
	return 1;
}

AMX_NATIVE_INFO Natives[ ] =
{
	{ "AntiSleepUpdate",		n_AntiSleepUpdate},
	{ 0,						0 }
};

void NativesOnAMXLoad(AMX *amx)
{
	amx_Register( amx, Natives, -1 );
}