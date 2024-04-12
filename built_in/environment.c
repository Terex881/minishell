/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:29:34 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/12 08:58:44 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_lstfind_env(t_env **env, char *line, char *new_line)
{
	t_env	*tmp;
	char	*find;
	int		n;

	if (!env || !*env || !line)
		return (NULL);
	tmp = *env;
	n = ft_strlen(line);
	while (tmp)
	{
		if (tmp && ft_strncmp(tmp -> line, line, n) == 0
			&& (tmp->line[n] == '\0' || tmp->line[n] == '='))
		{
			if (!new_line || !*new_line)
			{
				find = ft_strdup(tmp->line);
				return (find);
			}
			tmp -> line = ft_strdup(new_line);
			find = ft_strdup(tmp->line);
			return (find);
		}
		tmp = tmp -> next;
	}
	return (NULL);
}

char	*ft_get_line(t_data *data, char *line, int i)
{
	t_env	*tmp;
	char	*res;
	int		n;

	if (!data)
		return (NULL);
	tmp = data->env;
	n = ft_strlen(line);
	while (tmp)
	{
		if (tmp && !ft_strncmp(tmp -> line, line, n)
			&& (tmp->line[n] == '\0' || tmp->line[n] == '='))
		{
			res = ft_strdup(tmp->line + i + 1);
			return (res);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_lstcpy_env(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	while (env)
	{
		tmp = ft_lstnew_env(ft_strdup(env -> line));
		if (!tmp)
			return (NULL);
		ft_lstadd_back_env(&copy, tmp);
		env = env -> next;
	}
	return (copy);
}

t_env	*ft_sort_env(t_env *env, int (*cmp)(char *, char *))
{
	t_env	*tmp;
	t_env	*t;
	char	*m;

	if (!env || !cmp)
		return ((t_env *){0});
	tmp = env;
	while (tmp && tmp->next)
	{
		t = tmp -> next;
		while (t)
		{
			if (cmp(tmp -> line, t -> line) > 0)
			{
				m = tmp -> line;
				tmp -> line = t -> line;
				t -> line = m;
			}
			t = t -> next;
		}
		tmp = tmp -> next;
	}
	return (env);
}

t_env	*ft_get_env(t_data **data, char **env)
{
	t_env	*p;
	char	*pwd;

	p = NULL;
	*data = c_malloc(sizeof(t_data), 1);
	if (!*data)
		return (NULL);
	g_stat = 0;
	if (!env || !*env)
	{
		pwd = getcwd(NULL, 0);
		p = ft_lstnew_env(ft_strjoin("PWD=", pwd));
		(*data)->env = p;
		(*data)->path
			= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		return (free(pwd), p);
	}
	while (*env)
	{
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup(*env)));
		env++;
	}
	(*data)->env = p;
	(*data)->path = ft_get_line((*data), "PATH", 5);
	return (p);
}
