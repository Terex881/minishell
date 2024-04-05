#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>


void ft_close_pipe(t_data *data)
{
    close(data->pipe_ends[0]);
	close(data->pipe_ends[1]);
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
        return(ft_exit(exec, &data, exec->arg, len)); 
    }
    if(check_builtin(exec, data))
        return(exit(data->stat));
	path = valid_path(exec->arg[0], data->path);
    if (!path)
        return (perror("Invalid path!\n"), exit(126)); // 126
    if (execve(path, exec->arg, arr) == -1)
		return (perror("execve"), exit(1)); // change
}


void ft_multi_childs(t_var *exec, t_data *data, t_env *env)
{
    if(dup2(exec->f_in, 0) == -1)
        (perror("dup2 error!\n"), exit(1));
	if (exec->next != NULL)
    {
        if((exec->f_out != 1) && dup2(exec->f_out, 1) == -1)
            (perror("dup2 error!\n"), exit(1));
        else if((exec->f_out == 1) && dup2(data->pipe_ends[1], 1) == -1)
            (perror("dup2 error!\n"), exit(1));     
    }
	else
    {

		if(dup2(exec->f_out, 1) == -1)
            (perror("dup2 error!\n"), exit(1));
    }
    ft_close_pipe(data);
	ft_execution_(exec, data, env, data->len);

}
void ft_execute_pipe(t_var *exec, t_data *data, t_env *env)
{
    data->len= ft_varsize(exec);
    data->or_in = dup(STDIN_FILENO);
    if (data->or_in == -1)
        (perror("dup error!\n"), exit(1));
    while (exec)
    {
        if (pipe(data->pipe_ends) == -1)
           return (perror("pipe error!\n"));
        data->pid = fork();
        if (data->pid == -1)
	    	return (perror("fork\n"));
        else if (data->pid == 0)
            ft_multi_childs(exec, data, env);
        else
		{
			if(dup2(data->pipe_ends[0], 0) == -1)
                (perror("dup2 error!\n"), exit(1));
            ft_close_pipe(data);
            wait(&data->status);
		}
        exec = exec->next;
    }
    if(dup2(data->or_in, 0) == -1)
        (perror("dup2 error!\n"));
    close(data->or_in);
    data->stat = WEXITSTATUS(data->status); // check
}
















































// void ft_process(t_var *exec, t_data *data, t_env *env, int len)
// {
//     int or_in;
//     int pid;
//     int status;
//     int pipe_ends[2];

//     or_in = dup(STDIN_FILENO);
//     if (or_in == -1)
//         (perror("dup error!\n"), exit(1));
//     while (exec)
//     {
//         if (pipe(pipe_ends) == -1)
//            return (perror("pipe error!\n"));
//         pid = fork();
//         if (pid == -1)
// 	    	return (perror("fork\n"));
//         else if (pid == 0)
// 		{       
//             if(dup2(exec->f_in, 0) == -1)
//                 (perror("dup2 error!\n"), exit(1));
// 			if (exec->next != NULL)
//             {
//                 if((exec->f_out != 1) && dup2(exec->f_out, 1) == -1)
//                     (perror("dup2 error!\n"), exit(1));
//                 else if((exec->f_out == 1) && dup2(pipe_ends[1], 1) == -1)
//                     (perror("dup2 error!\n"), exit(1));     
//             }
// 			else
// 				if(dup2(exec->f_out, 1) == -1)
//                     (perror("dup2 error!\n"), exit(1));
// 			close(pipe_ends[0]);
// 			close(pipe_ends[1]);
// 			ft_execution_(exec, data, env, len);
// 		}
//         else
// 		{
// 			if(dup2(pipe_ends[0], 0) == -1)
//                 (perror("dup2 error!\n"), exit(1));
// 			close(pipe_ends[0]);
// 			close(pipe_ends[1]);
//             while(wait(&status) != -1);
//             data->stat = WEXITSTATUS(status);
// 		}
//         exec = exec->next;
//     }
//     if(dup2(or_in, 0) == -1)
//         (perror("dup2 error!\n"));
//     close(or_in);
//     return ;
// }

// void ft_execute_pipe(t_var *exec, t_data *data, t_env *env)
// {
//     int len = ft_varsize(exec);
    
//     ft_process(exec, data, env, len);
// }
