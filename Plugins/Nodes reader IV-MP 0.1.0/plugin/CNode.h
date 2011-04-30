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
	CNode(unsigned int mode,const char* nodename);
	~CNode();

	void	GetInfo(int* nodes,int* vehnodes,int* pednodes);
	// paths
	void	SetPoint(int pointid);
	void	GetPos(float* x,float* y,float* z);
	int		GetLinkId();
	int		GetAreaId();
	int		GetPointId();
	int		GetPathWidth();
	int		GetNodeType();
	int		GetFlags();
	// links
	void	SetLink(int linkid);
	int		GetLinkAreaId();
	int		GetLinkNodeId();
	int		GetLinkLength();
	int		GetLinkFlags();

private:
	FILE*			NodeFile;
	NodeHeader*		header;
	NodePath*		PathTmp;
	NodeLink*		LinkTmp;
	unsigned int	CurrentPoint;
	unsigned int	CurrentLink;
	unsigned int	read_mode;
};

