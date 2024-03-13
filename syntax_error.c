#include "minishell.h"
#include <stdio.h>

int ft_return(t_list *lst)
{
	if (!lst)
		return (0);

	if(lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC 
		|| lst->type == APPEND || lst->type == PIPE)
		return (2);
	if (lst->type == WORD || lst->type == D_Q || lst->type == S_Q || lst->type == VARIABLE)
		return (3);
	return 0;
}

void    ft_syntax_error(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	if (!tmp)
		return ; 
	if (tmp->type == PIPE || ft_return(ft_lstlast(tmp)) == 2)
		return(perror("33"));
	while (tmp)
	{
		if (ft_return(tmp) == 2 && ft_return(tmp->next) != 3 
			&& ft_return(tmp->next->next) != 3)
			return (perror("44"));
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp) 
	{
		if(tmp->type == D_Q || tmp->type == VARIABLE)
			ft_expand(tmp);
		tmp = tmp->next;
	}
}
