#include "minishell.h"

int ff(t_list *lst)
{
	if (!lst)
		return 0;
	if (lst->type == PIPE)
		return (1);
	if(lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC || lst->type == APPEND)
		return (2);
	if (lst->type == WORD)
		return (3);
	return 0;
}

void ft_parsing(t_list *tmp)
{
	if (ff(tmp) == 1 || ff(ft_lstlast(tmp)) == 1)
		write(1, "33\n", 3);
	if (ff(ft_lstlast(tmp)) == 2)
		write(1, "55\n", 3);
	while (tmp && tmp->next)
	{
		if (ff(tmp) == 2 && ff(tmp->next->next) == 1)
			write(1, "11\n", 3);
		if (ff(tmp) == 1 && ff(tmp->next->next) == 1)
			write(1, "22\n", 3);
		if (ff(tmp) == 2 && ff(tmp->next->next) != 3)
			write(1, "44\n", 3);
		if (ff(tmp) == 1 && ff(tmp->next->next) != 3)
			write(1, "66\n", 3);
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
	// ft_print(list);
	ft_lstclear(&list);
}