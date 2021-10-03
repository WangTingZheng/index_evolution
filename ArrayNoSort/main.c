#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "index.h"

void
main()
{
	init(100);
	
	put(1, "a");
	put(2, "b");
	put(3, "c");
	put(4, "d");
	put(5, "e");
	
	del(3);
	
	print();
	printf("\n");
	
	del(4);
	
	update(5, "f");
		
	printf("Key = %d, Value = %s\n", 1, get(1));
	printf("Key = %d, Value = %s\n", 2, get(2));
	printf("Key = %d, Value = %s\n", 3, get(3));
	printf("Key = %d, Value = %s\n", 4, get(4));
	printf("Key = %d, Value = %s\n", 5, get(5));
}