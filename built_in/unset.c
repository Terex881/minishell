#include "../minishell.h"

void	ft_unset(t_var *exec, t_data **data, char *line)
{
	t_env	*p;
	t_env	*tmp;

	if (!data || !(*data) || !(*data)->env || !line)
		return ;
	p = (*data)->env;
	tmp = NULL;
	if (ft_strncmp(line, "PATH", 5) == 0)
	{
		free((*data)->path);
		(*data)->path = NULL;
	}
	while (p)
	{
		if (ft_strncmp(p->line, line, ft_strlen(line)) == 0)
		{
			if (tmp)
				tmp->next = p->next;
			else
				(*data)->env = p->next;
			free(p->line);
			// free(p);
			return ;
		}
		tmp = p;
		p = p->next;
	}
}

// void	ft_unset(t_var *exec, t_data **data, char *line)
// {
// 	t_env *p;

// 	if (!data || !(*data) || !(*data)->env || !line)
// 		return ;
// 	if (ft_strncmp(line, "PATH", 5) == 0)
// 	{
// 		free((*data)->path);
// 		(*data)->path = NULL;
// 	}
// 	if (ft_strncmp((*data)->env->line, line, ft_strlen(line)) == 0)
// 	{
// 		free((*data)->env->line);
// 		(*data)->env = (*data)->env->next;
// 		return ;
// 	}
// 	p = (*data)->env;
// 	while (p->next)
// 	{
// 		if (ft_strncmp(p->next->line, line, ft_strlen(line)) == 0)
// 		{
// 			free(p->next->line);
// 			free(p->next);
// 			p->next = p->next->next;
// 			return ;
// 		}
// 		p = p->next;
// 	}
// }
