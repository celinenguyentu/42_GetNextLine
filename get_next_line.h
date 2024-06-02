/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:50 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/02 03:28:35 by cnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/resource.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
/*
# if BUFFER_SIZE > RLIMIT_DATA * 1000000000 || BUFFER_SIZE < 1 || BUFFER_SIZE > SSIZE_MAX
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
*/

// macOS = ~2100000000

char	*get_next_line(int fd);

// utils
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strappend(char *s1, char const *s2, size_t len);


#endif