/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:20:43 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/09 15:13:22 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_cmd(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ft_error( cmd, ": filename argument required");
		ft_error("usage: . filename [arguments]", NULL);
		// ft_error(".: ", "usage: . filename [arguments]", NULL);
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
		(check_cmd(cmd), i = -1);
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		paths = get_paths(line);
		if (!paths)
			return (exit_status(126, 1), NULL);
		if ((cmd[0] == '.' || cmd[0] == '/') && !access(cmd, F_OK))
			(ft_error( cmd, ": Permission denied"), exit(exit_status(126, 1)));
		if (cmd[0] == '.' || cmd[0] == '/')
			return (exit_status(127, 1), NULL);
		while (paths && paths[++i])
		{
			(tmp = ft_strjoin(paths[i], "/"), path = ft_strjoin(tmp, cmd));
			if (!access(path, F_OK | X_OK))
				return (path);
		}
		if (ft_strchr(cmd, '/'))
			(ft_error( cmd, ": No such file or directory"), exit(exit_status(127, 1)));
	}
	(ft_error( cmd, ": command not found"), exit_status(127, 1), exit(exit_status(0, 0)));
}

int	check_builtin(t_var *exec, t_data *data)
{
	if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
		return (ft_echo(exec->arg + 1, exec, data), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
		return (ft_pwd(exec, data->env, data), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
		return (ft_cd(exec->arg[1], data), 1);
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
	if (!args || !args[0])
		(ft_error( args[0], \
				": command not found"), exit(1));
	path = valid_path(args[0], ft_get_line(data, "PATH", 4));
	if (!path)
		return (ft_error( args[0], ": No such file or directory"), exit(exit_status(0, 0)));//127
	if (dup2(exec->f_in, 0) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (dup2(exec->f_out, 1) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (execve(path, args, new_env) == -1)
	{
		if (ft_strchr(args[0], '/'))//?
			(ft_error(args[0], \
				": is a directory"), exit(126));
		else
			(ft_error(args[0], \
				": command not found"), exit(127));
	}
}

void ft_fork(t_data *data, t_var *exec, char **new_env)
{
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
	{
		signal(SIGQUIT, ft_signal_c);
		signal(SIGINT, SIG_DFL);
		ft_child(exec, data, new_env);
	}
	else
	{
		waitpid(data->pid, &data->status, 0);
		if(WIFSIGNALED(data->status))
		{
			exit_status(WTERMSIG(data->status) + 128, 1);
			if (WTERMSIG(data->status) == SIGQUIT)
				printf("Quit: 3\n");
			if(WTERMSIG(data->status) == SIGINT)
				ft_putstr_fd("\n", 1);
		}
		else
			exit_status(WEXITSTATUS(data->status), 1);
	}
}


void	ft_execution(t_var *exec, t_data *data, t_env *env)
{
	char	**new_env;

	if(!exec->arg || (!exec->arg[0] && !exec->arg[1]))
		return;
	if (!exec->arg[0])
		return (exec->arg++, ft_execution(exec, data, env));
	if (exec->arg && !ft_strcmp(exec->arg[0], "exit"))
		return (ft_exit(exec, exec->arg, data->len));
	data->path = get_path(data, exec->arg[ft_arglen(exec->arg) - 1]);
	if (check_builtin(exec, data))
		return ;
	new_env = ft_cpy_to_2d(env);
	ft_fork(data, exec, new_env);

}
