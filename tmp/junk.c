/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:44:15 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/02 18:43:46 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* MANDATORY PART */
/* Using strlcat to merge cache and new content from read buffer when bytes_read > 0 */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_idx;
	size_t	src_idx;

	dst_idx = 0;
	src_idx = 0;
	if (dst || dstsize != 0)
	{
		while (dst[dst_idx] && dst_idx < dstsize)
			dst_idx++;
		if (dst_idx < dstsize)
		{
			while (src[src_idx] && dst_idx + src_idx < dstsize - 1)
			{
				dst[dst_idx + src_idx] = src[src_idx];
				src_idx++;
			}
			dst[dst_idx + src_idx] = '\0';
		}
	}
	while (src[src_idx])
		src_idx++;
	return (dst_idx + src_idx);
}

char	*ft_strexpand(char *str, int size)
{
	char	*new_str;
	int		idx;

	if (str)
		new_str = malloc((ft_strlen(str) + size) * sizeof(char));
	else
		new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (NULL);
	idx = 0;
	while (str && str[idx])
	{
		new_str[idx] = str[idx];
		idx++;
	}
	new_str[idx] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			bytes_read;
	static char	*cache = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (cache && ft_find_newline(cache) != -1)
		return (extract_line(&cache));
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!cache || ft_find_newline(cache) == -1))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read > 0)
		{
			cache = ft_strexpand(cache, bytes_read + 1);
			ft_strlcat(cache, buffer, ft_strlen(cache) + bytes_read + 1);
		}
	}
	free(buffer);
	return (extract_line(&cache));
}

/* Using strlcpy to copy cache into line and new_cache */
/* + free and clear cache when it's empty before return */

char	*extract_line(char **cache)
{
	char	*line;
	char	*new_cache;
	int		l_len;

	if (!*cache || **cache == '\0')
		return (NULL);
	if (ft_strchr(*cache, '\n'))
		l_len = ft_strchr(*cache, '\n') - *cache + 1;
	else
		l_len = ft_strlen(*cache);
	line = (char *)malloc((l_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	new_cache = (char *)malloc((ft_strlen(*cache) - l_len + 1) * sizeof(char));
	if (!new_cache)
		return (ft_free_null(line));
	ft_strlcpy(line, *cache, l_len + 1);
	ft_strlcpy(new_cache, &(*cache)[l_len], ft_strlen(*cache) - l_len + 1);
	free(*cache);
	*cache = new_cache;
	/*
	if (ft_strlen(new_cache) > 0)
		*cache = new_cache;
	else
	{
		free(new_cache);
		*cache = NULL;
	}*/
	return (line);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	idx = 0;
	if (dstsize != 0)
	{
		while (src[idx] && idx < dstsize - 1)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	while (src[idx])
		idx++;
	return (idx);
}

/* BONUS PART	*/
#include "../get_next_line_bonus.h"

void	print_caches(t_cachelist *caches)
{
	if (caches)
	{
		printf("fd = %d : \"%s\"\n", caches->fd, caches->cache);
		print_caches(caches->next);
	}
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

void	*remove_cache(t_cachelist **caches, int fd)
{
	t_cachelist	*prev;
	t_cachelist	*current;

	prev = *caches;
	current = *caches;
	if (fd == -1)
	{
		while (prev)
		{
			current = prev->next;
			free(prev->cache);
			free(prev);
			prev = current;
		}
		*caches = NULL;
	}
	else
	{
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
	return (NULL);
}

t_cachelist	*add_to_caches(t_cachelist **caches, int fd, char const *src)
{
	t_cachelist	*current;
	t_cachelist	*cachefd;

	current = *caches;
	while (current && current->fd != fd && current->next)
		current = current->next;
	if (current && current->fd == fd)
	{
		current->cache = ft_strjoin_and_free(current->cache, src);
		if (!current->cache)
			return (remove_cache(caches, -1));
	}
	else
	{
		cachefd = (t_cachelist *)malloc(sizeof(t_cachelist));
		if (!cachefd)
			return (remove_cache(caches, -1));
		cachefd->fd = fd;
		cachefd->cache = ft_substr(src, 0, ft_strlen(src));
		cachefd->next = NULL;
		if (!cachefd->cache)
			return (remove_cache(caches, -1));
		if (current)
			current->next = cachefd;
		else
			*caches = cachefd;
	}
	return (*caches);
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

/*// SAVE
void	*exit_error(char buffer[OPEN_MAX][BUFFER_SIZE + 1], int fd, void *ptr)
{
	ssize_t	idx;
	
	idx = 0;
	if (fd >= 0)
	{
		while (buffer[fd][idx])
		{
			buffer[fd][idx] = '\0';
			idx++;
		}
	}
	free(ptr);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			bytes_read;
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (exit_error(buffer, fd, NULL));
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (exit_error(buffer, fd, NULL));
	line[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer[fd], '\n'))
	{
		line = ft_strappend(line, buffer[fd], ft_strlen(buffer[fd]));
		if (!line)
			return (exit_error(buffer, fd, NULL));
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read == - 1)
			return (exit_error(buffer, fd, line));
		buffer[fd][bytes_read] = '\0';
	}
	if (bytes_read == 0 && ft_strlen(line) == 0)
		return (exit_error(buffer, fd, line));
	if (bytes_read == 0)
		return (line);
	line = ft_strappend(line, buffer[fd], ft_strchr(buffer[fd], '\n') - buffer[fd] + 1);
	if (!line)
		return (exit_error(buffer, fd, NULL));
	ft_memcpy(buffer[fd], ft_strchr(buffer[fd], '\n') + 1, ft_strlen(ft_strchr(buffer[fd], '\n') + 1) + 1);
	return (line);
}
*/



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	idx;
	size_t	size;

	idx = 0;
	size = 0;
	if (!s)
		return (NULL);
	while (idx < start && s[idx])
		idx++;
	while (size < len && s[idx + size])
		size++;
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[size] = '\0';
	while (size > 0)
	{
		substr[size - 1] = s[idx + size - 1];
		size--;
	}
	return (substr);
}

char	*ft_stradd(char *s1, char const *s2, size_t len)
{
	char	*str;
	size_t	idx;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + len + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	idx = 0;
	while (s1 && s1[idx])
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (len-- > 0)
		str[idx++] = *s2++;
	str[idx] = '\0';
	free(s1);
	return (str);
}

char	*ft_strappend(char *s1, char const *s2, size_t len)
{
	char	*str;
	int		idx;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + len + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	idx = 0;
	while (s1[idx])
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (len-- > 0)
		str[idx++] = *s2++;
	str[idx] = '\0';
	free(s1);
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	if (!dst && !src)
		return (NULL);
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		idx++;
	}
	return (dst);
}