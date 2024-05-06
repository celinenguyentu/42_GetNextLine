/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/06 00:34:30 by cnguyen-         ###   ########.fr       */
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

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
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
		return (ft_free(s1));
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
