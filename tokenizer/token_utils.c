#include "../minishell.h"

int	ft_check(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t')
		return (1);
	if (c == '\"' || c == '\'')
		return (2);
	if (c == '$')
		return (3);
	return (0);
}



void ft_skip_space(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	if(tmp && tmp->next && tmp->next->type == SPACE_ && tmp->next->next == NULL)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
}

