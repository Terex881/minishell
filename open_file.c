#include "minishell.h"

void ft_print_var(t_var *list)
{
	int i = 0;
	while (list)
	{
		printf("f_in is : %d\n", list->f_in);
		printf("f_out is : %d\n", list->f_out);
		// printf("f_arg is : %s\n", list->arg[i]);
		i++;
		list = list->next;
	}
}
t_var *ft_get_number_of_pipe(t_list **list)
{
	t_list *tmp;
	t_var *exec;

	exec = NULL;
	int n;
	int i;

	i = 0;
	n = 1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		tmp->skip = false;
		tmp = tmp->next;
	}
	while (i < n)
	{
		ft_lstadd_var(&exec,ft_allocate_for_new_node(&i));
		i++;
	}
	return  (exec);
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