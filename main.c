#include "minishell.h"

int ff(t_list *list)
{
			
	if (list->type == PIPE || list->type == HER_DOC || list->type == APPEND || list->type == R_IN || list->type == R_OUT)
		return 1;
	return 0;
}

void ft_parsing(t_list *tmp)
{
	while (tmp && tmp->next->next)
	{
		if (ff(tmp) == 1 && ff(tmp->next->next)==1)
			write(1, "11\n", 3);
		tmp = tmp->next;	
	}
}

void f1()
{
	system("leaks minishell");
}
int main ()
{
	t_list *list;

	list = NULL;

	ft_token(&list);
	ft_print(list);
	ft_lstclear(&list);
}