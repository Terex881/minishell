/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:24:55 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/08 16:11:05 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_sub_variable(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[*i] && ft_isalpha(str[*i]) != 0)
		(*i)++;
	return (ft_substr(str, j, *i - j));
}

static char	*ft_charjoin(char const *s1, char s2)
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
			if(ret)
				fin = ft_strjoin(fin, ft_get_line(data, ret, ft_strlen(ret)));
		}
		else
			(1) && (fin = ft_charjoin(fin, str[i]), i++);
	}
	return (fin);
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
