#include "minishell.h"
#include <stdio.h>

char	*ft_sub_variable(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[*i] && ft_isalpha(str[*i]) != 0)
		(*i)++;
	return (ft_substr(str, j, *i - j));
}





char	*ft_charjoin(char const *s1, char s2)
{
	char	*x;
	int i;
	
	i = 0;
	if (!s1)
	{
		x = malloc(2);
		x[i] = s2;
		x[i+1] = '\0';
		return x;
	}
	x = malloc(ft_strlen(s1) + 2);
	if (!x)
		return (NULL);
	while (s1[i])
	{
		x[i] = s1[i];
		i++;
	}
	x[i] = s2;
	x[i+1]= '\0';
	return (x);
}

char *ft_expand_her_doc(char *str)
{
	char	*tmp;
	char	*tt;
	int		i;
	char 	*retur;
	char *f1;

	retur = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (ft_isalpha(str[i]) == 2)
				i++;
			else if (ft_isalpha(str[i]) == 1)
			{
				tmp = ft_sub_variable(str, &i);
				tt = getenv(tmp);
				if (!tt)
					return (free(tmp), NULL);	
				f1 = retur;	
				retur = ft_strjoin(retur, tt);
				free(f1);
				free(tmp);
			}
		}
		else
		{
			f1 = retur;
			(retur = ft_charjoin(retur, str[i]), i++);
			free(f1);
		}
	}
	return  (retur);
}
