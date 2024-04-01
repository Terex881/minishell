#include "minishell.h"
#include <stdbool.h>

int	ft_type(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC
		|| lst->type == APPEND)
		return (2);
	if (lst->type == D_Q || lst->type == S_Q)
		return  (3);
	if (lst->type == WORD || lst->type == D_Q
		|| lst->type == S_Q || lst->type == VARIABLE)
		return (3);
	if (lst->type == PIPE)
		return  (4);
	return (0);
}

t_list *ff(t_list *tmp)
{
	
	if(tmp->type == SPACE_)
		tmp = tmp->next;
		
	return (tmp);

}
int	ft_syntax_error(t_list **list)
{
	t_list	*tmp;
	
	tmp = *list;
	if (!tmp)
		return 1;
	if (tmp->type == PIPE || ft_lstlast(tmp)->type == PIPE)
		return (ft_putstr_fd("1\n", 2), 1);
	if (ft_type(ft_lstlast(tmp)) == 2 )
		return (ft_putstr_fd("2\n", 2), 1);
	while (tmp && tmp->next)
	{
		if(ft_type(tmp) == 2 && (ft_type(ff(tmp->next)) == 4) || !tmp->next)
			return (ft_putstr_fd("8\n", 2), 1);
		if(ft_type(tmp) == 4 && ft_type(ff(tmp->next)) == 4 || !tmp->next)
			return (ft_putstr_fd("4\n", 2), 1);

		tmp->skip = false;
		if(tmp->type == SPACE_)
			tmp->skip = true;
		tmp = tmp->next;
	}
	return (0);
}













// int	ft_syntax_error(t_list **list)
// {
// 	t_list	*tmp;
	
// 	tmp = *list;
// 	if (!tmp)
// 		return 1;
// 	if (tmp->type == PIPE || ft_lstlast(tmp)->type == PIPE)
// 		return (ft_putstr_fd("1\n", 2), 1);
// 	if (ft_type(ft_lstlast(tmp)) == 2 )
// 		return (ft_putstr_fd("2\n", 2), 1);
// 	while (tmp)
// 	{
// 		if (ft_type(tmp) == 2 && ft_type(tmp->next) != 3
// 			&& ft_type(tmp->next->next) != 3)
// 			return (ft_putstr_fd("3\n", 2), 1);

// 		if (ft_type(tmp) == 4 && ft_type(tmp->next) == 4 )
// 			return (ft_putstr_fd("4\n", 2), 1); // check PIPE after piep
// 		if(ft_type(tmp) == 4 && ft_type(tmp->next->next) == 4)
// 			return (ft_putstr_fd("5\n", 2), 1); // check PIPE after piep





// 		if (tmp->type == PIPE && ft_type(ft_lstlast(tmp)) == 0)
// 			return (ft_putstr_fd("99\n", 2), 1);
// 		tmp->skip = false;
// 		if(tmp->type == SPACE_)
// 			tmp->skip = true;
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
