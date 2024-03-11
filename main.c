#include "minishell.h"
#include <stdio.h>


void ft_expand(t_list **list)
{
	t_list	*tmp;
	int		i;
	char *content;

	i = 0;
	tmp = *list;
	while (tmp) 
	{
		if(tmp->type == D_Q)
		{
			content = tmp->value;
			printf("-->%s\n", content);
		}
		tmp = tmp->next;
	}
}


int main ()
{
	t_list *list;
	

	list = NULL;

	ft_token(&list);
	// ft_print(list);
	ft_lstclear(&list);
}