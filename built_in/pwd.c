/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:20:39 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/06 23:50:58 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_var *exec, t_env *env)
{
	char	*tmp;

	tmp = ft_lstfind_env(&env, "PWD", NULL);
	if (tmp)
	{
		ft_putstr_fd(tmp + 4, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		ft_putstr_fd(tmp, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
		free(tmp);
		return ;
	}
}
