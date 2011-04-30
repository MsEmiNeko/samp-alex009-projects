/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

// plugin
#include "stdio.h"
#include "NodesStructs.h"

class CNode
{
public:
	CNode(unsigned int mode,char* nodename);
	~CNode();

	void	GetInfo(int* nodes,int* vehnodes,int* pednodes,int* navinodes);
	// paths
	void	SetPoint(int pointid);
	void	GetPos(float* x,float* y,float* z);
	int		GetLinkId();
	int		GetAreaId();
	int		GetPointId();
	int		GetPathWidth();
	int		GetNodeType();
	int		GetLinkCount();
	int		GetTrafficLevel();
	int		IsRoadBlock();
	int		IsBoats();
	int		IsEmergency();
	int		IsNotHighway();
	int		IsSpawn();
	int		IsRoadBlock1();
	int		IsParking();
	int		IsRoadBlock2();
	// links
	void	SetLink(int linkid);
	int		GetLinkAreaId();
	int		GetLinkNodeId();
	// navi
	void	SetNaviPoint(int naviid);
	void	GetNaviPos(float* x,float* y);
	void	GetNaviDirection(float* x,float* y);
	int		GetNaviAreaId();
	int		GetNaviPointId();

private:
	FILE*			NodeFile;
	NodeHeader*		header;
	NodePath*		PathTmp;
	NodeLink*		LinkTmp;
	NodeNavi*		NaviTmp;
	unsigned int	CurrentPoint;
	unsigned int	CurrentLink;
	unsigned int	CurrentNavi;
	unsigned int	read_mode;
};

