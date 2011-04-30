/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include <stdio.h>
#include "hooks.h"

// types
typedef void (* typeInitializeHooks)(unsigned long version);
typedef void (* typeSetPlaybackDir)(char * string);
typedef void (* typeDeleteLogFile)();
typedef int (* typeGetLogFileLength)();
typedef void (* typeDisableBadCharsCheck)();
typedef void (* typeDisableChangeNameLogging)();
typedef void (* typeTargetAdminTeleportTo)(unsigned long function);

// vars
typeInitializeHooks				fInitializeHooks;
typeSetPlaybackDir				fSetPlaybackDir;
typeDeleteLogFile				fDeleteLogFile;
typeGetLogFileLength			fGetLogFileLength;
typeDisableBadCharsCheck		fDisableBadCharsCheck;
typeDisableChangeNameLogging	fDisableChangeNameLogging;
typeTargetAdminTeleportTo		fTargetAdminTeleportTo;

// class
CHooks::CHooks(unsigned long s_version)
{
	if((mHooks = GetModuleHandle(L"hooks.dll")) == NULL) mHooks = LoadLibrary(L"./plugins/hooks.dll");
	if(mHooks)
	{
		fInitializeHooks			=	reinterpret_cast<typeInitializeHooks>(GetProcAddress(mHooks,			"EXPORT_InitializeHooks"));
		fSetPlaybackDir				=	reinterpret_cast<typeSetPlaybackDir>(GetProcAddress(mHooks,				"EXPORT_SetPlaybackDir"));
		fDeleteLogFile				=	reinterpret_cast<typeDeleteLogFile>(GetProcAddress(mHooks,				"EXPORT_DeleteLogFile"));
		fGetLogFileLength			=	reinterpret_cast<typeGetLogFileLength>(GetProcAddress(mHooks,			"EXPORT_GetLogFileLength"));
		fDisableBadCharsCheck		=	reinterpret_cast<typeDisableBadCharsCheck>(GetProcAddress(mHooks,		"EXPORT_DisableBadCharsCheck"));
		fDisableChangeNameLogging	=	reinterpret_cast<typeDisableChangeNameLogging>(GetProcAddress(mHooks,	"EXPORT_DisableChangeNameLogging"));
		fTargetAdminTeleportTo		=	reinterpret_cast<typeTargetAdminTeleportTo>(GetProcAddress(mHooks,		"EXPORT_TargetAdminTeleportTo"));

		if(fInitializeHooks) fInitializeHooks(s_version);
	}
}

CHooks::~CHooks()
{

}

void CHooks::SetPlaybackDir(char* string)
{
	if(fSetPlaybackDir) fSetPlaybackDir(string);
}

void CHooks::DeleteLogFile()
{
	if(fDeleteLogFile) fDeleteLogFile();
}

int CHooks::GetLogFileLength()
{
	if(fGetLogFileLength) return fGetLogFileLength();
	return 0;
}

void CHooks::DisableBadCharsCheck()
{
	if(fDisableBadCharsCheck) fDisableBadCharsCheck();
}

void CHooks::DisableChangeNameLogging()
{
	if(fDisableChangeNameLogging) fDisableChangeNameLogging();
}

void CHooks::TargetAdminTeleportTo(unsigned long function)
{
	if(fTargetAdminTeleportTo) fTargetAdminTeleportTo(function);
}