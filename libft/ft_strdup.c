#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	len = ft_strlen(str);
	arr = c_malloc(len + 1, 1);
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
