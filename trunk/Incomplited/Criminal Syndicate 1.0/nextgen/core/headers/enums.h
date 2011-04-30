/*
*	Created:			30.09.10
*	Author:				009
*	Description:		перечисления
*/

#if defined headers_enums_included
	#endinput
#endif

#define headers_enums_included
#pragma library headers_enums

// --------------------------------------------------
// enums
// --------------------------------------------------
enum
{
	PICKUP_MODE_INTERIOR,
	PICKUP_PREMISE
};

enum
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

enum
{
	ACTION_NONE,
	ACTION_ENTER_IN_PREMISE,
	ACTION_EXIT_FROM_PREMISE,
	ACTION_MOVE_FURNITURE,
	ACTION_GET_FURNITURE_FROM_VEH,
	ACTION_PUT_FURNITURE_IN_VEH,	
};

enum
{
	DIALOG_NONE,
	DIALOG_FURNITURE_MOVING,
	DIALOG_FURNITURE_IN_VEHICLE

};

enum
{
	MODE_OBJECT_TYPE_FURNITURE,
};

enum
{
	HELPBOX_FURNITURE_FAST_MOVING,
	HELPBOX_FURNITURE_SLOW_MOVING,
	HELPBOX_FURNITURE_ANGLE_MOVING
};

enum
{
	MODE_CAMERA_FURNITURE_MOVING,
};