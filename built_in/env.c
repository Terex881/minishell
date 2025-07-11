/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:39:39 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/13 18:07:31 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_no_env(t_data *data)
{
	char	**paths;
	char	*tmp;
	char	*path;
	int		i;

	path = NULL;
	if (!ft_get_line(data, "PATH", 4)
		|| !ft_strlen(ft_get_line(data, "PATH", 4)))
		return (1);
	paths = get_paths(ft_lstfind_env(&data->env, "PATH", NULL));
	i = -1;
	while (paths && paths[++i])
	{
		(1) && (tmp = ft_strjoin(paths[i], "/"), path = ft_strjoin(tmp, "env"));
		data->path = ft_strdup(path);
		if (!access(path, F_OK | X_OK))
			return (0);
	}
	return (1);
}

void	ft_env(t_var *exec, t_data *data)
{
	t_env		*env;

	exit_status(0, 1);
	if (check_no_env(data))
	{
		ft_error("env: ", "No such file or directory");
		return ((void)exit_status(127, 1));
	}
	env = data->env;
	ft_lstfind_env(&data->env, "_", ft_strjoin("_=", data->path));
	while (env)
	{
		if (ft_strchr(env->line, '='))
		{
			if ((data->no_env && !ft_strncmp(env->line, "PATH=", 5))
				|| (data->no_pwd && !ft_strncmp(env->line, "OLDPWD=", 7)))
			{
				env = env->next;
				continue ;
			}
			ft_putstr_fd(env->line, exec->f_out);
			ft_putstr_fd("\n", exec->f_out);
		}
		env = env->next;
	}
}
