/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:44:01 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/02 21:48:40 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	ft_puterror(const char *str)
{
	printf("Cannot read file \"%s\".\n", str);
	return (1);
}

size_t	ft_stringlength(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	end_of_all_files(int *end_of_file, int nb_files)
{
	int	end;
	int	idx;
	
	end = 1;
	idx = 0;
	while (idx < nb_files)
	{
		if (end_of_file[idx] == 0)
		{
			end = 0;
			break ;
		}
		idx++;
	}
	return (end);
}

int	main(int argc, char **argv)
{
	int		filedescriptors[argc - 1]; 
	int		end_of_file[argc - 1];
	char	*line;
	int		idx;
	int		line_no;

	line = "";
	if (argc == 1)
	{
		while (line != NULL)
		{
			line = get_next_line(0);
			printf("%s", line);
			free(line);
		}
		return (0);
	}
	idx = 0;
	while (idx < argc - 1)
	{
		filedescriptors[idx] = open(argv[idx + 1], O_RDONLY);
		if (filedescriptors[idx] == -1)
			return (ft_puterror(argv[idx + 1]));
		end_of_file[idx] = 0;
		idx++;
	}
	line_no = 1;
	while (!end_of_all_files(end_of_file, argc - 1))
	{
		idx = 0;
		while (idx < argc - 1)
		{
			line = get_next_line(filedescriptors[idx]);
			printf("%d | %s", line_no, line);
			if (!line)
			{
				printf("\n");
				end_of_file[idx] = 1;
			}
			else if (line[ft_stringlength(line) - 1] != '\n')
				printf("$\n");
			free(line);
			idx++;
		}
		line_no++;
	}
	idx = 0;
	while (idx < argc - 1)
	{
		close(filedescriptors[idx]);
		idx++;
	}
	printf("\n--------------------------------------------------\n");
	printf("Printed %d alternated files : ", argc - 1);
	idx = 0;
	while (idx < argc - 1)
	{
		printf("%s", argv[idx + 1]);
		if (idx == argc - 2)
			printf(".\n");
		else
			printf(", ");
		idx++;
	}
	printf("BUFFER_SIZE = %lu\n", (unsigned long)BUFFER_SIZE);
	return (0);
}