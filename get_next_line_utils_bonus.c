/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/02 23:36:13 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	idx;
	size_t	total_length;

	total_length = ft_strlen(s2);
	if (s1)
		total_length += ft_strlen(s1);
	str = (char *)malloc((total_length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	idx = 0;
	while (s1 && s1[idx])
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (s2 && *s2)
		str[idx++] = *s2++;
	if (s1)
		free(s1);
	str[idx] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

void	*ft_free_null(void *ptr)
{
	free(ptr);
	return (NULL);
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
