#include <stdio.h>
#include "index.h"

void
main()
{
	put(4, "a");
	put(2, "b");
	put(1, "c");
	put(3, "d");
	
	del(3);
	
	printf("key = %d, value %s\n", 1, get(1));
	printf("key = %d, value %s\n", 2, get(2));
	printf("key = %d, value %s\n", 3, get(3));
	printf("key = %d, value %s\n", 4, get(4));
}