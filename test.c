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


	printf("RLIMIT_DATA = %d\n", RLIMIT_DATA * 1000000000);
	printf("SIZE_MAX : %lu\n", LONG_MAX);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	fd = open("tests/linesnumber", O_RDONLY);
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