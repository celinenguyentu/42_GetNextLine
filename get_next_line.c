/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/08 15:03:46 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	EXIT_ERROR
	Frees cache and other pointer. Cache is reinitialized to NULL.
	PARAMETER(S)
	1/	Pointer to cache
	2/	Other pointer to free
	RETURN
	Always returns NULL.
*/

static void	*exit_error(char **cache, void *ptr)
{
	free(*cache);
	*cache = NULL;
	free(ptr);
	return (NULL);
}

/*
	EXTRACT_LINE
	Extracts the first line from the cache, including the terminating newline
	character '\n' if found. If no newline is found, the full cache is
	considered as a line. If the cache is empty, the function reinitializes it
	to NULL before returning NULL. After extraction, the cache is updated to
	contain only the remaining characters.
	PARAMETER(S)
		Pointer to cache
	RETURN
	The function returns the first line of the cache. If the cache is empty or
	if an error occurred, it returns NULL.
*/

static char	*extract_line(char **cache)
{
	char	*line;
	char	*new_cache;
	int		line_len;

	if (**cache == '\0')
		return (exit_error(cache, NULL));
	if (ft_strchr(*cache, '\n'))
		line_len = ft_strchr(*cache, '\n') - *cache + 1;
	else
		line_len = ft_strlen(*cache);
	line = ft_substr(*cache, 0, line_len);
	if (!line)
		return (exit_error(cache, NULL));
	new_cache = ft_substr(*cache + line_len, 0, ft_strlen(*cache) - line_len);
	if (!new_cache)
		return (exit_error(cache, line));
	free(*cache);
	*cache = new_cache;
	return (line);
}

/*
	GET_NEXT_LINE
	Reads from the file descriptor to get the next first line. The function
	reads BUFFER_SIZE characters at a time and stores them in a cache until a
	newline character is read or the end of the file is reached. If a newline
	is already present in the initial cache, no additional characters are read.
	The first line is extracted from the cache.
	PARAMETER(S)
		File descriptor to read from
	RETURN
	The function returns the next line read from the file descriptor as a
	string. If there is nothing left to be read or if an error occurred, it
	returns NULL.
*/

char	*get_next_line(int fd)
{
	char		*buffer;
	int			bytes_read;
	static char	*cache = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (exit_error(&cache, NULL));
	if (cache && ft_strchr(cache, '\n'))
		return (extract_line(&cache));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (exit_error(&cache, NULL));
	bytes_read = 1;
	while (bytes_read > 0 && (!cache || !ft_strchr(cache, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (exit_error(&cache, buffer));
		buffer[bytes_read] = '\0';
		cache = ft_strjoin_and_free(cache, buffer);
		if (!cache)
			return (exit_error(&cache, buffer));
	}
	free(buffer);
	return (extract_line(&cache));
}
