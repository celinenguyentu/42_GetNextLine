typedef struct s_line
{
	size_t	size;
	char	*str;
} t_line;

char	*ft_strappend(char *s1, size_t s1_len, char *s2, size_t s2_len)
{
	size_t	idx;

	idx = 0;
	while (idx < s2_len)
		s1[s1_len++] = s2[idx++];
	s1[s1_len] = '\0';
	while (s2[idx])
		s2[s2_len++] = s2[idx++];
	s2[s2_len] = '\0';
	return (s1);
}
#include <stdio.h>
char	*ft_strsmove(char **s1, char *s2, char *stopmove)
{
	char	*str;
	size_t	s2_len;
	size_t	s1_len;
	size_t	idx;
	size_t	idy;
	size_t	s1_size;

	s2_len = stopmove - s2 + 1;
	s1_len = ft_strchr(*s1, '\0') - *s1;
	s1_size = sizeof(*s1);
	printf("line \"%s\"\n", *s1);
	printf("buffer \"%s\"\n", s2);
	printf("s1_size =  \"%lu\"\n", s1_size);
	printf("s1_len =  \"%lu\"\n", s1_len);
	printf("s2_len =  \"%lu\"\n", s2_len);
	if (s1_size - s1_len - 1 > s2_len)
		return (ft_strappend(*s1, s1_len, s2, s2_len));
	if (s1_size * 2 < s2_len)
		str = (char *)malloc((s1_size + s2_len) * sizeof(char));
	else
		str = (char *)malloc((s1_size * 2 - 1) * sizeof(char));
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