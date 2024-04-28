/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:09:35 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/28 09:44:17 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sub_variable(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[*i] && ft_isalpha(str[*i]) != 0)
		(*i)++;
	return (ft_substr(str, j, *i - j));
}

char	*ft_search_var(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*fin;

	ret = NULL;
	fin = NULL;
	i = 0;
	if (!str[i])
		return (ft_strdup(""));
	while (str[i])
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]) == 0)
			(1) && (fin = ft_charjoin(fin, str[i]), i++);
		if (str[i] == '$')
		{
			i++;
			ret = ft_sub_variable(str, &i);
			fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
		}
		else
			(1) && (fin = ft_charjoin(fin, str[i]), i++);
	}
	return (fin);
}

void	ft_expand(t_list **list, t_data *data)
{
	t_list	*tmp;

	tmp = *list;
	char *str;
	while (tmp)
	{
	str = ft_strchr(tmp->value, '$');
		if (tmp->type == HER_DOC)
		{
			tmp = ft_next(tmp->next);
			tmp = tmp->next;
			continue ;
		}
        if (tmp && tmp->value && !ft_strncmp(tmp->value, "$?", 2))
		{
			tmp->value = ft_strjoin(ft_itoa(g_stat), ft_substr(tmp->value, 2,
						ft_strlen(tmp->value) - 2));
		}
		if (str && !ft_strncmp(str, "$?", 2) && tmp->type == D_Q)
		{
			tmp->value = ft_strjoin(ft_substr(tmp->value, 0, str - tmp->value),
					ft_itoa(g_stat));
			tmp->value = ft_strjoin(tmp->value, ft_substr(str, 2,
						ft_strlen(str) - 2));	
		}
		if (tmp && !ft_strcmp(tmp->value, "$?"))
			tmp->value = ft_itoa(g_stat);
		else if (tmp && (tmp->type == D_Q || tmp->type == VARIABLE))
			tmp->value = ft_search_var(tmp->value, data);
		else if (tmp && tmp->next && !ft_strcmp(tmp->value, "$")
			&& !ft_type(tmp->next))
			tmp->value = ft_strdup("$");
		else if (tmp && tmp->next && !ft_strcmp(tmp->value, "$"))
			;
		else if (str && *str && *(str + 1) == '0')
			tmp->value = ft_strjoin("minishell", str + 2);
		else if (str && *str && *(str + 1) >= '0' && *(str + 1) <= '9')
			tmp->value = ft_strdup(str + 2);
		tmp = tmp->next;
	}
}

char	*ft_charjoin(char const *s1, char s2)
{
	char	*x;
	int		i;

	i = 0;
	if (!s1)
	{
		x = c_malloc(2, 1);
		if (!x)
			return (NULL);
		x[i] = s2;
		x[i + 1] = '\0';
		return (x);
	}
	x = c_malloc(ft_strlen(s1) + 2, 1);
	if (!x)
		return (NULL);
	while (s1[i])
	{
		x[i] = s1[i];
		i++;
	}
	x[i] = s2;
	x[i + 1] = '\0';
	return (x);
}

char	*ft_expand_her_doc(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*fin;

	ret = NULL;
	fin = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]) == 0)
			(1) && (fin = ft_charjoin(fin, str[i]), i++);
		else if (str[i] == '$')
		{
			i++;
			ret = ft_sub_variable(str, &i);
			fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
		}
		else
			(1) && (fin = ft_charjoin(fin, str[i]), i++);
	}
	return (fin);
}
