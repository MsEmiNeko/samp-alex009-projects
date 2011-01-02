/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

#define	PLUGIN_VERSION	"0.1"
#define	PLUGIN_CONFIG	"antisleep/config.cfg"

#define ACTION_KILL_PROCESS		0
#define ACTION_CREATE_FILE		1
#define	MAX_CREATION_FILE_LEN	24


typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;