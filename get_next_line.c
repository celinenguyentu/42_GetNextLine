/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/03 15:17:46 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **cache)
{
	char	*line;
	char	*new_cache;
	int		l_len;

	if (**cache == '\0')
	{
		free(*cache);
		*cache = NULL;
		return (NULL);
	}
	if (ft_strchr(*cache, '\n'))
		l_len = ft_strchr(*cache, '\n') - *cache + 1;
	else
		l_len = ft_strlen(*cache);
	line = ft_substr(*cache, 0, l_len);
	if (!line)
		return (NULL);
	new_cache = ft_substr(*cache, l_len, ft_strlen(*cache) - l_len);
	if (!new_cache)
		return (ft_free(line));
	free(*cache);
	*cache = new_cache;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			bytes_read;
	static char	*cache = NULL;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > B_MAX || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (cache && ft_strchr(cache, '\n'))
		return (extract_line(&cache));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!cache || !ft_strchr(cache, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer));
		buffer[bytes_read] = '\0';
		cache = ft_strjoin_and_free(cache, buffer);
		if (!cache)
			return (ft_free(buffer));
	}
	free(buffer);
	return (extract_line(&cache));
}
