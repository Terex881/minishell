#include "minishell.h"
#include <stdbool.h>

void ft_join(t_list **list, t_var *exec)
{
	t_list	*tmp;
	int		i;

	if(!exec->arg)
		return;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i = 0;
			exec = exec->next;
			ft_len_node_elem(&tmp->next, exec);
		}
		else if (tmp->skip == false)
		{
			if(tmp->skip == false && tmp->next->type == SPACE_)
			{
				exec->arg[i] = tmp->value;
			}
			else if (tmp->skip == false && tmp->next->type != SPACE_)
			{
				exec->arg[i] = ft_strjoin(tmp->value, tmp->next->value);
				i++;
				tmp->skip = true;
				tmp->next->skip = true;
				tmp = tmp->next;
				
			}


		}
		else
			tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	
	// rl_catch_signals = 0;
	// list = NULL;
	ft_all(&list, env);
}
