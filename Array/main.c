#include <stdio.h>
#include "index.h"

void
main(){
	init(100);
	
	put(1, "a");
	put(2, "b");
	put(3, "c");
	put(6, "d");
	put(5, "e");
	
	del(3);

	printf("key = %d, value = %s\n", 1, get(1));
	printf("key = %d, value = %s\n", 2, get(2));
	printf("key = %d, value = %s\n", 3, get(3));
	printf("key = %d, value = %s\n", 6, get(6));
	printf("key = %d, value = %s\n", 5, get(5));
}