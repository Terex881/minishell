/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:25:29 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/09 20:02:46 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_(t_var *exec, t_data *data, t_env *env, int len)
{
	char	*path;
	char	**arr;
	char	**args;
	int		i;

	i = 0;
	if (!exec->arg)
		exit(0);
	arr = ft_cpy_to_2d(env);
	if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
		return (ft_exit(exec, exec->arg, len));
	if (check_builtin(exec, data))
		exit(exit_status(0, 0));
	args = get_args(exec);
	if (!args)
		return (exit(exit_status(0, 1)));
	if (!args[0])
		(exit(exit_status(0, 1)));
	path = valid_path(args[0], ft_get_line(data, "PATH", 5) + 5);
	if (!path)
		return (ft_error(args[0], ": No such file or directory")
			, exit(exit_status(0, 0)));
	if (execve(path, args, arr) == -1)
		(perror("execve"), exit(1));
}

void	ft_multi_childs(t_var *exec, t_data *data, t_env *env)
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
	ft_execution_(exec, data, env, data->len);
}

void	ft_void(t_data *data, t_var *exec, t_env *env)
{
	while (exec)
	{
		if (pipe(data->pipe_ends) == -1)
			return (perror("pipe error!\n"));
		data->pid = fork();
		if (data->pid == -1)
			return (perror("fork\n"));
		else if (data->pid == 0)
		{
			signal(SIGQUIT, ft_signal);
			ft_multi_childs(exec, data, env);
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

void	ft_execute_pipe(t_var *exec, t_data *data, t_env *env)
{
	exit_status(0, 1);
	data->status = 0;
	data->len = ft_varsize(exec);
	data->or_in = dup(STDIN_FILENO);
	if (data->or_in == -1)
		(perror("dup error!\n"), exit(1));
	ft_void(data, exec, env);
	waitpid(data->pid, &data->status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (WIFSIGNALED(data->status))
	{
		exit_status(WTERMSIG(data->status) + 128, 1);
		if (WTERMSIG(data->status) == SIGQUIT)
			printf("Quit: 3\n");
		if (WTERMSIG(data->status) == SIGINT)
			ft_putstr_fd("\n", 1);
	}
	else
		exit_status(WEXITSTATUS(data->status), 1);
}
