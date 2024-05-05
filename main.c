/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:41:42 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/05 17:15:19 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("tests/linesnumber", O_RDONLY);
	fd2 = open("tests/lorem_ipsum.txt", O_RDONLY);
	line1 = "";
	line2 = "";
	while (line1 != NULL || line2 != NULL)
	{
		line1 = get_next_line(fd1);
		printf("%s", line1);
		line2 = get_next_line(fd2);
		printf("%s", line2);
		free(line1);
		free(line2);
	}
	return (0);
}
