#include "../minishell.h"

static int	count_word(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

static char	*length_word(const char **str1, char sep)
{
	int			i;
	int			start;
	int			j;
	char		*arr;
	const char	*str;

	i = 0;
	start = 0;
	j = 0;
	str = *str1;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] == sep)
		i++;
	start = i;
	while (str[i] && str[i] != sep)
		i++;
	arr = (char *)c_malloc((i - start) + 1, 1);
	if (!arr)
		return (NULL);
	while (start < i)
		arr[j++] = str[start++];
	arr[j] = '\0';
	*str1 = str + i;
	return (arr);
}

static void	libre(char **str, int i)
{
	while (i >= 0)
	{
		// free(str[i]);
		i--;
	}
	// free(str);
}

char	**ft_split(const char *str, char sep)
{
	int		i;
	int		count;
	char	**arr;

	i = 0;
	if (!str)
		return (NULL);
	count = count_word(str, sep);
	arr = c_malloc(sizeof(char *) * (count + 1), 1);
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	while (i < count)
	{
		arr[i] = length_word(&str, sep);
		if (!arr[i])
		{
			libre(arr, i);
			return (NULL);
		}
		i++;
	}
	return (arr);
}