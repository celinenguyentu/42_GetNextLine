/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:41:42 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/08 15:43:48 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	
#if defined(OPEN_MAX)
	printf("OPEN_MAX = %d\n", OPEN_MAX);
#endif
#if defined(FOPEN_MAX)
	printf("FOPEN_MAX = %d\n", FOPEN_MAX);
#endif
#if defined(RLIMIT_NOFILE)
	printf("RLIMIT_NOFILE = %d\n", RLIMIT_NOFILE);
#endif
#if defined(_SC_OPEN_MAX)
	printf("_SC_OPEN_MAX = %d\n", _SC_OPEN_MAX);
#endif

	fd1 = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd1 == -1)
		printf("Error creating fd1\n");
	write(fd1, "1\n", 2);
	close(fd1);
	fd2 = open("2.txt", O_CREAT);
	if (fd2 == -1)
		printf("Error creating fd2\n");
	write(fd2, "2\n", 2);
	close(fd2);
/*
	fd1 = open("1.txt", O_RDONLY);
	if (fd1 == -1)
		printf("Error reading fd1\n");
	fd2 = open("2.txt", O_RDONLY);
	if (fd2 == -1)
		printf("Error reading fd2\n");*/
	line1 = "";
	line2 = "";
	while (line1 != NULL || line2 != NULL)
	{
		line1 = get_next_line(fd1);
		printf("Output : %s", line1);
		line2 = get_next_line(fd2);
		printf("Output : %s", line2);
		free(line1);
		free(line2);
	}
/*	line1 = get_next_line(fd3);
	printf("[1] %s", line1);
	free(line1);
	char c = 0; read(fd3, &c, 1);
	printf("[2] (check : %d)\n", (c == '1'));
	line1 = get_next_line(fd3);
	printf("[3] %s", line1);
	free(line1);*/
	return (0);
}
