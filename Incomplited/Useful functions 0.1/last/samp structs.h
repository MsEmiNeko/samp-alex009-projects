/*
*	Created:			09.04.10
*	Author:				009
*	Last Modifed:		-
*/

// struct offsets
#define C_SAMP_PLAYERS_OFFSET					0x4
#define C_SAMP_VEHICLES_OFFSET					0x8
//
#define C_PLAYERS_PLAYER_OFFSET					0x7D0
#define C_PLAYERS_IS_ADMIN_OFFSET				0x5FB4
#define C_PLAYERS_IS_NPC_OFFSET					0x6F54
//
#define C_VEHICLES_VEHICLE_OFFSET				0x1F40
//
// R4
#define R4_C_PLAYER_POS_X_OFFSET				0x0
#define R4_C_PLAYER_POS_Y_OFFSET				0x4
#define R4_C_PLAYER_POS_Z_OFFSET				0x8
#define R4_C_PLAYER_HEALTH_OFFSET				0xC
#define R4_C_PLAYER_ARMOUR_OFFSET				0x10
#define R4_C_PLAYER_ANGLE_OFFSET				0x14
#define R4_C_PLAYER_SYNC_TYPE_OFFSET			0x2E
#define R4_C_PLAYER_FOOT_SYNC_OFFSET			0x32
#define R4_C_PLAYER_INCAR_SYNC_OFFSET			0x66
#define R4_C_PLAYER_PASSANGER_SYNC_OFFSET		0xA5
#define R4_C_PLAYER_AIM_SYNC_OFFSET				0xBD
#define R4_C_PLAYER_AIM_SYNC_STATE_OFFSET		0x170
#define R4_C_PLAYER_STATE_OFFSET				0x17C
#define R4_C_PLAYER_WEAPON_SKILL_OFFSET			0x18A1
#define R4_C_PLAYER_SKIN_OFFSET					0x18BC
#define R4_C_PLAYER_INTERIOR_OFFSET				0x18FE
#define R4_C_PLAYER_IS_STREAMED_OFFSET			0x1B6
#define R4_C_PLAYER_VEHICLE_ID_OFFSET			0x18F0
#define R4_C_PLAYER_VEHICLE_SEAT_OFFSET			0x18EF
// R51
#define R51_C_PLAYER_POS_X_OFFSET				0x0
#define R51_C_PLAYER_POS_Y_OFFSET				0x4
#define R51_C_PLAYER_POS_Z_OFFSET				0x8
#define R51_C_PLAYER_HEALTH_OFFSET				0xC
#define R51_C_PLAYER_ARMOUR_OFFSET				0x10
#define R51_C_PLAYER_ANGLE_OFFSET				0x14
#define R51_C_PLAYER_FOOT_SYNC_OFFSET			0xCB56
#define R51_C_PLAYER_INCAR_SYNC_OFFSET			0xCB8A
#define R51_C_PLAYER_PASSANGER_SYNC_OFFSET		0xCBC9
#define R51_C_PLAYER_AIM_SYNC_OFFSET			0xCBE1
#define R51_C_PLAYER_AIM_SYNC_STATE_OFFSET		0xCC94
#define R51_C_PLAYER_SYNC_TYPE_OFFSET			0xCCA0
#define R51_C_PLAYER_STATE_OFFSET				0xCB52
#define R51_C_PLAYER_WEAPON_SKILL_OFFSET		0xE3C5
#define R51_C_PLAYER_SKIN_OFFSET				0xE3E0
#define R51_C_PLAYER_INTERIOR_OFFSET			0xE422
#define R51_C_PLAYER_IS_STREAMED_OFFSET			0xCCDA
#define R51_C_PLAYER_VEHICLE_ID_OFFSET			0xE414
#define R51_C_PLAYER_VEHICLE_SEAT_OFFSET		0xE413
// R52
#define R52_C_PLAYER_POS_X_OFFSET				0x0
#define R52_C_PLAYER_POS_Y_OFFSET				0x4
#define R52_C_PLAYER_POS_Z_OFFSET				0x8
#define R52_C_PLAYER_HEALTH_OFFSET				0xC
#define R52_C_PLAYER_ARMOUR_OFFSET				0x10
#define R52_C_PLAYER_ANGLE_OFFSET				0x14
#define R52_C_PLAYER_SYNC_TYPE_OFFSET			0x2E
#define R52_C_PLAYER_FOOT_SYNC_OFFSET			0x32
#define R52_C_PLAYER_INCAR_SYNC_OFFSET			0x66
#define R52_C_PLAYER_PASSANGER_SYNC_OFFSET		0xA5
#define R52_C_PLAYER_AIM_SYNC_OFFSET			0xBD
#define R52_C_PLAYER_AIM_SYNC_STATE_OFFSET		0x170
#define R52_C_PLAYER_STATE_OFFSET				0x17C
#define R52_C_PLAYER_WEAPON_SKILL_OFFSET		0x18A1
#define R52_C_PLAYER_SKIN_OFFSET				0x18BC
#define R52_C_PLAYER_INTERIOR_OFFSET			0x18FE
#define R52_C_PLAYER_IS_STREAMED_OFFSET			0x1B6
#define R52_C_PLAYER_VEHICLE_ID_OFFSET			0x18F0
#define R52_C_PLAYER_VEHICLE_SEAT_OFFSET		0x18EF
// R6
#define R6_C_PLAYER_POS_X_OFFSET				0x0
#define R6_C_PLAYER_POS_Y_OFFSET				0x4
#define R6_C_PLAYER_POS_Z_OFFSET				0x8
#define R6_C_PLAYER_HEALTH_OFFSET				0xC
#define R6_C_PLAYER_ARMOUR_OFFSET				0x10
#define R6_C_PLAYER_ANGLE_OFFSET				0x14
#define R6_C_PLAYER_SYNC_TYPE_OFFSET			0x2E
#define R6_C_PLAYER_FOOT_SYNC_OFFSET			0x32
#define R6_C_PLAYER_INCAR_SYNC_OFFSET			0x66
#define R6_C_PLAYER_PASSANGER_SYNC_OFFSET		0xA5
#define R6_C_PLAYER_AIM_SYNC_OFFSET				0xBD
#define R6_C_PLAYER_AIM_SYNC_STATE_OFFSET		0x170
#define R6_C_PLAYER_STATE_OFFSET				0x17C
#define R6_C_PLAYER_WEAPON_SKILL_OFFSET			0x18A1
#define R6_C_PLAYER_SKIN_OFFSET					0x18BC
#define R6_C_PLAYER_INTERIOR_OFFSET				0x18FE
#define R6_C_PLAYER_IS_STREAMED_OFFSET			0x1B6
#define R6_C_PLAYER_VEHICLE_ID_OFFSET			0x18F0
#define R6_C_PLAYER_VEHICLE_SEAT_OFFSET			0x18EF
// R7
#define R7_C_PLAYER_POS_X_OFFSET				0x0
#define R7_C_PLAYER_POS_Y_OFFSET				0x4
#define R7_C_PLAYER_POS_Z_OFFSET				0x8
#define R7_C_PLAYER_HEALTH_OFFSET				0xC
#define R7_C_PLAYER_ARMOUR_OFFSET				0x10
#define R7_C_PLAYER_ANGLE_OFFSET				0x14
#define R7_C_PLAYER_SYNC_TYPE_OFFSET			0x2E
#define R7_C_PLAYER_FOOT_SYNC_OFFSET			0x32
#define R7_C_PLAYER_INCAR_SYNC_OFFSET			0x66
#define R7_C_PLAYER_PASSANGER_SYNC_OFFSET		0xA5
#define R7_C_PLAYER_AIM_SYNC_OFFSET				0xBD
#define R7_C_PLAYER_AIM_SYNC_STATE_OFFSET		0x170
#define R7_C_PLAYER_STATE_OFFSET				0x17C
#define R7_C_PLAYER_WEAPON_SKILL_OFFSET			0x18A1
#define R7_C_PLAYER_SKIN_OFFSET					0x18BC
#define R7_C_PLAYER_INTERIOR_OFFSET				0x18FE
#define R7_C_PLAYER_IS_STREAMED_OFFSET			0x1B6
#define R7_C_PLAYER_VEHICLE_ID_OFFSET			0x18F0
#define R7_C_PLAYER_VEHICLE_SEAT_OFFSET			0x18EF
//
//
#define R4_C_VEHICLE_POS_X_OFFSET				0x0
#define R4_C_VEHICLE_POS_Y_OFFSET				0x4
#define R4_C_VEHICLE_POS_Z_OFFSET				0x8
#define R4_C_VEHICLE_DRIVER_OFFSET				0x6A
#define R4_C_VEHICLE_HEALTH_OFFSET				0xA6
//
#define R51_C_VEHICLE_POS_X_OFFSET				0x0
#define R51_C_VEHICLE_POS_Y_OFFSET				0x4
#define R51_C_VEHICLE_POS_Z_OFFSET				0x8
#define R51_C_VEHICLE_DRIVER_OFFSET				0x6A
#define R51_C_VEHICLE_HEALTH_OFFSET				0xA6
//
#define R52_C_VEHICLE_POS_X_OFFSET				0x0
#define R52_C_VEHICLE_POS_Y_OFFSET				0x4
#define R52_C_VEHICLE_POS_Z_OFFSET				0x8
#define R52_C_VEHICLE_DRIVER_OFFSET				0x6A
#define R52_C_VEHICLE_HEALTH_OFFSET				0xA6
//
#define R6_C_VEHICLE_POS_X_OFFSET				0x0
#define R6_C_VEHICLE_POS_Y_OFFSET				0x4
#define R6_C_VEHICLE_POS_Z_OFFSET				0x8
#define R6_C_VEHICLE_DRIVER_OFFSET				0x6A
#define R6_C_VEHICLE_HEALTH_OFFSET				0xA6
//
#define R7_C_VEHICLE_POS_X_OFFSET				0x0
#define R7_C_VEHICLE_POS_Y_OFFSET				0x4
#define R7_C_VEHICLE_POS_Z_OFFSET				0x8
#define R7_C_VEHICLE_DRIVER_OFFSET				0x6A
#define R7_C_VEHICLE_HEALTH_OFFSET				0xA6
//
#define FOOT_SYNC_KEYS_UD_OFFSET				0x0
#define FOOT_SYNC_KEYS_LR_OFFSET				0x2
#define FOOT_SYNC_KEYS_OTHER_OFFSET				0x4
#define FOOT_SYNC_POS_X_OFFSET					0x6
#define FOOT_SYNC_POS_Y_OFFSET					0xA
#define FOOT_SYNC_POS_Z_OFFSET					0xE
#define FOOT_SYNC_ANGLE_OFFSET					0x12
#define FOOT_SYNC_HEALTH_OFFSET					0x16
#define FOOT_SYNC_ARMOUR_OFFSET					0x17
#define FOOT_SYNC_WEAPON_OFFSET					0x18
#define FOOT_SYNC_SPECTIAL_ACTION_OFFSET		0x19
#define FOOT_SYNC_VELOCITY_X_OFFSET				0x1A
#define FOOT_SYNC_VELOCITY_Y_OFFSET				0x1E
#define FOOT_SYNC_VELOCITY_Z_OFFSET				0x22
#define FOOT_SYNC_SURFING_X_OFFSET				0x26
#define FOOT_SYNC_SURFING_Y_OFFSET				0x2A
#define FOOT_SYNC_SURFING_Z_OFFSET				0x2E
#define FOOT_SYNC_SURFING_INFO_OFFSET			0x32
//
#define AIM_SYNC_CAMERA_MODE_OFFSET				0x0
#define AIM_SYNC_WEAPON_STATE_OFFSET			0x1
#define AIM_SYNC_CAMERA_FRONT_VECTOR_X_OFFSET	0x2
#define AIM_SYNC_CAMERA_FRONT_VECTOR_Y_OFFSET	0x6
#define AIM_SYNC_CAMERA_FRONT_VECTOR_Z_OFFSET	0xA
#define AIM_SYNC_CAMERA_UP_VECTOR_X_OFFSET		0xE
#define AIM_SYNC_CAMERA_UP_VECTOR_Y_OFFSET		0x12
#define AIM_SYNC_CAMERA_UP_VECTOR_Z_OFFSET		0x16
#define AIM_SYNC_CAMERA_POS_X_OFFSET			0x1A
#define AIM_SYNC_CAMERA_POS_Y_OFFSET			0x1E
#define AIM_SYNC_CAMERA_POS_Z_OFFSET			0x22
#define AIM_SYNC_CAMERA_Z_AIM_OFFSET			0x26
//
#define INCAR_SYNC_VEHICLEID_OFFSET				0x0
#define INCAR_SYNC_KEYS_LR_ANALOG_OFFSET		0x2
#define INCAR_SYNC_KEYS_UD_ANALOG_OFFSET		0x6
#define INCAR_SYNC_KEYS_OTHER_OFFSET			0xA
#define INCAR_SYNC_ROLL_X_OFFSET				0xC
#define INCAR_SYNC_ROLL_Y_OFFSET				0x10
#define INCAR_SYNC_ROLL_Z_OFFSET				0x14
#define INCAR_SYNC_POS_X_OFFSET					0x18
#define INCAR_SYNC_POS_Y_OFFSET					0x1C
#define INCAR_SYNC_POS_Z_OFFSET					0x20
#define INCAR_SYNC_VELOCITY_X_OFFSET			0x24
#define INCAR_SYNC_VELOCITY_Y_OFFSET			0x28
#define INCAR_SYNC_VELOCITY_Z_OFFSET			0x2C
#define INCAR_SYNC_HEALTH_OFFSET				0x30
#define INCAR_SYNC_PLAYER_HEALTH_OFFSET			0x34
#define INCAR_SYNC_PLAYER_ARMOUR_OFFSET			0x35
#define INCAR_SYNC_CURRENT_WEAPON_OFFSET		0x36
#define INCAR_SYNC_SIREN_OFFSET					0x37
#define INCAR_SYNC_UNK1_OFFSET					0x38
#define INCAR_SYNC_TRAILER_ID_OFFSET			0x39
#define INCAR_SYNC_UNIQUE_OFFSET				0x3B
//
#define PASSANGER_SYNC_VEHICLEID_OFFSET			0x0
#define PASSANGER_SYNC_SEAT_OFFSET				0x2
#define PASSANGER_SYNC_PLAYER_WEAPON_OFFSET		0x3
#define PASSANGER_SYNC_PLAYER_HEALTH_OFFSET		0x4
#define PASSANGER_SYNC_PLAYER_ARMOUR_OFFSET		0x5
#define PASSANGER_SYNC_KEYS_LR_OFFSET			0x6
#define PASSANGER_SYNC_KEYS_UD_OFFSET			0x8
#define PASSANGER_SYNC_KEYS_OTHER_OFFSET		0xA
#define PASSANGER_SYNC_POS_X_OFFSET				0xC
#define PASSANGER_SYNC_POS_Y_OFFSET				0x10
#define PASSANGER_SYNC_POS_Z_OFFSET				0x14
#define PASSANGER_SYNC_DRIVEBY_OFFSET			0x18