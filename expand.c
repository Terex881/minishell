#include "minishell.h"

char *ft_get_variable(char *str, int *i)
{
	int j = *i;
	while (str[*i] && ft_isalpha(str[*i]) != 0)
		(*i)++;
	return (ft_substr(str, j, *i - j));
}
void	ft_expand(t_list *list)
{
	char *str;
	char *tmp;
	int i;

	i = 0;
	str = list->value;
	while (str[i])
	{
		if(str[i] == '$')
		{
			i++;
			if (ft_isalpha(str[i]) == 1)
			{
				tmp = ft_get_variable(str, &i);
				char *tt =  getenv(tmp);
				if (!tt)
					return (free(tmp));		
				// printf("%s",tt);
				free(tmp);
			}
		}
		// else
			// (printf("%c", str[i]), i++);
	}
}