#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int ff(t_list *lst)
{
	if (!lst)
		return 0;
	// if (lst->type == PIPE)
	// 	return (1);
	if(lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC || lst->type == APPEND || lst->type == PIPE)
		return (2);
	if (lst->type == WORD)
		return (3);
	return 0;
}

void ft_sysntax_error(t_list *tmp)
{
	if (!tmp)
		return ; 
	if (tmp->type == PIPE || ff(ft_lstlast(tmp)) == 2)
		return(perror("33"));
	while (tmp && tmp->next)
	{
		if (ff(tmp) == 2 && ff(tmp->next->next) == 1)
			return (perror("22"));
		if (ff(tmp) == 2 && ff(tmp->next->next) != 3 && ff(tmp->next) != 3)
			return (perror("44"));
		tmp = tmp->next;
	}
}


int main ()
{
	t_list *list;

	list = NULL;

	ft_token(&list);
	ft_print(list);
	ft_lstclear(&list);
}