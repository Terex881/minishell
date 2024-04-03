#include "minishell.h"

int ft_IN_OUT(t_list *tmp, t_var *var)
{
	char	*name;

	name = ft_varjoin(&tmp->next);
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
	int		check;

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

// char	*ft_lim_name(t_list *tmp)
// {
// 	char	*name;

// 	if (!tmp)
// 		return (NULL);
// 	if (tmp->next && tmp->type == SPACE_)
// 	{
// 		tmp->next->skip = true;
// 		name = tmp->next->value;
// 	}
// 	else
// 	{
// 		tmp->skip = true;
// 		name = tmp->value;
// 	}
// 	return (name);
// }


void ft_read_herdoc(t_list *tmp, t_var *exec, t_data *data)
{
	char	*line;
	char	*limter;


	line = readline(">");
	limter = ft_varjoin(&tmp->next);
	while (line)
	{
		if (!ft_strcmp(limter, line))
			break;
		if(ft_type(ff(tmp->next)) != 1)
			line = ft_expand_her_doc(line, data);
		write(exec->f_in, line, ft_strlen(line));
		write(exec->f_in, "\n", 1);
		free(line);
		line = readline(">");
	}
	close(exec->f_in);// check this
	exec->f_in = open("/tmp/test", O_RDONLY);
}


void	ft_open_her_doc(t_list **list, t_var *exec, t_data *data)
{
	t_list	*tmp;

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
		}
		tmp = tmp->next;
	}
	unlink("/tmp/test");
}
