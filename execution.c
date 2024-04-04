#include "minishell.h"
#include <sys/wait.h>

char	**ft_free(char **p, int i)
{
	while (p && p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

char	**get_paths(char *path)
{
    // int     i;
    int		j;
    char	*tmp;
    char	**paths;

    // i = 0;
    j = 0;
    if (!path)
        return (NULL);
    // while (ft_strncmp(tmp_env->line, "PATH=", 5))
    //     tmp_env = tmp_env->next;
    while (path[j] != '\n' && path[j] != '\0')
        j++;
    tmp = ft_substr(path, 5, --j);
    if (!tmp)
        return (NULL);
    paths = ft_split(tmp, ':');
    if (!paths)
        return (NULL);
    free(tmp);
    return (paths);
}

void    ft_error(char *str1, char *str2, char *str3)
{
    int i;

    i = 0;
    while (str1 && str1[i])
        write(2, &str1[i++], 1);
    i = 0;
    while (str2 && str2[i])
        write(2, &str2[i++], 1);
    i = 0;
    while (str3 && str3[i])
        write(2, &str3[i++], 1);
    write(2, "\n", 1);
}

char *valid_path(char *cmd, char *line)
{
    int     i;
    char    *path;
    char    *tmp;
    char    **paths;
    if (!access(cmd, F_OK | X_OK))
        return (ft_strdup(cmd));    //add protection for strdup
    paths = get_paths(line);
    if (!paths)
        return (NULL);
    i = 0;
    if (cmd[i] == '.')
        return (ft_free(paths, i), NULL);
    while (paths && paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");    //add protection for strjoin
        free(paths[i]);
        path = ft_strjoin(tmp, cmd);    //add protection for strjoin
        free(tmp);
        if (!access(path, F_OK | X_OK))
            return (ft_free(paths, i + 1), path);
        i++;
        free(path);
    }
    free(paths);
    ft_error("minshell: ", cmd, ": command not found");
    exit(100); // 127
    return (NULL);
}
int check_builtin(t_var *exec, t_data *data)
{
    
    if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
        return (ft_echo(exec->arg + 1, exec), 1);
    if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
        return (ft_pwd(exec, data->env), 1);
    if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
    {
        ft_export(exec, data, "OLDPWD=");//🌸to put back oldpwd
        return (ft_cd(exec->arg[1], data), 1);
    }
    if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
        return (ft_unset(exec, data, exec->arg[1]), 1);
    if (exec->arg &&!ft_strncmp(exec->arg[0], "env", 4))
    {
		if (exec->arg[1])
			return (perror(exec->arg[1]), 1);
		return (ft_env(exec, data), 1);
	}
    if (!ft_strncmp(exec->arg[0], "export", 7))
    {
        if (exec->arg[1] && exec->arg[2])
            return (ft_error_export(exec->arg[1]), 1);
        return (ft_export(exec, data, exec->arg[1]), 1);
    }
    // if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
    //     (ft_exit(exec, &data, exec->arg)); // 
    return (0);
}

void ft_execution(t_var *exec, t_data *data, t_env *env)//int to return error
{
    char	*path;
    pid_t	pid;
    char	**new_env ;
    int     status;
    int len = ft_varsize(exec);

    new_env= ft_cpy_to_2d(env);
    if (!exec->arg)
        return ((void)ft_free(new_env, 0));
	if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
        (ft_free(new_env, 0), ft_exit(exec, &data, exec->arg, len)); 
    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"));
    if (pid == 0)
    {
        if (check_builtin(exec, data))
        	return ;
        path = valid_path(exec->arg[0], data->path);
        if (!path)
            return (perror(exec->arg[0]), ft_free(new_env, 0), exit(1));
        if (dup2(exec->f_in, 0) == -1)
            (perror("dup2 error!\n"), ft_free(new_env, 0), exit(0));
        if (dup2(exec->f_out, 1) == -1)
            (perror("dup2 error!\n"), ft_free(new_env, 0), exit(0)); // remove return and add exit(0)
        if (execve(path, exec->arg, new_env) == -1)
            (perror(exec->arg[0]), ft_free(new_env, 0), exit(133));
    }
    else
        waitpid(pid, &status, 0);
    ft_free(new_env, 0);
    // free(path);
    data->stat = WEXITSTATUS(status);
    // return (free(path));
    
}


// int check_builtin(t_var *exec, t_data *data)
// {
    
//     if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
//         return (ft_echo(exec->arg + 1, exec), 1);
//     if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
//         return (ft_pwd(exec, data->env), 1);
//     if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
//     {
//         ft_export(exec, data, "OLDPWD=");//🌸to put back oldpwd
//         return (ft_cd(exec->arg[1], data), 1);
//     }
//     if (exec->arg &&!ft_strncmp(exec->arg[0], "env", 4))
//     {
// 		if (exec->arg[1])
// 			return (perror(exec->arg[1]), 1);
// 		else
// 			return (ft_env(exec, data), 1);
// 	}
//     if (!ft_strncmp(exec->arg[0], "export", 7))
//     {
//         if (exec->arg[1] && exec->arg[2])
//             return (ft_error_export(exec->arg[1]), 1);
//         return (ft_export(exec, data, exec->arg[1]), 1);
//     }
//     if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
//         return (ft_unset(exec, data, exec->arg[1]), 1);
//     // if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
//     //     (ft_exit(exec, &data, exec->arg)); // 
//     return (0);
// }