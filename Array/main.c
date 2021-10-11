#include <stdio.h>
#include "index.h"

void
main(){
	init(100);
	
	put(2, "a");
	put(5, "b");
	put(1, "c");
	put(6, "d");
	put(3, "e");
	
	del(3);

	printf("key = %d, value = %s\n", 1, get(1));
	printf("key = %d, value = %s\n", 2, get(2));
	printf("key = %d, value = %s\n", 3, get(3));
	printf("key = %d, value = %s\n", 6, get(6));
	printf("key = %d, value = %s\n", 5, get(5));
	
	printf("\n");
	print();
}