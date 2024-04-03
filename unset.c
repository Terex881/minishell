#include "minishell.h"

void	ft_unset(t_var *exec, t_data *data, char *line)
{
	t_env	*p;
	t_env	*tmp;

	p = data->env;
	tmp = NULL;
	if (ft_strncmp(line, "PATH", 5) == 0)
		data->path = NULL;
	while (p)
	{
		if (ft_strncmp(p->line, line, ft_strlen(line)) == 0)
		{
			if (tmp)
				tmp->next = p->next;
			else
				data->env = p->next;
			free(p->line);
			free(p);
			// ft_lstdelone_env(p);

			return ;
		}
		tmp = p;
		p = p->next;
	}
}
