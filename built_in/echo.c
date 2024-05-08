/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:24 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/08 16:57:17 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_n(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	if (!s[1])
		return (0);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **arg, t_var *exec, t_data *data, int *g_stat)
{
	int	i;
	int	n;
	int	count;

	(void)data;//to remove
	(1) && (i = 0, n = 0, count = 0, *g_stat = 0);
	if (!arg || !*arg)
		return (ft_putstr_fd("\n", exec->f_out));
	if (check_n(arg[0]))
		(1) && (n = 1, i++, count++);
	if (!arg[i])
		return ;
	while (arg && arg[i])
	{
		while (n == 1 && check_n(arg[i]) && count == 1 && i++)
			continue ;
		count = 0;
		ft_putstr_fd(arg[i], exec->f_out);
		if (arg[i] && arg[i + 1])
			ft_putstr_fd(" ", exec->f_out);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", exec->f_out);
}
