#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index.h"

KVNum kvnum;

void
init(int num)
{	
	kvnum.kv = (KV *)malloc(sizeof(KV) * num);
	kvnum.num = num;
	kvnum.add_num = 0;
}

KV
initKV(Key key, Value value)
{
	KV kv;
	int len = 0;
	
	kv.key = key;
	len = strlen(value);
	kv.value = (Value)malloc(sizeof(char) * (len + 1));
	memcpy(kv.value, value, len);
	kv.value[len] = '\0';

	return kv;
}

int
put(Key key, Value value)
{
	if(kvnum.add_num >= kvnum.num)
	{
		printf("Array is fulled.\n");
		return 0;
	}
	kvnum.kv[kvnum.add_num] = initKV(key, value);
	kvnum.add_num ++;
	
	return 1;
}

Value
get(Key key)
{
	Value r_value;
	int len = 0;
	
	for(int i = 0;i < kvnum.add_num; i++)
	{
		if(kvnum.kv[i].key == key)
		{
			len = strlen(kvnum.kv[i].value);
			r_value = (Value)malloc(sizeof(char) * (len + 1));
			memcpy(r_value, kvnum.kv[i].value, len);
			r_value[len] = '\0';
			return r_value;
		}
	}
	
	printf("The value of key %d is not exist!\n", key);
	return NULL;
}

int 
del(Key key)
{
	int len = 0;
	
	for(int i = 0;i < kvnum.add_num; i++)
	{
		if(kvnum.kv[i].key == key)
		{
			kvnum.kv[i].key = kvnum.kv[kvnum.add_num - 1].key;
			
			if(kvnum.kv[kvnum.add_num - 1].value)
			{
				len = strlen(kvnum.kv[kvnum.add_num - 1].value);
			}
			else
			{
				len = 0;
			}
			
			kvnum.kv[i].value = (Value)malloc(sizeof(char) * (len + 1));
			memcpy(kvnum.kv[i].value, kvnum.kv[kvnum.add_num - 1].value, len);
			kvnum.kv[i].value[len] = '\0';
			kvnum.add_num--;
			
			return 1;
		}
	}
	
	return 0;
}

void 
print()
{
	for(int i = 0;i < kvnum.add_num; i++)
	{
		printf("Key =  %d, Value = %s\n", kvnum.kv[i].key, kvnum.kv[i].value);
	}
}