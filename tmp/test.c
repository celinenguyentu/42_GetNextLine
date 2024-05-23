#include <stdio.h>
#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 42
#endif

int main(void)
{
	if (BUFFER_SIZE > 1)
		printf("yoyo");
	return (0);
}