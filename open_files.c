/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:15:01 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/11 15:05:20 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_out(t_list *tmp, t_var *var, t_data *data)
{
	char	*name;

	name = ft_varjoin(&tmp->next, data);
	if (((tmp->type == R_OUT || tmp->type == R_IN) && !name)
		|| (tmp->next->type != D_Q && ft_strchr(tmp->next->value, ' ')))
	{
		ft_error(name, ": ambiguous redirect");
		return (exit_status(1, 1), 1);
	}
	else if (tmp->type == R_IN)
	{
		var->f_in = open(name, O_RDWR);
		tmp->skip = true;
		if (var->f_in == -1)
			return (ft_error(name, ": No such file or directory"), \
		exit_status(1, 1), 1);
	}
	else if (tmp->type == R_OUT)
		var->f_out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (tmp->type == APPEND)
		var->f_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	tmp->skip = true;
	if (var->f_out == -1)
		return (perror(name), exit_status(1, 1), 1);
	return (0);
}

int	ft_open_files(t_list **list, t_var *var, t_data *data)
{
	t_list	*tmp;
	int		check;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			var = var->next;
		if (tmp->type == R_IN || tmp->type == R_OUT || tmp->type == APPEND)
		{
			check = ft_in_out(tmp, var, data);
			if (check == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_read_herdoc(t_var *exec, t_data *data, char *limter)
{
	char	*line;
	int		fd;
	char	*res;

	while (1)
	{
		signal(SIGINT, ft_signal_her);
		line = readline("> ");
		if (!ttyname(0))
			(1) && (fd = open(ttyname(2), O_RDONLY), dup2(0, fd));
		if (!line || !ft_strcmp(limter, line))
		{
			free (line);
			break ;
		}
		if (data->val == 0)
		{
			res = ft_expand_her_doc(line, data);
			ft_putstr_fd(res, exec->f_in);
		}
		else
			ft_putstr_fd(line, exec->f_in);
		ft_putstr_fd("\n", exec->f_in);
		free(line);
	}
}

void	ft_open_her_doc(t_list **list, t_var *exec, t_data *data)
{
	t_list	*tmp;
	char	*limter;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			exec = exec->next;
		if (tmp->type == HER_DOC)
		{
			tmp->skip = true;
			exec->f_in = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC, 0644);
			data->val = 0;
			limter = ft_varjoin(&tmp->next, data);
			ft_read_herdoc(exec, data, limter);
			close(exec->f_in);
			exec->f_in = open("/tmp/test", O_RDONLY);
		}
		tmp = tmp->next;
	}
	unlink("/tmp/test");
}
