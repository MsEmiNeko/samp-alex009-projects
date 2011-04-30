/*
*	Created:			21.01.10
*	Author:				009
*	Description:		ƒействи€ и визуальный выбор (like menus)
*/

#if defined core_actions_included
	#endinput
#endif

#define core_actions_included
#pragma library core_actions

// --------------------------------------------------
// includes
// --------------------------------------------------
#tryinclude "../core/headers/defines.h"

// --------------------------------------------------
// defines
// --------------------------------------------------
#define ACTION_SELECT_KEY           KEY_LOOK_BEHIND

// --------------------------------------------------
// checks
// --------------------------------------------------
#if !defined Debug
	#define Debug(%1);
#endif

// --------------------------------------------------
// enums
// --------------------------------------------------

// --------------------------------------------------
// statics
// --------------------------------------------------
static
	Player_Action[MAX_PLAYERS char], // think need more then 256 actions? delete 'char' word
	// action selecting rows data
	ActionSelectRowState[MAX_ACTION_SELECT char],
    Text:ActionSelectRowTexts[MAX_ACTION_SELECT][3],
	ActionSelectRowAction[MAX_ACTION_SELECT char], // think need more then 256 actions? delete 'char' word
    // action selecting player data
    ActionSelectPlayerState[MAX_PLAYERS char],
    ActionSelectPlayerRows[MAX_PLAYERS char][3 char]; // MAX_ACTION_SELECT > 256? delete 'char' word

// --------------------------------------------------
// forwards
// --------------------------------------------------
forward OnPlayerActionSelectCheck(playerid,actionid);
forward OnPlayerActionSelect(playerid,actionid);

// --------------------------------------------------
// publics
// --------------------------------------------------

// --------------------------------------------------
// natives list (for pawno functions list)
// --------------------------------------------------
/*
native SetPlayerAction(playerid,actionid);
native GetPlayerAction(playerid);
native AddActionSelectRow(const actionname[],actionid);
native ShowActionSelecting(playerid);
*/

// --------------------------------------------------
// stocks
// --------------------------------------------------
stock GetPlayerAction(playerid)
{
	Debug(DEBUG_SMALL,"GetPlayerAction(%d)",playerid);
	return Player_Action{playerid};
}

stock SetPlayerAction(playerid,actionid)
{
	Debug(DEBUG_SMALL,"SetPlayerAction(%d,%d)",playerid,actionid);
	Player_Action{playerid} = actionid;
	return 1;
}

stock AddActionSelectRow(actionname[],actionid)
{
	Debug(DEBUG_START,"AddActionSelectRow('%s',%d)",actionname,actionid);
	for(new id = 0;id < MAX_ACTION_SELECT;id++)
	{
		if(ActionSelectRowState{id} == 1) continue;
		// Status
		ActionSelectRowState{id} = 1;
		// Left sel
		ActionSelectRowTexts[id][0] = TextDrawCreate(220.0,370.0,actionname);
		TextDrawAlignment(ActionSelectRowTexts[id][0],3);
		TextDrawSetShadow(ActionSelectRowTexts[id][0],0);
		TextDrawFont(ActionSelectRowTexts[id][0],2);
		// Center sel
		ActionSelectRowTexts[id][1] = TextDrawCreate(320.0,360.0,actionname);
		TextDrawLetterSize(ActionSelectRowTexts[id][1],0.399999,2.400000);
		TextDrawAlignment(ActionSelectRowTexts[id][1],2);
		TextDrawSetShadow(ActionSelectRowTexts[id][1],0);
		TextDrawFont(ActionSelectRowTexts[id][1],2);
		// Right sel
		ActionSelectRowTexts[id][2] = TextDrawCreate(420.0,370.0,actionname);
		TextDrawAlignment(ActionSelectRowTexts[id][2],1);
		TextDrawSetShadow(ActionSelectRowTexts[id][2],0);
		TextDrawFont(ActionSelectRowTexts[id][2],2);
		// Parameters
		ActionSelectRowAction{id} = actionid;
		Debug(DEBUG_END,"AddActionSelectRow(reason: complete)");
		return id;
	}
	Debug(DEBUG_END,"AddActionSelectRow(reason: error)");
	print("[ERROR] Core -> Actions -> AddActionSelectRow (all slots used)");
	return INVALID_ACTION_SELECT_ROW;
}

stock ShowActionSelecting(playerid)
{
	Debug(DEBUG_START,"ShowActionSelecting(%d)",playerid);
	static
		cid,
		rid;
	for(cid = 0;cid < MAX_ACTION_SELECT;cid++)
	{
		if(ActionSelectRowState{cid} == 0) continue;
		// Test player info for this select
		if(!OnPlayerActionSelectCheck(playerid,ActionSelectRowAction{cid})) continue;
		ActionSelectPlayerState{playerid} = 1;
		ActionSelectPlayerRows[playerid]{1} = cid;
		TextDrawShowForPlayer(playerid,ActionSelectRowTexts[cid][1]);
		break;
	}
	if(cid == MAX_ACTION_SELECT)
	{
		Debug(DEBUG_END,"ShowActionSelecting(reason: complete)");
		return 0;
	}
	ActionSelectPlayerRows[playerid]{0} = INVALID_ACTION_SELECT_ROW;
	// Ћевый выбор не ищем,т.к. мы отображаем начальное.»щем сразу правый
	for(rid = (cid + 1);rid < MAX_ACTION_SELECT;rid++)
	{
		if(ActionSelectRowState{rid} == 0) continue;
		// Test player info for this select
		if(!OnPlayerActionSelectCheck(playerid,ActionSelectRowAction{rid})) continue;
		ActionSelectPlayerRows[playerid]{2} = rid;
		TextDrawShowForPlayer(playerid,ActionSelectRowTexts[rid][2]);
		break;
	}
	if(rid == MAX_ACTION_SELECT) ActionSelectPlayerRows[playerid]{2} = INVALID_ACTION_SELECT_ROW;
	TogglePlayerControllable(playerid,false);
	Debug(DEBUG_END,"ShowActionSelecting(reason: complete)");
	return 1;
}

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Core_Actions_OPKSC(playerid,newkeys,oldkeys)
{
	Debug(DEBUG_START,"Core_Actions_OPKSC(%d,%d,%d)",playerid,newkeys,oldkeys);
	if(ActionSelectPlayerState{playerid})
	{
	    switch(newkeys)
		{
			case KEY_ANALOG_LEFT:
			{
				if(ActionSelectPlayerRows[playerid]{0} == INVALID_ACTION_SELECT_ROW)
				{
					Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
					return 1;
				}
				if(ActionSelectPlayerRows[playerid]{2} != INVALID_ACTION_SELECT_ROW) TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{2} ][2]);
				TextDrawShowForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][2]);
				ActionSelectPlayerRows[playerid]{2} = ActionSelectPlayerRows[playerid]{1};
				TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][1]);
				ActionSelectPlayerRows[playerid]{1} = ActionSelectPlayerRows[playerid]{0};
				TextDrawShowForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][1]);
				if(ActionSelectPlayerRows[playerid]{0} != INVALID_ACTION_SELECT_ROW) TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{0} ][0]);
				new lid;
				for(lid = (ActionSelectPlayerRows[playerid]{1} - 1);lid >= 0;lid--)
				{
					if(ActionSelectRowState{lid} == 0) continue;
					// Test player info for this select
					if(!OnPlayerActionSelectCheck(playerid,ActionSelectRowAction{lid})) continue;
					ActionSelectPlayerRows[playerid]{0} = lid;
					TextDrawShowForPlayer(playerid,ActionSelectRowTexts[lid][0]);
					break;
				}
				if(lid == -1) ActionSelectPlayerRows[playerid]{0} = INVALID_ACTION_SELECT_ROW;
				Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
				return 1;
			}
			case KEY_ANALOG_RIGHT:
			{
			    if(ActionSelectPlayerRows[playerid]{2} == INVALID_ACTION_SELECT_ROW)
				{
					Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
					return 1;
				}
				if(ActionSelectPlayerRows[playerid]{0} != INVALID_ACTION_SELECT_ROW) TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{0} ][0]);
				TextDrawShowForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][0]);
				ActionSelectPlayerRows[playerid]{0} = ActionSelectPlayerRows[playerid]{1};
				TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][1]);
				ActionSelectPlayerRows[playerid]{1} = ActionSelectPlayerRows[playerid]{2};
				TextDrawShowForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][1]);
				if(ActionSelectPlayerRows[playerid]{2} != INVALID_ACTION_SELECT_ROW) TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{2} ][2]);
				new rid;
				for(rid = (ActionSelectPlayerRows[playerid]{1} + 1);rid < MAX_ACTION_SELECT;rid++)
				{
					if(ActionSelectRowState{rid} == 0) continue;
					// Test player info for this select
					if(!OnPlayerActionSelectCheck(playerid,ActionSelectRowAction{rid})) continue;
					ActionSelectPlayerRows[playerid]{2} = rid;
					TextDrawShowForPlayer(playerid,ActionSelectRowTexts[rid][2]);
					break;
				}
				if(rid == MAX_ACTION_SELECT) ActionSelectPlayerRows[playerid]{2} = INVALID_ACTION_SELECT_ROW;
				Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
				return 1;
			}
			case KEY_SPRINT:
			{
				OnPlayerActionSelect(playerid,ActionSelectRowAction{ ActionSelectPlayerRows[playerid]{1} });
				if(ActionSelectPlayerRows[playerid]{0} != INVALID_ACTION_SELECT_ROW)
				{
					TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{0} ][0]);
					ActionSelectPlayerRows[playerid]{0} = INVALID_ACTION_SELECT_ROW;
				}
				if(ActionSelectPlayerRows[playerid]{1} != INVALID_ACTION_SELECT_ROW)
				{
					TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{1} ][1]);
					ActionSelectPlayerRows[playerid]{1} = INVALID_ACTION_SELECT_ROW;
				}
				if(ActionSelectPlayerRows[playerid]{2} != INVALID_ACTION_SELECT_ROW)
				{
					TextDrawHideForPlayer(playerid,ActionSelectRowTexts[ ActionSelectPlayerRows[playerid]{2} ][2]);
					ActionSelectPlayerRows[playerid]{2} = INVALID_ACTION_SELECT_ROW;
				}
				ActionSelectPlayerState{playerid} = 0;
				TogglePlayerControllable(playerid,true);
				Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
				return 1;
			}
		}
	}
	else
	{
	    if(newkeys == ACTION_SELECT_KEY) ShowActionSelecting(playerid);
	}
	Debug(DEBUG_END,"Core_Actions_OPKSC(reason: complete)");
	return 0;
}
