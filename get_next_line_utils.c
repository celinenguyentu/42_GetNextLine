/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:02 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/01 17:32:53 by cnguyen-         ###   ########.fr       */
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
