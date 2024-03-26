#include "../minishell.h"

char	*ft_strtrim(char *str, char set)
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
	if(start < ft_strlen(str) && str[start] == set)
	{
		start++;
		count ++;
	}
	if(str[end] == set)
	{
		end--;
		count++;
	}
	x = ft_substr(str, start, ft_strlen(str) - count);
	return (x);
}
