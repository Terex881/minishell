#include "../minishell.h"

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