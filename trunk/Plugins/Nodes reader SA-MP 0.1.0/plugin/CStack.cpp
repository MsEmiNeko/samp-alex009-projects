/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

#include "CStack.h"
#include <string.h>

CStack::CStack()
{
	head_member = 0;
}

CStack::~CStack()
{
	while(head_member != 0)
	{
		StackMember* to_delete = head_member;
		head_member = to_delete->last_member;
		if(to_delete->string_data != 0) delete to_delete->string_data;
		delete to_delete;
	}
}

void CStack::push(unsigned int type,void* data)
{
	StackMember* old_head = head_member;
	head_member = new StackMember;
	head_member->last_member = old_head;
	head_member->string_data = 0;
	switch(type)
	{
	case STACK_DATA_INT:
		{
			head_member->integer_data = *(int*)data;
			break;
		}
	case STACK_DATA_FLOAT:
		{
			head_member->float_data = *(float*)data;
			break;
		}
	case STACK_DATA_STRING:
		{
			head_member->string_len = strlen((char*)data);
			head_member->string_data = new char[head_member->string_len];
			memset(head_member->string_data,0,head_member->string_len);
			memcpy(head_member->string_data,data,head_member->string_len);
			break;
		}
	}
}

void CStack::pop(unsigned int type,void* data)
{
	if(head_member != 0)
	{
		StackMember* to_delete = head_member;
		head_member = to_delete->last_member;
		switch(type)
		{
		case STACK_DATA_INT:
			{
				*(int*)data = to_delete->integer_data;
				break;
			}
		case STACK_DATA_FLOAT:
			{
				*(float*)data = to_delete->float_data;
				break;
			}
		case STACK_DATA_STRING:
			{
				memcpy(data,to_delete->string_data,to_delete->string_len);
				delete to_delete->string_data;
				break;
			}
		}
		delete to_delete;
	}
}