/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/01 15:17:13 by cnguyen-         ###   ########.fr       */
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

char	*ft_strappend(char *s1, char const *s2, size_t len)
{
	char	*str;
	int		idx;
	size_t	len_cpy;

	if (!s1 || !s2)
		return (NULL);
	len_cpy = ft_strlen(s2);
	len_cpy = (len < len_cpy) * len + (len >= len_cpy) * len_cpy;
	str = (char *)malloc((ft_strlen(s1) + len_cpy + 1) * sizeof(char));
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
	while (len_cpy-- > 0)
		str[idx++] = *s2++;
	str[idx] = '\0';
	free(s1);
	return (str);
}
