/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

// SDK
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
// core
#include <stdio.h>
// plugin
#include "CNode.h"
#include "defines.h"

CNode::CNode(unsigned int mode,char* nodename)
{
	char* buf = new char[128];
	// path
	sprintf(buf,"scriptfiles/%s",nodename);
	// data
	read_mode = mode;
	// open
	NodeFile = fopen(buf,"rb");
	if(NodeFile)
	{
		// init vars
		header = new NodeHeader;
		// read main info
		fread(header,sizeof(NodeHeader),1,NodeFile);
		switch(read_mode)
		{
		case NODE_MODE_FILE:
			{
				// init vars
				PathTmp = new NodePath;
				LinkTmp = new NodeLink;
				NaviTmp = new NodeNavi;
				// read data
				fread(PathTmp,sizeof(NodePath),1,NodeFile);
				break;
			}
		case NODE_MODE_MEMORY:
			{
				// init vars
				PathTmp = new NodePath[header->NumNodes];
				LinkTmp = new NodeLink[header->NumLinks];
				NaviTmp = new NodeNavi[header->NumNaviNodes];
				// read data
				fread(PathTmp,sizeof(NodePath),header->NumNodes,NodeFile);
				fread(NaviTmp,sizeof(NodeNavi),header->NumNaviNodes,NodeFile);
				fread(LinkTmp,sizeof(NodeLink),header->NumLinks,NodeFile);
				// close file
				fclose(NodeFile);
				break;
			}
		}
		CurrentPoint = 0;
		CurrentLink = 0;
		CurrentNavi = 0;
	}
}

CNode::~CNode()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NodeFile) fclose(NodeFile);
			break;
		}
	case NODE_MODE_MEMORY:
		{
			delete PathTmp;
			delete LinkTmp;
			delete NaviTmp;
			delete header;
			break;
		}
	}
}

void CNode::GetInfo(int* nodes,int* vehnodes,int* pednodes,int* navinodes)
{
	if(header)
	{
		*nodes = header->NumNodes;
		*vehnodes = header->NumVehicleNodes;
		*pednodes = header->NumPedNodes;
		*navinodes = header->NumNaviNodes;
	}
}

void CNode::SetPoint(int pointid)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NodeFile)
			{
				if(pointid > static_cast<int>(header->NumNodes)) return;
				CurrentPoint = pointid;

				pointid *= sizeof(NodePath);

				fseek(NodeFile,(pointid + sizeof(NodeHeader)),0);

				fread(PathTmp,sizeof(NodePath),1,NodeFile);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			if(pointid > static_cast<int>(header->NumNodes)) return;
			CurrentPoint = pointid;
			break;
		}
	}
}

void CNode::GetPos(float* x,float* y,float* z)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				*x = static_cast<float>(PathTmp->PosX) * 0.125f;
				*y = static_cast<float>(PathTmp->PosY) * 0.125f;
				*z = static_cast<float>(PathTmp->PosZ) * 0.125f;
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			*x = static_cast<float>(PathTmp[CurrentPoint].PosX) * 0.125f;
			*y = static_cast<float>(PathTmp[CurrentPoint].PosY) * 0.125f;
			*z = static_cast<float>(PathTmp[CurrentPoint].PosZ) * 0.125f;
			break;
		}
	}
}

int CNode::GetLinkId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->LinkId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].LinkId);
			break;
		}
	}
	return 0;
}

int CNode::GetAreaId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->AreaId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].AreaId);
			break;
		}
	}
	return 0;
}

int CNode::GetPointId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->NodeId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].NodeId);
			break;
		}
	}
	return 0;
}

int CNode::GetPathWidth()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->PathWidth);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].PathWidth);
			break;
		}
	}
	return 0;
}

int CNode::GetNodeType()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->NodeType);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].NodeType);
			break;
		}
	}
	return 0;
}

int CNode::GetLinkCount()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0xF);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0xF);
			break;
		}
	}
	return 0;
}

int CNode::GetTrafficLevel()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x30);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x30);
			break;
		}
	}
	return 0;
}

int CNode::IsRoadBlock()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x40);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x40);
			break;
		}
	}
	return 0;
}

int CNode::IsBoats()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x80);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x80);
			break;
		}
	}
	return 0;
}

int CNode::IsEmergency()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x100);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x100);
			break;
		}
	}
	return 0;
}

int CNode::IsNotHighway()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x1000);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x1000);
			break;
		}
	}
	return 0;
}

int CNode::IsSpawn()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0xF0000);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0xF0000);
			break;
		}
	}
	return 0;
}

int CNode::IsRoadBlock1()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x100000);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x100000);
			break;
		}
	}
	return 0;
}

int CNode::IsParking()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x200000);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x200000);
			break;
		}
	}
	return 0;
}

int CNode::IsRoadBlock2()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(PathTmp)
			{
				return static_cast<int>(PathTmp->Flags & 0x800000);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(PathTmp[CurrentPoint].Flags & 0x800000);
			break;
		}
	}
	return 0;
}

void CNode::SetLink(int linkid)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NodeFile)
			{
				if(linkid > static_cast<int>(header->NumLinks)) return;
				CurrentLink = linkid;

				fseek(NodeFile,(sizeof(NodeHeader) + ((header->NumNodes) * sizeof(NodePath)) + (header->NumNaviNodes * sizeof(NodeNavi)) + (CurrentLink  * sizeof(NodeLink))),0);
				fread(LinkTmp,sizeof(NodeLink),1,NodeFile);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			if(linkid > static_cast<int>(header->NumLinks)) return;
			CurrentLink = linkid;
			break;
		}
	}
}

int CNode::GetLinkAreaId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(LinkTmp)
			{
				return static_cast<int>(LinkTmp->AreaId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(LinkTmp[CurrentPoint].AreaId);
			break;
		}
	}
	return 0;
}

int CNode::GetLinkNodeId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(LinkTmp)
			{
				return static_cast<int>(LinkTmp->NodeId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(LinkTmp[CurrentPoint].NodeId);
			break;
		}
	}
	return 0;
}

void CNode::SetNaviPoint(int naviid)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NodeFile)
			{
				if(naviid > static_cast<int>(header->NumNaviNodes)) return;
				CurrentNavi = naviid;

				fseek(NodeFile,(sizeof(NodeHeader) + ((header->NumNodes) * sizeof(NodePath)) + (CurrentNavi * sizeof(NodeNavi))),0);
				fread(NaviTmp,sizeof(NodeNavi),1,NodeFile);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			if(naviid > static_cast<int>(header->NumNaviNodes)) return;
			CurrentNavi = naviid;
			break;
		}
	}
}

void CNode::GetNaviPos(float* x,float* y)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NaviTmp)
			{
				*x = static_cast<float>(NaviTmp->PosX) * 0.125f;
				*y = static_cast<float>(NaviTmp->PosY) * 0.125f;
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			*x = static_cast<float>(NaviTmp[CurrentNavi].PosX) * 0.125f;
			*y = static_cast<float>(NaviTmp[CurrentNavi].PosY) * 0.125f;
			break;
		}
	}
}

void CNode::GetNaviDirection(float* x,float* y)
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NaviTmp)
			{
				*x = static_cast<float>(NaviTmp->DirectionX) * 0.125f;
				*y = static_cast<float>(NaviTmp->DirectionY) * 0.125f;
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			*x = static_cast<float>(NaviTmp[CurrentNavi].DirectionX) * 0.125f;
			*y = static_cast<float>(NaviTmp[CurrentNavi].DirectionY) * 0.125f;
			break;
		}
	}
}

int CNode::GetNaviAreaId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NaviTmp)
			{
				return static_cast<int>(NaviTmp->AreaId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(NaviTmp[CurrentNavi].AreaId);
			break;
		}
	}
	return 0;
}

int CNode::GetNaviPointId()
{
	switch(read_mode)
	{
	case NODE_MODE_FILE:
		{
			if(NaviTmp)
			{
				return static_cast<int>(NaviTmp->NodeId);
			}
			break;
		}
	case NODE_MODE_MEMORY:
		{
			return static_cast<int>(NaviTmp[CurrentNavi].NodeId);
			break;
		}
	}
	return 0;
}
