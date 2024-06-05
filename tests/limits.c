#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
//#include "get_next_line_bonus.h"
#include <sys/resource.h>

int	main(void)
{
	int		fds[10496];
	char	*line;
	int		n;

	printf("RLIMIT_AS = %d\n", RLIMIT_AS);
	printf("RLIMIT_DATA = %d\n", RLIMIT_DATA);
	//printf("BUFFER_SIZE = %ld\n", (long)BUFFER_SIZE);
	//printf("SIZE_MAX = %lu\n", SIZE_MAX);
	printf("SSIZE_MAX = %ld\n", SSIZE_MAX);
	//printf("OPEN_MAX = %d\n", OPEN_MAX);
	printf("FOPEN_MAX = %d\n", FOPEN_MAX);
	printf("_SC_OPEN_MAX = %ld\n", sysconf(_SC_OPEN_MAX));
	printf("_POSIX_OPEN_MAX = %d\n", _POSIX_OPEN_MAX);
	printf("RLIMIT_NOFILE = %d\n", RLIMIT_NOFILE);

	struct rlimit open_files_limit;
	struct rlimit limit_as;
    struct rlimit limit_data;

	// Get the current limits on the number of open files
    if (getrlimit(RLIMIT_NOFILE, &open_files_limit) == 0) {
        printf("Open files limit:\n");
        printf("  Soft limit: %ld\n", (long)open_files_limit.rlim_cur);
        printf("  Hard limit: %ld\n", (long)open_files_limit.rlim_max);
    } else {
        perror("getrlimit RLIMIT_NOFILE");
        return EXIT_FAILURE;
    }

    // Get the current limits on address space
    if (getrlimit(RLIMIT_AS, &limit_as) == 0) {
        printf("Address space limit (RLIMIT_AS):\n");
        printf("  Soft limit: %ld bytes\n", (long)limit_as.rlim_cur);
        printf("  Hard limit: %ld bytes\n", (long)limit_as.rlim_max);
    } else {
        perror("getrlimit RLIMIT_AS");
    }

    // Get the current limits on data segment size
    if (getrlimit(RLIMIT_DATA, &limit_data) == 0) {
        printf("Data segment size limit (RLIMIT_DATA):\n");
        printf("  Soft limit: %ld bytes\n", (long)limit_data.rlim_cur);
        printf("  Hard limit: %ld bytes\n", (long)limit_data.rlim_max);
    } else {
        perror("getrlimit RLIMIT_DATA");
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
