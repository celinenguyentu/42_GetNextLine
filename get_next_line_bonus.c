/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/05 17:07:14 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*remove_cache(t_cachelist **caches, int fd)
{
	t_cachelist	*current;

	while (*caches && ((*caches)->fd == fd || fd == -1))
	{
		current = *caches;
		*caches = (*caches)->next;
		free(current->cache);
		free(current);
	}
	if (*caches)
		remove_cache(&((*caches)->next), fd);
	return (NULL);
}

t_cachelist	*add_to_caches(t_cachelist **caches, int fd, char const *src)
{
	t_cachelist	*current;
	t_cachelist	*cachefd;

	current = *caches;
	while (current && current->fd != fd)
		current = current->next;
	if (current)
	{
		current->cache = ft_strjoin_and_free(current->cache, src);
		if (!current->cache)
			return (remove_cache(caches, -1));
		return (*caches);
	}
	cachefd = (t_cachelist *)malloc(sizeof(t_cachelist));
	if (!cachefd)
		return (remove_cache(caches, -1));
	cachefd->fd = fd;
	cachefd->cache = ft_substr(src, 0, ft_strlen(src));
	if (!cachefd->cache)
		return (remove_cache(caches, -1));
	cachefd->next = *caches;
	*caches = cachefd;
	return (*caches);
}

t_cachelist	*get_caches(t_cachelist *caches, int fd)
{
	while (caches && caches->fd != fd)
		caches = caches->next;
	if (caches)
		return (caches);
	else
		return (NULL);
}

static char	*extract_line(t_cachelist **caches, int fd)
{
	char		*line;
	char		*new_cache;
	int			l_len;
	t_cachelist	*elem;

	elem = get_caches(*caches, fd);
	if (ft_strlen(elem->cache) == 0)
		return (remove_cache(caches, fd));
	if (ft_strchr(elem->cache, '\n'))
		l_len = ft_strchr(elem->cache, '\n') - elem->cache + 1;
	else
		l_len = ft_strlen(elem->cache);
	line = ft_substr(elem->cache, 0, l_len);
	if (!line)
		return (NULL);
	new_cache = ft_substr(elem->cache, l_len, ft_strlen(elem->cache) - l_len);
	if (!new_cache)
		return (ft_free(line));
	free(elem->cache);
	elem->cache = new_cache;
	return (line);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	int					bytes_read;
	static t_cachelist	*cachelist = NULL;
	t_cachelist			*cachefd;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	cachefd = get_caches(cachelist, fd);
	if (cachelist && cachefd && ft_strchr(cachefd->cache, '\n'))
		return (extract_line(&cachelist, fd));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!cachefd || !ft_strchr(cachefd->cache, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer));
		buffer[bytes_read] = '\0';
		if (!add_to_caches(&cachelist, fd, buffer))
			return (ft_free(buffer));
	}
	free(buffer);
	return (extract_line(&cachelist, fd));
}
