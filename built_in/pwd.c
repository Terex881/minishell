/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:20:39 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/09 14:59:55 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_var *exec, t_env *env, t_data *data)
{
	char	*tmp;
	exit_status(0, 1); //add this
	tmp = ft_lstfind_env(&env, "PWD", NULL);
	if (tmp)
	{
		ft_putstr_fd(tmp + 4, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
		{
			ft_putstr_fd(data->pwd, exec->f_out);
			ft_putstr_fd("\n", exec->f_out);
			return ;
		}
		ft_putstr_fd(tmp, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
		free(tmp);
		return ;
	}
}
