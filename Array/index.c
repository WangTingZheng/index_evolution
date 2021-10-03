#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "index.h"

KVNum kvnum;

void 
init(int num)
{
	kvnum.kv = (KV *)malloc(sizeof(KV) * num);
	kvnum.num = num;
	kvnum.add_num = 0;
}

/*
* 复制一个value然后返回
* value@Value: 需要复制的值
* return: 复制好的值
*/
Value
copyValue(Value value)
{
	Value t_value;
	int len = 0;
	
	if(value)
	{
		len = strlen(value);
	}
	
	t_value = (Value)malloc(sizeof(char) * (len + 1));
	memcpy(t_value, value, len);
	t_value[len] = '\0';
	
	return t_value;
}


int 
reinitValue(int pos, Value value)
{
	if(pos >= kvnum.num)
	{
		printf("There is not position on %d\n", pos);
		return 0;
	}
	
	free(kvnum.kv[pos].value);
	kvnum.kv[pos].value = copyValue(value);
	return 1;
}

int 
getNotSmallPosition(Key key)
{
	int start = 0;
	int end   = kvnum.add_num - 1;
	int mid   = (start + end) >> 1;
	
	do
	{
		if(kvnum.kv[mid].key > key)
		{
			end   = mid - 1;
		}
		else if(kvnum.kv[mid].key < key)
		{
		    start = mid + 1;
		}
		else
		{
			return mid;
		}
		
		mid = (start + end) >> 1;
	}
	while(start <= end);
	
	return mid + 1;
}

int
reinitNode(int pos, Key key, Value value)
{
	if(reinitValue(pos, value))
	{
		kvnum.kv[pos].key = key;
	}
	else
	{
		return 0;
	}
}

void
reinitNodeFromNode(int dist, int origin)
{
	reinitNode(dist, kvnum.kv[origin].key, kvnum.kv[origin].value);
}

void
moveRightNode(int start, int end)
{
	if(end > kvnum.num)
	{
		printf("Node can not be move\n");
		return;
	}
	
	for(int i = end + 1; i > start; i--)
	{
		reinitNodeFromNode(i, i - 1);
	}
}

void
moveLeftNode(int start, int end)
{
	if(start <= 1)
	{
		printf("Node can not be move\n");
		return;
	}
	
	for(int i = start; i <= end; i++)
	{
		reinitNodeFromNode(i - 1, i);
	}
}

int 
put(Key key, Value value)
{
	int len = 0;
	int pos = getNotSmallPosition(key);
	
	if(kvnum.kv[pos].key == key)
	{
		reinitNode(pos, key, value);
	}
	else if(pos >= kvnum.add_num)
	{
		reinitNode(kvnum.add_num, key, value);
	}else
	{
		moveRightNode(pos, kvnum.add_num - 1);
		reinitNode(pos, key, value);
	}
	
	kvnum.add_num ++;
}

Value 
get(Key key)
{
	int pos = getNotSmallPosition(key);
	
	if(pos < kvnum.add_num && kvnum.kv[pos].key == key)
	{
		Value t_value = copyValue(kvnum.kv[pos].value);
		return t_value;
	}
	
	return NULL;
}

void
del(Key key)
{
	int pos = getNotSmallPosition(key);
	if(pos < kvnum.add_num && kvnum.kv[pos].key == key)
	{
		moveLeftNode(pos + 1, kvnum.add_num);
	}
	
	kvnum.add_num --;
}

void 
print()
{
	for(int i = 0;i < kvnum.add_num; i++)
	{
		printf("Key =  %d, Value = %s\n", kvnum.kv[i].key, kvnum.kv[i].value);
	}
}