/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:20:33 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/06 06:20:48 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(t_var *exec)
{
	while(exec)
	{
		while(exec->f_out > 2)
    	{
    	    close(exec->f_out);
    	    exec->f_out--;
    	}
    	while(exec->f_in > 2)
    	{
    	    close(exec->f_in);
    	    exec->f_in--;
    	}
		exec = exec->next;
	}
}

void ft_success(t_list **list, t_env *env, t_data *data)
{
	t_var	*exec;

	exec = NULL;
	if (ft_syntax_error(list) == 0)
	{
		ft_expand(list,  data); // fix vraiable
		exec = ft_allocate_list(list);
		ft_open_her_doc(list, exec, data);
		if (ft_open_files(list, exec, data) == 0)
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
	ft_signal(); // check this
	while (1)
	{
		tok = ft_token(line, node, list); 
		if (tok == 0)////Process 11421: 98 leaks for 3136 total leaked bytes.
			return(printf("exit"), c_malloc(0, 0), 0);// this
		else if (tok > 0)
			ft_success(list, env,data);

	}
	c_malloc(0, 0);
	return 1;
}


int	main(int ac, char **av, char **env)
{

	(void)ac;
	(void)av;
	t_list	*list;
	t_data	*data;

	// rl_catch_signals = 0;
	// tcgetattr(STDIN_FILENO, &original_terminos);
	list = NULL;
	t_env *env1 = ft_get_env(&data, env);
	
	ft_all(&list, env1, data);
}