#include "minishell.h"

int	ft_type(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC 
		|| lst->type == APPEND || lst->type == PIPE)
		return (2);
	if (lst->type == WORD || lst->type == D_Q
		|| lst->type == S_Q || lst->type == VARIABLE)
		return (3);
	return (0);
}

void	ft_syntax_error(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	if (tmp->type == PIPE || ft_type(ft_lstlast(tmp)) == 2)
		return (ft_putstr_fd("11\n", 2));
	while (tmp)
	{
		if (ft_type(tmp) == 2 && ft_type(tmp->next) != 3
			&& ft_type(tmp->next->next) != 3)
				return (ft_putstr_fd("22\n", 2));
		tmp->skip = false;
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == D_Q || tmp->type == VARIABLE)
		{
			ft_expand(tmp);
			tmp = tmp->next;
		}
		else if(tmp->type == SPACE_)
		{
			printf(" ");
			tmp = tmp->next;
		}
		else
		{
			printf("%s", tmp->value);
			tmp = tmp->next;
		}
	}
	printf("\n");
}
