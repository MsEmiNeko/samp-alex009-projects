/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// plugin
#include "defines.h"
#include "CNode.h"
#include "CStack.h"

CNode * pNodes[MAX_NODES];
CStack*	pStacks[MAX_STACKS];

// Node:OpenNode(mode,name[]);
static cell AMX_NATIVE_CALL n_OpenNode( AMX* amx, cell* params )
{
	for(int i = 0;i < MAX_NODES;i++)
	{
		if(pNodes[i]) continue;
		char* temp;
		amx_StrParam(amx, params[2], temp);

		pNodes[i] = new CNode((unsigned int)params[1],temp);
		return i;
	}
	return 0;	
}
// CloseNode(Node:nodeid);
static cell AMX_NATIVE_CALL n_CloseNode( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		delete pNodes[nodeid];
		pNodes[nodeid] = 0;
		return 1;
	}
	return 0;
}
// GetNodeHeader(Node:nodeid,&nodes,&vehicle_nodes,&ped_nodes,&navi_nodes);
static cell AMX_NATIVE_CALL n_GetNodeHeader( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		int d1 = 0,
			d2 = 0,
			d3 = 0,
			d4 = 0;
		pNodes[nodeid]->GetInfo(&d1,&d2,&d3,&d4);
		//
		cell
			* p1,
			* p2,
			* p3,
			* p4;
		amx_GetAddr(amx, params[2], &p1);
		amx_GetAddr(amx, params[3], &p2);
		amx_GetAddr(amx, params[4], &p3);
		amx_GetAddr(amx, params[5], &p4);
		//
		*p1 = d1;
		*p2 = d2;
		*p3 = d3;
		*p4 = d4;
		return 1;
	}
	return 0;
}
// SetNodePoint(Node:nodeid,node_type,pointid);
static cell AMX_NATIVE_CALL n_SetNodePoint( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		pNodes[nodeid]->SetPoint((int)params[2]);
		return 1;
	}
	return 0;
}
// GetNodePoint(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePoint( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetPointId();
	}
	return 0;
}
// GetNodePointPos(Node:nodeid,&Float:X,&Float:Y,&Float:Z);
static cell AMX_NATIVE_CALL n_GetNodePointPos( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		float x,y,z;
		pNodes[nodeid]->GetPos(&x,&y,&z);

		cell
			* p1,
			* p2,
			* p3;
		amx_GetAddr(amx, params[2], &p1);
		amx_GetAddr(amx, params[3], &p2);
		amx_GetAddr(amx, params[4], &p3);

		*p1 = amx_ftoc(x);
		*p2 = amx_ftoc(y);
		*p3 = amx_ftoc(z);
		return 1;
	}
	return 0;
}
// GetNodePointLinkId(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointLinkId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetLinkId();
	}
	return 0;
}
// GetNodePointAreaId(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointAreaId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetAreaId();
	}
	return 0;
}
// GetNodePointWidth(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointWidth( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetPathWidth();
	}
	return 0;
}
// GetNodePointLinkCount(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointLinkCount( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetLinkCount();
	}
	return 0;
}
// GetNodePointTrafficLevel(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointTrafficLevel( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetTrafficLevel();
	}
	return 0;
}
// IsNodePointRoadBlock(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointRoadBlock( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsRoadBlock();
	}
	return 0;
}
// IsNodePointBoats(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointBoats( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsBoats();
	}
	return 0;
}
// IsNodePointEmergency(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointEmergency( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsEmergency();
	}
	return 0;
}
// IsNodePointNotHighway(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointNotHighway( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsNotHighway();
	}
	return 0;
}
// IsNodePointSpawn(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointSpawn( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsSpawn();
	}
	return 0;
}
// IsNodePointRoadBlock1(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointRoadBlock1( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsRoadBlock1();
	}
	return 0;
}
// IsNodePointParking(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointParking( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsParking();
	}
	return 0;
}
// IsNodePointRoadBlock2(Node:nodeid);
static cell AMX_NATIVE_CALL n_IsNodePointRoadBlock2( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->IsRoadBlock2();
	}
	return 0;
}
// GetNodePointType(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodePointType( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetNodeType();
	}
	return 0;
}
// SetNodeLink(Node:nodeid,linkid);
static cell AMX_NATIVE_CALL n_SetNodeLink( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		pNodes[nodeid]->SetLink((int)params[2]);
		return 1;
	}
	return 0;
}
// GetNodeLinkAreaId(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodeLinkAreaId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetLinkAreaId();
	}
	return 0;
}
// GetNodeLinkNodeId(Node:nodeid,&type);
static cell AMX_NATIVE_CALL n_GetNodeLinkNodeId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetLinkNodeId();
	}
	return 0;
}
// SetNodeNaviPoint(Node:nodeid,naviid);
static cell AMX_NATIVE_CALL n_SetNodeNaviPoint( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		pNodes[nodeid]->SetNaviPoint((int)params[2]);
		return 1;
	}
	return 0;
}
// GetNodeNaviPointPos(Node:nodeid,&Float:X,&Float:Y);
static cell AMX_NATIVE_CALL n_GetNodeNaviPointPos( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		float x,y;
		pNodes[nodeid]->GetNaviPos(&x,&y);

		cell
			* p1,
			* p2;
		amx_GetAddr(amx, params[2], &p1);
		amx_GetAddr(amx, params[3], &p2);

		*p1 = amx_ftoc(x);
		*p2 = amx_ftoc(y);
		return 1;
	}
	return 0;
}
// GetNodeNaviPointDirection(Node:nodeid,&Float:X,&Float:Y);
static cell AMX_NATIVE_CALL n_GetNodeNaviPointDirection( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		float x,y;
		pNodes[nodeid]->GetNaviDirection(&x,&y);

		cell
			* p1,
			* p2;
		amx_GetAddr(amx, params[2], &p1);
		amx_GetAddr(amx, params[3], &p2);

		*p1 = amx_ftoc(x);
		*p2 = amx_ftoc(y);
		return 1;
	}
	return 0;
}
// GetNodeNaviPointAreaId(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodeNaviPointAreaId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetNaviAreaId();
	}
	return 0;
}
// GetNodeNaviPointPointId(Node:nodeid);
static cell AMX_NATIVE_CALL n_GetNodeNaviPointPointId( AMX* amx, cell* params )
{
	int nodeid = (int)params[1];
	if(pNodes[nodeid])
	{
		return pNodes[nodeid]->GetNaviPointId();
	}
	return 0;
}
// Stack:StackCreate();
static cell AMX_NATIVE_CALL n_StackCreate( AMX* amx, cell* params )
{
	for(int i = 0;i < MAX_STACKS;i++)
	{
		if(pStacks[i]) continue;

		pStacks[i] = new CStack();
		return i;
	}
	return 0;
}
// StackDestroy(Stack:stackid);
static cell AMX_NATIVE_CALL n_StackDestroy( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		delete pStacks[stackid];
		pStacks[stackid] = 0;
		return 1;
	}
	return 0;
}
// StackPushInt(Stack:stackid,data);
static cell AMX_NATIVE_CALL n_StackPushInt( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		int temp = (int)params[2];
		
		pStacks[stackid]->push(STACK_DATA_INT,&temp);
		return 1;
	}
	return 0;
}
// StackPushFloat(Stack:stackid,data);
static cell AMX_NATIVE_CALL n_StackPushFloat( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		float temp = amx_ctof(params[2]);
		
		pStacks[stackid]->push(STACK_DATA_FLOAT,&temp);
		return 1;
	}
	return 0;
}
// StackPushString(Stack:stackid,data[]);
static cell AMX_NATIVE_CALL n_StackPushString( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		char* temp;
		amx_StrParam(amx, params[2], temp);
		
		pStacks[stackid]->push(STACK_DATA_STRING,temp);
		return 1;
	}
	return 0;
}
// StackPopInt(Stack:stackid);
static cell AMX_NATIVE_CALL n_StackPopInt( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		int result;
		pStacks[stackid]->pop(STACK_DATA_INT,&result);
		return result;
	}
	return 0;
}
// Float:StackPopFloat(Stack:stackid);
static cell AMX_NATIVE_CALL n_StackPopFloat( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		float result;
		pStacks[stackid]->pop(STACK_DATA_FLOAT,&result);
		return amx_ftoc(result);
	}
	return 0;
}
// StackPopString(Stack:stackid,data[],size);
static cell AMX_NATIVE_CALL n_StackPopString( AMX* amx, cell* params )
{
	int stackid = (int)params[1];
	if(pStacks[stackid])
	{
		int size = (int)params[3];
		char* temp = new char[size];
		memset(temp,0,size);
		pStacks[stackid]->pop(STACK_DATA_STRING,temp);
		cell* p1;
		amx_GetAddr(amx, params[2], &p1);
		amx_SetString(p1,temp,0,0,size);
		return 1;
	}
	return 0;
}

AMX_NATIVE_INFO Natives[ ] =
{
	// node
	{ "OpenNode",					n_OpenNode},
	{ "CloseNode",					n_CloseNode},
	{ "GetNodeHeader",				n_GetNodeHeader},
	{ "SetNodePoint",				n_SetNodePoint},
	{ "GetNodePoint",				n_GetNodePoint},
	{ "GetNodePointPos",			n_GetNodePointPos},
	{ "GetNodePointLinkId",			n_GetNodePointLinkId},
	{ "GetNodePointLinkCount",		n_GetNodePointLinkCount},
	{ "GetNodePointAreaId",			n_GetNodePointAreaId},
	{ "GetNodePointWidth",			n_GetNodePointWidth},
	{ "GetNodePointType",			n_GetNodePointType},
	{ "SetNodeLink",				n_SetNodeLink},
	{ "GetNodeLinkAreaId",			n_GetNodeLinkAreaId},
	{ "GetNodeLinkNodeId",			n_GetNodeLinkNodeId},
	{ "GetNodePointTrafficLevel",	n_GetNodePointTrafficLevel},
	{ "IsNodePointRoadBlock",		n_IsNodePointRoadBlock},
	{ "IsNodePointBoats",			n_IsNodePointBoats},
	{ "IsNodePointEmergency",		n_IsNodePointEmergency},
	{ "IsNodePointNotHighway",		n_IsNodePointNotHighway},
	{ "IsNodePointSpawn",			n_IsNodePointSpawn},
	{ "IsNodePointRoadBlock1",		n_IsNodePointRoadBlock1},
	{ "IsNodePointParking",			n_IsNodePointParking},
	{ "IsNodePointRoadBlock2",		n_IsNodePointRoadBlock2},
	{ "SetNodeNaviPoint",			n_SetNodeNaviPoint},
	{ "GetNodeNaviPointPos",		n_GetNodeNaviPointPos},
	{ "GetNodeNaviPointDirection",	n_GetNodeNaviPointDirection},
	{ "GetNodeNaviPointAreaId",		n_GetNodeNaviPointAreaId},
	{ "GetNodeNaviPointPointId",	n_GetNodeNaviPointPointId},
	// stack
	{ "StackCreate",				n_StackCreate},
	{ "StackDestroy",				n_StackDestroy},
	{ "StackPushInt",				n_StackPushInt},
	{ "StackPushFloat",				n_StackPushFloat},
	{ "StackPushString",			n_StackPushString},
	{ "StackPopInt",				n_StackPopInt},
	{ "StackPopFloat",				n_StackPopFloat},
	{ "StackPopString",				n_StackPopString},
	{ 0,							0 }
};

void NativesOnAMXLoad(AMX* amx)
{
	amx_Register(amx, Natives, -1 );
}
