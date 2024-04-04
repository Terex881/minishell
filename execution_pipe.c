#include "minishell.h"
#include <stdio.h>

char    **ft_cpy_to_2d(t_env *tmp)
{
    char    **ret;
    int     len;
    int     i;

    i = 0;
    len  = ft_lstsize_env(tmp);
    ret = malloc(sizeof(char*) * (len + 1));
    if(!ret)
        return (NULL);
    while(tmp)
    {
        ret[i] = (tmp->line);
        i++;
        tmp = tmp->next;
    }
    ret[i]  = NULL;
    return (ret);
}

void ft_execution_(t_var *exec, t_data *data, t_env *env, int len)
{
    char    *path;
    char    **arr;

    if (!exec->arg) 
        exit(1);
    arr = ft_cpy_to_2d(env);
    if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
    {
        printf("******\n");
        return(ft_exit(exec, &data, exec->arg, len)); 
    }
    check_builtin(exec, data);
    
		
    
	path = valid_path(exec->arg[0], data->path);
    if (!path)
    	(perror("Invalid path!\n"), exit(1));
    if (execve(path, exec->arg, arr) == -1)
		(perror("111"), exit(1)); // change
    // return (1);
}

int ft_process(t_var *exec, t_data *data, t_env *env, int len)
{
    int or_in;
    int pid;
    int pipe_ends[2];

    or_in = dup(STDIN_FILENO);
    if (or_in == -1)
        (perror("dup error!\n"), exit(1));
    while (exec)
    {
        if (pipe(pipe_ends) == -1)
           return (perror("pipe error!\n"), 0);
        pid = fork();
        if (pid == -1)
	    	return (perror("fork\n"), 0);
        else if (pid == 0)
		{       
            if(dup2(exec->f_in, 0) == -1)
                (perror("dup2 error!\n"), exit(1));
			if (exec->next != NULL)
            {
                if((exec->f_out != 1) && dup2(exec->f_out, 1) == -1)
                    (perror("dup2 error!\n"), exit(1));
                else if((exec->f_out == 1) && dup2(pipe_ends[1], 1) == -1)
                    (perror("dup2 error!\n"), exit(1)); 
                
            }
			else
				if(dup2(exec->f_out, 1) == -1)
                    (perror("dup2 error!\n"), exit(1));
			close(pipe_ends[0]);
			close(pipe_ends[1]);
			ft_execution_(exec, data, env, len);
		}
        else
		{
			if(dup2(pipe_ends[0], 0) == -1)
                (perror("dup2 error!\n"), exit(1));
			close(pipe_ends[0]);
			close(pipe_ends[1]);
		}
        exec = exec->next;
    }
    if(dup2(or_in, 0) == -1)
        (perror("dup2 error!\n"));
    close(or_in);
    return 1;
}

void ft_execute_pipe(t_var *exec, t_data *data, t_env *env)
{
    int status;
    int len = ft_varsize(exec);
    
    ft_process(exec, data, env, len);
    
    while(wait(&status) != -1);
    data->stat = WEXITSTATUS(status);
}
