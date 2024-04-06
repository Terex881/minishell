/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:39:39 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/06 20:42:51 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_var *exec, t_data *data)
{
	t_env		*env;

	data->stat = 0;
	if (!data->path)
	{
		perror("env");
		data->stat = 127;
		return ;
	}
	env = data->env;
	while (env)
	{
		if (ft_strchr(env->line, '='))
		{
			ft_putstr_fd(env->line, exec->f_out);
			ft_putstr_fd("\n", exec->f_out);
		}
		env = env->next;
	}
}
