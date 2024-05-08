/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/08 05:37:46 by cnguyen-         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
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

	total_length = ft_strlen(s1) + ft_strlen(s2);
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
