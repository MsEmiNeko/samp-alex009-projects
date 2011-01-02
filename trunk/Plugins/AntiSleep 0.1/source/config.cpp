/*
*	Created:			06.03.10
*	Author:				009
*	Last Modifed:		-
*/

#include "main.h"
#include <stdio.h>

extern	int		max_sleep_time;
extern	int		action;
extern	char	creation_file[MAX_CREATION_FILE_LEN];

char	buffer[128];

void ReadConfig()
{
	FILE* f = fopen(PLUGIN_CONFIG,"r");
	if(f)
	{
		while(!feof(f))
		{
			fgets(buffer,sizeof(buffer),f);
			if(buffer[0] == '/') continue;

			sscanf(buffer,"MaxSleepTime=%d",&max_sleep_time);
			sscanf(buffer,"Action=%d",&action);
			sscanf(buffer,"CreationFile=%s",&creation_file);
		}
	}
	fclose(f);
}