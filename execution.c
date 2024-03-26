/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:40:16 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/02/01 18:29:35 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_paths(char **env)
{
    int i = 0;
    int j = 0;

    while (ft_strncmp(env[i], "PATH=", 5))
        i++;
    while (env[i][j] != '\n' && env[i][j] != '\0')
        j++;
    return (ft_split(ft_substr(env[i], 5, --j), ':'));
}

char *valid_path(char *cmd, char **env)
{
    int     i = 0;
    char    *path;
    char    *tmp;
    char    **paths;

    /*******************************/
    if (!access(cmd, F_OK | X_OK))
        return (ft_strdup(cmd));
    /*******************************/
    paths = get_paths(env);
    if (!paths)
        return (perror("env failed!"), NULL);
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!access(path, F_OK | X_OK)) //checks if the file or directory specified by path exists and if it can be accessed with the file access permissions given by amode
        {                       // R_OK for read permission
            // free(cmd);       // F_OK existence test
            return (path);      // W_OK for write permission
        }                       // X_OK for execute/search permission             
        i++;
        free(path);
    }
    return (NULL);
    /*******************************/
}

int execution(char *av, char **env)
{
    char     **cmd;
    char    *path;

    /*******************************/
    cmd = ft_split(av, ' ');
    path = valid_path(cmd[0], env);
    if (!path)
        return (perror("Invalid path!\n"), 0);//free cmd
    /*******************************/
    if (execve(path, cmd, env) == -1)
        return (perror("execv error!\n"), 0);
    /*******************************/
    return (1);
}


int main(int ac, char **av, char **env)
{
    if (ac == 2)
        execution(av[1], env);
    return (0);
}
