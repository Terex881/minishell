#include "minishell.h"

void	ft_print_var(t_var *list)
{
	int	i;

	while (list && list->arg)
	{
		i = 0;
		printf("f_in is : %d\n", list->f_in);
		printf("f_out is : %d\n", list->f_out);
		while (list->arg[i])
		{
			printf("f_arg is : %s\n", list->arg[i]);
			i++;
		}
		list = list->next;
	}
}

t_var	*ft_allocate_list(t_list **list)
{
	t_list	*tmp;
	t_var	*exec;
	t_var	*node;
	int		n;
	int		i;

	exec = NULL;
	i = 0;
	n = 1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		if (tmp->type == SPACE_ && tmp->skip == false)
			tmp->skip = true;
		tmp = tmp->next;
	}
	while (i < n)
	{
		node = ft_varnew(&i);
		if (!node)
			return (ft_lstclear_var(&exec), free(node), NULL);
		ft_varadd_back(&exec, node);
		i++;
	}
	return (exec);
}

char	*ft_file_name(t_list *tmp)
{
	char	*name;

	if (!tmp)
		return (NULL);
	if (tmp->next && tmp->type == SPACE_)
	{
		tmp->next->skip = true;
		name = tmp->next->value;
	}
	else
	{
		tmp->skip = true;
		name = tmp->value;
	}
	return (name);
}

t_var	*ft_varnew(void *value)
{
	t_var	*node;
	(void)value;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->f_in = 0;
	node->f_out = 1;
	node->arg = NULL;
	node->next = NULL;
	return (node);
}
void	ft_len_node_elem(t_list **list, t_var *exec)
{
	t_list	*tmp;
	int		n;

	if (!exec)
		return ;
	n = 0;
	tmp = *list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp && tmp->skip == false)
			n++;
		tmp = tmp->next;
	}
	exec->arg = malloc(sizeof(char *) * (n + 1));
	if(!exec->arg)
		return ;
	exec->arg[n] = NULL;
}
