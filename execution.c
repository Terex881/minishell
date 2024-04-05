#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

char	**ft_free(char **p, int i)
{
	while (p && p[i])
	{
		// free(p[i]);
		i++;
	}
	// free(p);
	return (NULL);
}

char	**get_paths(char *path)
{
    int		j;
    char	*tmp;
    char	**paths;

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
    return (paths);
}

void    ft_error(char *str1, char *str2, char *str3) // check this
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

    if (cmd && ft_strlen(cmd))
    {
        if (cmd[0] == '.' && cmd[1] == '\0')
        {
            ft_error("minshell: ", cmd, ": filename argument required");
            ft_error(".: ", "usage: . filename [arguments]", NULL);
            exit(2002);
        }
        if (!access(cmd, F_OK | X_OK))
            return (ft_strdup(cmd));    //add protection for strdup
        paths = get_paths(line);
        if (!paths)
            return (NULL);
        i = 0;
        if (cmd[i] == '.' || cmd[i] == '/')
            return ( NULL);
        while (paths && paths[i])
        {
            tmp = ft_strjoin(paths[i], "/");   
            path = ft_strjoin(tmp, cmd);   
            if (!access(path, F_OK | X_OK))
                return (path);
            i++;  
        }
    }
    ft_error("minshell: ", cmd, ": command not found"); //put it
    exit(100); // 127
    return (NULL);
}
int check_builtin(t_var *exec, t_data *data)
{
    if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
        return (ft_echo(exec->arg + 1, exec, data), 1);
    if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
        return (ft_pwd(exec, data->env), 1);
    if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
    {
        // ft_export(exec, data, "OLDPWD=");//🌸to put back oldpwd
        return (ft_cd(exec->arg[1], data),  1);
    }
    if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
        return (ft_unset(exec, &data, exec->arg), 1);
    if (exec->arg &&!ft_strncmp(exec->arg[0], "env", 4))
    {
		if (exec->arg[1])
			return (perror(exec->arg[1]), 1);
		return (ft_env(exec, data), 1);
	}
    if (!ft_strncmp(exec->arg[0], "export", 7))
        return (ft_export(exec, data, exec->arg), 1);
    return (0);
}


void ft_child(t_var *exec, t_data *data, char **new_env)
{
    char *path;
    path = valid_path(exec->arg[0], data->path);
    if (!path)
        return (perror(exec->arg[0]), exit(126));
    if (dup2(exec->f_in, 0) == -1)
        (perror("dup2 error!\n"),  exit(1));
    if (dup2(exec->f_out, 1) == -1)
        (perror("dup2 error!\n"),  exit(1));
    if (execve(path, exec->arg, new_env) == -1)
        (ft_error("minshell: ", exec->arg[0], ": command not found"),  exit(133));       
    
}
void ft_execution(t_var *exec, t_data *data, t_env *env)
{
    char	**new_env ;
    
    new_env= ft_cpy_to_2d(env);
    if (!exec->arg)
        return ;
	if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
    {
        printf("***\n");
        (ft_exit(exec, &data, exec->arg, data->len)); 
    }
    if (check_builtin(exec, data))
        return ;
    data->pid = fork();
    if (data->pid == -1)
        return (perror("fork"));
    if (data->pid == 0)
        ft_child(exec, data, new_env);
    else
    {
        while(wait(&data->status) != -1);
        data->stat = WEXITSTATUS(data->status);
    }
}
