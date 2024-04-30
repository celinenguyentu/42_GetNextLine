/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/04/30 19:44:03 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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


char	*ft_strnchr(const char *s, int c, int n)
{
	while (*s && n-- && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*store_line(char *line, char *src, int src_size)
{
	char	*eol;
	
	eol = ft_strnchr(src, '\n', src_size);
	if (eol)
	{
		ft_strlcat(line, src, ft_strlen(line) + (eol - src + 1) + 1);
		return (++eol);
	}
	else
	{
		ft_strlcat(line, src, src_size + 1);
		return (NULL);
	}
}


char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*line;
	static char	next_line[BUFFER_SIZE];

	bytes_read = 1;
	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = 0;
	
	//while (bytes_read > 0)
	//{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read == -1)
			return (NULL);
		next_line = store_line(line, buffer, bytes_read);
//	}
	//printf("next line : %c", *next_line);
	return (line);
}