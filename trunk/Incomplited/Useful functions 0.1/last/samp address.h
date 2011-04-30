/*
*	Created:			09.04.10
*	Author:				009
*	Last Modifed:		-
*/

#ifdef WIN32

// test address
#define TEST_ADDR_1								0x479590
#define TEST_ADDR_2								0x46E71C
#define R4_DATA_1								0x00
#define R4_DATA_2								0x00
#define R51_DATA_1								0x00
#define R51_DATA_2								0x00
#define R52_DATA_1								0x00
#define R52_DATA_2								0x00
#define R6_DATA_1								0x00
#define R6_DATA_2								0x00

#define R7_DATA_1								0x00
#define R7_DATA_2								0xFF

// structs address
// R4
#define R4_C_SAMP_STRUCTURE						0x4B337C
// R51
#define R51_C_SAMP_STRUCTURE					0x4C13FC
// R52
#define R52_C_SAMP_STRUCTURE					0x4B32F4
// R6
#define R6_C_SAMP_STRUCTURE						0x4BD0FC
// R7
#define R7_C_SAMP_STRUCTURE						0x4BD0FC

// fuctions address
// R4
#define R4_CLIENT_CONNECT						0x465E60
#define R4_CLIENT_DISCONNECT					0x466100
#define R4_SPAWN_FOR_WORLD						0x460D30
#define R4_KILL_FOR_WORLD						0x461C10
#define R4_SET_SPAWN_INFO						0x460D00
#define R4_SET_SKIN								0x45A840
#define R4_SET_WEAPON_SKILL						0x462B50

#define R4_PLAYBACK_DIR							0x0
#define R4_LOG_FILE								0x0
#define R4_BAD_CHARS							0x0
#define R4_CHANGE_NAME_LOG						0x0
#define R4_OPSP_DISABLE_CHECK_ADMIN_1			0x0
#define R4_OPSP_DISABLE_CHECK_ADMIN_2			0x0
#define R4_OPSP_GOTO_CALLBACK_START				0x0
#define R4_OPSP_GOTO_CALLBACK_END				0x0
// R51
#define R51_CLIENT_CONNECT						0x4742C0
#define R51_CLIENT_DISCONNECT					0x474560
#define R51_SPAWN_FOR_WORLD						0x46EA60
#define R51_KILL_FOR_WORLD						0x46FA50
#define R51_SET_SPAWN_INFO						0x46EA30
#define R51_SET_SKIN							0x468510
#define R51_SET_WEAPON_SKILL					0x4709E0

#define R51_PLAYBACK_DIR						0x0
#define R51_LOG_FILE							0x0
#define R51_BAD_CHARS							0x0
#define R51_CHANGE_NAME_LOG						0x0
#define R51_OPSP_DISABLE_CHECK_ADMIN_1			0x0
#define R51_OPSP_DISABLE_CHECK_ADMIN_2			0x0
#define R51_OPSP_GOTO_CALLBACK_START			0x0
#define R51_OPSP_GOTO_CALLBACK_END				0x0
// R52
#define R52_CLIENT_CONNECT						0x457030
#define R52_CLIENT_DISCONNECT					0x4572D0
#define R52_SPAWN_FOR_WORLD						0x4519B0
#define R52_KILL_FOR_WORLD						0x452930
#define R52_SET_SPAWN_INFO						0x451980
#define R52_SET_SKIN							0x46E780
#define R52_SET_WEAPON_SKILL					0x453870

#define R52_PLAYBACK_DIR						0x0
#define R52_LOG_FILE							0x0
#define R52_BAD_CHARS							0x0
#define R52_CHANGE_NAME_LOG						0x0
#define R52_OPSP_DISABLE_CHECK_ADMIN_1			0x0
#define R52_OPSP_DISABLE_CHECK_ADMIN_2			0x0
#define R52_OPSP_GOTO_CALLBACK_START			0x0
#define R52_OPSP_GOTO_CALLBACK_END				0x0
// R6
#define R6_CLIENT_CONNECT						0x473AF0
#define R6_CLIENT_DISCONNECT					0x473D90
#define R6_SPAWN_FOR_WORLD						0x46E3D0
#define R6_KILL_FOR_WORLD						0x46F350
#define R6_SET_SPAWN_INFO						0x46E3A0
#define R6_SET_SKIN								0x467EB0
#define R6_SET_WEAPON_SKILL						0x470300

#define R6_PLAYBACK_DIR							0x0
#define R6_LOG_FILE								0x0
#define R6_BAD_CHARS							0x0
#define R6_CHANGE_NAME_LOG						0x0
#define R6_OPSP_DISABLE_CHECK_ADMIN_1			0x0
#define R6_OPSP_DISABLE_CHECK_ADMIN_2			0x0
#define R6_OPSP_GOTO_CALLBACK_START				0x0
#define R6_OPSP_GOTO_CALLBACK_END				0x0
// R7
#define R7_CLIENT_CONNECT						0x473B70
#define R7_CLIENT_DISCONNECT					0x473E10
#define R7_SPAWN_FOR_WORLD						0x46E400
#define R7_KILL_FOR_WORLD						0x46F380
#define R7_SET_SPAWN_INFO						0x46E3D0
#define R7_SET_SKIN								0x467EB0
#define R7_SET_WEAPON_SKILL						0x470330

#define R7_PLAYBACK_DIR							0x49D95C
#define R7_LOG_FILE								0x4BD0F4
#define R7_BAD_CHARS							0x475418
#define R7_CHANGE_NAME_LOG						0x467E49
#define R7_OPSP_DISABLE_CHECK_ADMIN_1			0x47E669
#define R7_OPSP_DISABLE_CHECK_ADMIN_2			0x47E684
#define R7_OPSP_GOTO_CALLBACK_START				0x47E6EE
#define R7_OPSP_GOTO_CALLBACK_END				0x47E776

#else

// test address
#define TEST_ADDR_1									0x80744D4
#define TEST_ADDR_2									0x808F1E4
#define R4_DATA_1									0x55
#define R4_DATA_2									0x8D
#define R51_DATA_1									0xFF
#define R51_DATA_2									0x00
#define R52_DATA_1									0x0
#define R52_DATA_2									0x0
#define R6_DATA_1									0xFF
#define R6_DATA_2									0x42
#define R7_DATA_1									0xFF
#define R7_DATA_2									0x75

// structs address
// R4
#define R4_C_SAMP_STRUCTURE							0x813AEF4
// R51
#define R51_C_SAMP_STRUCTURE						0x813EFB8
// R52
#define R52_C_SAMP_STRUCTURE						0x0
// R6
#define R6_C_SAMP_STRUCTURE							0x813EFB8
// R7
#define R7_C_SAMP_STRUCTURE							0x813EFB8

// fuctions address
// R4
#define R4_CLIENT_CONNECT							0x8086038
#define R4_CLIENT_DISCONNECT						0x808633E
#define R4_SPAWN_FOR_WORLD							0x8083D92
#define R4_KILL_FOR_WORLD							0x8083B6E
#define R4_SET_SPAWN_INFO							0x80AFC12
#define R4_SET_SKIN									0x80B017C
#define R4_SET_WEAPON_SKILL							0x8085956
// R51
#define R51_CLIENT_CONNECT							0x8089250
#define R51_CLIENT_DISCONNECT						0x8089560
#define R51_SPAWN_FOR_WORLD							0x8086460
#define R51_KILL_FOR_WORLD							0x8086230
#define R51_SET_SPAWN_INFO							0x80B4AA0
#define R51_SET_SKIN								0x80B5030
#define R51_SET_WEAPON_SKILL						0x80BF850
// R52
#define R52_CLIENT_CONNECT							0x0
#define R52_CLIENT_DISCONNECT						0x0
#define R52_SPAWN_FOR_WORLD							0x0
#define R52_KILL_FOR_WORLD							0x0
#define R52_SET_SPAWN_INFO							0x0
#define R52_SET_SKIN									0x0
#define R52_SET_WEAPON_SKILL						0x0
// R6
#define R6_CLIENT_CONNECT							0x8089060
#define R6_CLIENT_DISCONNECT						0x8089370
#define R6_SPAWN_FOR_WORLD							0x80863A0
#define R6_KILL_FOR_WORLD							0x8086180
#define R6_SET_SPAWN_INFO							0x80B4890
#define R6_SET_SKIN									0x80B4E20
#define R6_SET_WEAPON_SKILL							0x80BF6A0
// R7
#define R7_CLIENT_CONNECT							0x8089060
#define R7_CLIENT_DISCONNECT						0x8089370
#define R7_SPAWN_FOR_WORLD							0x80863A0
#define R7_KILL_FOR_WORLD							0x8086180
#define R7_SET_SPAWN_INFO							0x80B48A0
#define R7_SET_SKIN									0x80B4E30
#define R7_SET_WEAPON_SKILL							0x80BF6B0

#endif
