#include "minishell.h" //🌸

static char **get_paths(char **env)
{
    int i = 0;
    int j = 0;

    while (ft_strncmp(env[i], "PATH=", 5))
        i++;
    while (env[i][j] != '\n' && env[i][j] != '\0')
        j++;
    return (ft_split(ft_substr(env[i], 5, --j), ':'));
}

static char *valid_path(char *cmd, char **env)
{
    int     i = 0;
    char    *path;
    char    *tmp;
    char    **paths;

    if (!access(cmd, F_OK | X_OK))
        return (ft_strdup(cmd));
    paths = get_paths(env);
    if (!paths)
        return (perror("env failed!"), NULL);
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!access(path, F_OK | X_OK))
            return (path);
        i++;
        free(path);
    }
    return (NULL);
}

int ft_execution(t_var *exec, char **env)
{
    char    *path;
    pid_t   pid;

    path = valid_path(exec->arg[0], env);
    if (!path)
        return (perror("Invalid path!\n"), 0);
    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"), 0);
    if (pid == 0)
    {
        if (dup2(exec->f_out, 1) == -1)
            return (perror("dup2 error!\n"), 0);
        if (execve(path, exec->arg, env) == -1)
            return (perror("execv error!\n"), 0);
    }
    else
    {
        if (dup2(exec->f_in, 0) == -1)
            return (perror("dup2 error!\n"), 0);
        waitpid(pid, NULL, 0);
    }
    return (1);
}
//fix here_doc and redirection in