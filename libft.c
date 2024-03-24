#include "minishell.h"


int	ft_strncmp(const char *str1, const char *str2)
{
	size_t				i;
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnew(void *value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

t_var	*ft_new(void *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	*node->arg = ft_strdup(value);
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_size(t_var *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	*ft_memchr(const void *str1, int c1, size_t n)
{
	size_t				i;
	unsigned char		c;
	const unsigned char	*str;

	c = (unsigned char)c1;
	i = 0;
	str = str1;
	while (i < n)
	{
		if (str[i] == c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t					i;
	const unsigned char		*s1;
	const unsigned char		*s2;

	i = 0;
	s1 = str1;
	s2 = str2;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	src = src1;
	dest = dest1;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	dest = dest1;
	src = src1;
	if (dest == src)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			dest[n - 1] = src[n - 1];
			n--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}

char	*ft_strchr(const char *s, int chr)
{
	int		i;
	char	c;
	char	*s1;

	c = (char)chr;
	s1 = (char *)s;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (&s1[i]);
		i++;
	}
	if (s1[i] == c)
		return (&s1[i]);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	len = ft_strlen(str);
	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = str[i];
		i++;
	}
	arr[len] = '\0';
	return (arr);
}

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*x;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	x = malloc((len1 + len2) + 1);
	if (!x)
		return (NULL);
	ft_memcpy(x, s1, len1);
	ft_memcpy(x + len1, s2, len2);
	x [len1 + len2] = '\0';
	return (x);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ls = ft_strlen(src);
	if (!dest && n == 0)
		return (ls);
	ld = ft_strlen(dest);
	if (n <= ld)
		return (ls + n);
	while (src[i] && i < n - 1 - ld)
	{
		dest[ld + i] = src[i];
		i++;
	}
	dest[ld + i] = '\0';
	return (ls + ld);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ls;

	i = 0;
	ls = ft_strlen(src);
	if (n == 0)
		return (ls);
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ls);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	start;
	size_t	end;
	char	*x;
	size_t	count;

	if (!str || !set)
		return (NULL);
	count = 0;
	start = 0;
	end = ft_strlen(str) - 1;
	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	while (start < ft_strlen(str) && ft_strchr(set, str[start]))
	{
		start++;
		count ++;
	}
	while (end > start && ft_strchr(set, str[end]))
	{
		end--;
		count++;
	}
	x = ft_substr(str, start, ft_strlen(str) - count);
	return (x);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	j;
	char	*arr;

	j = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str) || len == 0)
		return (ft_strdup(""));
	if (len > (ft_strlen(str) - start))
		arr = malloc ((ft_strlen(str) - start) + 1);
	else
		arr = malloc (len + 1);
	if (!arr)
		return (NULL);
	while (j < len && str[start])
	{
		arr[j] = str[start];
		j++;
		start++;
	}
	arr[j] = '\0';
	return (arr);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if (*lst)
		{
			free((*lst)->value);
			free(*lst);
		}
		*lst = tmp;
	}
	lst = NULL;
}

void	ft_lstclear_var(t_var **exec)
{
	t_var	*tmp;
	int		i;

	if (!exec || !(*exec))
		return ;
	while (*exec)
	{
		tmp = (*exec)->next;
		if (*exec)
		{
			free((*exec)->arg);
			free(*exec);
		}
		*exec = tmp;
	}
	exec = NULL;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (fd >= 0 && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
