/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/02 16:48:58 by cnguyen-         ###   ########.fr       */
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

char	*ft_strnmove(char **s1, char *s2, size_t len)
{
	char	*str;
	size_t	cpylen;
	size_t	idx;
	size_t	idy;

	cpylen = ft_strlen(s2);
	cpylen = (len < cpylen) * len + (len >= cpylen) * cpylen;
	str = (char *)malloc((ft_strlen(*s1) + cpylen + 1) * sizeof(char));
	if (!str)
		return (free(*s1), NULL);
	idx = -1;
	while ((*s1)[++idx])
		str[idx] = (*s1)[idx];
	idy = 0;
	while (idy < cpylen && s2[idy])
		str[idx++] = s2[idy++];
	str[idx] = '\0';
	idx = 0;
	while (s2[idy])
		s2[idx++] = s2[idy++];
	s2[idx] = '\0';
	free(*s1);
	*s1 = str;
	return (str);
}

/*
char	*ft_strappend(char **s1, char const *s2, size_t len)
{
	char	*str;
	int		idx;
	size_t	len_cpy;

	len_cpy = ft_strlen(s2);
	len_cpy = (len < len_cpy) * len + (len >= len_cpy) * len_cpy;
	if (*s1)
		len_cpy += ft_strlen(*s1);
	str = (char *)malloc((len_cpy + 1) * sizeof(char));
	if (!str)
	{
		free(*s1);
		return (NULL);
	}
	idx = 0;
	while ((*s1) && (*s1)[idx])
	{
		str[idx] = (*s1)[idx];
		idx++;
	}
	while (len_cpy-- > 0)
		str[idx++] = *s2++;
	str[idx] = '\0';
	free(*s1);
	*s1 = str;
	return (*s1);
}*/

/*
char	*ft_strappend(char *s1, char const *s2, size_t len)
{
	char	*str;
	int		idx;
	size_t	len_cpy;

	if (!s2)
		return (NULL);
	len_cpy = ft_strlen(s2);
	len_cpy = (len < len_cpy) * len + (len >= len_cpy) * len_cpy;
	if (s1)
		len_cpy += ft_strlen(s1);
	str = (char *)malloc((len_cpy + 1) * sizeof(char));
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	idx = 0;
	while (s1 && s1[idx])
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (len_cpy-- > 0)
		str[idx++] = *s2++;
	str[idx] = '\0';
	if (s1)
		free(s1);
	return (str);
}*/

/* SAVE
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

	if (!s2 || !s1)
		return (NULL);
	len_cpy = ft_strlen(s2);
	len_cpy = (len < len_cpy) * len + (len >= len_cpy) * len_cpy;
	str = (char *)malloc((ft_strlen(s1) +len_cpy + 1) * sizeof(char));
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
}*/