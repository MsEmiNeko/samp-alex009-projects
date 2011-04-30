/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 *	Description: Vehicles SA-MP server class
 */

#pragma once

#include "CVehicle.h"
#include "defines.h"

class CVehicles
{
public:
	CVehicles();
	~CVehicles();

	unsigned long	unknown[MAX_VEHICLES];
	CVehicle*		vehicle[MAX_VEHICLES];
};