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


void ft_read_herdoc(t_list *tmp, t_var *exec, t_data *data)
{
	char	*line;
	char	*limter;
	char	*str;


	line = readline(">");
	limter = ft_varjoin(&tmp->next);
	
	while (line)
	{
		if (!ft_strcmp(limter, line))
		{
			free(line);
			break;
		}
		if(ft_type(ft_next(tmp->next)) != 1)
			str = ft_expand_her_doc(line, data);
		write(exec->f_in, str, ft_strlen(str));
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
		}
		tmp = tmp->next;
	}
	unlink("/tmp/test");
}
