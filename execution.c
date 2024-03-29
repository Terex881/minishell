#include "minishell.h"

static char **ft_free(char **p, int i)
{
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static char **get_paths(char **env)
{
    int     i;
    int     j;
    char    *tmp;
    char    **paths;

    i = 0;
    j = 0;
    while (ft_strncmp(env[i], "PATH=", 5))
        i++;
    while (env[i][j] != '\n' && env[i][j] != '\0')
        j++;
    tmp = ft_substr(env[i], 5, --j);
    if (!tmp)
        return (NULL);
    paths = ft_split(tmp, ':');
    if (!paths)
        return (NULL);
    free(tmp);
    return (paths);
}

static char *valid_path(char *cmd, char **env)
{
    int     i;
    char    *path;
    char    *tmp;
    char    **paths;

    if (!access(cmd, F_OK | X_OK))
        return (ft_strdup(cmd));
    paths = get_paths(env);
    if (!paths)
        return (perror("env failed!"), NULL);
    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        free(paths[i]);
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!access(path, F_OK | X_OK))
            return (ft_free(paths, i + 1), path);
        i++;
        free(path);
    }
    return (free(paths), NULL);
}

int check_builtin(t_var *exec, char **env, t_data *data)
{
    if (!ft_strncmp(exec->arg[0], "echo", 5))
        return (ft_echo(exec->arg + 1), 1);
    if (!ft_strncmp(exec->arg[0], "pwd", 4))
        return (ft_pwd(data->env, data), 1);
    if (!ft_strncmp(exec->arg[0], "env", 4))
    {
		if (exec->arg[1])
			return (perror(exec->arg[1]), 1);
		else
			return (ft_env(exec, data), 1);
	}
    if (!ft_strncmp(exec->arg[0], "cd", 3))
        return (ft_cd(exec->arg[1], data), 1);
    if (!ft_strncmp(exec->arg[0], "exit", 5))
        return (ft_exit(), 1);
    return (0);
}

int ft_execution(t_var *exec, char **env, t_exit info, t_data *data)
{
    char    *path;
    pid_t   pid;

    if (exec->arg[0] == NULL)
        return (0);
    if (check_builtin(exec, env, data))
        return (1);
    path = valid_path(exec->arg[0], env);
    if (!path)
        return (perror(exec->arg[0]), 0);
    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"), 0);
    if (pid == 0)
    {
        if (dup2(exec->f_in, 0) == -1)
            return (perror("dup2 error!\n"), 0);
        if (dup2(exec->f_out, 1) == -1)
            return (perror("dup2 error!\n"), 0);
        if (execve(path, exec->arg, env) == -1)
            return (perror(exec->arg[0]), 0);
    }
    else
        waitpid(pid, &info.exitstat, 0);
    return (free(path), 1);
}

