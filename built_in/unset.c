/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:32 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/07 01:29:50 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_unset_arg(t_data **data, char *arg, t_env *p, t_env *tmp)
{
	while (p)
	{
		if (ft_strncmp(p->line, arg, ft_strlen(arg)) == 0
			&& (p->line[ft_strlen(arg)] == '\0'
				|| p->line[ft_strlen(arg)] == '='))
		{
			if (tmp)
				tmp->next = p->next;
			else
				(*data)->env = p->next;
			p->line = NULL;
			if (!(arg + 1))
				return (0);
			break ;
		}
		tmp = p;
		p = p->next;
	}
	return (1);
}

void	ft_unset(t_data **data, char **args)
{
	t_env	*p;
	t_env	*tmp;
	int		i;

	i = 0;
	if (!data || !(*data) || !(*data)->env || !args || !*args)
		return ;
	while (args && args[++i])
	{
		p = (*data)->env;
		tmp = NULL;
		if (ft_strncmp(args[i], "PATH", 5) == 0)
			(*data)->path = NULL;
		if (!ft_unset_arg(data, args[i], p, tmp))
			return ;
	}
}
