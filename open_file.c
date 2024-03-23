#include "minishell.h"
#include <stdio.h>

void ft_print_var(t_var *list)
{
	while (list)
	{
		int i = 0;
		printf("f_in is : %d\n", list->f_in);
		printf("f_out is : %d\n", list->f_out);
		while(list->arg[i])
		{
			printf("f_arg is : %s\n", list->arg[i]);
			i++;
		}
		list = list->next;
	}
}
t_var *ft_allocate_for_list(t_list **list)
{
	t_list *tmp;
	t_var *exec;
	t_var *node;
	int n;
	int i;

	exec = NULL;
	i = 0;
	n = 1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		tmp = tmp->next;
	}
	while (i < n)
	{
		node = ft_allocate_for_new_node(&i);
		if(!node)
			return (ft_lstclear_var(&exec),free(node),  NULL);
		ft_lstadd_var(&exec,node);

		i++;
	}
	return (exec);
}

void	ft_lstadd_var(t_var **lst, t_var *new)
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

char *ft_name_of_file(t_list *tmp)
{
	char *name;
	if(!tmp)
		return (NULL);
	if (tmp->type == SPACE_)
	{
		tmp->next->skip = true;
 	    name = tmp->next->value;
	}
	else
	{
		tmp->skip = true;
		name = tmp->value;
	}
	return  (name);
}

t_var	*ft_allocate_for_new_node(void *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->f_in = 0;
	node->f_out = 1;
	node->arg = NULL;
	node->next = NULL;
	return (node);
}