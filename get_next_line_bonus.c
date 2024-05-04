/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/04 19:54:53 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_cache(t_cachelist *caches, int fd)
{
	while (caches && caches->fd != fd)
		caches = caches->next;
	if (caches)
		return (caches->cache);
	else
		return (NULL);
}

t_cachelist	*new_cache(int fd, const char *str)
{
	t_cachelist		*new;
	char			*cache;

	new = (t_cachelist *)malloc(sizeof(t_cachelist));
	if (!new)
		return (NULL);
	cache = ft_substr(str, 0, ft_strlen(str));
	if (!cache)
		return (ft_free(new));
	new->fd = fd;
	new->cache = cache;
	new->next = NULL;
	return (new);
}

void	*free_caches(t_cachelist **caches)
{
	if (*caches)
	{
		if ((*caches)->next)
			free_caches(&(*caches)->next);
		free((*caches)->cache);
		free(*caches);
	}
	*caches = NULL;
	return (NULL);
}

void	add_to_caches(t_cachelist **caches, int fd, char const *src)
{
	t_cachelist	*current;

	current = *caches;
	while (current && current->fd != fd && current->next)
		current = current->next;
	if (current && current->fd == fd)
	{
		current->cache = ft_strjoin_and_free(current->cache, src);
		if (!current->cache)
		{
			free_caches(caches);
			return ;
		}
	}
	else if (current)
	{
		current->next = new_cache(fd, src);
		if (!current->cache)
		{
			free_caches(caches);
			return ;
		}
	}
	else
	{
		*caches = new_cache(fd, src);
	}
}

void	remove_cache(t_cachelist **caches, int fd)
{
	t_cachelist	*prev;
	t_cachelist	*current;

	prev = *caches;
	current = *caches;
	while (current && current->fd != fd)
	{
		prev = current;
		current = current->next;
	}
	if (current == *caches)
		*caches = current->next;
	else
		prev->next = current->next;
	free(current->cache);
	free(current);
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
	char		*cache;
	t_cachelist	*elem;

	cache = get_cache(*caches, fd);
	if (*cache == '\0')
	{
		remove_cache(caches, fd);
		return (NULL);
	}
	if (ft_strchr(cache, '\n'))
		l_len = ft_strchr(cache, '\n') - cache + 1;
	else
		l_len = ft_strlen(cache);
	line = ft_substr(cache, 0, l_len);
	if (!line)
		return (NULL);
	new_cache = ft_substr(cache, l_len, ft_strlen(cache) - l_len);
	if (!new_cache)
		return (ft_free(line));
	elem = get_caches(*caches, fd);
	free(elem->cache);
	elem->cache = new_cache;
	return (line);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	int					bytes_read;
	static t_cachelist	*cachelist = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (cachelist && get_cache(cachelist, fd) && ft_strchr(get_cache(cachelist, fd), '\n'))
		return (extract_line(&cachelist, fd));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!get_cache(cachelist, fd) || !ft_strchr(get_cache(cachelist, fd), '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer));
		buffer[bytes_read] = '\0';
		add_to_caches(&cachelist, fd, buffer);
		if (!cachelist)
			return (ft_free(buffer));
	}
	free(buffer);
	return (extract_line(&cachelist, fd));
}

/*
int	main(void)
{
	int	fd1;
	int fd2;
	char *line;

	fd1 = open("tests/linesnumber", O_RDONLY);
	fd2 = open("tests/feelinggood.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	return (0);
}
*/