/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/02 22:18:55 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/*
	FT_STRSMOVE
	Moves the initial portion of the string s2 until the character pointed to
	by the third argument (included) to the end of the string s1. The first
	string has to be allocated in the heap, so that the memory is freed and a
	new concatenated string is allocated. The remaining characters in s2 are
	moved to the beginning of the memory area.
	PARAMETERS
	1.	The address of the string to append with characters from s2.
	2.	The string from which the characters are moved.
	3.	The address of the last character to move.
	RETURN
	The function returns the new string from concatenation of s1 and the
	beginning of s2. If an error occured, it returns NULL.
*/

char	*ft_strsmove(char **s1, char *s2, char *stopmove)
{
	char	*str;
	size_t	s2_len;
	size_t	s1_len;
	size_t	idx;
	size_t	idy;

	s2_len = stopmove - s2 + 1;
	s1_len = ft_strchr(*s1, '\0') - *s1;
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (free(*s1), NULL);
	idx = -1;
	while ((*s1)[++idx])
		str[idx] = (*s1)[idx];
	idy = 0;
	while (idy < s2_len && s2[idy])
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
