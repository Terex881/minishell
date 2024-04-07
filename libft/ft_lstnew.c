/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:06:00 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:10:41 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *value)
{
	t_list	*node;

	node = c_malloc(sizeof(t_list), 1);
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

t_var	*ft_varnew(void *value)
{
	t_var	*node;

	(void)value;
	node = c_malloc(sizeof(t_var), 1);
	if (!node)
		return (NULL);
	node->f_in = 0;
	node->f_out = 1;
	node->arg = NULL;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstnew_env(char *line)
{
	t_env	*p;

	if (!line)
		return (NULL);
	p = (t_env *)c_malloc(sizeof (t_env), 1);
	if (!p)
		return (NULL);
	p -> line = line;
	p -> next = NULL;
	return (p);
}
