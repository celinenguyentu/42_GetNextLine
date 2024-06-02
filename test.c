#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int	fd;
	char	*line;
	int		n;


	printf("RLIMIT_AS = %d\n", RLIMIT_AS);
	printf("RLIMIT_DATA = %d\n", RLIMIT_DATA);
	printf("BUFFER_SIZE = %ld\n", (long)BUFFER_SIZE);
	printf("SIZE_MAX = %lu\n", SIZE_MAX);
	printf("SSIZE_MAX = %ld\n", SSIZE_MAX);
	fd = open("tests/1char.txt", O_RDONLY);
	if (fd == -1)
		exit(1);
	n = 0;
	while (n++ < 5)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}