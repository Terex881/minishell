#include "minishell.h"

int ff(t_list *list)
{
			
	if (list->type == 1 || list->type == 4 || list->type == 9 || list->type == 3 || list->type == 2)
		return 1;
	return 0;
}

void ft_parsing(t_list *tmp)
{
	// t_list *tmp;
	int i;

	// tmp = list;
	i = 0;
	while(tmp && tmp->next)
	{
		if (ff(tmp) == 1 && ff(tmp->next) == 1)
			write(1, "11111\n", 6);
		if(ff(tmp) == 1 && tmp->next->type == SPACE_ && ff(tmp->next->next) == 1)
			write(1, "2222\n", 5);
		if (ff(ft_lstlast(tmp)) == 1)
			write(1, "3333\n", 5);
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
	// ft_parsing(list);
	// ft_print(list);
	ft_lstclear(&list);
}