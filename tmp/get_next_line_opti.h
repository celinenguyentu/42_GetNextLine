/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_opti.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:50 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/14 20:23:22 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define B_MAX LONG_MAX

typedef struct s_buffer
{
	char			*content;
	struct s_buffer	*next;
} t_buffer;

typedef struct s_cache
{
	size_t	line_length;
	size_t	total_length;
	struct s_buffer *first;
	struct s_buffer *last;	
} t_cache;

char	*get_next_line(int fd);

// utils
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_and_free(char *s1, char const *s2);

t_cache *cache_init(void);
int		has_newline(t_cache *cache);
#endif