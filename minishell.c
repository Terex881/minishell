#include "minishell.h"

int ff(t_list *list)
{
	while(list)
	{
		if (list->type == 1 || list->type == 4 || list->type == 9 || list->type == 3 || list->type == 2)
			return 1;
		list = list->next;
	}
	return 0;
}

void ft_parsing(t_list *list)
{
	t_list *tmp;
	int i;

	tmp = list;
	i = 0;
	while(tmp && tmp->next)
	{
		if (ff(tmp) == 1 && ff(tmp->next) == 1)
			(perror("pipe in begenning"), exit(0));
		// if (tmp)

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
	// atexit(f1);
	ft_token(&list);
	ft_parsing(list);
	ft_print(list);
	ft_lstclear(&list);
}