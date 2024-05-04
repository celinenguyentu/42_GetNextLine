/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:50 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/05/04 18:16:05 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define B_MAX SSIZE_MAX

typedef struct s_cachelist
{
	int					fd;
	char				*cache;
	struct s_cachelist	*next;
} t_cachelist;

char		*get_next_line(int fd);
void	add_to_caches(t_cachelist **caches, int fd, char const *src);
char		*get_cache(t_cachelist *caches, int fd);
void	print_caches(t_cachelist *caches);

// utils
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_free(void *ptr);
char	*ft_strjoin_and_free(char *s1, char const *s2);

#endif