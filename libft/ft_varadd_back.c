#include "../minishell.h"

void	ft_varadd_back(t_var **lst, t_var *new)
{
	t_var	*current;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current && current->next)
		current = current->next;
	current->next = new;
}