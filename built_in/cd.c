/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:46 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/26 21:43:26 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cd_home(char **path, t_data *data)
{
	(void)data;
	if (!path || !*path || !ft_strncmp(*path, "~", 1))
	{
		*path = getenv("HOME");
		if (!path || !*path)
		{
			ft_error("minishell: ", "cd: ", "HOME not set");
			g_stat = 1;
			return (1);
		}
		// if (!data->path)
		// {
		// 	ft_error("minishell: ", "cd: ", "HOME not set\n");
		// 	g_stat = 1;
		// 	return (1);
		// }
	}
	return (0);
}

static void	ft_change_dir(int n, char *tmp, char *pwd, t_data *data)
{
	char	*join;
	char	*path;

	if (!n && pwd)
	{
		if (!tmp)
			tmp = data->pwd;
		join = ft_strjoin("OLDPWD=", tmp + 4);
		ft_lstfind_env(&data->env, "OLDPWD", join);
		path = getcwd(NULL, 0);
		if (path)
			data->pwd = ft_strdup(path);
		join = ft_strjoin("PWD=", pwd);
		ft_lstfind_env(&data->env, "PWD", join);
		free(path);
	}
	else if (!n)
	{
		if (!tmp)
			tmp = data->pwd;
		join = ft_strjoin("OLDPWD=", tmp + 4);
		ft_lstfind_env(&data->env, "OLDPWD", join);
		join = ft_strjoin(tmp, "/..");
		ft_lstfind_env(&data->env, "PWD", join);
		data->pwd = ft_strdup(join);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		(perror("path"), g_stat = 1);
	}
}

void	ft_cd(char *path, t_data *data)
{
	char	*tmp;
	char	*pwd;
	int		n;

	g_stat = 0;

	if (ft_cd_home(&path, data))
		return ;
	n = chdir(path);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_error("cd: error retrieving current directory: "
			, "getcwd: cannot access parent directories: "
			, "No such file or directory");
	if (pwd)
		data->pwd = ft_strdup(pwd);
	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
	if (!tmp)
		tmp = ft_strdup(pwd);
	ft_change_dir(n, tmp, pwd, data);
	free(pwd);
	return ;
}
