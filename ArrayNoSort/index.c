#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index.h"


/*
* 复制一个value然后返回
* value@Value: 需要复制的值
* return: 复制好的值
*/
inline static Value
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

Value
getValueFromArray(int pos)
{
	if(pos >= kvnum.num)
	{
		printf("Pos %d out of array size.\n", pos);
		return NULL;
	}
	
	return copyValue(kvnum.kv[pos].value);
}

int
putValueToArray(int pos, Value value)
{
	if(pos >= kvnum.num)
	{
		printf("Pos %d out of array size.\n", pos);
		return 0;
	}
	kvnum.kv[pos].value = copyValue(value);
	return 1;
}

int
putKVToArray(int pos, Key key, Value value)
{
	if(pos >= kvnum.num)
	{
		printf("Pos %d out of array size.\n", pos);
		return 0;
	}
	
	kvnum.kv[pos].key = key;
	putValueToArray(pos, value);
	
	return 1;
}

KV
getKVFromArray(int pos)
{
	KV kv;
	kv.key = kvnum.kv[pos].key;
	kv.value = getValueFromArray(pos);
}

int 
putKVToKV(int dest, int src)
{
	Key key = kvnum.kv[src].key;
	Value value = getValueFromArray(src);
	return putKVToArray(dest, key, value);
}


/*
* 初始化长度为num的数组
* num@int: 数组长度
* return: 
*  -1 : 初始化失败，申请内存失败
*   0 : 数组长度小于等于0，无法初始化
*   1 ：初始化成功
*/
int
init(int num)
{	
	if(num <= 0)
	{
		printf("Length of the array is smaller than 0!\n");
		return 0;
	}
	kvnum.kv = (KV *)malloc(sizeof(KV) * num);
	
	if(kvnum.kv == NULL)
	{
		printf("KV num malloc failed!\n");
		return -1;
	}
	
	kvnum.num = num;
	kvnum.add_num = 0;
	
	return 1;
}

/*
* 放入一个键值对
* key@Key: 键
* value@Value: 值
* return 
*   0:数组满了，无法放入
*   1:放入成功
*/
int
put(Key key, Value value)
{
	if(kvnum.add_num >= kvnum.num)
	{
		printf("Array is fulled.\n");
		return 0;
	}
	
	putKVToArray(kvnum.add_num, key, value);
	kvnum.add_num ++;
	
	return 1;
}

/*
* 更新一个已经存在的键值对，如果不存在则插入
* key@Key: 键
* value@Value: 值
* return
*   0:要更新的键值对不存在，直接放入
*   1:要更新的键值对存在，更新其值，形参可以随意处理
*/
int
update(Key key, Value value)
{
	Value r_value;
	int len = 0;
	
	for(int i = 0;i < kvnum.add_num; i++)
	{
		if(kvnum.kv[i].key == key)
		{
			putValueToArray(i, value);
			return 1;
		}
	}
	
	put(key, value);
	return 0;
}

/*
* 获得key所对应的value
* key@Key:要获得值的key
* return
*   r_value: 取得key对应的值
*   NULL: 没找到，返回空
*/
Value
get(Key key)
{
	Value r_value;
	int len = 0;
	
	for(int i = 0;i < kvnum.add_num; i++)
	{
		if(kvnum.kv[i].key == key)
		{
			return getValueFromArray(i);
		}
	}
	
	printf("The value of key %d is not exist!\n", key);
	return NULL;
}

/*
* 删除key对应的节点
* key@Key: 键
* return
*  1:能找到且已删除
*  0:没找到不用删除
*/
int 
del(Key key)
{	
	for(int i = 0;i < kvnum.add_num; i++)
	{
		if(kvnum.kv[i].key == key)
		{
			putKVToKV(i, kvnum.add_num - 1);
			kvnum.add_num--;

			return 1;
		}
	}
	
	return 0;
}

/*
* 打印数组里的键值对
*/
void 
print()
{
	for(int i = 0; i < kvnum.add_num; i++)
	{
		printf("Key =  %d, Value = %s\n", kvnum.kv[i].key, kvnum.kv[i].value);
	}
}