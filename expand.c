#include "minishell.h"


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
	char *fin;

	ret = NULL;
	fin = NULL;
	i = 0;
	if(!str[i])
		return (ft_strdup(""));
	while(str[i])
	{
			
		if(str[i] == '$' && ft_isalpha(str[i+1]) == 0)
			(fin = ft_charjoin(fin,str[i]), i++); // for 'ECURITYSESSIONID=186a8'
		if (str[i] == '$')
		{
			i++;
			ret = ft_sub_variable(str, &i);
			fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
		}
		else
			(fin = ft_charjoin(fin, str[i]), i++);
	}
	return fin;
}
int ft_chck_if_herdoc(t_list **list)
{
	t_list *tmp;
	tmp = *list;
	while (tmp)
	{
		if(tmp->type == HER_DOC) // check in PIPE
			return (1);
		tmp = tmp->next;
	}
	return (0);

}

void	ft_expand(t_list **list, t_data *data)
{
	t_list *tmp;

	tmp = *list;
	
	while (tmp)
	{
		if(!ft_chck_if_herdoc(list))
		{
	

			if(tmp->type == D_Q || tmp->type == VARIABLE)
				tmp->value = ft_search_var(tmp->value, data);
			else if(tmp->next && !ft_strcmp(tmp->value , "$") && !ft_type(tmp->next))
				tmp->value = ft_strdup("$") ;
			else if(tmp->next && !ft_strcmp(tmp->value , "$"))
				tmp->value = ft_strdup("") ;
		}
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


char *ft_expand_her_doc(char *str, t_data *data)
{
	int i;
	char *ret;
	char *fin;

	ret = NULL;
	fin = NULL;
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && ft_isalpha(str[i+1]) == 0)
			(fin = ft_charjoin(fin,str[i]), i++);
			
		else if (str[i] == '$')
		{
			i++;
			ret = ft_sub_variable(str, &i);
			fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
		}
		else
			(fin = ft_charjoin(fin, str[i]), i++);
	}
	return fin;
}
