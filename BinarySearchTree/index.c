#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "index.h"

KVNode *head;

KVNode *
findParentNode(Key key)
{
	KVNode *temp = head;
	KVNode *next;
	KVNode *returnNode;
	
	if(!head)
	{
		return NULL;
	}else if(head->kv.key == key)
	{
		return head;
	}
	
	while(1)
	{
		if(temp->kv.key > key)
		{
			next = temp->left;
		}else if(temp->kv.key < key)
		{
			next = temp->right;
		}
		
		
		returnNode = temp;
		
		if(next && next->kv.key != key)
		{
			temp = next;
		}
		else
		{
			return temp;
		}
	}

}

Value
copyValue(Value src)
{
	int len = 0;
	Value dest;
	
	if(src)
	{
		len = strlen(src);
	}
	
	dest = (Value)malloc(sizeof(char) * (len + 1));
	memcpy(dest, src, len);
	dest[len] = '\0';
	
	return dest;
}

KVNode *
KVToNode(Key key, Value value)
{
	KVNode *node = (KVNode *)malloc(sizeof(KVNode));
	node->kv.key = key;
	node->kv.value  = copyValue(value);
	
	node->right = NULL;
	node->left = NULL;
	
	return node;
}

KVNode *
findNode(Key key)
{
	KVNode *parent = findParentNode(key);
	
	if(head && head->kv.key == key)
	{
		return head;
	}
		
	if(parent)
	{
		if(parent->kv.key > key)
		{
			return parent->left;
		}else if(parent->kv.key < key)
		{
			return parent->right;
		}
	}
	
	return NULL;
}

void 
freeNode(KVNode *node)
{
	if(node)
	{
		if(node->kv.value)
		{
			free(node->kv.value);
		}
		free(node);
	}
}

KVNode *
findMaxNodeInLeftTree(KVNode *node)
{
	if(!node)
	{
		return NULL;
	}
	
	KVNode *left = node->left;
	
	while(left && left->right)
	{
		left = left->right;
	}
	
	return left;
}

KVNode *
findMinNodeInRightTree(KVNode *node)
{
	if(!node)
	{
		return NULL;
	}
	
	KVNode *right = node->right;
	
	while(right && right->left)
	{
		right = right->left;
	}

	return right;
}

int 
copyNode(KVNode *dest, KVNode *src)
{
	if(dest && src)
	{
		dest->kv.value = copyValue(src->kv.value);
		dest->kv.key = src->kv.key;
		return 1;
	}
	
	return 0;
}

int 
modifyNodeValue(KVNode *node, Value value)
{
	int len = 0;
	if(node)
	{
		node->kv.value = copyValue(value);
	}
	return 0;
}

Value 
returnNodeValue(KVNode *node)
{
	int len = 0;
	Value value;
	
	if(node)
	{
		if(node->kv.value)
		{
			len = strlen(node->kv.value);
		}
	
		return copyValue(node->kv.value);
	}
	
	return NULL;
}

int
put(Key key, Value value)
{
   KVNode *parent = findParentNode(key);
   KVNode *son    = KVToNode(key, value);
   
   if(parent)
   {
      if(parent->kv.key > key)
      {
         parent->left = son;
         return 1;
      }else if(parent->kv.key < key)
      {
         parent->right = son;
         return 1;
      }else
      {
		 modifyNodeValue(parent, value);
      }
   }else
   {
		if(!head)
		{
			head = son;
			return 1;
		}
   }
   return 0;
}

void
del(Key key)
{
  KVNode *node = findNode(key);
  if(!node)
  {
	return;
  }
  
  if(node->left && node->right)
  {
      KVNode *max = findMaxNodeInLeftTree(node);
      copyNode(node, max);
      del(max->kv.key);
  }else if(node->left || node->right)
  {
      KVNode *parent = findParentNode(key);
      if(parent->kv.key > key)
      {
         parent->left = node->right?node->right:node->left;
         freeNode(node);
      }else if(parent->kv.key < key)
      {
         parent->right = node->right?node->right:node->left;
         freeNode(node);
      }else
      {
		 freeNode(head);
		 head = NULL;
      }
  }else
  {
      KVNode *parent = findParentNode(key);
       if(parent->kv.key > key)
       {
          freeNode(parent->left);
          parent->left = NULL;
       }else if(parent->kv.key < key)
       {
          freeNode(parent->right);
          parent->right= NULL;
       }else
       {
			freeNode(head);
			head = NULL;
       }
  }
}

int
update(Key key, Value value)
{
   int len = 0;
   KVNode *node = findNode(key);
   return modifyNodeValue(node, value);
}

Value
get(Key key)
{
   KVNode *node = findNode(key);
   return returnNodeValue(node);
}