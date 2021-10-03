#ifndef __INDEX_H
#define __INDEX_H

typedef int Key;
typedef char *Value;

typedef struct
{
	Key key;
	Value value;
}KV;

typedef struct
{
	KV *kv;
	int num;
    int add_num;
}KVNum;

void init(int num);
int put(Key key, Value value);
Value get(Key key);
int del(Key key);
void print();

#endif