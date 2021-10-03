#include <stdio.h>
#include "index.h"

void
main()
{
	put(1, "a");
	put(3, "b");
	put(4, "c");
	put(2, "e");
	put(5, "f");
	
	printf("Key = %d, Value = %s\n", 1, get(1));
	printf("Key = %d, Value = %s\n", 3, get(3));
	printf("Key = %d, Value = %s\n", 4, get(4));
	printf("Key = %d, Value = %s\n", 2, get(2));
	printf("Key = %d, Value = %s\n", 5, get(5));
	
	del(1);
	del(3);
	del(4);
	del(2);
	del(5);
	
	printf("\n");
	print();
}