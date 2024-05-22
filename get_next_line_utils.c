/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/22 14:41:12 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		((unsigned char *)b)[idx] = (unsigned char)c;
		idx++;
	}
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	idx;
	size_t	size;

	idx = 0;
	size = 0;
	if (!s)
		return (NULL);
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

char	*ft_stradd(char *s1, char const *s2, size_t len)
{
	char	*str;
	size_t	idx;

	if (!s2)
		return (NULL);
	if (s1)
		str = (char *)malloc((ft_strlen(s1) + len + 1) * sizeof(char));
	else
		str = (char *)malloc((len + 1) * sizeof(char));
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
