#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	if (env)
	{
		if (*env && new)
			ft_lstlast_env(*env)-> next = new;
		else if (new)
			*env = new;
	}
}

void	ft_varadd_back(t_var **lst, t_var *new)
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