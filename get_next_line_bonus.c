/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/22 16:07:09 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
	EXIT_ERROR
	Deletes the node corresponding to the file descriptor in the list of caches
	and frees an additional pointer.
	PARAMETER(S)
	1/	Pointer to cache
	2/	File descriptor of the node to remove
	3/	Other pointer to free
	RETURN
	Always returns NULL.
*/

static void	*exit_error(t_cache **cache, int fd, void *ptr)
{
	t_cache	*current;

	if (*cache && (*cache)->fd == fd)
	{
		current = *cache;
		*cache = (*cache)->next;
		free(current->data);
		free(current);
	}
	else if (*cache)
		exit_error(&((*cache)->next), fd, NULL);
	free(ptr);
	return (NULL);
}

/*
	ADD_CACHE
	Inserts new data copied from s to the cache corresponding to the
	specified file descriptor by appending the existing data. If no cache
	already exist, the function creates a new node to the cache list.
	PARAMETER(S)
	1/	Pointer to cache
	2/	File descriptor associated with the data to add
	3/	Pointer to the data to copy into cache
	4/	Number of characters from s to be copied into cache
	RETURN
	The function returns a pointer to the first node of the cache list if
	insertion was successful. If an error occurred, it returns NULL.
*/

static t_cache	*add_cache(t_cache **cache, int fd, char const *s, size_t len)
{
	t_cache	*current;
	t_cache	*new_cache;

	current = *cache;
	while (current && current->fd != fd)
		current = current->next;
	if (current)
	{
		current->data = ft_stradd(current->data, s, len);
		if (!current->data)
			return (exit_error(cache, fd, NULL));
		return (*cache);
	}
	new_cache = (t_cache *)malloc(sizeof(t_cache));
	if (!new_cache)
		return (exit_error(cache, fd, NULL));
	new_cache->fd = fd;
	new_cache->data = ft_substr(s, 0, len);
	if (!new_cache->data)
		return (exit_error(cache, fd, new_cache));
	new_cache->next = *cache;
	*cache = new_cache;
	return (*cache);
}

/*
	GET_DATA
	Retrieves the address of the data stored in the cache corresponding to the
	file descriptor.
	PARAMETER(S)
	1/	Pointer to the first node of the cache
	2/	File descriptor corresponding to the search
	RETURN
	A pointer to the data stored in the cache for the specified file descriptor
	is returned. If no matching file descriptor is found, it returns NULL.
*/

static char	**get_data(t_cache *cache, int fd)
{
	while (cache && cache->fd != fd)
		cache = cache->next;
	if (cache)
		return (&cache->data);
	else
		return (NULL);
}

/*
	EXTRACT_LINE
	Extracts the first line from the cache corresponding to fd, including the
	terminating newline character '\n' if found. If no newline is found, the
	full cache corresponding to the file descriptor is considered as a line. If
	the cache is empty, the function removes its node from the list of caches
	before returning NULL. After extraction, the cache is updated to contain
	only the remaining characters.
	PARAMETER(S)
	1/	Pointer to cache
	2/	File descriptor to read from
	RETURN
	The function returns the first line of the cache corresponding to the file
	descriptor. If the cache is empty or if an error occurred, it returns NULL.
*/

static char	*extract_line(t_cache **cache, int fd)
{
	char		*line;
	char		*new_data;
	int			line_len;
	char		**p_data;

	p_data = get_data(*cache, fd);
	if (ft_strlen(*p_data) == 0)
		return (exit_error(cache, fd, NULL));
	if (ft_strchr(*p_data, '\n'))
		line_len = ft_strchr(*p_data, '\n') - *p_data + 1;
	else
		line_len = ft_strlen(*p_data);
	line = ft_substr(*p_data, 0, line_len);
	if (!line)
		return (exit_error(cache, fd, NULL));
	new_data = ft_substr(*p_data + line_len, 0, ft_strlen(*p_data) - line_len);
	if (!new_data)
		return (exit_error(cache, fd, line));
	free(*p_data);
	*p_data = new_data;
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
	char				*buffer;
	int					bytes_read;
	static t_cache		*cache = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (exit_error(&cache, fd, NULL));
	if (cache && get_data(cache, fd) && ft_strchr(*get_data(cache, fd), '\n'))
		return (extract_line(&cache, fd));
	buffer = (char *)malloc((BUFFER_SIZE) * sizeof(char));
	if (!buffer)
		return (exit_error(&cache, fd, NULL));
	bytes_read = 1;
	while (bytes_read > 0 && (!get_data(cache, fd)
			|| !ft_strchr(*get_data(cache, fd), '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (exit_error(&cache, fd, buffer));
		if (!add_cache(&cache, fd, buffer, bytes_read))
			return (exit_error(&cache, fd, buffer));
	}
	free(buffer);
	return (extract_line(&cache, fd));
}
