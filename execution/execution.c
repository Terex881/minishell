/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:20:43 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/07 20:58:47 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/signal.h>


static void	check_cmd(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ft_error("minshell: ", cmd, ": filename argument required");
		ft_error(".: ", "usage: . filename [arguments]", NULL);
		exit(2);
	}
}

char	*valid_path(char *cmd, char *line, int *g_stat)
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
			return (*g_stat = 126, NULL);
		if ((cmd[0] == '.' || cmd[0] == '/') && !access(cmd, F_OK))
			(*g_stat = 126, ft_error("minshell: ", cmd, ": Permission denied"), exit(*g_stat));
			
			// return (g_stat = 126, NULL);
		if (cmd[0] == '.' || cmd[0] == '/')
			return (*g_stat = 127, NULL);
		while (paths && paths[++i])
		{
			(tmp = ft_strjoin(paths[i], "/"), path = ft_strjoin(tmp, cmd));
			if (!access(path, F_OK | X_OK))
				return (path);
		}
		if (ft_strchr(cmd, '/'))
			(*g_stat = 127, ft_error("minshell: ", cmd, ": No such file or directory"), exit(*g_stat));
	}
	(ft_error("minshell: ", cmd, ": command not found"), *g_stat = 127, exit(*g_stat));
}

int	check_builtin(t_var *exec, t_data *data, int *g_stat)
{
	if (exec->arg && !ft_strncmp(exec->arg[0], "echo", 5))
		return (ft_echo(exec->arg + 1, exec, data, g_stat), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "pwd", 4))
		return (ft_pwd(exec, data->env, data), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "cd", 3))
		return (ft_cd(exec->arg[1], data, g_stat), 1);
	if (exec->arg && !ft_strncmp(exec->arg[0], "unset", 6))
		return (ft_unset(&data, exec->arg, g_stat), 1);
	if (exec->arg &&!ft_strncmp(exec->arg[0], "env", 4))
	{
		if (exec->arg[1])
			return (ft_putstr_fd("env: ", 1)
				, perror(exec->arg[1]), *g_stat = 127, 1);
		return (ft_env(exec, data, g_stat), 1);
	}
	if (!ft_strncmp(exec->arg[0], "export", 7))
		return (ft_export(exec, data, exec->arg, g_stat), 1);
	return (0);
}

void	ft_child(t_var *exec, t_data *data, char **new_env, int *g_stat)
{
	char	*path;
	char	**args;
	args = get_args(exec);
	if (!args || !args[0])
		(ft_error("minshell: ", args[0], \
				": command not found"), exit(1));
	path = valid_path(args[0], ft_get_line(data, "PATH", 4), g_stat);
	if (!path)
		return (ft_error("minshell: ", args[0], ": No such file or directory"), exit(*g_stat));//127
	if (dup2(exec->f_in, 0) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (dup2(exec->f_out, 1) == -1)
		(perror("dup2 error!\n"), exit(1));
	if (execve(path, args, new_env) == -1)
	{
		if (ft_strchr(args[0], '/'))//?
			(ft_error("minshell: ", args[0], \
				": is a directory"), exit(126));
		else
			(ft_error("minshell: ", args[0], \
				": command not found"), exit(127));
	}
}

void	ft_execution(t_var *exec, t_data *data, t_env *env, int *g_stat)
{
	char	**new_env;

	new_env = ft_cpy_to_2d(env);
	if (!exec->arg)
		return ;
	if (!exec->arg[0])
		return (exec->arg++, ft_execution(exec, data, env, g_stat));
	if (exec->arg && !ft_strcmp(exec->arg[0], "exit"))
		return (ft_exit(exec, exec->arg, data->len, g_stat));
	data->path = get_path(data, exec->arg[ft_arglen(exec->arg) - 1]);
	if (check_builtin(exec, data, g_stat))
		return ;
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
	{
		signal(SIGQUIT, ft_signal_c);
		// signal(SIGINT, SIG_DFL);
		ft_child(exec, data, new_env, g_stat);
	}
	else
	{
		waitpid(data->pid, &data->status, 0);
		if(WIFSIGNALED(data->status))
		{
			*g_stat = WTERMSIG(data->status) + 128;
			if (WTERMSIG(data->status) == SIGQUIT)
				printf("Quit: 3\n");
		}
		else
			*g_stat = WEXITSTATUS(data->status);
		if(WTERMSIG(data->status) == SIGINT)
		{
			ft_putstr_fd("\n", 1);		
			
		}
	}
}
