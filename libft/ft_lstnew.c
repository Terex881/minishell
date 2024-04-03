#include "../minishell.h"

t_list	*ft_lstnew(void *value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

t_var	*ft_varnew(void *value)
{
	t_var	*node;
	(void)value;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->f_in = 0; // move this function
	node->f_out = 1;
	node->arg = NULL;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstnew_env(char *line)
{
	t_env	*p;

	p = (t_env *)malloc(sizeof (t_env));
	if (!p)
		return (NULL);
	p -> line = line;
	p -> next = NULL;
	return (p);
}
