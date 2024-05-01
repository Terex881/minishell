/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:46 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/01 15:07:29 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cd_home(char **path, t_data *data)
{
	(void)data;
	if (*path && *path[0] == '~')
	{
		*path = getenv("HOME");
		if (!path || !*path)
			*path = ft_strdup(data->home);
		return (0);
	}
	if (!path || !*path || !ft_strncmp(*path, "~", 1))
	{
		*path = getenv("HOME");
		if (!path || !*path)
		{
			ft_error("minishell: ", "cd: ", "HOME not set");
			g_stat = 1;
			return (1);
		}
	}
	return (0);
}

static int	ft_change_dir(int n, char *tmp, char *pwd, t_data *data)
{
	char	*path;

	if (!n && pwd)
	{
		if (!tmp)
			tmp = data->pwd;
		ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", tmp + 4));
		path = getcwd(NULL, 0);
		if (path)
			data->pwd = ft_strdup(path);
		ft_lstfind_env(&data->env, "PWD", ft_strjoin("PWD=", pwd));
		free(path);
	}
	else if (!n)
	{
		if (!tmp)
			tmp = data->pwd;
		ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", tmp + 4));
		data->pwd = ft_strdup(ft_strjoin(tmp, "/.."));
		ft_lstfind_env(&data->env, "PWD", data->pwd);
	}
	else
		return (0);
	return (1);
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
		ft_error("cd: error retrieving current directory: ",
			"getcwd: cannot access parent directories: ",
			"No such file or directory");
	if (pwd)
		data->pwd = ft_strdup(pwd);
	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
	if (!tmp)
		tmp = ft_strdup(pwd);
	if (!ft_change_dir(n, tmp, pwd, data))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		(perror(path), g_stat = 1);
	}
	return (free(pwd));
}

char	*ft_gethome(char *pwd)
{
	char	*home;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!pwd)
		return (NULL);
	while (pwd[i] && count != 3)
	{
		if (pwd[i] == '/')
			count++;
		i++;
	}
	home = ft_substr(pwd, 0, i);
	return (home);
}
