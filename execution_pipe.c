/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:25:29 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/12 08:57:17 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(t_data *data)
{
	close(data->pipe_ends[0]);
	close(data->pipe_ends[1]);
}

void	ft_execution_(t_var *exec, t_data *data, t_env *env, int len)
{
	char	*path;
	char	**arr;
	int		i;

	i = 0;
	if (!exec->arg)
		exit(1);
	arr = ft_cpy_to_2d(env);
	if (exec->arg && !ft_strncmp(exec->arg[0], "exit", 5))
		return (ft_exit(exec, exec->arg, len));
	if (check_builtin(exec, data))
	{
		while (i < 1000000)
			i++;
		exit(g_stat);
	}
	path = valid_path(exec->arg[0], data->path);
	if (!path)
		return (perror("Invalid path!\n"));
	if (execve(path, exec->arg, arr) == -1)
		(perror("execve"), exit(1));
}

void	ft_multi_childs(t_var *exec, t_data *data, t_env *env)
{
	if (dup2(exec->f_in, 0) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (exec->next != NULL)
	{
		if ((exec->f_out != 1) && dup2(exec->f_out, 1) == -1)
			(perror("dup2 error!\n"), exit(1));
		else if ((exec->f_out == 1) && dup2(data->pipe_ends[1], 1) == -1)
			(perror("dup2 error!\n"), exit(1));
	}
	else
	{
		if (dup2(exec->f_out, 1) == -1)
			(perror("dup2 error!\n"), exit(1));
	}
	ft_close_pipe(data);
	ft_execution_(exec, data, env, data->len);
}

void	ft_void(t_data *data, t_var *exec, t_env *env)
{
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
			ft_multi_childs(exec, data, env);
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
	ft_void(data, exec, env);
	while (wait(&data->status) != -1)
		;
	if (data->status == SIGINT)
		g_stat = 130;
	else if (data->status == SIGQUIT)
		g_stat = 131;
	else
		g_stat = WEXITSTATUS(data->status);
}
