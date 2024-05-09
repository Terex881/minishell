/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:53:14 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/09 20:03:38 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_cmd(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ft_error(cmd, ": filename argument required");
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
}

void	ft_close_pipe(t_data *data)
{
	close(data->pipe_ends[0]);
	close(data->pipe_ends[1]);
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
			return (exit_status(127, 1), NULL);
		if ((cmd[0] == '.' || cmd[0] == '/') && !access(cmd, F_OK))
			(ft_error(cmd, ": Permission denied"), exit(exit_status(126, 1)));
		if (cmd[0] == '.' || cmd[0] == '/')
			return (exit_status(127, 1), NULL);
		while (paths && paths[++i])
		{
			(1) && (tmp = ft_strjoin(paths[i], "/"), path = ft_strjoin(tmp, cmd));
			if (!access(path, F_OK | X_OK))
				return (path);
		}
		if (ft_strchr(cmd, '/'))
			(ft_error(cmd, ": No such file or directory"), exit(exit_status(127, 1)));
	}
	(ft_error(cmd, ": command not found"), exit_status(127, 1), exit(exit_status(0, 0)));
}
