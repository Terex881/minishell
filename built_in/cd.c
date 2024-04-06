/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:46 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/06 20:10:22 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int    ft_cd_home(char **path, t_data *data)
{
    if (!path || !*path || (*path[0] == '~' && *path[1] == '\0'))
    {
        *path = getenv("HOME");
        if (!path || !*path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            data->stat = 1;
            return (1);
        }
        if (!data->path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            data->stat = 1;
            return (1);
        }
    }
    return (0);
}

static void    ft_change_dir(int n, char *tmp, char *pwd, t_data *data)
{
    char    *join;
    char    *path;

    if (!n && pwd)
    {
        join = ft_strjoin("OLDPWD=", tmp + 4);
        ft_lstfind_env(&data->env, "OLDPWD", join);
        path = getcwd(NULL, 0);
        join = ft_strjoin("PWD=", pwd);
        ft_lstfind_env(&data->env, "PWD", join);
        free(path);
    }
    else if (!n)
    {
        join = ft_strjoin("OLDPWD=", tmp + 4);
        ft_lstfind_env(&data->env, "OLDPWD", join);
        join = ft_strjoin(tmp, "/..");
        ft_lstfind_env(&data->env, "PWD", join);
    }
    else
    {
        ft_putstr_fd("minishell: ", 2);
        (perror("path"), data->stat = 1);
    }
}

void    ft_cd(char *path, t_data *data)
{
    char    *tmp;
    char    *pwd;
    int        n;

    data->stat = 0;
    if (ft_cd_home(&path, data))
        return ;
    tmp = ft_lstfind_env(&data->env, "PWD", NULL);
    n = chdir(path);
    pwd = getcwd(NULL, 0);
    ft_change_dir(n, tmp, pwd, data);
    free(pwd);
    return ;
}