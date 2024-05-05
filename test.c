	//TEST CASES
#include <stdio.h>
#include <stdlib.h>

typedef struct s_cachelist
{
	int					fd;
	char				*cache;
	struct s_cachelist	*next;
} t_cachelist;


void	*remove_cache(t_cachelist **caches, int fd)
{
    t_cachelist *current;
	
    while (*caches && ((*caches)->fd == fd || fd == -1))
	{
        current = *caches;
        *caches = (*caches)->next;
		free(current->cache);
        free(current);
    }
    if (*caches)
		remove_cache(&((*caches)->next), fd);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

t_cachelist	*ft_create_elem(int fd, char *data)
{
	t_cachelist	*elem;
	char		*cache;
	int			idx;

	elem = malloc(sizeof(t_cachelist));
	if (!elem)
		return (NULL);
	cache = (char *)malloc((ft_strlen(data) + 1) * sizeof(char));
	if (!cache)
		return (NULL);
	idx = 0;
	while (data[idx])
	{
		cache[idx] = data[idx];
		idx++;
	}
	cache[idx] = '\0';
	elem->next = NULL;
	elem->cache = cache;
	elem->fd = fd;
	return (elem);
}

void	ft_list_push_front(t_cachelist **begin_list, int fd, char *data)
{
	t_cachelist	*elem;

	elem = ft_create_elem(fd, data);
	if (elem)
	{
		if (*begin_list)
			elem->next = *begin_list;
		*begin_list = elem;
	}
}

void	ft_print_list(t_cachelist *list)
{
	if (!list)
	{
		printf("NULL\n");
		return ;
	}
	printf("%d -> %s\n", list->fd, (char *)list->cache);
	ft_print_list(list->next);
}

int	main(void)
{
	t_cachelist	*list;

	list = NULL;
	ft_list_push_front(&list, 3, "42");
	ft_list_push_front(&list, 4,"World");
	ft_list_push_front(&list, 5, "Hello");
	ft_list_push_front(&list, 6, "salutsalut");
	ft_print_list(list);
	remove_cache(&list, -1);
	ft_print_list(list);
	return (0);
}
