#include "minishell.h"
#include <stdio.h>

int ft_IN_OUT(t_list *tmp, t_var *var, t_data *data)
{
	char	*name;

	name = ft_varjoin(&tmp->next, data);
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

int	ft_open_files(t_list **list, t_var *var, t_data *data)
{
	t_list	*tmp;
	int		check;

	tmp = *list;
	while (tmp)
	{
		if ((tmp)->type == PIPE)
			var = var->next;
		if ((tmp)->type == R_IN || (tmp)->type == R_OUT || (tmp)->type == APPEND)
		{
			check = ft_IN_OUT(tmp, var, data);
			if (check == 1)
				return (1);
		}
		tmp = (tmp)->next;
	}
	return (0);
}


void ft_read_herdoc(t_list *tmp, t_var *exec, t_data *data)
{
	char	*line;
	char	*limter;
	char	*str;

	data->a = 0;
	limter = ft_varjoin(&tmp->next, data);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(limter, line))
		{
			free(line);
			break;
		}
		if(data->a == 0)
		{
			str = line;
			line = ft_expand_her_doc(line, data);
			free(str);
		}
		write(exec->f_in, line, ft_strlen(line));
		write(exec->f_in, "\n", 1);
		free(line);
	}
}


void	ft_open_her_doc(t_list **list, t_var *exec, t_data *data)
{
	t_list	*tmp;
	int i;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			exec = exec->next;	
		if(tmp->type == HER_DOC)
		{
			tmp->skip = true;
			exec->f_in = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC, 0644); // hide this file
			ft_read_herdoc(tmp, exec, data);
			close(exec->f_in);// check this
			exec->f_in = open("/tmp/test", O_RDONLY);
		}
		tmp = tmp->next;
	}
	unlink("/tmp/test");
}
