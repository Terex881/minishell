#include "minishell.h"
#include <stdio.h>


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
int	ft_all(t_list **list, t_env *env, t_data *data)
{
	t_list	*node;
	t_var	*exec;
	char	*line;

	line = NULL;
	node = NULL;
	exec = NULL;
	ft_signal(); // check this
	while (1)
	{
		if(ft_token(line, node, list) == 0)////Process 11421: 98 leaks for 3136 total leaked bytes.
		{
			ft_lstclear(list);
			ft_lstclear_env(&data->env);
			free(data->path);
			free(data);
			return(printf("exit"), 0);// this
		}
		ft_skip_space(list);
		if (ft_syntax_error(list) == 0)
		{
			ft_expand(list,  data); // fix vraiable
			exec = ft_allocate_list(list);
			ft_open_her_doc(list, exec, data);
			if (ft_open_files(list, exec) == 0)
			{
				ft_len_node_elem(list, exec);
				ft_copy_to_list(list, exec);
				if (exec->next)
					ft_execute_pipe(exec, data, env);
				else
					ft_execution(exec, data, env);
			}
			ft_close(exec);
			ft_lstclear_var(&exec);
			ft_lstclear(list);
		}
	}
	return 1;
}
int	main(int ac, char **av, char **env)
{
	// atexit(leak);
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