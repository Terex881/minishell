#include "../minishell.h"

void	ft_unset(t_var *exec, t_data **data, char **args)
{
	t_env	*p;
	t_env	*tmp;
	int		i;

	i = 0;
	if (!data || !(*data) || !(*data)->env || !args || !*args)
		return ;
	while (args && args[++i])
	{
		p = (*data)->env;
		tmp = NULL;
		if (ft_strncmp(args[i], "PATH", 5) == 0)
		{
			// free((*data)->path);
			(*data)->path = NULL;
		}
		while (p)
		{
			if (ft_strncmp(p->line, args[i], ft_strlen(args[i])) == 0
				&& (p->line[ft_strlen(args[i])] == '\0' || p->line[ft_strlen(args[i])] == '='))
			{
				if (tmp)
					tmp->next = p->next;
				else
					(*data)->env = p->next;
				// free(p->line);
				// free(p);
				p->line = NULL;
				if (!args[i + 1])
					return ;
				break ;
			}
			tmp = p;
			p = p->next;
		}
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
// 		// free((*data)->env->line);
// 		(*data)->env = (*data)->env->next;
// 		return ;
// 	}
// 	p = (*data)->env;
// 	while (p && p->next)
// 	{
// 		if (ft_strcmp(p->next->line, line) == 0)
// 		{
// 			free(p->next->line);
// 			free(p->next);
// 			p->next = p->next->next;
// 			return ;
// 		}
// 		p = p->next;
// 	}
// }
