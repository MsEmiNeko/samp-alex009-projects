/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 *	Description: Players SA-MP server class
 */

#pragma once

#include "CPlayer.h"
#include "defines.h"

class CPlayers
{
public:
	CPlayers();
	~CPlayers();

	unsigned long	unknown[MAX_PLAYERS];
	CPlayer*		player[MAX_PLAYERS];
};