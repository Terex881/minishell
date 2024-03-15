#include "minishell.h"
#include <stdio.h>

void ft_youchen(t_list **list)
{
	t_list *tmp;
	t_list *tmp1;

	tmp = *list;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	
	
}

int main ()
{
	t_list *list;	

	list = NULL;

	ft_token(&list);
	// ft_print(list);

	// ft_lstclear(&list);
}
