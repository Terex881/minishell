#include "../minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_lstsize_env(t_env *env)
{
	int		count;

	count = 0;
	// if (!env || !env->line)
	// 	return (0);
	while (env)
	{
		count++;
		env = env->next;
	}
	// printf("len is : %d\n", count);
	return (count);
}



int	ft_varsize(t_var *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}