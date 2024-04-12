/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:39:39 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/12 08:58:28 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_var *exec, t_data *data)
{
	t_env		*env;

	g_stat = 0;
	if (!data->path)
	{
		perror("env");
		g_stat = 127;
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
