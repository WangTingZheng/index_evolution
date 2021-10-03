#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "index.h"

KVNode *root;

inline static KVNode *
initNode(KVNode *node, Key key, Value value)
{
	int len = strlen(value);
	if(!node)
	{
		node = (KVNode *)malloc(sizeof(KVNode));
	}
	
	node->kv.key = key;
	
	node->kv.value = (Value)malloc(sizeof(char) * (len + 1));
	memcpy(node->kv.value, value, len);
	node->kv.value[len] = '\0';
	
	return node;
}

inline static KVNode *
newNode(Key key, Value value)
{
	KVNode *temp = (KVNode *)malloc(sizeof(KVNode));
	temp = initNode(temp, key, value);
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

inline static void
freeNode(KVNode *node)
{
	free(node->kv.value);
	free(node);
}

void 
put(Key key, Value value)
{
	KVNode *temp = root;
	int flag = 0;
	
	if(!temp)
	{
		root = newNode(key, value);
		return;
	}
	
	do
	{
		if(temp->kv.key > key)
		{
			if(temp->left)
			{
				temp = temp->left;
			}
			else
			{
				temp->left = newNode(key, value);
				flag = 1;
			}
		}else if(temp->kv.key < key)
		{
			if(temp->right)
			{
				temp = temp->right;
			}
			else
			{
				temp->right = newNode(key, value);
				flag = 1;
			}
		}else
		{
			temp = initNode(temp, key, value);
		}
	}while(!flag && temp->kv.key != key);
}

KVNode *
getSecondNode(Key key)
{
	KVNode *temp;
	KVNode *second;
	temp = root;
	second = root;
	
	if(!temp)
	{
		return NULL;
	}

	while(1)
	{
		if(temp->kv.key > key)
		{
			if(temp->left)
			{
				temp = temp->left;
				second = temp;
			}
			else
			{
				return NULL;
			}
		}
		else if(temp->kv.key < key)
		{
			if(temp->right)
			{
				temp = temp->right;
				second = temp;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return second;
		}
	}
}

KVNode * 
getNode(Key key)
{
	KVNode *node = getSecondNode(key);
	
	if(!node)
	{
		return NULL;
	}
	
	if(node->kv.key == key)
	{
		return node;
	}else if(node->left)
	{
		if(node->left->kv.key == key)
		{
			return node->left;
		}
	}else if(node->right)
	{
		if(node->right->kv.key == key)
		{
			return node->right;
		}
	}
	return NULL;
}

Value
get(Key key)
{
	KVNode *temp = getNode(key);
	if(temp)
	{
		return temp->kv.value;
	}
	
	return NULL;
}

KVNode *
findLeftSecondNode(KVNode *node)
{
	KVNode *temp = node;
	while(temp && temp->left && temp->left->left)
	{
		temp = temp->left;
	}
	
	if(temp && temp->left)
	{
		return temp;
	}
	
	return NULL;
}

void 
del(Key key)
{
	KVNode *node = getNode(key);
	KVNode *second = getSecondNode(key);
	KVNode *secondLeft;

	if(!node)
	{
		return;
	}
	
	if(node->left && node->right)
	{
		secondLeft = findLeftSecondNode(node);
		if(secondLeft)
		{
			node = initNode(node, secondLeft->left->kv.key, secondLeft->left->kv.value);
			freeNode(secondLeft->left);
		}
	}else if(node->left)
	{
		node = initNode(node, node->left->kv.key, node->left->kv.value);
		node->left = node->left->left;
		node->right = node->left->right;
	}
	else if(node->right)
	{
		node = initNode(node, node->right->kv.key, node->right->kv.value);
		node->left = node->right->left;
		node->right = node->right->right;
	}
	else
	{
		if(second->left->kv.key == key)
		{
			free(second->left);
			second->left = NULL;
		}else if(second->right->kv.key == key)
		{
			free(second->right);
			second->right = NULL;
		}
	}
}