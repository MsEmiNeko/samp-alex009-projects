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
#include "SDK/SDK.h"
// plugin
#include "defines.h"
#include "CNode.h"

CNode * pNodes[MAX_NODES];

// Node:OpenNode(mode,name);
int n_OpenNode(HSQUIRRELVM pVM)
{
	for(int i = 0;i < MAX_NODES;i++)
	{
		if(pNodes[i]) continue;
		const char* temp;
		int mode;
		sq_getinteger(pVM,-2,&mode);
		sq_getstring(pVM, -1, &temp);

		pNodes[i] = new CNode((unsigned int)mode,temp);

		sq_pushinteger(pVM,i);
		return 1;
	}
	return 0;
}
// CloseNode(Node:nodeid);
int n_CloseNode(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		delete pNodes[nodeid];
		pNodes[nodeid] = 0;
		return 1;
	}
	return 0;
}
// GetNodeHeader(Node:nodeid,&nodes,&vehicle_nodes,&ped_nodes,&navi_nodes);
int n_GetNodeHeader(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int d1 = 0,
			d2 = 0,
			d3 = 0;
		pNodes[nodeid]->GetInfo(&d1,&d2,&d3);

		sq_newarray(pVM, 0);
		sq_pushinteger(pVM,d1);
		sq_arrayappend(pVM, -2);
		sq_pushinteger(pVM,d2);
		sq_arrayappend(pVM, -2);
		sq_pushinteger(pVM,d3);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}
	return 0;
}
// SetNodePoint(Node:nodeid,node_type,pointid);
int n_SetNodePoint(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-2,&nodeid);
	if(pNodes[nodeid])
	{
		int pointid;
		sq_getinteger(pVM,-1,&pointid);

		pNodes[nodeid]->SetPoint(pointid);
		return 1;
	}
	return 0;
}
// GetNodePoint(Node:nodeid);
int n_GetNodePoint(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetPointId();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodePointPos(Node:nodeid,&Float:X,&Float:Y,&Float:Z);
int n_GetNodePointPos(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		float x,y,z;
		pNodes[nodeid]->GetPos(&x,&y,&z);

		sq_newarray(pVM, 0);
		sq_pushfloat(pVM,x);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM,y);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM,z);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}
	return 0;
}
// GetNodePointLinkId(Node:nodeid);
int n_GetNodePointLinkId(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetLinkId();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodePointAreaId(Node:nodeid);
int n_GetNodePointAreaId(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetAreaId();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodePointWidth(Node:nodeid);
int n_GetNodePointWidth(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetPathWidth();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodePointFlags(Node:nodeid);
int n_GetNodePointFlags(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetFlags();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodePointType(Node:nodeid);
int n_GetNodePointType(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetNodeType();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// SetNodeLink(Node:nodeid,linkid);
int n_SetNodeLink(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-2,&nodeid);
	if(pNodes[nodeid])
	{
		int pointid;
		sq_getinteger(pVM,-1,&pointid);

		pNodes[nodeid]->SetLink(pointid);
		return 1;
	}
	return 0;
}
// GetNodeLinkAreaId(Node:nodeid);
int n_GetNodeLinkAreaId(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetLinkAreaId();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodeLinkNodeId(Node:nodeid);
int n_GetNodeLinkNodeId(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetLinkNodeId();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodeLinkLength(Node:nodeid);
int n_GetNodeLinkLength(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetLinkLength();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}
// GetNodeLinkFlags(Node:nodeid);
int n_GetNodeLinkFlags(HSQUIRRELVM pVM)
{
	int nodeid;
	sq_getinteger(pVM,-1,&nodeid);
	if(pNodes[nodeid])
	{
		int result = pNodes[nodeid]->GetLinkFlags();
		sq_pushinteger(pVM,result);
		return 1;
	}
	return 0;
}

void NativesScriptLoad(HSQUIRRELVM pVM)
{
	// node
	RegisterFunction(pVM,"OpenNode",n_OpenNode);
	RegisterFunction(pVM,"CloseNode",n_CloseNode);
	RegisterFunction(pVM,"GetNodeHeader",n_GetNodeHeader);
	RegisterFunction(pVM,"SetNodePoint",n_SetNodePoint);
	RegisterFunction(pVM,"GetNodePoint",n_GetNodePoint);
	RegisterFunction(pVM,"GetNodePointPos",n_GetNodePointPos);
	RegisterFunction(pVM,"GetNodePointLinkId",n_GetNodePointLinkId);
	RegisterFunction(pVM,"GetNodePointAreaId",n_GetNodePointAreaId);
	RegisterFunction(pVM,"GetNodePointWidth",n_GetNodePointWidth);
	RegisterFunction(pVM,"GetNodePointFlags",n_GetNodePointFlags);
	RegisterFunction(pVM,"GetNodePointType",n_GetNodePointType);
	RegisterFunction(pVM,"SetNodeLink",n_SetNodeLink);
	RegisterFunction(pVM,"GetNodeLinkAreaId",n_GetNodeLinkAreaId);
	RegisterFunction(pVM,"GetNodeLinkNodeId",n_GetNodeLinkNodeId);
	RegisterFunction(pVM,"GetNodeLinkLength",n_GetNodeLinkLength);
	RegisterFunction(pVM,"GetNodeLinkFlags",n_GetNodeLinkFlags);
}
