/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:33:11 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/06 20:34:53 by cnguyen-         ###   ########.fr       */
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
	int		l_print;
	int		l_total;

	line = "";
	l_total = 0;
	l_print = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (n_lines == -1 || n_lines > 0)
		{
			printf("%s", line);
			if (line)
				l_print++;
			if (n_lines != -1)
				n_lines--;
		}
		if (line)
			l_total++;
		free(line);
	}
	printf("\n--------------------------------------------------\n");
	printf("Printed %d lines out of %d.\n", l_print, l_total);
	printf("BUFFER_SIZE = %lu / %lu\n", (unsigned long)BUFFER_SIZE, LONG_MAX);
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
