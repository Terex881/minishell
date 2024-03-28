#include "../minishell.h"

char	*ft_strchr(char *s1, int c)
{
	int		i;

	i = 0;
	if(!s1[i])
		return NULL;
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
