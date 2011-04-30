/*
*	Created:			14.10.10
*	Author:				009
*	Description:		определители
*/

#if defined headers_defines_included
	#endinput
#endif

#define headers_defines_included
#pragma library headers_defines

// --------------------------------------------------
// defines
// --------------------------------------------------
#define FORCE_SYNC_ALL				1

// limits
#define MAX_MODE_OBJECTS			1000
#define MAX_MODE_3DTEXTS 			1500
#define MAX_MODE_ICONS				1500
#define MAX_MODE_PICKUPS 			1500
#define MAX_ACTION_SELECT			5

// distances
#define MODE_OBJECTS_DISTANCE 		100.0
#define MODE_3DTEXTS_DISTANCE		100.0
#define MODE_ICONS_DISTANCE			100.0
#define MODE_PICKUPS_DISTANCE 		100.0

// invalids
#define INVALID_MODE_INTERIOR_ID	255
#define INVALID_MODE_OBJECT_ID		-1
#define INVALID_MODE_3DTEXT_ID		-1
#define INVALID_MODE_ICON_ID		-1
#define INVALID_MODE_CAMERA_ID		-1
#define INVALID_MODE_DIALOG_ID		255
#define INVALID_MODE_PICKUP_ID 		-1
#define INVALID_MODE_VEHICLE_ID		-1

#define INVALID_VIRTUAL_WORLD_ID	-1
#define INVALID_3DTEXT_PLAYER_ID	PlayerText3D:-1
#define INVALID_3DTEXT_ATTACH_ID	-1
#define INVALID_ACTION_SELECT_ROW	255
#define INVALID_PAINT_JOB			255

#if !defined MAX_ICONS 
	#define MAX_ICONS 200
#endif
#if defined INVALID_ICON_ID
	#undef	INVALID_ICON_ID
#endif
#define INVALID_ICON_ID MAX_ICONS+1
#if !defined INVALID_PICKUP_ID
	#define INVALID_PICKUP_ID 	-1
#endif
#if defined INVALID_OBJECT_ID
	#undef	INVALID_OBJECT_ID
#endif
#define INVALID_OBJECT_ID		255
