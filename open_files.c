#include "minishell.h"


int ft_IN_OUT(t_list *tmp, t_var *var)
{
	char *name;

	name = ft_file_name(tmp->next);
	if (tmp->type == R_IN)
	{
		var->f_in = open(name, O_RDWR);
		tmp->skip = true;
		if (var->f_in == -1)
			return (perror(name), 1);
	}
	else if (tmp->type == R_OUT)
		var->f_out = open(name,O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (tmp->type == APPEND)
		var->f_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	tmp->skip = true;
	if (var->f_out == -1)
		return (perror(name), 1);
	return (0);
}

int	ft_open_files(t_list **list, t_var *var)
{
	t_list	*tmp;
	int check;

	tmp = *list;
	while (tmp)
	{
		if ((tmp)->type == PIPE)
			var = var->next;
		if ((tmp)->type == R_IN || (tmp)->type == R_OUT || (tmp)->type == APPEND)
		{
			check = ft_IN_OUT(tmp, var);
			if (check == 1)
				return (1);
		}
		tmp = (tmp)->next;
	}
	return (0);
}

char	*ft_lim_name(t_list *tmp)
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

void ft_open_her_doc(t_list **list, t_var *var, t_data *data)
{
	t_list	*tmp;
	char	*line;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			var = var->next;		
		if(tmp->type == HER_DOC)
		{
			tmp->skip = true;
			var->f_in = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644); // hide this file
			line = readline(">");
			while (line)
			{
				if (ft_strcmp(ft_lim_name(tmp->next), line) == 0)
					break;
				if(ft_type(tmp->next) != 3 && ft_type(tmp->next->next) != 3)
					line = ft_expand_her_doc(line, data);
				write(var->f_in, line, ft_strlen(line));
				write(var->f_in, "\n", 1);
				line = readline(">");
			}
			free(line);
			close(var->f_in);
			var->f_in = open("test", O_RDONLY);
		}
		tmp = tmp->next;
	}
	unlink("/tmp/test");
}
