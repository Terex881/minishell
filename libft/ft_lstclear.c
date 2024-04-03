#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if (*lst)
		{
			// printf("-%p\n", (*lst)->value);
			free((*lst)->value);
			free(*lst);
		}
		*lst = tmp;
	}
	lst = NULL;
}



void	ft_lstclear_env(t_env **env)
{
	t_env	*p;

	if (!env)
		return ;
	if (*env)
	{
		while (*env)
		{
			p = (*env)-> next;
			// ft_lstdelone_env(*env);
			free((*env)->line);
			free(*env);
			*env = p;
		}
		*env = NULL;
	}
}

void	ft_lstclear_var(t_var **exec)
{
	t_var	*tmp;
	
	if (!exec || !(*exec))
		return ;
	while (*exec)
	{
		tmp = (*exec)->next;
		if (*exec)
		{
			free((*exec)->arg);
			free(*exec);
		}
		*exec = tmp;
	}
	exec = NULL;
}