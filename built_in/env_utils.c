/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:29:34 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/12 09:56:35 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_lstfind_env(t_env **env, char *line, char *new_line)
{
	t_env	*tmp;
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
				return (ft_strdup(tmp->line));
			tmp->line = ft_strdup(new_line);
			return (ft_strdup(new_line));
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

t_env	*ft_no_env(t_data **data)
{
	t_env	*p;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	p = ft_lstnew_env(ft_strjoin("PWD=", pwd));
	ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("SHLVL=1")));
	ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("OLDPWD")));
	ft_lstadd_back_env(&p, ft_lstnew_env(ft_strjoin("PATH=", _PATH_STDPATH)));
	(*data)->path = ft_strdup("/usr/bin/env");
	if ((*data)->path)
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strjoin("_=", (*data)->path)));
	(*data)->env = p;
	(*data)->pwd = ft_strdup(pwd);
	(*data)->home = ft_gethome(pwd);
	(*data)->shlvl = ft_strdup("1");
	(*data)->no_env = 1;
	(*data)->no_pwd = 1;
	return (free(pwd), p);
}

t_env	*ft_get_env(t_data **data, char **env)
{
	t_env	*p;
	int		i;

	i = 0;
	p = NULL;
	*data = c_malloc(sizeof(t_data), 1);
	if (!*data)
		return (NULL);
	if (!env || !*env)
		return (ft_no_env(data));
	while (*env)
	{
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup(*env)));
		env++;
	}
	(*data)->env = p;
	(*data)->path = ft_strdup("/usr/bin/env");
	(*data)->shlvl = ft_itoa(ft_valid_arg(ft_get_line(*data, "SHLVL", 5), \
		&i) + 1);
	(*data)->no_env = 0;
	(*data)->no_pwd = 1;
	return (p);
}
