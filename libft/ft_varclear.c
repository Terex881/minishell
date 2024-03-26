#include "../minishell.h"
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