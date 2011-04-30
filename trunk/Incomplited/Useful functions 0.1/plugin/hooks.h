/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "os.h"

// class
class CHooks
{
public:
	// functions
	CHooks(unsigned long s_version);
	~CHooks();

	void SetPlaybackDir(char* string);
	void DeleteLogFile();
	int GetLogFileLength();
	void DisableBadCharsCheck();
	void DisableChangeNameLogging();
	void TargetAdminTeleportTo(unsigned long function);
		
	// vars
	HMODULE	mHooks;
};