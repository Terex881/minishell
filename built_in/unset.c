/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:32 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/08 18:23:35 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_valid_unset(char *arg)
{
	if ((arg[0] >= 'a' && arg[0] <= 'z')
		|| (arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_')
		return (1);
	ft_error("minishell: unset: `", arg, "': not a valid identifier");
	exit_status(1, 1);
	return (0);
}

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
	char	*pwd;
	int		i;

	i = 0;
	if (!data || !(*data) || !(*data)->env || !args || !*args)
		return ;
	while (args && args[++i])
	{
		if (!ft_valid_unset(args[i]))
			return ;
		p = (*data)->env;
		pwd = ft_lstfind_env(&(*data)->env, "PWD", NULL);
		tmp = NULL;
		if (ft_strncmp(args[i], "PATH", 5) == 0)
			ft_lstfind_env(&(*data)->env, "PATH=", "");
			// (*data)->path = NULL;
		if (!ft_strcmp(args[i], "PWD") && pwd)
			(*data)->pwd = ft_strdup(pwd + 4);
		if (!ft_unset_arg(data, args[i], p, tmp))
			return ;
	}
}
