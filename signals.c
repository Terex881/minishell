/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:47:37 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:37:22 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_her(int num)
{
	(void)num;
	close(0);
}

void	ft_signal_c(int num)
{
	if (num == SIGINT)
	{
		rl_clear_history();
		write(1, "\n", 1);
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
