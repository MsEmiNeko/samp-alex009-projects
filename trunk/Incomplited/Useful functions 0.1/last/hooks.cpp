/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// plugin
#include "os.h"
#include "hooks.h"
#include "main.h"
// samp data
#include "samp address.h"
#include "samp defines.h"
#include "samp structs.h"

// main vars
DWORD					c_samp;
DWORD					c_mass;
DWORD					CSampPointer;
// offsets
DWORD CPlayerPosXOffset;
DWORD CPlayerPosYOffset;
DWORD CPlayerPosZOffset;
DWORD CPlayerHealthOffset;
DWORD CPlayerArmourOffset;
DWORD CPlayerAngleOffset;
DWORD CPlayerStateOffset;
DWORD CPlayerFootSyncOffset;
DWORD CPlayerInCarSyncOffset;
DWORD CPlayerPassangerSyncOffset;
DWORD CPlayerAimSyncOffset;
DWORD CPlayerAimSyncStateOffset;
DWORD CPlayerSyncTypeOffset;
DWORD CPlayerWeaponSkillOffset;
DWORD CPlayerSkinOffset;
DWORD CPlayerInteriorOffset;
DWORD CPlayerIsStreamedOffset;
DWORD CPlayerVehicleIdOffset;
DWORD CPlayerVehicleSeatOffset;
DWORD CVehiclePosXOffset;
DWORD CVehiclePosYOffset;
DWORD CVehiclePosZOffset;
DWORD CVehicleDriverOffset;
DWORD CVehicleHealthOffset;
// core
DWORD PlaybackDirAddr;
DWORD LogFileAddr;
DWORD BadCharsAddr;
DWORD ChangeNameLogAddr;
// callbacks
DWORD OPSP_DisableCheckAdmin1;
DWORD OPSP_DisableCheckAdmin2;
DWORD OPSP_GotoCallback_start;
DWORD OPSP_GotoCallback_end;

extern int SampVersion;

extern AMX*			gAMX;

//
// ------------------------------------------------------
//
void HooksInstall(int version)
{
	void *temp;
	switch(version)
	{
	case SAMP_VERSION_034:
		{			
			POINTER_TO_MEMBER(CPlayerPosXOffset,(void *)(R4_C_PLAYER_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosYOffset,(void *)(R4_C_PLAYER_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosZOffset,(void *)(R4_C_PLAYER_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerHealthOffset,(void *)(R4_C_PLAYER_HEALTH_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerArmourOffset,(void *)(R4_C_PLAYER_ARMOUR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAngleOffset,(void *)(R4_C_PLAYER_ANGLE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerStateOffset,(void *)(R4_C_PLAYER_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerFootSyncOffset,(void *)(R4_C_PLAYER_FOOT_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInCarSyncOffset,(void *)(R4_C_PLAYER_INCAR_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPassangerSyncOffset,(void *)(R4_C_PLAYER_PASSANGER_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncOffset,(void *)(R4_C_PLAYER_AIM_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncStateOffset,(void *)(R4_C_PLAYER_AIM_SYNC_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSyncTypeOffset,(void *)(R4_C_PLAYER_SYNC_TYPE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerWeaponSkillOffset,(void *)(R4_C_PLAYER_WEAPON_SKILL_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSkinOffset,(void *)(R4_C_PLAYER_SKIN_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInteriorOffset,(void *)(R4_C_PLAYER_INTERIOR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerIsStreamedOffset,(void *)(R4_C_PLAYER_IS_STREAMED_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleIdOffset,(void *)(R4_C_PLAYER_VEHICLE_ID_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleSeatOffset,(void *)(R4_C_PLAYER_VEHICLE_SEAT_OFFSET),DWORD);
			
			POINTER_TO_MEMBER(CVehiclePosXOffset,(void *)(R4_C_VEHICLE_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosYOffset,(void *)(R4_C_VEHICLE_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosZOffset,(void *)(R4_C_VEHICLE_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleDriverOffset,(void *)(R4_C_VEHICLE_DRIVER_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleHealthOffset,(void *)(R4_C_VEHICLE_HEALTH_OFFSET),DWORD);

			POINTER_TO_MEMBER(PlaybackDirAddr,(void *)(R4_PLAYBACK_DIR),DWORD);
			POINTER_TO_MEMBER(LogFileAddr,(void *)(R4_LOG_FILE),DWORD);
			POINTER_TO_MEMBER(BadCharsAddr,(void *)(R4_BAD_CHARS),DWORD);
			POINTER_TO_MEMBER(ChangeNameLogAddr,(void *)(R4_CHANGE_NAME_LOG),DWORD);

			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin1,(void *)(R4_OPSP_DISABLE_CHECK_ADMIN_1),DWORD);
			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin2,(void *)(R4_OPSP_DISABLE_CHECK_ADMIN_2),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_start,(void *)(R4_OPSP_GOTO_CALLBACK_START),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_end,(void *)(R4_OPSP_GOTO_CALLBACK_END),DWORD);
			break;
		}
	case SAMP_VERSION_0351:
		{			
			POINTER_TO_MEMBER(CPlayerPosXOffset,(void *)(R51_C_PLAYER_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosYOffset,(void *)(R51_C_PLAYER_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosZOffset,(void *)(R51_C_PLAYER_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerHealthOffset,(void *)(R51_C_PLAYER_HEALTH_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerArmourOffset,(void *)(R51_C_PLAYER_ARMOUR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAngleOffset,(void *)(R51_C_PLAYER_ANGLE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerStateOffset,(void *)(R51_C_PLAYER_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerFootSyncOffset,(void *)(R51_C_PLAYER_FOOT_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInCarSyncOffset,(void *)(R51_C_PLAYER_INCAR_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPassangerSyncOffset,(void *)(R51_C_PLAYER_PASSANGER_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncOffset,(void *)(R51_C_PLAYER_AIM_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncStateOffset,(void *)(R51_C_PLAYER_AIM_SYNC_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSyncTypeOffset,(void *)(R51_C_PLAYER_SYNC_TYPE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerWeaponSkillOffset,(void *)(R51_C_PLAYER_WEAPON_SKILL_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSkinOffset,(void *)(R51_C_PLAYER_SKIN_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInteriorOffset,(void *)(R51_C_PLAYER_INTERIOR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerIsStreamedOffset,(void *)(R51_C_PLAYER_IS_STREAMED_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleIdOffset,(void *)(R51_C_PLAYER_VEHICLE_ID_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleSeatOffset,(void *)(R51_C_PLAYER_VEHICLE_SEAT_OFFSET),DWORD);
			
			POINTER_TO_MEMBER(CVehiclePosXOffset,(void *)(R51_C_VEHICLE_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosYOffset,(void *)(R51_C_VEHICLE_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosZOffset,(void *)(R51_C_VEHICLE_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleDriverOffset,(void *)(R51_C_VEHICLE_DRIVER_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleHealthOffset,(void *)(R51_C_VEHICLE_HEALTH_OFFSET),DWORD);

			POINTER_TO_MEMBER(PlaybackDirAddr,(void *)(R51_PLAYBACK_DIR),DWORD);
			POINTER_TO_MEMBER(LogFileAddr,(void *)(R51_LOG_FILE),DWORD);
			POINTER_TO_MEMBER(BadCharsAddr,(void *)(R51_BAD_CHARS),DWORD);
			POINTER_TO_MEMBER(ChangeNameLogAddr,(void *)(R51_CHANGE_NAME_LOG),DWORD);

			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin1,(void *)(R51_OPSP_DISABLE_CHECK_ADMIN_1),DWORD);
			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin2,(void *)(R51_OPSP_DISABLE_CHECK_ADMIN_2),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_start,(void *)(R51_OPSP_GOTO_CALLBACK_START),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_end,(void *)(R51_OPSP_GOTO_CALLBACK_END),DWORD);
			break;
		}
	case SAMP_VERSION_0352:
		{			
			POINTER_TO_MEMBER(CPlayerPosXOffset,(void *)(R52_C_PLAYER_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosYOffset,(void *)(R52_C_PLAYER_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosZOffset,(void *)(R52_C_PLAYER_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerHealthOffset,(void *)(R52_C_PLAYER_HEALTH_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerArmourOffset,(void *)(R52_C_PLAYER_ARMOUR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAngleOffset,(void *)(R52_C_PLAYER_ANGLE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerStateOffset,(void *)(R52_C_PLAYER_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerFootSyncOffset,(void *)(R52_C_PLAYER_FOOT_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInCarSyncOffset,(void *)(R52_C_PLAYER_INCAR_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPassangerSyncOffset,(void *)(R52_C_PLAYER_PASSANGER_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncOffset,(void *)(R52_C_PLAYER_AIM_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncStateOffset,(void *)(R52_C_PLAYER_AIM_SYNC_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSyncTypeOffset,(void *)(R52_C_PLAYER_SYNC_TYPE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerWeaponSkillOffset,(void *)(R52_C_PLAYER_WEAPON_SKILL_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSkinOffset,(void *)(R52_C_PLAYER_SKIN_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInteriorOffset,(void *)(R52_C_PLAYER_INTERIOR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerIsStreamedOffset,(void *)(R52_C_PLAYER_IS_STREAMED_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleIdOffset,(void *)(R52_C_PLAYER_VEHICLE_ID_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleSeatOffset,(void *)(R52_C_PLAYER_VEHICLE_SEAT_OFFSET),DWORD);
			
			POINTER_TO_MEMBER(CVehiclePosXOffset,(void *)(R52_C_VEHICLE_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosYOffset,(void *)(R52_C_VEHICLE_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosZOffset,(void *)(R52_C_VEHICLE_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleDriverOffset,(void *)(R52_C_VEHICLE_DRIVER_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleHealthOffset,(void *)(R52_C_VEHICLE_HEALTH_OFFSET),DWORD);

			POINTER_TO_MEMBER(PlaybackDirAddr,(void *)(R52_PLAYBACK_DIR),DWORD);
			POINTER_TO_MEMBER(LogFileAddr,(void *)(R52_LOG_FILE),DWORD);
			POINTER_TO_MEMBER(BadCharsAddr,(void *)(R52_BAD_CHARS),DWORD);
			POINTER_TO_MEMBER(ChangeNameLogAddr,(void *)(R52_CHANGE_NAME_LOG),DWORD);

			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin1,(void *)(R52_OPSP_DISABLE_CHECK_ADMIN_1),DWORD);
			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin2,(void *)(R52_OPSP_DISABLE_CHECK_ADMIN_2),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_start,(void *)(R52_OPSP_GOTO_CALLBACK_START),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_end,(void *)(R52_OPSP_GOTO_CALLBACK_END),DWORD);
			break;
		}
	case SAMP_VERSION_036:
		{
			POINTER_TO_MEMBER(CPlayerPosXOffset,(void *)(R6_C_PLAYER_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosYOffset,(void *)(R6_C_PLAYER_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosZOffset,(void *)(R6_C_PLAYER_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerHealthOffset,(void *)(R6_C_PLAYER_HEALTH_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerArmourOffset,(void *)(R6_C_PLAYER_ARMOUR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAngleOffset,(void *)(R6_C_PLAYER_ANGLE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerStateOffset,(void *)(R6_C_PLAYER_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerFootSyncOffset,(void *)(R6_C_PLAYER_FOOT_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInCarSyncOffset,(void *)(R6_C_PLAYER_INCAR_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPassangerSyncOffset,(void *)(R6_C_PLAYER_PASSANGER_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncOffset,(void *)(R6_C_PLAYER_AIM_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncStateOffset,(void *)(R6_C_PLAYER_AIM_SYNC_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSyncTypeOffset,(void *)(R6_C_PLAYER_SYNC_TYPE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerWeaponSkillOffset,(void *)(R6_C_PLAYER_WEAPON_SKILL_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSkinOffset,(void *)(R6_C_PLAYER_SKIN_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInteriorOffset,(void *)(R6_C_PLAYER_INTERIOR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerIsStreamedOffset,(void *)(R6_C_PLAYER_IS_STREAMED_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleIdOffset,(void *)(R6_C_PLAYER_VEHICLE_ID_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleSeatOffset,(void *)(R6_C_PLAYER_VEHICLE_SEAT_OFFSET),DWORD);
			
			POINTER_TO_MEMBER(CVehiclePosXOffset,(void *)(R6_C_VEHICLE_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosYOffset,(void *)(R6_C_VEHICLE_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosZOffset,(void *)(R6_C_VEHICLE_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleDriverOffset,(void *)(R6_C_VEHICLE_DRIVER_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleHealthOffset,(void *)(R6_C_VEHICLE_HEALTH_OFFSET),DWORD);

			POINTER_TO_MEMBER(PlaybackDirAddr,(void *)(R6_PLAYBACK_DIR),DWORD);
			POINTER_TO_MEMBER(LogFileAddr,(void *)(R6_LOG_FILE),DWORD);
			POINTER_TO_MEMBER(BadCharsAddr,(void *)(R6_BAD_CHARS),DWORD);
			POINTER_TO_MEMBER(ChangeNameLogAddr,(void *)(R6_CHANGE_NAME_LOG),DWORD);

			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin1,(void *)(R6_OPSP_DISABLE_CHECK_ADMIN_1),DWORD);
			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin2,(void *)(R6_OPSP_DISABLE_CHECK_ADMIN_2),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_start,(void *)(R6_OPSP_GOTO_CALLBACK_START),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_end,(void *)(R6_OPSP_GOTO_CALLBACK_END),DWORD);
			break;
		}
	case SAMP_VERSION_037:
		{
			POINTER_TO_MEMBER(CPlayerPosXOffset,(void *)(R7_C_PLAYER_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosYOffset,(void *)(R7_C_PLAYER_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPosZOffset,(void *)(R7_C_PLAYER_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerHealthOffset,(void *)(R7_C_PLAYER_HEALTH_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerArmourOffset,(void *)(R7_C_PLAYER_ARMOUR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAngleOffset,(void *)(R7_C_PLAYER_ANGLE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerStateOffset,(void *)(R7_C_PLAYER_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerFootSyncOffset,(void *)(R7_C_PLAYER_FOOT_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInCarSyncOffset,(void *)(R7_C_PLAYER_INCAR_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerPassangerSyncOffset,(void *)(R7_C_PLAYER_PASSANGER_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncOffset,(void *)(R7_C_PLAYER_AIM_SYNC_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerAimSyncStateOffset,(void *)(R7_C_PLAYER_AIM_SYNC_STATE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSyncTypeOffset,(void *)(R7_C_PLAYER_SYNC_TYPE_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerWeaponSkillOffset,(void *)(R7_C_PLAYER_WEAPON_SKILL_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerSkinOffset,(void *)(R7_C_PLAYER_SKIN_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerInteriorOffset,(void *)(R7_C_PLAYER_INTERIOR_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerIsStreamedOffset,(void *)(R7_C_PLAYER_IS_STREAMED_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleIdOffset,(void *)(R7_C_PLAYER_VEHICLE_ID_OFFSET),DWORD);
			POINTER_TO_MEMBER(CPlayerVehicleSeatOffset,(void *)(R7_C_PLAYER_VEHICLE_SEAT_OFFSET),DWORD);
			
			POINTER_TO_MEMBER(CVehiclePosXOffset,(void *)(R7_C_VEHICLE_POS_X_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosYOffset,(void *)(R7_C_VEHICLE_POS_Y_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehiclePosZOffset,(void *)(R7_C_VEHICLE_POS_Z_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleDriverOffset,(void *)(R7_C_VEHICLE_DRIVER_OFFSET),DWORD);
			POINTER_TO_MEMBER(CVehicleHealthOffset,(void *)(R7_C_VEHICLE_HEALTH_OFFSET),DWORD);

			POINTER_TO_MEMBER(PlaybackDirAddr,(void *)(R7_PLAYBACK_DIR),DWORD);
			POINTER_TO_MEMBER(LogFileAddr,(void *)(R7_LOG_FILE),DWORD);
			POINTER_TO_MEMBER(BadCharsAddr,(void *)(R7_BAD_CHARS),DWORD);
			POINTER_TO_MEMBER(ChangeNameLogAddr,(void *)(R7_CHANGE_NAME_LOG),DWORD);

			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin1,(void *)(R7_OPSP_DISABLE_CHECK_ADMIN_1),DWORD);
			POINTER_TO_MEMBER(OPSP_DisableCheckAdmin2,(void *)(R7_OPSP_DISABLE_CHECK_ADMIN_2),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_start,(void *)(R7_OPSP_GOTO_CALLBACK_START),DWORD);
			POINTER_TO_MEMBER(OPSP_GotoCallback_end,(void *)(R7_OPSP_GOTO_CALLBACK_END),DWORD);
			break;
		}
	}
}

void JmpHook(DWORD from, DWORD to) 
{
    DWORD oldp;
    VirtualProtect((LPVOID)from, 5, PAGE_EXECUTE_READWRITE, &oldp);
    BYTE *patch = (BYTE *)from;
    *patch = 0xE9;    // JMP
    *(DWORD *)(patch + 1) = (to - (from + 5));    
}
