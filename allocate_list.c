/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:03:05 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/06 06:05:35 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_allocate_list(t_list **list)
{
	t_list	*tmp;
	t_var	*exec;
	t_var	*node;
	int		n;
	int		i;

	exec = NULL;
	i = 0;
	n = 1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			(1) && (tmp->skip = true, n++);
		tmp = tmp->next;
	}
	while (i < n)
	{
		node = ft_varnew(&i);
		if (!node)
			return (NULL);
		ft_varadd_back(&exec, node);
		i++;
	}
	return (exec);
}

void	ft_len_node_elem(t_list **list, t_var *exec)
{
	t_list	*tmp;
	int		n;

	if (!exec)
		return ;
	n = 0;
	tmp = *list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == SPACE_)
			tmp->skip = true;
		if (tmp && tmp->skip == false)
			n++;
		tmp = tmp->next;
	}
	if (n <= 0)
		exec->arg = NULL;
	else
<<<<<<< HEAD
		exec->arg = c_malloc(sizeof(char *) * (n + 1), 1);
=======
		exec->arg = c_malloc(sizeof(char *) * (n + 1), 1); // check this
>>>>>>> 76b65ae3c92372cc60405cb29557a6e0521675b3
	if (!exec->arg)
		return ;
}

char	*ft_varjoin(t_list **tmp, t_data *data)
{
	char	*str;

	str = (*tmp)->value;
<<<<<<< HEAD
	while (*tmp && (*tmp)->next && (*tmp)->next->skip == false
		&& ft_type((*tmp)->next) != 2)
=======
	while (*tmp && (*tmp)->next
		&& (*tmp)->next->skip == false && ft_type((*tmp)->next) != 2)
>>>>>>> 76b65ae3c92372cc60405cb29557a6e0521675b3
	{
		if (ft_type((*tmp)->next) == 1)
			data->a = 1;
		str = ft_strjoin(str, (*tmp)->next->value);
		(*tmp)->skip = true;
		*tmp = (*tmp)->next;
	}
	(*tmp)->skip = true;
	return (str);
}

void	ft_copy_to_list(t_list **list, t_var *exec, t_data *data)
{
	t_list	*tmp;
	int		i;

	if (!exec->arg)
		return ;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i = 0;
			exec = exec->next;
<<<<<<< HEAD
			tmp->skip = true;
=======
			tmp->skip = true; // for pipe
>>>>>>> 76b65ae3c92372cc60405cb29557a6e0521675b3
			ft_len_node_elem(&tmp->next, exec);
		}
		if (tmp->skip == false)
		{
<<<<<<< HEAD
			exec->arg[i++] = ft_varjoin(&tmp, data);
			tmp->skip = true;
=======
			exec->arg[i] = ft_varjoin(&tmp, data);
			(1) && (i++, tmp->skip = true);
>>>>>>> 76b65ae3c92372cc60405cb29557a6e0521675b3
		}
		if (exec->arg)
			exec->arg[i] = NULL;
		tmp = tmp->next;
	}
}
