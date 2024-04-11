/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:47:37 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/11 16:32:45 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_her()
{
	close(0);
}

void	ft_signal_c(int num)
{
	if (num == SIGINT)
	{
		data_stat = 1;
		if (wait(NULL) != -1)
			return (ft_putstr_fd("\n", 1));
		rl_clear_history();
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_signal_c);
	signal(SIGQUIT, ft_signal_c);
}
