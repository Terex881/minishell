/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:15:01 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:29:11 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_out(t_list *tmp, t_var *var, t_data *data)
{
	char	*name;

	name = ft_varjoin(&tmp->next, data);
	if (tmp->type == R_IN)
	{
		var->f_in = open(name, O_RDWR);
		tmp->skip = true;
		if (var->f_in == -1)
			return (perror(name), 1);
	}
	else if (tmp->type == R_OUT)
		var->f_out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (tmp->type == APPEND)
		var->f_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	tmp->skip = true;
	if (var->f_out == -1)
		return (perror(name), 1);
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
	char	*str;
	int		fd;

	while (1)
	{
		signal(SIGINT, ft_signal_her);
		line = readline(">");
		if (!ttyname(0))
			(1) && (fd = open(ttyname(2), O_RDONLY), dup2(0, fd));
		if (!line || !ft_strcmp(limter, line))
		{
			free (line);
			break ;
		}
		if (data->val == 0)
		{
			str = line;
			line = ft_expand_her_doc(line, data);
			free(str);
		}
		write(exec->f_in, line, ft_strlen(line));
		write(exec->f_in, "\n", 1);
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
