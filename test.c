#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int		fds[10496];
	char	*line;
	int		n;

	printf("RLIMIT_AS = %d\n", RLIMIT_AS);
	printf("RLIMIT_DATA = %d\n", RLIMIT_DATA);
	//printf("BUFFER_SIZE = %ld\n", (long)BUFFER_SIZE);
	printf("SIZE_MAX = %lu\n", SIZE_MAX);
	printf("SSIZE_MAX = %ld\n", SSIZE_MAX);
	printf("OPEN_MAX = %d\n", OPEN_MAX);
	printf("FOPEN_MAX = %d\n", FOPEN_MAX);
	printf("_SC_OPEN_MAX = %ld\n", sysconf(_SC_OPEN_MAX));
	printf("_POSIX_OPEN_MAX = %d\n", _POSIX_OPEN_MAX);
	printf("RLIMIT_NOFILE = %d\n", RLIMIT_NOFILE);

	struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Soft limit: %llu\n", limit.rlim_cur);
        printf("Hard limit: %llu\n", limit.rlim_max);
    } else {
        perror("getrlimit");
    }
	
/*
	int i;
	for (i = 0; i < 10496; i++)
	{
		fds[i] = open("tests/1char.txt", O_RDONLY);
		if (fds[i] == -1)
		{
			printf("Error opening %dth file.\n", i + 1);
			break;
		}
		line = get_next_line(fds[i]);
		printf("file %i (fd = %i): %s\n", i + 1, fds[i], line);
		free(line);
	}
	for (int j = 0; j <= i; j++) {
        close(fds[j]);
    }
*/
/*
	int fd = open("tests/1char.txt", O_RDONLY);
	if (fd == -1)
		exit(1);
	n = 0;
	while (n++ < 5)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	*/
	return (0);
}