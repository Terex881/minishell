/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:25:29 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/07 22:01:07 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/wait.h>

void	ft_close_pipe(t_data *data)
{
	close(data->pipe_ends[0]);
	close(data->pipe_ends[1]);
}

void	ft_execution_(t_var *exec, t_data *data, t_env *env, int len, int *g_stat)
{
	char	*path;
	char	**arr;
	char	**args;
	int		i;

	i = 0;
	if (!exec->arg)
		exit(1);
	arr = ft_cpy_to_2d(env);
	if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
		return (ft_exit(exec, exec->arg, len, g_stat));
	if (check_builtin(exec, data, g_stat))
	{
		exit(*g_stat);//
	}
	args = get_args(exec);
	if (!args || !args[0])
		return (perror("malloc error!\n"));////to check	
	path = valid_path(args[0], ft_get_line(data, "PATH", 5) + 5, g_stat);
	if (!path)
		return (perror("Invalid path!\n"));
	if (execve(path, args, arr) == -1)
		(perror("execve"), exit(1));
}

void	ft_multi_childs(t_var *exec, t_data *data, t_env *env, int *g_stat)
{
	if (dup2(exec->f_in, 0) == -1)
		(exit(1));
	if (exec->next != NULL)
	{
		if ((exec->f_out != 1) && dup2(exec->f_out, 1) == -1)
			(exit(1));
		else if ((exec->f_out == 1) && dup2(data->pipe_ends[1], 1) == -1)
			(exit(1));
	}
	else
	{
		if (dup2(exec->f_out, 1) == -1)
			(exit(1));
	}
	ft_close_pipe(data);
	ft_execution_(exec, data, env, data->len, g_stat);
	
}

void	ft_void(t_data *data, t_var *exec, t_env *env, int *g_stat)
{
	data->status = 0;
	data->len = ft_varsize(exec);
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
		{
			// signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, ft_signal_c);
			ft_multi_childs(exec, data, env, g_stat);
		}
		else
		{
			if (dup2(data->pipe_ends[0], 0) == -1)
				(perror("dup2 error!\n"), exit(1));
			ft_close_pipe(data);
		}
		exec = exec->next;
	}
	if (dup2(data->or_in, 0) == -1)
		(perror("dup2 error!\n"));
	(close(data->or_in), data->len = 0);
	return ;
}

void	ft_execute_pipe(t_var *exec, t_data *data, t_env *env, int *g_stat)
{
	ft_void(data, exec, env, g_stat);

	waitpid(-1, &data->status, 0);
	while (waitpid(-1,NULL, 0) != -1)
		;
	if(WIFSIGNALED(data->status) != 0)
	{
		*g_stat = WTERMSIG(data->status) + 128;
	}
	else
		*g_stat = WEXITSTATUS(data->status);
}
