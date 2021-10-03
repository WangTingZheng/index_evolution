#ifndef __INDEX_H
#define __INDEX_H

typedef int Key;
typedef char *Value;

typedef struct KVNODE KVNode;

typedef struct{
	Key key;
	Value value;
}KV;

struct KVNODE
{
	KV kv;
	KVNode *left;
	KVNode *right;
};

void put(Key key, Value value);
Value get(Key key);
void del(Key key);

#endif