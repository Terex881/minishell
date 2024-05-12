/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:03:05 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/12 10:14:55 by cmasnaou         ###   ########.fr       */
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
		exec->arg = c_malloc(sizeof(char *) * (n + 1), 1);
	if (!exec->arg)
		return ;
}

char	*ft_varjoin(t_list **tmp, t_data *data)
{
	char	*str;

	str = (*tmp)->value;
	while (*tmp && (*tmp)->next
		&& (*tmp)->next->skip == false && ft_type((*tmp)->next) != 2)
	{
		if (ft_type((*tmp)->next) == 1)
			data->val = 1;
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

	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i = 0;
			exec = exec->next;
			tmp->skip = true;
			ft_len_node_elem(&tmp->next, exec);
		}
		if (exec->arg && tmp->skip == false)
		{
			exec->arg[i] = ft_varjoin(&tmp, data);
			(1) && (i++, tmp->skip = true);
		}
		if (exec->arg)
			exec->arg[i] = NULL;
		tmp = tmp->next;
	}
}
