/*
*	Created:			16.11.09
*	Author:				009
*	Description:		Функции дебага 
*/

#if defined core_debug_included
	#endinput
#endif

#define core_debug_included
#pragma library core_debug

// --------------------------------------------------
// defines
// --------------------------------------------------
#define MAX_DEBUG_STRING 		512
#define MAX_DEBUG_FUNCS_ON 		50
#define MAX_DEBUG_WRITES        100
#define DEBUG_FILE 				"debug.txt"

// --------------------------------------------------
// enums
// --------------------------------------------------
enum
{
	DEBUG_START,
	DEBUG_ACTION,
	DEBUG_SMALL,
	DEBUG_END
};

// --------------------------------------------------
// statics
// --------------------------------------------------
static stock
	tabcounts,
	tabs_tmp[MAX_DEBUG_FUNCS_ON],
	func_time[MAX_DEBUG_FUNCS_ON],
	File:debugfile,
	writes_count,
	if_not_write;

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native Debug(type,const format[],{Float,_}:...);
*/

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward DebugCheck();

// --------------------------------------------------
// publics
// --------------------------------------------------
public DebugCheck()
{
    if(debugfile)
	{
		if(writes_count > MAX_DEBUG_WRITES)
		{
		    fclose(debugfile);
			debugfile = fopen(DEBUG_FILE, io_append);
		}
	}
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Debug_Init()
{
#if defined DEBUG
	static tmp[10];
	format(tmp,10,"just init for hook");
	SetTimer("DebugCheck",10_000,1); // every 10 seconds all save
#endif
}

// --------------------------------------------------
// stocks
// --------------------------------------------------
#if !defined DEBUG
	#define Debug(%1);
	#endinput
#endif

stock Debug(mtype,fstring[],{Float, _}:...)
{
	// check unused debug

	// just not debug OnPlayerUpdate
	if(strfind(fstring,"PlayerUpdate") != -1)
	{
		if(!if_not_write) if_not_write = 1;
	    else if_not_write = 0;
	    return 1;
	}

	/*
	// debug one of OnPlayerUpdate
	if(strfind(fstring,"PlayerUpdate") != -1)
	{
		if(strfind(fstring,"Core_Icons_PlayerUpdate") == -1)
		{
	    	if(!if_not_write) if_not_write = 1;
	    	else if_not_write = 0;
	    	return 1;
		}
	}
	*/
	/*
	// debug more then one OnPlayerUpdate
	if(strfind(fstring,"PlayerUpdate") != -1)
	{
		if(
			(strfind(fstring,"Core_Icons_PlayerUpdate") == -1) &&
			(strfind(fstring,"Core_Pickups_PlayerUpdate") == -1)
		)
		{
	    	if(!if_not_write) if_not_write = 1;
	    	else if_not_write = 0;
	    	return 1;
		}
	}
	*/
	if(if_not_write) return 1;
	// tabs
	if(mtype == DEBUG_END) tabcounts--;
	for(new i = 0;i < tabcounts;i++) tabs_tmp[i] = '\t';
	tabs_tmp[tabcounts] = 0;
	// file operations
	if(!debugfile) debugfile = fopen(DEBUG_FILE, io_append);
	// write
	if(debugfile)
	{
		// tabs
		fwrite(debugfile,tabs_tmp);
		// used Y_Less's code
		#define BYTES_PER_CELL (cellbits / 8)
		// This is the number of parameters which are not variable that are passed
		// to this function (i.e. the number of named parameters).
		static const
			STATIC_ARGS = 1;
		// Get the number of variable arguments.
		new n = (numargs() - STATIC_ARGS) * BYTES_PER_CELL;
		if(n)
		{
			new
				message[128],
				arg_start,
				arg_end;

			// Load the real address of the last static parameter. Do this by
			// loading the address of the last known static parameter and then
			// adding the value of [FRM].
			#emit CONST.alt			fstring
			#emit LCTRL				5
			#emit ADD
			#emit STOR.S.pri		arg_start

			// Load the address of the last variable parameter. Do this by adding
			// the number of variable parameters on the value just loaded.
			#emit LOAD.S.alt		n
			#emit ADD
			#emit STOR.S.pri		arg_end

			// Push the variable arguments. This is done by loading the value of
			// each one in reverse order and pushing them. I'd love to be able to
			// rewrite this to use the values of pri and alt for comparison,
			// instead of having to constantly load and reload two variables.
			do
			{
				#emit LOAD.I
				#emit PUSH.pri
				arg_end -= BYTES_PER_CELL;
				#emit LOAD.S.pri      arg_end
			}
			while (arg_end > arg_start);

			// Push the static format parameters.
			#emit PUSH.S			fstring
			#emit PUSH.C			128
			#emit PUSH.ADR			message

			// Now push the number of arguments passed to format, including both
			// static and variable ones and call the function.
			n += BYTES_PER_CELL * 3;
			#emit PUSH.S			n
			#emit SYSREQ.C			format

			// Remove all data, including the return value, from the stack.
			n += BYTES_PER_CELL;
			#emit LCTRL				4
			#emit LOAD.S.alt		n
			#emit ADD
			#emit SCTRL				4

			fwrite(debugfile,message);
		}
		else 
		{
			fwrite(debugfile,fstring);
		}
		// undef
		#undef BYTES_PER_CELL
		switch(mtype)
		{
			case DEBUG_START: 
			{
				fwrite(debugfile," start");
				func_time[tabcounts] = GetTickCount();
			}
			case DEBUG_END: 
			{
				format(tabs_tmp,sizeof(tabs_tmp)," end (%d ticks)",(GetTickCount() - func_time[tabcounts]));
				fwrite(debugfile,tabs_tmp);
			}
			case DEBUG_SMALL:
			{
				fwrite(debugfile," called");
			}
		}
		// write end
		fwrite(debugfile,"\r\n");
	}
	else print("[ERROR] cant open debug file");
	// tabs
	if(mtype == DEBUG_START) tabcounts++;
	return 1;
}
