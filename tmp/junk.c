/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:44:15 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/03 15:07:45 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
