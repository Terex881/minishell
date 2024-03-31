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

char *ft_search_var(char *str, t_data *data)
{
	int i;
	char *ret;
	char *tmp;
	char *fin;
	char *res;
	ret = NULL;
	res=NULL;
	fin = NULL;
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && ft_isalpha(str[i+1]) == 0)
		{
			tmp = fin;
			fin = ft_charjoin(fin,str[i]);
			(free(tmp), i++);
		}
		else if (str[i] == '$')
		{
			i++;
			ret = ft_sub_variable(str, &i);
			fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
			free(ret);
		}
		else
		{
			tmp = fin;
			fin = ft_charjoin(fin, str[i]);
			(free(tmp), i++);
		}
	}
	return fin;
}

void	ft_expand(t_list **list, char **env, t_data *data)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		if(tmp->type == D_Q || tmp->type == VARIABLE)
			tmp->value = ft_search_var(tmp->value, data);
		else if(tmp->next && tmp->type == WORD && !ft_strcmp(tmp->value , "$"))
			tmp->value = ft_strdup("") ;
		tmp = tmp->next;
	}
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

// char *ft_expand_her_doc(char *str)
// {
// 	char	*tmp;
// 	char	*tt;
// 	int		i;
// 	char 	*retur;
// 	char *f1;

// 	retur = NULL;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			if (ft_isalpha(str[i]) == 2)
// 				i++;
// 			else if (ft_isalpha(str[i]) == 1)
// 			{
// 				tmp = ft_sub_variable(str, &i);
// 				tt = getenv(tmp);
// 				if (!tt)
// 					return (free(tmp), NULL);	
// 				f1 = retur;	
// 				retur = ft_strjoin(retur, tt);
// 				free(f1);
// 				free(tmp);
// 			}
// 		}
// 		else
// 		{
// 			f1 = retur;
// 			(retur = ft_charjoin(retur, str[i]), i++);
// 			free(f1);
// 		}
// 	}
// 	return  (retur);
// }
