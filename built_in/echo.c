/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:24 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/12 10:13:53 by cmasnaou         ###   ########.fr       */
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

static void	put_str(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == '\\' && !s[i + 1])
			return ;
		if (s[i] == '\\' && s[i + 1] != '\\')
		{
			i++;
			continue ;
		}
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_echo(char **arg, t_var *exec)
{
	int	i;
	int	n;
	int	count;

	(1) && (i = 0, n = 0, count = 0, exit_status(0, 1));
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
		put_str(arg[i], exec->f_out);
		if (arg[i] && arg[i + 1])
			ft_putstr_fd(" ", exec->f_out);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", exec->f_out);
}
