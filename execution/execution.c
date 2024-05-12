/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:20:43 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/12 10:07:05 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_var *exec, t_data *data)
{
	if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
		return (ft_echo(exec->arg + 1, exec), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
		return (ft_pwd(exec, data->env, data), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
		return (ft_cd(exec->arg[1], data), data->no_pwd = 0, 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
		return (ft_unset(&data, exec->arg), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "env", 4))
	{
		if (exec->arg[1])
			return (ft_putstr_fd("env: ", 1)
				, perror(exec->arg[1]), exit_status(127, 1), 1);
		return (ft_env(exec, data), 1);
	}
	if (!ft_strncmp(exec->arg[0], "export", 7))
		return (ft_export(exec, data, exec->arg), 1);
	return (0);
}

void	ft_child(t_var *exec, t_data *data, char **new_env)
{
	char	*path;
	char	**args;

	args = get_args(exec);
	if (!args)
		(exit(exit_status(0, 1)));
	if (!args[0])
		(exit(exit_status(0, 1)));
	path = valid_path(args[0], ft_get_line(data, "PATH", 4));
	if (!path)
		return (ft_error(args[0], ": No such file or directory")
			, exit(exit_status(0, 0)));
	if (dup2(exec->f_in, 0) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (dup2(exec->f_out, 1) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (execve(path, args, new_env) == -1)
	{
		if (ft_strchr(args[0], '/'))
			(ft_error(args[0], \
				": is a directory"), exit(126));
		else
			(ft_error(args[0], \
				": command not found"), exit(127));
	}
}

void	ft_fork(t_data *data, t_var *exec, char **new_env)
{
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
	{
		signal(SIGQUIT, ft_signal_c);
		ft_child(exec, data, new_env);
	}
	else
	{
		waitpid(data->pid, &data->status, 0);
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
}

void	ft_execution(t_var *exec, t_data *data, t_env *env)
{
	char	**new_env;

	exit_status(0, 1);
	if (!exec->arg || (!exec->arg[0] && !exec->arg[1]))
		return ;
	if (!exec->arg[0])
		return (exec->arg++, ft_execution(exec, data, env));
	if (exec->arg && !ft_strcmp(exec->arg[0], "exit"))
		return (ft_exit(exec, exec->arg, data->len));
	if (data)
		data->path = get_path(data, exec->arg[ft_arglen(exec->arg) - 1]);
	if (check_builtin(exec, data))
		return ;
	new_env = ft_cpy_to_2d(env);
	ft_fork(data, exec, new_env);
}
