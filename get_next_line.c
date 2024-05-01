/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:36 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/01 22:15:45 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

char	*ft_expand(char *str, int size)
{
	char	*new_str;
	int		idx;

	if (str)
		new_str = malloc((ft_strlen(str) + size) * sizeof(char));
	else
		new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (NULL);
	idx = 0;
	while (str && str[idx])
	{
		new_str[idx] = str[idx];
		idx++;
	}
	new_str[idx] = '\0';
	free(str);
	return (new_str);
}

int	ft_find_eol(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	return (-1);
}

char	*extract_line(char **cache)
{
	char	*line;
	char	*new_cache;
	int		n_line;
	int		idx;
	
	if (!*cache || **cache == '\0')
		return (NULL);
	if (ft_find_eol(*cache) != -1)
		n_line = ft_find_eol(*cache) + 1;
	else
		n_line = ft_strlen(*cache);
	line = (char *)malloc((n_line + 1) * sizeof(char));
	new_cache = (char *)malloc((ft_strlen(*cache) - n_line + 1) * sizeof(char));
	idx = 0;
	while ((*cache)[idx] && idx < n_line)
		line[idx++] = (*cache)[idx];
	line[idx] = '\0';
	while ((*cache)[idx])
		new_cache[idx++ - n_line] = (*cache)[idx];
	new_cache[idx - n_line] = '\0';
	free(*cache);
	*cache = new_cache;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	int			bytes_read;
	static char	*cache = NULL;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX || fd < 0)
		return (NULL);
	bytes_read = 1;
	if (cache && ft_find_eol(cache) != -1)
		return (extract_line(&cache));
	while (bytes_read > 0 && (!cache || ft_find_eol(cache) == -1))
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read > 0)
		{
			cache = ft_expand(cache, bytes_read + 1);
			ft_strlcat(cache, buffer, ft_strlen(cache) + bytes_read + 1);
		}
	}
	return (extract_line(&cache));
}
