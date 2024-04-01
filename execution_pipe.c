#include "minishell.h"

int ft_execution_(t_var *exec, char **env,  t_data *data)
{
    char    *path;

    path = valid_path(exec->arg[0], env);
    if (!path)
        return (perror("Invalid path!\n"), 0);
    /*******************************/
    if (execve(path, exec->arg, env) == -1)
        return (perror(exec->arg[0]), 0);
    /*******************************/
    return (1);
}

int ft_process(t_var *exec, char **env,  t_data *data)
{
    int pid;
    int pipe_ends[2];

    /*******************************/
    if (pipe(pipe_ends) == -1)
        return (perror("pipe error!\n"), 0);
    /*******************************/
    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"), 0);
    /*******************************/
    if (pid == 0)
    {
        close(pipe_ends[0]);
        if (dup2(pipe_ends[1], 1) < 0)
            (write(2, "dup2 failed!\n", 14), exit(0)); // here too
        ft_execution_(exec, env, data);
    }
    /*******************************/
    else
    {
        close(pipe_ends[1]);
        if (dup2(pipe_ends[0], 0) < 0)
<<<<<<< HEAD
            (write(2, "dup2 failed!\n", 14), exit(0));
        waitpid(pid, NULL, 0);
=======
            return (write(2, "dup2 failed!\n", 14), 0);
        // waitpid(pid, NULL, 0);
>>>>>>> 13808502d87d965b66c1a1961bfd24856c7a38ab
    }
    /*******************************/
    return (1);
}

int ft_execute_pipe(t_list *list, t_var *exec, char **env,  t_data *data)
{
    // int infile;
    // int outfile;
    int pid;
    // int i = 0;

    (void)list;
    t_var *tmp = exec;
    // while (tmp)
    //     tmp = tmp->next;
    // while (tmp->arg[i])
    //     i++;

    pid = fork();
    if (pid == -1)
        return (perror("fork error!\n"), 0);
    if (pid == 0)                                                                                                                    
    {
        if (dup2(exec->f_in, 0) == -1)
            (perror("dup2 error!\n"), exit(0)); // remove 0 add exit
        // ft_execution_(exec, env, data);
        // exec = exec->next;
        while (exec->next)
        {
            ft_process(exec, env, data);
            exec = exec->next;
        }
        if (dup2(exec->f_out, 1) == -1)
            (perror("dup2 error!\n"), exit(0));// here too
        ft_execution_(exec, env, data);
    }
    else
        while(wait(NULL) !=  -1);
    // }
    // else
    //     waitpid(pid, NULL, 0);
    return (1);
}
