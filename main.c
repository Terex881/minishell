#include "minishell.h"

void	ft_open_files(t_list **list, t_var *var)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)	
	{
		if (tmp->type == PIPE)
			var = var->next;
		if (tmp->type == R_IN)
		{
			var->f_in = open(ft_name_of_file(tmp->next), O_RDWR);
			tmp->skip = true;		
			if (var->f_in == -1)
				write(1, "555\n", 4);
		}
		else if (tmp->type == R_OUT)
		{
			var->f_out = open(ft_name_of_file(tmp->next), O_CREAT | O_RDWR , 0644);
			tmp->skip = true;	
			if (var->f_out == -1)
				write(1, "666\n", 4);
		}
		tmp = tmp->next;
	}
}


void ft_return_n(t_list **list, t_var *exec)
{
	t_list *tmp;
	int n = 0;
	tmp = *list;

	while (tmp && tmp->type != PIPE)
	{
		if (tmp && tmp->type == WORD && tmp->skip == false)
			n++;
		tmp = tmp->next;
	}
	exec->arg = malloc(sizeof(char *) * (n + 1));
	exec->arg[n] = NULL;
	
}
void ft_call(t_list **list, t_var *exec)
{
	t_list *tmp;
	int i;

	tmp = *list;
	i = 0;
	ft_open_files(list, exec);
	ft_return_n(&tmp, exec);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i = 0;
			exec = exec->next;
			ft_return_n(&tmp->next, exec);
		}
		else if (tmp->type == WORD && tmp->skip == false)
		{
			exec->arg[i] = tmp->value;
			i++;
			tmp->skip = true;
		}
		tmp = tmp->next;
	}
}

int main ()
{
	t_list *list;	
	list = NULL;
	ft_token(&list);
}

