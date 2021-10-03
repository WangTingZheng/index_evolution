#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

KVNode *head;

KVNode *
initNode(Key key, Value value)
{
	int len  = strlen(value);
	KVNode *insert = (KVNode *)malloc(sizeof(struct KVNODE));
	
	insert->kv.key = key;
	insert->kv.value = (Value)malloc(sizeof(char) * (len + 1));
	memcpy(insert->kv.value, value, len);
	insert->kv.value[len] = '\0';
	insert->next = NULL;
	
	return insert;
}

void 
put(Key key, Value value)
{
	if(head == NULL)
	{
		head = initNode(key, value);
	}else
	{
		KVNode *temp = initNode(key, value);
		temp->next = head->next;
		head->next = temp;
	}
}

Value 
get(Key key)
{
	KVNode *temp = head;
	while(temp->kv.key != key)
	{
		temp = temp->next;
	}
	
	return temp->kv.value;
}

void 
del(Key key)
{
	KVNode *temp = head; 
	KVNode *deleteNode = head;
	
	/*
	* 当找到需要删除的节点时
	*/
	while(temp && temp->kv.key == key)
	{
		head = temp->next; //将头节点保存为要删除节点的下一个节点
		free(temp->kv.value); //释放要删除节点的value空间
		free(temp); //释放要删除的节点
		if(head)
		{
			temp = head->next; //将节点移动到下一个位置，继续检查
		}
		else
		{
			temp = NULL;
		}
	}
	//此时，头节点比不可能是要删除的节点
	
	//从头节点开始，如果下一个节点存在
	while(deleteNode && deleteNode->next)
	{
		//如果下一个节点是要删除的节点
		if(deleteNode->next->kv.key == key)
		{
			temp = deleteNode->next; //保存要删除的节点
			deleteNode->next = temp->next; //更新下一个节点
			free(temp->kv.value);
			free(temp);
		}
		deleteNode = deleteNode->next;
	}
}

void 
print()
{
	KVNode *temp = head;
	while(temp != NULL)
	{
		printf("Key = %d, Value = %s\n", temp->kv.key, temp->kv.value);
		temp = temp->next;
	}
}