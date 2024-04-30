/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:33:11 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/04/30 19:37:19 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int	fd1;
	int	fd2;
	int	n_call;
	
	fd1 = open("lorem_ipsum.txt", O_RDONLY);
	fd2 = open("file.txt", O_RDONLY);
	n_call = 0;

	printf("file.txt\n");
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	return (0);
}
