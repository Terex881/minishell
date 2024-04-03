#include "minishell.h"

char	**ft_free(char **p, int i)
{
	while (p[i])
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

char *valid_path(char *cmd, char *line)
{
    int     i;
    char    *path;
    char    *tmp;
    char    **paths;

    if (!access(cmd, F_OK | X_OK))
        return (ft_strdup(cmd));//add protection for strdup
    paths = get_paths(line);
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");//add protection for strjoin
        free(paths[i]);
        path = ft_strjoin(tmp, cmd);//add protection for strjoin
        free(tmp);
        if (!access(path, F_OK | X_OK))
            return (ft_free(paths, i + 1), path);
        i++;
        free(path);
    }
    return (free(paths), NULL);
}

int check_builtin(t_var *exec, t_data *data)
{
    if (!ft_strncmp(exec->arg[0], "echo", 5))
        return (ft_echo(exec->arg + 1, exec), 1);
    if (!ft_strncmp(exec->arg[0], "pwd", 4))
        return (ft_pwd(exec, data->env), 1);
    if (!ft_strncmp(exec->arg[0], "cd", 3))
    {
        ft_export(exec, data, "OLDPWD=");//🌸to put back oldpwd
        return (ft_cd(exec->arg[1], data), 1);
    }
    if (!ft_strncmp(exec->arg[0], "env", 4))
    {
		if (exec->arg[1])
			return (perror(exec->arg[1]), 1);
		else
			return (ft_env(exec, data), 1);
	}
    if (!ft_strncmp(exec->arg[0], "export", 7))
        return (ft_export(exec, data, exec->arg[1]), 1);
    if (!ft_strncmp(exec->arg[0], "unset", 6))
        return (ft_unset(exec, data, exec->arg[1]), 1);
    if (!ft_strncmp(exec->arg[0], "exit", 5))
        return (ft_exit(exec, &data, exec->arg), 1);
    return (0);
}

int ft_execve(char *path, t_var *exec, t_data *data)
{
    t_env *tmp;

	tmp = data->env;
    while (execve(path, exec->arg, &tmp->line) == -1)
		tmp = tmp->next;
    if (execve(path, exec->arg, &tmp->line) == -1)
        return (perror(tmp->line), 0);
    return (-1);
}

void ft_execution(t_var *exec, t_data *data)//int to return error
{
    char    *path;
    pid_t   pid;

    if (exec->arg[0] == NULL)
        return ;
    if (check_builtin(exec, data))
        return ;
    path = valid_path(exec->arg[0], data->path);
    if (!path)
        return (perror(exec->arg[0]));
    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"));
    if (pid == 0)
    {
        if (dup2(exec->f_in, 0) == -1)
            (perror("dup2 error!\n"), exit(0));
        if (dup2(exec->f_out, 1) == -1)
            (perror("dup2 error!\n"), exit(0)); // remove return and add exit(0)
        if (ft_execve(path, exec, data) == -1)
            (perror(exec->arg[0]), exit(0));
    }
    else
        waitpid(pid, NULL, 0);
    while(exec->f_out > 2)
    {
        // printf("------>%d\n", exec->f_out);
        close(exec->f_out);
        exec->f_out--;
        // printf("====>%d\n", exec->f_out);
    }
    while(exec->f_in > 2)
    {
        // printf("------>%d\n", exec->f_in);
        close(exec->f_in);
        exec->f_in--;
        // printf("====>%d\n", exec->f_in);
    }
    return (free(path));
}

