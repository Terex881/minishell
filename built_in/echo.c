/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:24 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/10/12 17:40:45 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	j;
	int	n;

	(1) && (i = 0, n = 0, exit_status(0, 1));
	if (!arg || !*arg)
		return (ft_putstr_fd("\n", exec->f_out));
	while (arg && arg[i] && !ft_strncmp(arg[i], "-n", 2))
	{
		j = 1;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			break ;
		(1) && (i++, n = 1);
	}
	while (arg && arg[i])
	{
		put_str(arg[i], exec->f_out);
		if (arg[i + 1])
			ft_putstr_fd(" ", exec->f_out);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", exec->f_out);
}
