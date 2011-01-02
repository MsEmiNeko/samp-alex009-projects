/*
*	Created:			01.10.10
*	Author:				009
*	Description:		Хранение данных
*/

#if defined core_holding_included
	#endinput
#endif

#define core_holding_included
#pragma library core_holding

// --------------------------------------------------
// includes
// --------------------------------------------------
#if defined USING_MYSQL
	#include <a_mysql>
#endif

// --------------------------------------------------
// defines
// --------------------------------------------------
#define HOLDING_CONFIG_FILE "holding.cfg"
#define HOLDING_TEMP_FILE	"temp"
#define MAX_CONF_LEN     	50
// file
#define MAX_FILE_NAME       50
#define MAX_KEYS            25
#define MAX_KEY_LEN         50
#define MAX_DATA_LEN        128
// db
#define MAX_QUERY_LEN       512
#define MAX_RESULT_LEN      1024

#define ReadFileDataStr(%1,%2,%3,%4) if(!strcmp(%1,%2,true,%3)) strmid(%4,%1,(%3 + 1),strlen(%1))
#define ReadFileDataInt(%1,%2,%3,%4) if(!strcmp(%1,%2,true,%3)) %4 = strval(%1[%3 + 1])
#define ReadFileDataFloat(%1,%2,%3,%4) if(!strcmp(%1,%2,true,%3)) %4 = floatstr(%1[%3 + 1])
#define ReadArgByType(%1,%2,%3); switch(%2) \
	{\
	    case HOLDING_NAME_INT: format(%1,sizeof(%1),"%d",getarg(%3));\
	    case HOLDING_NAME_FLOAT: format(%1,sizeof(%1),"%f",getarg(%3));\
	    case HOLDING_NAME_STRING:\
		{\
		    new idx = 0;\
		    while((%1[idx] = getarg(%3,idx)) != 0) idx++;\
		}\
	}

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif
#if !defined StripNL
stock StripNL(str[]) // by Y_Less
{
	new l = strlen(str);
	while(l > 0 && (str[l] == '\r' || str[l] == '\n'))
	{
	    str[l] = 0;
		l--;
	}
}
#endif

// --------------------------------------------------
// enums
// --------------------------------------------------
enum
{
	HOLDING_MODE_NONE,
	HOLDING_MODE_WRITE,
	HOLDING_MODE_READ
};
enum
{
    HOLDING_ORDER_MINIMAL,
    HOLDING_ORDER_MAXIMAL
};
enum
{
    HOLDING_NAME_INT,
    HOLDING_NAME_FLOAT,
    HOLDING_NAME_STRING
};

// --------------------------------------------------
// statics
// --------------------------------------------------
#if defined USING_FILES
static
	HoldingDir[MAX_CONF_LEN],
	HoldingKeys[MAX_KEYS][MAX_KEY_LEN],
	HoldingData[MAX_KEYS][MAX_DATA_LEN],
	HoldingFile[MAX_FILE_NAME],
	HoldingKeysCount,
	File:CurrentFile;
#elseif defined USING_SQLITE
static
	DB:DB_id,
	DBResult:DB_result,
	DB_Base[MAX_CONF_LEN],
	query[MAX_QUERY_LEN],
	result[MAX_RESULT_LEN],
	vars[128];
#elseif defined USING_MYSQL
static
	DB_Host[MAX_CONF_LEN],
	DB_User[MAX_CONF_LEN],
	DB_Pass[MAX_CONF_LEN],
	DB_Base[MAX_CONF_LEN],
	query[MAX_QUERY_LEN],
	result[MAX_RESULT_LEN],
	vars[128];
#endif
static
	temp[512],
	CurrentMode;

// --------------------------------------------------
// forwards
// --------------------------------------------------

// --------------------------------------------------
// publics
// --------------------------------------------------

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native AddHolding(dir[],field[],name_type,{Float,_}:...);
native OpenHolding(dir[],field[],mode,name_type,{Float,_}:...);
native CloseHolding();
native IsHoldingExist(dir[],field[],name_type,{Float,_}:...);
native DeleteHolding(dir[],field[],name_type,{Float,_}:...);
native GetHoldingDataInt(field[]);
native Float:GetHoldingDataFloat(field[]);
native GetHoldingDataString(field[]);
native GetHoldingDataStringEx(field[],dest[],destlen=sizeof dest);
native SetHoldingDataInt(field[],data);
native SetHoldingDataFloat(field[],Float:data);
native SetHoldingDataString(field[],data[]);
native GetHoldingDataByOrder(dir[],field[],order);
native OpenHoldingTable(dir[]);
native NextHoldingTableRow();
native CloseHoldingTable();
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock AddHolding(dir[],field[],name_type,{Float,_}:...)
{
    Debug(DEBUG_START,"AddHolding(%s,%s,%d)",dir,field,name_type);
    // name generate
    new name[128];
    ReadArgByType(name,name_type,3);
	// access
#if defined USING_FILES
	// files...dir - directory, name - name of file
	format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
	CurrentFile = fopen(HoldingFile,io_read);
	new File:TempFile = fopen(HOLDING_TEMP_FILE,io_write);
	if(CurrentFile && TempFile)
	{
	    new key;
	    // read keys
	    fread(CurrentFile,temp);
	    // write keys in temp
		fwrite(TempFile,temp);
	    Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    // parsing
	    ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    HoldingKeysCount = key;
	    // get needed key id
		for(key = 0;key < HoldingKeysCount;key++)
		{
		    if(strcmp(HoldingKeys[key],field)) continue;
		    break;
		}
		if(key == HoldingKeysCount)
		{
			Debug(DEBUG_ACTION,"field '%s' not found",field);
		}
		// read file
	    Debug(DEBUG_ACTION,"read file");
		while(fread(CurrentFile,temp)) fwrite(TempFile,temp);
		// set data
	    Debug(DEBUG_ACTION,"set new data");
		format(HoldingData[key],MAX_DATA_LEN,name);
		// gen row
		temp[0] = 0;
		for(new i = 0;i < HoldingKeysCount;i++)
		{
			strcat(temp,HoldingData[i]);
			strcat(temp,"|");
		}
		// write
	    Debug(DEBUG_ACTION,"new row '%s'",temp);
		fwrite(TempFile,temp);
		fwrite(TempFile,"\r\n");
		// reopen
		fclose(CurrentFile);
		fclose(TempFile);
		CurrentFile = fopen(HoldingFile,io_write);
		TempFile = fopen(HOLDING_TEMP_FILE,io_read);
		// write data
		while(fread(TempFile,temp)) fwrite(CurrentFile,temp);
		// close
		fclose(CurrentFile);
		fclose(TempFile);
		// delete temp
		fremove(HOLDING_TEMP_FILE);
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"INSERT INTO `%s` (`%s`) VALUES ('%s')",dir,field,name);
	else format(query,sizeof(query),"INSERT INTO `%s` (`%s`) VALUES (%s)",dir,field,name);
	db_free_result(db_query(DB_id,query));
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"INSERT INTO `%s` (`%s`) VALUES ('%s')",dir,field,name);
	else format(query,sizeof(query),"INSERT INTO `%s` (`%s`) VALUES (%s)",dir,field,name);
	samp_mysql_query(query);
#endif
	Debug(DEBUG_END,"AddHolding(reason: complete)");
	return 1;
}

stock OpenHolding(dir[],field[],mode,name_type,{Float,_}:...)
{
	Debug(DEBUG_START,"OpenHolding(%s,%s,%d,%d)",dir,field,mode,name_type);
	new res = 0;
    new name[128];
    ReadArgByType(name,name_type,4);
	switch(mode)
	{
	    case HOLDING_MODE_READ:
		{
#if defined USING_FILES
			// files...dir - directory, name - name of file
			format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
			CurrentFile = fopen(HoldingFile,io_read);
			if(CurrentFile)
			{
			    new pos[2],key;
			    // read keys
			    fread(CurrentFile,temp);
	   			Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    		// parsing
	    		ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    		HoldingKeysCount = key;
			    // get needed key id
				for(key = 0;key < HoldingKeysCount;key++)
				{
				    if(strcmp(HoldingKeys[key],field)) continue;
				    break;
				}
				if(key == HoldingKeysCount)
				{
					Debug(DEBUG_ACTION,"field '%s' not found",field);
				}
				else
				{
	    			Debug(DEBUG_ACTION,"search row");
					// find string by key
					while(fread(CurrentFile,temp))
					{
			        	if(GetField(temp,key,pos[0],pos[1]))
			        	{
			        	    new fielddata[MAX_DATA_LEN],
								f;
			        	    strmid(fielddata,temp,pos[0],pos[1],MAX_DATA_LEN);
			        	    if(!strcmp(fielddata,name))
			        	    {
			        	        Debug(DEBUG_ACTION,"row founded");
			        	        ParseStringTo(temp,HoldingData,f,MAX_KEYS,MAX_DATA_LEN);
								res = 1;
								break;
			        	    }
			        	}
			        	else
						{
							Debug(DEBUG_ACTION,"invalid data '%s' - %d",temp,key);
						}
			        }
			    }
				fclose(CurrentFile);
			}
#elseif defined USING_SQLITE
			// db...dir - name of table, name - row
			if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s`='%s'",dir,field,name);
			else format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s`=%s",dir,field,name);
   			DB_result = db_query(DB_id,query);
			if(db_num_rows(DB_result)) res = 1;
			else db_free_result(DB_result);
#elseif defined USING_MYSQL
			// db...dir - name of table, name - row
			if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s`='%s'",dir,field,name);
			else format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s`=%s",dir,field,name);
			if(samp_mysql_query(query))
			{
				samp_mysql_store_result();
				res = 1;
			}
#endif
		}
		case HOLDING_MODE_WRITE:
		{
#if defined USING_FILES
            // files...dir - directory, name - name of file
			format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
			CurrentFile = fopen(HoldingFile,io_read);
			new File:TempFile = fopen(HOLDING_TEMP_FILE,io_write);
			if(CurrentFile && TempFile)
			{
			    new pos[2],key;
			    // read keys
			    fread(CurrentFile,temp);
			    // write keys in temp
			    fwrite(TempFile,temp);
	   			Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    		// parsing
	    		ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    		HoldingKeysCount = key;
			    // get needed key id
				for(key = 0;key < HoldingKeysCount;key++)
				{
				    if(strcmp(HoldingKeys[key],field)) continue;
				    break;
				}
				if(key == HoldingKeysCount)
				{
					Debug(DEBUG_ACTION,"field '%s' not found",field);
				}
				else
				{
	    			Debug(DEBUG_ACTION,"search row");
					// find string by key
					while(fread(CurrentFile,temp))
					{
			        	if(GetField(temp,key,pos[0],pos[1]))
			        	{
			        	    new fielddata[MAX_DATA_LEN],
								f;
			        	    strmid(fielddata,temp,pos[0],pos[1],MAX_DATA_LEN);
			        	    if(!strcmp(fielddata,name) && !res)
			        	    {
			        	        Debug(DEBUG_ACTION,"row founded");
			        	        ParseStringTo(temp,HoldingData,f,MAX_KEYS,MAX_DATA_LEN);
								res = 1;
			        	    }
			        	    else fwrite(TempFile,temp);
			        	}
			        	else
						{
							Debug(DEBUG_ACTION,"invalid data '%s' - %d",temp,key);
						}
			        }
			    }
				fclose(CurrentFile);
				fclose(TempFile);
			}
#elseif defined USING_SQLITE
			// db...dir - name of table, name - row
			format(query,sizeof(query),"UPDATE `%s` SET",dir);
			if(name_type == HOLDING_NAME_STRING) format(temp,sizeof(temp),"WHERE `%s` = '%s'",field,name);
			else format(temp,sizeof(temp),"WHERE `%s` = %s",field,name);
			vars[0] = 0;
			res = 1;
#elseif defined USING_MYSQL
			// db...dir - name of table, name - row
			format(query,sizeof(query),"UPDATE `%s` SET",dir);
			if(name_type == HOLDING_NAME_STRING) format(temp,sizeof(temp),"WHERE `%s` = '%s'",field,name);
			else format(temp,sizeof(temp),"WHERE `%s` = %s",field,name);
			vars[0] = 0;
			res = 1;
#endif
		}
	}
	if(res) CurrentMode = mode;
	Debug(DEBUG_END,"OpenHolding(reason: complete)");
	return res;
}

stock CloseHolding()
{
	Debug(DEBUG_START,"CloseHolding()");
	switch(CurrentMode)
	{
	    case HOLDING_MODE_READ:
	    {
#if defined USING_FILES
            for(new i = 0;i < MAX_KEYS;i++)
			{
			    HoldingKeys[i][0] = 0;
			    HoldingData[i][0] = 0;
			}
#elseif defined USING_SQLITE
			db_free_result(DB_result);
#elseif defined USING_MYSQL
	        samp_mysql_free_result();
#endif
	    }
	    case HOLDING_MODE_WRITE:
	    {
#if defined USING_FILES
			CurrentFile = fopen(HoldingFile,io_write);
			new File:TempFile = fopen(HOLDING_TEMP_FILE,io_read);
			while(fread(TempFile,temp)) fwrite(CurrentFile,temp);
			// gen
			temp[0] = 0;
			for(new i = 0;i < HoldingKeysCount;i++)
			{
				strcat(temp,HoldingData[i]);
				strcat(temp,"|");
			}
            // write
			fwrite(CurrentFile,temp);
			fwrite(CurrentFile,"\r\n");
			// close
			fclose(CurrentFile);
			fclose(TempFile);
			// delete temp
			fremove(HOLDING_TEMP_FILE);
#elseif defined USING_SQLITE
			format(query,sizeof(query),"%s %s %s",query,vars[1],temp);
			db_free_result(db_query(DB_id,query));
#elseif defined USING_MYSQL
			format(query,sizeof(query),"%s %s %s",query,vars[1],temp);
			samp_mysql_query(query);
#endif
	    }
	}
	Debug(DEBUG_END,"CloseHolding(reason: complete)");
}

stock IsHoldingExist(dir[],field[],name_type,{Float,_}:...)
{
	Debug(DEBUG_START,"IsHoldingExist(%s,%s,%d)",dir,field,name_type);
	new res = 0;
    new name[128];
    ReadArgByType(name,name_type,3);
#if defined USING_FILES
	// files...dir - directory, name - name of file
	format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
	CurrentFile = fopen(HoldingFile,io_read);
	if(CurrentFile)
	{
	    new pos[2],key;
	    // read keys
	    fread(CurrentFile,temp);
	    Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    // parsing
	    ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    HoldingKeysCount = key;
	    // get needed key id
		for(key = 0;key < HoldingKeysCount;key++)
		{
		    if(strcmp(HoldingKeys[key],field)) continue;
		    break;
		}
		if(key == HoldingKeysCount)
		{
			Debug(DEBUG_ACTION,"field '%s' not found",field);
		}
		else
		{
	    	Debug(DEBUG_ACTION,"search row");
			// read file and search row
			while(fread(CurrentFile,temp))
			{
		       	if(GetField(temp,key,pos[0],pos[1]))
		       	{
		       	    new fielddata[MAX_DATA_LEN];
		       	    strmid(fielddata,temp,pos[0],pos[1],MAX_DATA_LEN);
		       	    if(!strlen(fielddata)) continue;
		       	    if(!strcmp(fielddata,name))
		       	    {
		       	        Debug(DEBUG_ACTION,"row founded");
						res = 1;
						break;
		       	    }
		       	}
		       	else
				{
					Debug(DEBUG_ACTION,"invalid data '%s' - %d",temp,key);
				}
			}
		}
		fclose(CurrentFile);
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s` = '%s'",dir,field,name);
	else format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s` = %s",dir,field,name);
	DB_result = db_query(DB_id,query);
    if(db_num_rows(DB_result)) res = 1;
    db_free_result(DB_result);
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s` = '%s'",dir,field,name);
	else format(query,sizeof(query),"SELECT * FROM `%s` WHERE `%s` = %s",dir,field,name);
    if(samp_mysql_query(query))
	{
	    samp_mysql_store_result();
	    if(samp_mysql_num_rows()) res = 1;
	    samp_mysql_free_result();
	}
#endif
	Debug(DEBUG_END,"IsHoldingExist(reason: complete)");
	return res;
}

stock DeleteHolding(dir[],field[],name_type,{Float,_}:...)
{
	Debug(DEBUG_START,"DeleteHolding(%s,%s,%d)",dir,field,name_type);
    new name[128];
    ReadArgByType(name,name_type,3);
#if defined USING_FILES
    // files...dir - directory, name - name of file
	format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
	CurrentFile = fopen(HoldingFile,io_read);
	new File:TempFile = fopen(HOLDING_TEMP_FILE,io_write);
	if(CurrentFile && TempFile)
	{
	    new pos[2],key;
	    // read keys
	    fread(CurrentFile,temp);
	    // write keys in temp
		fwrite(TempFile,temp);
	    Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    // parsing
	    ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    HoldingKeysCount = key;
	    // get needed key id
		for(key = 0;key < HoldingKeysCount;key++)
		{
		    if(strcmp(HoldingKeys[key],field)) continue;
		    break;
		}
        if(key == HoldingKeysCount)
		{
			Debug(DEBUG_ACTION,"field '%s' not found",field);
		}
		else
		{
	    	Debug(DEBUG_ACTION,"search row");
			// find string by key
			while(fread(CurrentFile,temp))
			{
		       	if(GetField(temp,key,pos[0],pos[1]))
		       	{
		       	    new fielddata[MAX_DATA_LEN];
		       	    strmid(fielddata,temp,pos[0],pos[1],MAX_DATA_LEN);
		       	    if(!strcmp(fielddata,name))
		       	    {
		       	        Debug(DEBUG_ACTION,"row founded");
	        	    }
	        	    else fwrite(TempFile,temp);
	        	}
	        	else
				{
					Debug(DEBUG_ACTION,"invalid data '%s' - %d",temp,key);
				}
	        }
	    }
		// reopen
		fclose(CurrentFile);
		fclose(TempFile);
		CurrentFile = fopen(HoldingFile,io_write);
		TempFile = fopen(HOLDING_TEMP_FILE,io_read);
		// write data
		while(fread(TempFile,temp)) fwrite(CurrentFile,temp);
		// close
		fclose(CurrentFile);
		fclose(TempFile);
		// delete temp
		fremove(HOLDING_TEMP_FILE);
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"DELETE FROM `%s` WHERE `%s` = '%s'",dir,field,name);
	else format(query,sizeof(query),"DELETE FROM `%s` WHERE `%s` = %s",dir,field,name);
	db_free_result(db_query(DB_id,query));
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	if(name_type == HOLDING_NAME_STRING) format(query,sizeof(query),"DELETE FROM `%s` WHERE `%s` = '%s'",dir,field,name);
	else format(query,sizeof(query),"DELETE FROM `%s` WHERE `%s` = %s",dir,field,name);
	samp_mysql_query(query);
	samp_mysql_free_result();
#endif
	Debug(DEBUG_END,"DeleteHolding(reason: complete)");
	return 1;
}

stock GetHoldingDataInt(field[])
{
	Debug(DEBUG_START,"GetHoldingDataInt(%s)",field);
	new res;
#if defined USING_FILES
	for(new i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

 	    res = strval(HoldingData[i]);
	    break;
	}
#elseif defined USING_SQLITE
	db_get_field_assoc(DB_result,field,result,sizeof(result));
	if(result[0] == 0) res = 0;
	else res = strval(result);
#elseif defined USING_MYSQL
    samp_mysql_get_field(field,result);
	if(result[0] == 0) res = 0;
	else res = strval(result);
#endif
	Debug(DEBUG_END,"GetHoldingDataInt(reason: complete)");
	return res;
}

stock Float:GetHoldingDataFloat(field[])
{
	Debug(DEBUG_START,"GetHoldingDataFloat(%s)",field);
	new Float:res;
#if defined USING_FILES
	for(new i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

	    res = floatstr(HoldingData[i]);
	    break;
	}
#elseif defined USING_SQLITE
	db_get_field_assoc(DB_result,field,result,sizeof(result));
	if(result[0] == 0) res = 0.0;
	else res = floatstr(result);
#elseif defined USING_MYSQL
    samp_mysql_get_field(field,result);
	if(result[0] == 0) res = 0.0;
	else res = floatstr(result);
#endif
	Debug(DEBUG_END,"GetHoldingDataFloat(reason: complete)");
	return res;
}

stock GetHoldingDataString(field[])
{
	Debug(DEBUG_START,"GetHoldingDataString(%s)",field);
	new res[256];
#if defined USING_FILES
	for(new i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

 	    strmid(res,HoldingData[i],0,strlen(HoldingData[i]));
	    break;
	}
#elseif defined USING_SQLITE
	db_get_field_assoc(DB_result,field,res,sizeof(res));
#elseif defined USING_MYSQL
    samp_mysql_get_field(field,res);
#endif
	Debug(DEBUG_END,"GetHoldingDataString(reason: complete)");
	return res;
}

stock GetHoldingDataStringEx(field[],dest[],destlen=sizeof dest)
{
	Debug(DEBUG_START,"GetHoldingDataStringEx(%s)",field);
#if defined USING_FILES
	for(new i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

 	    strmid(dest,HoldingData[i],0,strlen(HoldingData[i]),destlen);
	    break;
	}
#elseif defined USING_SQLITE
	db_get_field_assoc(DB_result,field,dest,destlen);
#elseif defined USING_MYSQL
#pragma unused destlen
    samp_mysql_get_field(field,dest);
#endif
	Debug(DEBUG_END,"GetHoldingDataStringEx(reason: complete)");
	return 1;
}

stock SetHoldingDataInt(field[],data)
{
	Debug(DEBUG_START,"SetHoldingDataInt(%s,%d)",field,data);
#if defined USING_FILES
	new i;
	for(i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

		valstr(HoldingData[i],data);
	    break;
	}
	if(i == HoldingKeysCount)
	{
		Debug(DEBUG_ACTION,"field not found '%s'",field);
	}
#elseif defined USING_SQLITE
	format(vars,sizeof(vars),"%s,`%s`=%d",vars,field,data);
#elseif defined USING_MYSQL
	format(vars,sizeof(vars),"%s,`%s`=%d",vars,field,data);
#endif
	Debug(DEBUG_END,"SetHoldingDataInt(reason: complete)");
	return 1;
}

stock SetHoldingDataFloat(field[],Float:data)
{
	Debug(DEBUG_START,"SetHoldingDataFloat(%s,%f)",field,data);
#if defined USING_FILES
	new i;
	for(i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

 	    format(HoldingData[i],MAX_DATA_LEN,"%f",data);
	    break;
	}
	if(i == HoldingKeysCount)
	{
		Debug(DEBUG_ACTION,"field not found '%s'",field);
	}
#elseif defined USING_SQLITE
	format(vars,sizeof(vars),"%s,`%s`=%f",vars,field,data);
#elseif defined USING_MYSQL
	format(vars,sizeof(vars),"%s,`%s`=%f",vars,field,data);
#endif
	Debug(DEBUG_END,"SetHoldingDataFloat(reason: complete)");
	return 1;
}

stock SetHoldingDataString(field[],data[])
{
	Debug(DEBUG_START,"SetHoldingDataString(%s,%s)",field,data);
#if defined USING_FILES
	new i;
	for(i = 0;i < HoldingKeysCount;i++)
	{
	    if(!HoldingKeys[i][0]) continue;
	    if(strcmp(HoldingKeys[i],field)) continue;

 	    format(HoldingData[i],MAX_DATA_LEN,data);
	    break;
	}
	if(i == HoldingKeysCount)
	{
		Debug(DEBUG_ACTION,"field not found '%s'",field);
	}
#elseif defined USING_SQLITE
	format(vars,sizeof(vars),"%s,`%s`='%s'",vars,field,data);
#elseif defined USING_MYSQL
	format(vars,sizeof(vars),"%s,`%s`='%s'",vars,field,data);
#endif
	Debug(DEBUG_END,"SetHoldingDataString(reason: complete)");
	return 1;
}

stock GetHoldingDataByOrder(dir[],field[],order)
{
	Debug(DEBUG_START,"GetHoldingDataByOrder(%s,%s,%d)",dir,field,order);
	new res = 0;
#if defined USING_FILES
	// files...dir - directory
	format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
	CurrentFile = fopen(HoldingFile,io_read);
	if(CurrentFile)
	{
	    new pos[2],key;
	    // read keys
	    fread(CurrentFile,temp);
	    Debug(DEBUG_ACTION,"fields: '%s'",temp);
	    // parsing
	    ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
	    HoldingKeysCount = key;
	    // get needed key id
		for(key = 0;key < HoldingKeysCount;key++)
		{
		    if(strcmp(HoldingKeys[key],field)) continue;
		    break;
		}
		if(key == HoldingKeysCount)
		{
			Debug(DEBUG_ACTION,"field '%s' not found",field);
		}
		else
		{
	    	Debug(DEBUG_ACTION,"search by order");
			// read file and search by order
			while(fread(CurrentFile,temp))
			{
		       	if(GetField(temp,key,pos[0],pos[1]))
		       	{
		       	    new fielddata[MAX_DATA_LEN];
		       	    strmid(fielddata,temp,pos[0],pos[1],MAX_DATA_LEN);
		       	    switch(order)
		       	    {
		       	        case HOLDING_ORDER_MINIMAL:
		       	        {
		       	            if(strval(fielddata) < res) res = strval(fielddata);
		       	        }
		       	        case HOLDING_ORDER_MAXIMAL:
		       	        {
		       	            if(strval(fielddata) > res) res = strval(fielddata);
		       	        }
		       	    }
		       	}
		       	else
				{
					Debug(DEBUG_ACTION,"invalid data '%s' - %d",temp,key);
				}
			}
		}
		fclose(CurrentFile);
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	switch(order)
	{
		case HOLDING_ORDER_MINIMAL: format(query,sizeof(query),"SELECT `%s` FROM `%s` ORDER BY `%s` ASC",field,dir,field);
		case HOLDING_ORDER_MAXIMAL: format(query,sizeof(query),"SELECT `%s` FROM `%s` ORDER BY `%s` DESC",field,dir,field);
	}
	DB_result = db_query(DB_id,query);
    if(db_get_field(DB_result,0,result,sizeof(result))) res = strval(result);
	db_free_result(DB_result);
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	switch(order)
	{
		case HOLDING_ORDER_MINIMAL: format(query,sizeof(query),"SELECT `%s` FROM `%s` ORDER BY `%s` ASC",field,dir,field);
		case HOLDING_ORDER_MAXIMAL: format(query,sizeof(query),"SELECT `%s` FROM `%s` ORDER BY `%s` DESC",field,dir,field);
	}
	if(samp_mysql_query(query))
	{
	    samp_mysql_store_result();
	    if(samp_mysql_fetch_row(result)) res = strval(result);
		samp_mysql_free_result();
	}
#endif
	Debug(DEBUG_END,"GetHoldingDataByOrder(reason: complete)");
	return res;
}

stock OpenHoldingTable(dir[])
{
	Debug(DEBUG_START,"OpenHoldingTable(%s)",dir);
	new res = 0;
#if defined USING_FILES
    // files...dir - directory
	format(HoldingFile,sizeof(HoldingFile),"%s/%s.txt",HoldingDir,dir);
	CurrentFile = fopen(HoldingFile,io_read);
	if(CurrentFile)
	{
		// read keys
		if(fread(CurrentFile,temp))
		{
			new key;
			Debug(DEBUG_ACTION,"fields: '%s'",temp);
			// parsing
			ParseStringTo(temp,HoldingKeys,key,MAX_KEYS,MAX_KEY_LEN);
			HoldingKeysCount = key;
	    	if(fread(CurrentFile,temp))
	    	{
	    	    new f;
	    		ParseStringTo(temp,HoldingData,f,MAX_KEYS,MAX_DATA_LEN);
	    		res = 1;
			}
	    }
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	format(query,sizeof(query),"SELECT * FROM `%s`",dir);
	DB_result = db_query(DB_id,query);
	if(db_num_rows(DB_result) > 0) res = 1;
	else db_free_result(DB_result);
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	format(query,sizeof(query),"SELECT * FROM `%s`",dir);
	if(samp_mysql_query(query))
	{
	    samp_mysql_store_result();
		if(samp_mysql_num_rows() > 0) res = 1;
	}
#endif
	Debug(DEBUG_END,"OpenHoldingTable(reason: complete)");
	return res;
}

stock NextHoldingTableRow()
{
	Debug(DEBUG_START,"NextHoldingTableRow()");
	new res = 0;
#if defined USING_FILES
    // files...dir - directory
    new f;
	if(fread(CurrentFile,temp))
	{
		ParseStringTo(temp,HoldingData,f,MAX_KEYS,MAX_DATA_LEN);
		res = 1;
	}
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	if(db_next_row(DB_result)) res = 1;
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	if(samp_mysql_fetch_row(result)) res = 1;
#endif
	Debug(DEBUG_END,"NextHoldingTableRow(reason: complete)");
	return res;
}

stock CloseHoldingTable()
{
	Debug(DEBUG_START,"CloseHoldingTable()");
#if defined USING_FILES
    // files...dir - directory
	fclose(CurrentFile);
#elseif defined USING_SQLITE
	// db...dir - name of table, name - row
	db_free_result(DB_result);
#elseif defined USING_MYSQL
	// db...dir - name of table, name - row
	samp_mysql_free_result();
#endif
	Debug(DEBUG_END,"CloseHoldingTable(reason: complete)");
	return 1;
}

// --------------------------------------------------
// local functions
// --------------------------------------------------
static stock ParseStringTo(source[],dest[][],&fields,max_fields,max_field_len)
{
	new pos[2];
	for(fields = 0;fields < max_fields;fields++)
	{
		if((pos[1] = strfind(source,"|",false,pos[0])) == -1) break;
		strmid(dest[fields],source,pos[0],pos[1],max_field_len);
		pos[0] = pos[1] + 1;
	}
}

static stock GetField(string[],field,&start,&end)
{
	start = 0;
    for(;field > 0;field--) start = strfind(string,"|",false,start) + 1;
    if(start == -1) return 0;
	end = strfind(string,"|",false,start);
	if(end == -1) return 0;
	return 1;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Holding_Init()
{
	Debug(DEBUG_START,"Core_Holding_Init()");
	new File:conf = fopen(HOLDING_CONFIG_FILE,io_read),
		pos;
	if(conf)
	{
#if defined USING_FILES
		while(fread(conf,temp))
		{
		    if((pos = strfind(temp,"=",false)) == -1) continue;
			StripNL(temp);
			ReadFileDataStr(temp,"Dir",pos,HoldingDir);
		}
		fclose(conf);
    	print("[CORE] Holding (files) load complete.");
#elseif defined USING_SQLITE
		while(fread(conf,temp))
		{
		    if((pos = strfind(temp,"=",false)) == -1) continue;
		    StripNL(temp);
		    ReadFileDataStr(temp,"Base",pos,DB_Base);
		}
		fclose(conf);
		// open
		DB_id = db_open(DB_Base);
    	if(DB_id) print("[CORE] Holding (SQLite) load complete.");
    	else printf("[CORE] Holding (SQLite) load not complete: not found DB \"%s\".",DB_Base);
#elseif defined USING_MYSQL
		while(fread(conf,temp))
		{
		    if((pos = strfind(temp,"=",false)) == -1) continue;
		    StripNL(temp);
		    ReadFileDataStr(temp,"Host",pos,DB_Host);
		    ReadFileDataStr(temp,"User",pos,DB_User);
		    ReadFileDataStr(temp,"Password",pos,DB_Pass);
		    ReadFileDataStr(temp,"Base",pos,DB_Base);
		}
		fclose(conf);
		// connect
		if(samp_mysql_connect(DB_Host,DB_User,DB_Pass))
		{
			samp_mysql_select_db(DB_Base);
			samp_mysql_query("SET NAMES cp1251");
			print("[CORE] Holding (MySQL) load complete.");
		}
		else print("[CORE] Holding (MySQL) load not complete: connect error.");
#endif
	}
	else print("[CORE] Holding load not complete: not found settings file \"" HOLDING_CONFIG_FILE "\".");
	Debug(DEBUG_END,"Core_Holding_Init(reason: complete)");
}

Core_Holding_Exit()
{
	Debug(DEBUG_START,"Core_Holding_Exit()");
#if defined USING_SQLITE
	db_close(DB_id);
#elseif defined USING_MYSQL
	samp_mysql_close();
#endif
    Debug(DEBUG_END,"Core_Holding_Exit(reason: complete)");
}
