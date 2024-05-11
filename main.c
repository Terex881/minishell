/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:20:33 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/11 19:51:06 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int new_stat, int set)
{
	static int	status;

	if (set)
		status = new_stat;
	return (status);
}

void	ft_close(t_var *exec)
{
	while (exec)
	{
		while (exec->f_out > 2)
		{
			close(exec->f_out);
			exec->f_out--;
		}
		while (exec->f_in > 2)
		{
			close(exec->f_in);
			exec->f_in--;
		}
		exec = exec->next;
	}
}

void	ft_success(t_list **list, t_env *env, t_data *data)
{
	t_var	*exec;

	exec = NULL;
	if (ft_syntax_error(list) == 0)
	{
		ft_expand(list, data);
		exec = ft_allocate_list(list);
		ft_open_her_doc(list, exec, data);
		if (ft_open_files(list, exec, data) == 0 || exec->next)
		{
			ft_len_node_elem(list, exec);
			ft_copy_to_list(list, exec, data);
			if (exec->next)
				ft_execute_pipe(exec, data, env);
			else
				ft_execution(exec, data, env);
		}
		ft_close(exec);
	}
}

int	ft_all(t_list **list, t_env *env, t_data *data)
{
	t_list	*node;
	char	*line;
	int		tok;

	line = NULL;
	node = NULL;
	while (1)
	{
		ft_signal();
		tok = ft_token(line, node, list);
		if (tok == 0)
			return (ft_putstr_fd("exit\n", 1), c_malloc(0, 0), 0);
		else if (tok > 0)
		{
			g_stat = 1;
			ft_success(list, env, data);
			g_stat = 0;
			ft_lstfind_env(&data->env, "_", ft_strjoin("_=", data->path));
		}
	}
	c_malloc(0, 0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_list	*list;
	t_data	*data;
	t_env	*env1;

	if (ac > 1)
		return (ft_error(av[1], ": No such file or directory"), 1);
	rl_catch_signals = 0;
	list = NULL;
	env1 = ft_get_env(&data, env);
	ft_lstfind_env(&data->env, "SHLVL", ft_strjoin("SHLVL=", data->shlvl));
	ft_all(&list, env1, data);
	return (0);
}
