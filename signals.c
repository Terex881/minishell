/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:47:37 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:49 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/signal.h>
#include <sys/wait.h>

void	ft_signal_her(int num)
{
	(void)num;
	close(0);
}

void	ft_signal_c(int num)
{

	if(num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();	
		global = 12;
		return;
	}
	global = 10;
	
}



void	ft_signal()
{

	signal(SIGQUIT, ft_signal_c);
	signal(SIGINT, ft_signal_c);
		
	
}
