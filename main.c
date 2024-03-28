#include "minishell.h"

char	*ft_varjoin(t_list **tmp)
{
	char *str;

	str = (*tmp)->value;
	while (*tmp && (*tmp)->next && (*tmp)->next->skip == false)
	{
		// free(str);
		str = ft_strjoin((*tmp)->value, (*tmp)->next->value);
		(*tmp)->skip = true;
		*tmp = (*tmp)->next;
	}
	return str;
}

void ft_copy_to_list(t_list **list, t_var *exec)
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
		if (tmp->skip == false)
		{			
			exec->arg[i] = ft_varjoin(&tmp);
			i++;
			tmp->skip = true;
		}
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
