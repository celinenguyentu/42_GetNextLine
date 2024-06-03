/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnguyen- <cnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:59:50 by cnguyen-          #+#    #+#             */
/*   Updated: 2024/06/03 12:45:51 by cnguyen-         ###   ########.fr       */
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

//	2000000000 RLIMIT_DATA
//	10000000 Tripouille
//	1000000 fsoares
// ~2000000000 max on macOS

/*# if BUFFER_SIZE > RLIMIT_DATA * 1000000000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif*/

char	*get_next_line(int fd);

// utils
char	*ft_strchr(const char *s, int c);
char	*ft_strsmove(char **s1, char *s2, char *stopmove);

#endif