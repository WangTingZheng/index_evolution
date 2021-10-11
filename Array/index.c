#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "index.h"

KVNum kvnum;

void
init(int num)
{
	kvnum.kv = (KV *)malloc(sizeof(KV) * num);
	kvnum.num = num;
	kvnum.add_num = 0;
}

int 
findNotSmallPos(Key key){
  int start = 0;
  int end   = kvnum.add_num - 1;
  int mid   = 0;
  
  while(start <= end)
  {
     mid = (start + end)/2;
     if(kvnum.kv[mid].key > key)
     {
        end = mid - 1;
     }else if(kvnum.kv[mid].key < key)
     {
        start = mid + 1;
     }
     else 
    {
        return mid;
     }
   }

   if(kvnum.kv[mid].key > key)
   {
		return mid;
   }
   else
   {
		return mid + 1;
   }
}

void 
updateNodeValue(int pos, Value value)
{
  int len = 0;
  free(kvnum.kv[pos].value);
  if(value)
  {
     len = strlen(value);
  }
  kvnum.kv[pos].value = (Value)malloc(sizeof(char) * (len + 1));
  memcpy(kvnum.kv[pos].value, value, len);
  kvnum.kv[pos].value[len] = '\0';
}

void
updateNode(int pos, Key key, Value value)
{
   kvnum.kv[pos].key = key;
   updateNodeValue(pos, value);
}

void
shiftNodeRight(int pos)
{
   int len = 0;
   kvnum.kv[pos + 1].key = kvnum.kv[pos].key;
   updateNodeValue(pos + 1, kvnum.kv[pos].value);
}

void
shiftNodeLeft(int pos)
{
   int len = 0;
   kvnum.kv[pos - 1].key = kvnum.kv[pos].key;
   updateNodeValue(pos - 1, kvnum.kv[pos].value);
}

void 
shiftRangeRight(int start, int end)
{
   for(int i = end; i >= start; i--)
   {
      shiftNodeRight(i);
   }
}

void 
shiftRangeLeft(int start, int end)
{
   for(int i = start; i <= end; i++)
   {
      shiftNodeLeft(i);
   }
}

int
put(Key key, Value value)
{
  if(kvnum.add_num >= kvnum.num)
  {
	return 0;
  }
  
  int pos = findNotSmallPos(key);

  if(pos < kvnum.add_num)
  {
     if(kvnum.kv[pos].key == key)
     {
       updateNodeValue(pos, value);
     }else
     {
       shiftRangeRight(pos, kvnum.add_num - 1);
       updateNode(pos, key, value);
       kvnum.add_num ++;
     }
  }else
  {
	 updateNode(kvnum.add_num, key, value);
	 kvnum.add_num ++;
  }
  
  return 1;
}

void 
del(Key key)
{
	int pos = findNotSmallPos(key);
	
	if(pos < kvnum.add_num)
	{
		if(kvnum.kv[pos].key == key)
		{
			shiftRangeLeft(pos + 1, kvnum.add_num - 1);
			kvnum.add_num --;
		}
	}
}

void
update(Key key, Value value)
{
	int pos = findNotSmallPos(key);
	int len = 0;
	
	if(pos < kvnum.add_num)
	{
		if(kvnum.kv[pos].key == key)
		{
			updateNodeValue(pos, value);
		}
	}
}

Value 
get(Key key)
{
	int pos = findNotSmallPos(key);
	int len = 0;
	Value value;
	
	if(pos < kvnum.add_num)
	{
		if(kvnum.kv[pos].key == key)
		{
			if(kvnum.kv[pos].value)
			{
				len = strlen(kvnum.kv[pos].value);
			}
			
			value = (Value)malloc(sizeof(char) * (len + 1));
			memcpy(value, kvnum.kv[pos].value, len);
			kvnum.kv[pos].value[len] = '\0';
			return value;
		}
	}
	return NULL;	
}

void
print()
{
	for(int i=0;i< kvnum.add_num; i++)
	{
		printf("Key = %d, Value = %s\n", kvnum.kv[i].key, kvnum.kv[i].value);
	}
}