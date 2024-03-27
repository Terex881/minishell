#include "minishell.h"
#include <stdio.h>


int ft_IN_OUT(t_list *tmp, t_var *var)
{
	if (tmp->type == R_IN)
	{
		var->f_in = open(ft_file_name(tmp->next), O_RDWR);
		tmp->skip = true;
		if (var->f_in == -1)
			return (perror(ft_file_name(tmp->next)), 1);
	}
	else if (tmp->type == R_OUT)
	{
		var->f_out = open(ft_file_name(tmp->next),
			O_CREAT | O_RDWR, 0644);
		tmp->skip = true;
		if (var->f_out == -1)
			return (perror(ft_file_name(tmp->next)), 1);

	}
	else if (tmp->type == APPEND)
	{
		var->f_out = open(ft_file_name(tmp->next), O_CREAT 
			| O_RDWR | O_APPEND, 0644);
		tmp->skip = true;
		if (var->f_out == -1)
			return (perror(ft_file_name(tmp->next)), 1);
	}
	return (0);
}

int	ft_open_files(t_list **list, t_var *var)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			var = var->next;
		if (tmp->type == R_IN || tmp->type == R_OUT || tmp->type == APPEND)
		{
			if (ft_IN_OUT(tmp, var) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


void	ft_copy_to_list(t_list **list, t_var *exec)
{
	t_list	*tmp;
	int		i;

	if(!exec->arg)
		return;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i = 0;
			exec = exec->next;
			ft_len_node_elem(&tmp->next, exec);
		}
		else if (tmp->skip == false)
		{
			exec->arg[i] = tmp->value;
			i++;
			tmp->skip = true;
		}
		tmp = tmp->next;
	}
}

void ft_open_her_doc(t_list **list, t_var *var)
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
			line = readline(">");
			while (line)
			{
				if (ft_strcmp(ft_file_name(tmp->next), line) == 0)
					break;
				var->f_in = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644); // hide this file
				char *str = ft_expand_her_doc(line);
				write(var->f_in, str, ft_strlen(str));
				(free(line), free(str));
				line = readline(">");
			}
			free(line);
		}
		tmp = tmp->next;
	}
}
