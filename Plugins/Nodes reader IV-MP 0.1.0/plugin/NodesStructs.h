/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */


#pragma pack(1)
struct NodeHeader // 0x14
{
	unsigned long	NumNodes;
	unsigned long	NumVehicleNodes;
	unsigned long	NumPedNodes;
	unsigned long	NumLinks;
};

#pragma pack(1)
struct NodePath // 0x28
{
	unsigned long	MemAddress;
	unsigned long	Zero;
	unsigned short	AreaId;
	unsigned short	NodeId;
	unsigned long	Unknown;
	unsigned short	Unused;
	unsigned short	LinkId;
	signed short	PosX;
	signed short	PosY;
	signed short	PosZ;
	unsigned char	PathWidth;
	unsigned char	NodeType;
	unsigned long	Flags;
};

#pragma pack(1)
struct NodeLink // 0x4
{
	unsigned short	AreaId;
	unsigned short	NodeId;
	unsigned char	Unknown;
	unsigned char	Length;
	unsigned short	Flags;
};