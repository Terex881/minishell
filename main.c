#include "minishell.h"


void ft_youchen(t_list **list)
{
	t_list *tmp;
	tmp = *list;
	t_list *current;
	current = *list;
	t_var node;
	int i;
	i = 0;

	while (tmp)
	{
		if (tmp->type == R_IN)
		{
			char *name = tmp->next->next->value;
			node.in = open(name, O_CREAT | O_RDWR, 0644);
			tmp = current;
			while (tmp->next && tmp->next->type != R_IN)
			{
				if(tmp->type == SPACE_)
				{
					current = current->next;
					tmp = tmp->next;
				}
				else
				{
					node.arg = malloc(sizeof(char *) * 50);
					node.arg[i] = tmp->value;
					printf("--->%s\n", node.arg[i]);
					i++;
					tmp = tmp->next;
					current = current->next;
				}
				printf("****\n");
			}
		}
		tmp = tmp->next;
	}
}



int main ()
{
	t_list *list;	
	list = NULL;
	ft_token(&list);
}

