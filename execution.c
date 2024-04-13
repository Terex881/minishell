/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:20:43 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/13 20:17:25 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ft_error("minshell: ", cmd, ": filename argument required");
		ft_error(".: ", "usage: . filename [arguments]", NULL);
		exit(2);
	}
}

char	*valid_path(char *cmd, char *line)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**paths;

	if (cmd && ft_strlen(cmd))
	{
		check_cmd(cmd);
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		paths = get_paths(line);
		if (!paths)
			return (NULL);
		if (cmd[0] == '.' || cmd[0] == '/')
			return (NULL);
		i = -1;
		while (paths && paths[++i])
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, cmd);
			if (!access(path, F_OK | X_OK))
				return (path);
		}
	}
	(ft_error("minshell: ", cmd, ": command not found"), exit(127));
}

int	check_builtin(t_var *exec, t_data *data)
{
	if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
		return (ft_echo(exec->arg + 1, exec, data), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
		return (ft_pwd(exec, data->env), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
		return (ft_cd(exec->arg[1], data), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
		return (ft_unset(&data, exec->arg), 1);
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

void	ft_child(t_var *exec, t_data *data, char **new_env)
{
	char	*path;
	char	**args;
	
	args = get_args(exec);
	if (!args || !args[0])
		(perror("malloc error!\n"), exit(1));
	path = valid_path(args[0], data->path);
	if (!path)
		return (perror(args[0]), exit(127));
	if (dup2(exec->f_in, 0) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (dup2(exec->f_out, 1) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (execve(path, args, new_env) == -1)
		(ft_error("minshell: ", args[0], \
			": command not found"), exit(127));
}

void	ft_execution(t_var *exec, t_data *data, t_env *env)
{
	char	**new_env;

	new_env = ft_cpy_to_2d(env);
	if (!exec->arg)
		return ;
	if (exec->arg && !ft_strcmp(exec->arg[0], "exit"))
		return (ft_exit(exec, exec->arg, data->len));
	if (check_builtin(exec, data))
		return ;
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
		ft_child(exec, data, new_env);
	else
	{
		waitpid(data->pid, &data->status, 0);
		if (data->status == SIGINT)
			g_stat = 130;
		else if (data->status == SIGQUIT)
			g_stat = 131;
		else
			g_stat = WEXITSTATUS(data->status);
	}
}
