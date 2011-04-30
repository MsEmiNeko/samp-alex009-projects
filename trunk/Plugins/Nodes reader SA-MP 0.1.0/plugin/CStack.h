/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "defines.h"

struct StackMember
{
	StackMember*	last_member;
	int				integer_data;
	float			float_data;
	char*			string_data;
	unsigned short	string_len;
};

class CStack
{
public:
	CStack();
	~CStack();

	void push(unsigned int type,void* data);
	void pop(unsigned int type,void* data);
private:
	StackMember*	head_member;
};