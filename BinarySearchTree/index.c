#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "index.h"

KVNode *head;

/*
* 找到键为key的节点的父节点
*/
KVNode *
findParentNode(Key key)
{
	KVNode *temp = head;
	KVNode *next;
	
	//如果头节点为空，则说明查不到，直接返回空
	if(!head)
	{
		return NULL;
	//如果头节点就是要找的节点，那就没有父节点，直接返回头节点本身
	}else if(head->kv.key == key)
	{
		return head;
	}
	
	while(1)
	{
		//如果要查询的节点在当前节点temp左边，则更新next指针
		if(temp->kv.key > key)
		{
			next = temp->left;
		//在右边同理
		}else if(temp->kv.key < key)
		{
			next = temp->right;
		}
				
		//如果子节点存在且不是要查找的节点
		if(next && next->kv.key != key)
		{
			//继续更新当前节点
			temp = next;
		}
		else //如果子节点不存在或者子节点是要查找的节点
		{
			return temp;//返回当前节点，即为子节点的父节点
		}
	}
}

/*
* 拷贝一份src字符串返回
*/
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

/*
* 将键值对包装成一个节点
*/
KVNode *
KVToNode(Key key, Value value)
{
	//申请节点空间
	KVNode *node = (KVNode *)malloc(sizeof(KVNode));
	node->kv.key = key; //赋值键
	node->kv.value  = copyValue(value); //赋值值
	
	//置空左右指针
	node->right = NULL;
	node->left = NULL;
	
	return node;
}

/*
* 找到键为key的节点
*/
KVNode *
findNode(Key key)
{
	//找到其父节点
	KVNode *parent = findParentNode(key);
	
	// 如果头节点存在且为要查找的节点时，直接返回头节点
	// 因为头节点是无父节点的
	if(head && head->kv.key == key)
	{
		return head;
	}
	
	// 如果父节点存在
	if(parent)
	{
		// 如果节点在父节点左侧，就返回左节点
		if(parent->kv.key > key)
		{
			return parent->left;
		// 一样的道理
		}else if(parent->kv.key < key)
		{
			return parent->right;
		}
	}
	
	return NULL;
}

/*
* 释放节点空间
*/
void 
freeNode(KVNode *node)
{
	if(node)
	{
		if(node->kv.value)
		{
			// 释放节点字符串空间
			free(node->kv.value);
		}
		
		//释放节点空间
		free(node);
	}
}

/*
* 返回节点左子树的最大（最右）节点
*/
KVNode *
findMaxNodeInLeftTree(KVNode *node)
{
	// 如果节点不存在，直接返回NULL
	if(!node)
	{
		return NULL;
	}
	
	KVNode *left = node->left; //拿到左子树的头节点
	
	// 当左子树的头节点存在且其右节点存在时
	while(left && left->right)
	{
		// 更新到右节点
		left = left->right;
	}
	
	// 当节点不存在或者节点的右子节点不存在（此时当前节点为最右节点）
	return left; //返回这个节点
}

/*
* 返回右子树的最小（左）节点，同上
*/
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

/*
* 拷贝一个节点到另外一个节点
*/
int 
copyNode(KVNode *dest, KVNode *src)
{
	// 两个节点都存在才行
	if(dest && src)
	{
		// 拷贝键值对
		dest->kv.value = copyValue(src->kv.value);
		dest->kv.key = src->kv.key;
		return 1;
	}
	
	return 0;
}

/*
* 修改节点的值，会复制传入的value
*/
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


/*
* 返回节点的值，会复制一份返回，对返回值的修改不会影响节点内的值
*/
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
   
   if(parent) //如果父节点存在
   {
      if(parent->kv.key > key) //如果要添加的节点在父节点的左子树上
      {
         parent->left = son; //增加节点
         return 1;
      }else if(parent->kv.key < key)
      {
         parent->right = son;
         return 1;
      }else //父节点本身就是要添加的位置
      {
		 // 修改父节点的值
		 modifyNodeValue(parent, value);
      }
   }else //如果父节点为空
   {
		if(!head) //如果头节点不存在
		{
			head = son; //把新的节点作为头节点
			return 1;
		}else if(head->kv.key == key)
		{
			modifyNodeValue(parent, value);
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
  
  // 如果要删除的节点有两个子节点
  if(node->left && node->right)
  {
	  // 找到左子树的最右节点
      KVNode *max = findMaxNodeInLeftTree(node);
      copyNode(node, max); // 拷贝这个节点到要删除的节点
      del(max->kv.key); //删除最右节点
  // 如果要删除的节点有一个子节点
  }else if(node->left || node->right)
  {
	  // 找到要删除的节点父节点
      KVNode *parent = findParentNode(key);
      //如果要删除的节点在父节点的左侧
      if(parent->kv.key > key)
      {
		// 父节点的左子树指向要删除节点的子节点
         parent->left = node->right?node->right:node->left;
         // 释放要删除的节点的空间
         freeNode(node);
      }else if(parent->kv.key < key)
      {
         parent->right = node->right?node->right:node->left;
         freeNode(node);
      }else //如果父节点即是要删除的节点，那只有一种可能性，这个节点是head节点
      {
         //释放头节点空间
		 freeNode(head);
		 //置头节点指针为空
		 head = NULL;
      }
  }else //如果要删除的节点无子节点
  {
	  // 找到要删除节点的父节点
      KVNode *parent = findParentNode(key);
      if(parent->kv.key > key) //如果在左子树
      {
         //释放左子树空间，置左指针为空
         freeNode(parent->left);
         parent->left = NULL;
      }else if(parent->kv.key < key)
      {
         freeNode(parent->right);
         parent->right= NULL;
      }else //父节点本身就是要删除的节点
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
   KVNode *node = findNode(key); //找到节点
   return modifyNodeValue(node, value); //修改节点的值
}

Value
get(Key key)
{
   KVNode *node = findNode(key); //找到节点
   return returnNodeValue(node); //返回节点的值
}