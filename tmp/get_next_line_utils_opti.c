/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_opti.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/01 15:04:48 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_opti.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

int	has_newline(t_cache *cache)
{
	char	*newline;
	
	newline = ft_strchr(cache->last, '\n');
	if (!newline)
		return (0);
	else
		return (1);
}

t_cache	*add_to_cache(t_cache **cache, char *buffer)
{
	if (!cache)
	{
		
	}
}

t_cache	*cache_init(void)
{
	t_cache *cache;
	
	cache = (t_cache *)malloc(sizeof(t_cache));
	cache->first = NULL;
	cache->last = NULL;
	cache->total_length = 0;
	cache->line_length = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	idx;
	size_t	size;

	idx = 0;
	size = 0;
	while (s[idx] && idx < start)
		idx++;
	while (s[idx + size] && size < len)
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

char	*ft_strjoin_and_free(char *s1, char const *s2)
{
	char	*str;
	size_t	idx;
	size_t	total_length;

	total_length = ft_strlen(s2);
	if (s1)
		total_length += ft_strlen(s1);
	str = (char *)malloc((total_length + 1) * sizeof(char));
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
	while (s2 && *s2)
		str[idx++] = *s2++;
	str[idx] = '\0';
	free(s1);
	return (str);
}


/*

ssize_t	ft_find(const char *s, int c)
{
	ssize_t	idx;
	
	idx = 0;
	while (s[idx] && s[idx] != (unsigned char)c)
		idx++;
	if (s[idx] == (unsigned char)c)
		return (idx);
	return (-1);
}

char	*ft_strmove(char *s1, char *s2, char sep)
{
	char	*str;
	size_t	idx;
	size_t	strlen;

	
	strlen = ft_find(s2, '\n')
	str = (char *)malloc()

	
}*/