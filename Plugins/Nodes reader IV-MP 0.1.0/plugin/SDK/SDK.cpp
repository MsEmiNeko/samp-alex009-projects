//============== Copyright © 2010 IV:MP Team. All rights reserved. ==============
// File: SDK.cpp
//===============================================================================

#include "SDK.h"

FuncContainer_t FuncContainer;

EXPORT void SetupFunctions(FuncContainer_t * pContainer)
{
	FuncContainer = *pContainer;
}

void RegisterFunction(HSQUIRRELVM pVM, const char * szName, SQFUNCTION pfnFunction)
{
	sq_pushroottable(pVM);
	sq_pushstring(pVM, szName, -1);
	sq_newclosure(pVM, pfnFunction, 0);
	sq_createslot(pVM, -3);
	sq_pop(pVM, 1);
}

// by Kevz
void RegisterClass (HSQUIRRELVM pVM, char *classname)
{
	sq_pushroottable(pVM);
	sq_pushstring(pVM, classname, -1);
	sq_newclass(pVM, false);
	sq_createslot(pVM, -3);
	sq_pop(pVM, 1);
}

void RegisterClassMethod (HSQUIRRELVM pVM, char* classname, char* funcname, SQFUNCTION pfnFunction)
{
	sq_pushroottable(pVM);
	sq_pushstring(pVM, classname, -1);
	if(SQ_SUCCEEDED(sq_get(pVM, -2))) 
	{
		sq_pushstring(pVM, funcname, -1);
		sq_newclosure(pVM, pfnFunction, 0);
		sq_newslot(pVM, -3, true);
	} 
	sq_pop(pVM, 1);
}