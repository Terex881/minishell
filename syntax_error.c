/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:12:37 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/09 20:04:25 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_type(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->type == R_OUT || lst->type == R_IN || lst->type == HER_DOC
		|| lst->type == APPEND)
		return (2);
	if (lst->type == D_Q || lst->type == S_Q)
		return (1);
	if (lst->type == WORD || lst->type == D_Q
		|| lst->type == S_Q || lst->type == VARIABLE)
		return (3);
	if (lst->type == PIPE)
		return (4);
	return (0);
}

t_list	*ft_next(t_list *tmp)
{
	if (tmp->type == SPACE_)
		tmp = tmp->next;
	return (tmp);
}

int	ft_syntax_error(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return (1);
	ft_skip_space(list);
	if (tmp->type == PIPE || ft_lstlast(tmp)->type == PIPE)
		return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), 1);
	if (ft_type(ft_lstlast(tmp)) == 2)
		return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), 1);
	while (tmp && tmp->next)
	{
		if (ft_type(tmp) == 2 && (ft_type(ft_next(tmp->next)) == 4))
			return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), 1);
		if (ft_type(tmp) == 4 && ft_type(ft_next(tmp->next)) == 4)
			return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), 1);
		if (ft_type(tmp) == 2 && ft_type(ft_next(tmp->next)) == 2)
			return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), 1);
		tmp->skip = false;
		if (tmp->type == SPACE_)
			tmp->skip = true;
		tmp = tmp->next;
	}
	return (0);
}
