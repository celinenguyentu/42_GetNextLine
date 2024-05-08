/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/08 00:25:35 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
	CLEAR_CACHE
	Deletes a node from cache or complete cache. The node corresponding to data
	backup read from the file descriptor fd is removed from the cache list if
	fd is a valid file descriptor. If fd is -1, the function deletes all nodes
	and sets the pointer pointing to the beginning of the list to NULL.
	PARAMETER(S)
	1/	A pointer to the first node of the list representing the cache
	2/	The file descriptor corresponding to the node to delete. If the
	parameter is set to -1, the function deletes all the nodes, thus the full
	cache.
	RETURN
	Always returns NULL.
*/

static void	*clear_cache(t_cache **cache, int fd)
{
	t_cache	*current;

	while (*cache && ((*cache)->fd == fd || fd == -1))
	{
		current = *cache;
		*cache = (*cache)->next;
		free(current->data);
		free(current);
	}
	if (*cache)
		clear_cache(&((*cache)->next), fd);
	return (NULL);
}

static t_cache	*add_to_cache(t_cache **cache, int fd, char const *src)
{
	t_cache	*current;
	t_cache	*new_cache;

	current = *cache;
	while (current && current->fd != fd)
		current = current->next;
	if (current)
	{
		current->data = ft_strjoin_and_free(current->data, src);
		if (!current->data)
			return (clear_cache(cache, -1));
		return (*cache);
	}
	new_cache = (t_cache *)malloc(sizeof(t_cache));
	if (!new_cache)
		return (clear_cache(cache, -1));
	new_cache->fd = fd;
	new_cache->data = ft_substr(src, 0, ft_strlen(src));
	if (!new_cache->data)
		return (clear_cache(cache, -1));
	new_cache->next = *cache;
	*cache = new_cache;
	return (*cache);
}

static char	**get_data(t_cache *cache, int fd)
{
	while (cache && cache->fd != fd)
		cache = cache->next;
	if (cache)
		return (&cache->data);
	else
		return (NULL);
}

static char	*extract_line(t_cache **cache, int fd)
{
	char		*line;
	char		*new_data;
	int			line_len;
	char		**p_data;

	p_data = get_data(*cache, fd);
	if (ft_strlen(*p_data) == 0)
		return (clear_cache(cache, fd));
	if (ft_strchr(*p_data, '\n'))
		line_len = ft_strchr(*p_data, '\n') - *p_data + 1;
	else
		line_len = ft_strlen(*p_data);
	line = ft_substr(*p_data, 0, line_len);
	if (!line)
		return (NULL);
	new_data = ft_substr(*p_data + line_len, 0, ft_strlen(*p_data) - line_len);
	if (!new_data)
		return (ft_free(line));
	free(*p_data);
	*p_data = new_data;
	return (line);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	int					bytes_read;
	static t_cache		*cache = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (cache && get_data(cache, fd) && ft_strchr(*get_data(cache, fd), '\n'))
		return (extract_line(&cache, fd));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!get_data(cache, fd)
			|| !ft_strchr(*get_data(cache, fd), '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer));
		buffer[bytes_read] = '\0';
		if (!add_to_cache(&cache, fd, buffer))
			return (ft_free(buffer));
	}
	free(buffer);
	return (extract_line(&cache, fd));
}
