/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/01 15:43:41 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
	GET_NEXT_LINE
	Reads from the file descriptor to get the next first line. The function
	reads BUFFER_SIZE characters at a time and appends the characters to the
	return line. It only appends the characters until it meets a newline or the
	end of file is reached. The remaining characters stay in the buffer for the
	next call of get_next_line. If a newline is already present in the initial
	buffer, no additional characters are read.
	PARAMETER(S)
		File descriptor to read from
	RETURN
	The function returns the next line read from the file descriptor as a
	string. If there is nothing left to be read or if an error occurred, it
	returns NULL.
*/

static void	*exit_error(char *str, void *ptr)
{
	while (*str)
		*str++ = '\0';
	free(ptr);
	return (NULL);
}

static char	*update_line(char *line, char *buffer, int bytes_read)
{
	char	*next_line;

	if (bytes_read == 0 && *line == '\0')
		return (exit_error(buffer, line));
	if (bytes_read == 0)
		return (line);
	next_line = ft_strchr(buffer, '\n');
	line = ft_strappend(line, buffer, next_line - buffer + 1);
	if (!line)
		return (exit_error(buffer, NULL));
	ft_strlcpy(buffer, next_line + 1, ft_strlen(next_line + 1) + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			bytes_read;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (exit_error(buffer, NULL));
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (exit_error(buffer, NULL));
	line[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		line = ft_strappend(line, buffer, ft_strlen(buffer));
		if (!line)
			return (exit_error(buffer, NULL));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (exit_error(buffer, line));
		buffer[bytes_read] = '\0';
	}
	return (update_line(line, buffer, bytes_read));
}
