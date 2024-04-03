#include "minishell.h"




void	ft_print_var(t_var *list)
{
	int	i;

	while (list && list->arg)
	{
		i = 0;
		printf("f_in is : %d\n", list->f_in);
		printf("f_out is : %d\n", list->f_out);
		while ( list->arg[i])
		{
			printf("f_arg is : %s\n", list->arg[i]);
			i++;
		}
		list = list->next;
	}
	printf("----------------------------\n");
}


void	ft_print(t_list *list)
{
	while (list)
	{
		if (list && list->type == WORD)
			printf("Word   %s\n", list->value);
		else if (list && list->type == PIPE)
			printf("pipe   %s\n", list->value);
		else if (list && list->type == HER_DOC)
			printf("here_doc   %s\n", list->value);
		else if (list && list->type == R_IN)
			printf("R_IN   %s\n", list->value);
		else if (list && list->type == R_OUT)
			printf("R_OUT   %s\n", list->value);
		else if (list && list->type == SPACE_)
			printf("space   %s\n", list->value);
		else if (list && list->type == APPEND)
			printf("append   %s\n", list->value);
		else if (list && list->type == D_Q)
			printf("D_Q   %s\n", list->value);
		else if (list && list->type == S_Q)
			printf("S_Q   %s\n", list->value);
		else if (list && list->type == VARIABLE)
			printf("variable   %s\n", list->value);
		// printf("- > %d\n", list->skip);
		list = list->next;
	}
}
