/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:33:11 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/01 15:36:31 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int	ft_isuint(char *str)
{
	int	n;

	if (*str < '0' || *str > '9')
		return (-1);
	n = 0;
	while (*str >= '0' && *str <= '9')
		n = 10 * n + *str++ - '0';
	if (*str != '\0')
		return (-1);
	return (n);
}

int	ft_puterror(const char *str)
{
	printf("%s", str);
	return (1);
}

void	run_gnl(int fd, int n_lines)
{
	char	*line;
	int		n_print;

	line = "";
	n_print = 0;
	while ((n_lines == -1 || n_print < n_lines) && line != NULL)
	{
		line = get_next_line(fd);
		if (line)
		{
			n_print++;
			printf("%d | ", n_print);
		}
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------\n");
	printf("Printed %d lines.\n", n_print);
	printf("BUFFER_SIZE = %lu \n", (unsigned long)BUFFER_SIZE);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		n_lines;

	fd = 0;
	n_lines = -1;
	if (argc > 1 && ft_isuint(argv[1]) != -1)
	{
		n_lines = ft_isuint(argv[1]);
		if (argc > 2)
			return (ft_puterror("Too many inputs.\n"));
	}
	else if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_puterror("Cannot read file.\n"));
		if (argc > 2 && ft_isuint(argv[2]) != -1)
			n_lines = ft_isuint(argv[2]);
		else if (argc > 2)
			return (ft_puterror("Too many inputs.\n"));
		if (argc > 3)
			return (ft_puterror("Too many inputs.\n"));
	}
	run_gnl(fd, n_lines);
	close(fd);
	return (0);
}
