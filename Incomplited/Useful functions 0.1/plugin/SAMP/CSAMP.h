/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 *	Description: main SA-MP server class
 */

#pragma once

#include "CPlayers.h"
#include "CVehicles.h"
#include "defines.h"

class CSAMP
{
public:
	CSAMP();
	~CSAMP();

	void*		unknown;
	CPlayers*	players;
	CVehicles*	vehicles;
};