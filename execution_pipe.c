#include "minishell.h"
#include <unistd.h>

int ft_execution_(t_var *exec, t_data *data)
{
    char    *path;
	t_env *tmp;

	tmp = data->env;
    path = valid_path(exec->arg[0], data->path);
    if (!path)
        (perror("Invalid path!\n"), exit(1));
	while (execve(path, exec->arg, &tmp->line) == -1)
		tmp = tmp->next;
    if (execve(path, exec->arg, &tmp->line) == -1)
        (perror(exec->arg[0]), exit(1));
    return (1);   
}



int ft_process(t_var *exec, t_data *data)
{
    int or_in;
    int pid;
    int pipe_ends[2];

    or_in = dup(STDIN_FILENO);
    if(or_in == -1)
        (perror("dup error!\n"), exit(0));
    while (exec)
    {
        if (pipe(pipe_ends) == -1)
           return (perror("pipe error!\n"), 0);
        pid = fork();
        if (pid == -1)
	    	return (perror("fork"), 0);
        else if (pid == 0)
		{       
            if(dup2(exec->f_in, 0) == -1)
                (perror("dup2 error!\n"), exit(0));
			if (exec->next != NULL)
            {
				if(dup2(pipe_ends[1], 1) == -1)
                    (perror("dup2 error!\n"), exit(0));
            }
			else
				if(dup2(exec->f_out, 1) == -1)
                    (perror("dup2 error!\n"), exit(0));
			close(pipe_ends[0]);
			close(pipe_ends[1]);
			ft_execution_(exec, data);
		}
        else
		{
			if(dup2(pipe_ends[0], 0) == -1)
                (perror("dup2 error!\n"), exit(0));
			close(pipe_ends[0]);
			close(pipe_ends[1]);
		}
        exec = exec->next;
    }
    if(dup2(or_in, 0) == -1)
        (perror("dup2 error!\n"), exit(0));
    close(or_in);
    return 1;
}

void ft_execute_pipe(t_var *exec, t_data *data)
{
    int exit_status;
    
    // ft_print_var(exec);
    ft_process(exec, data);
    
    while(wait(NULL) != -1);
    // sleep(100);
    
}
