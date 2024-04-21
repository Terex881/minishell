/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:56 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/20 20:22:49 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_valid_arg(char *str, int *valid)
{
	short				s;
	unsigned long long	n;
	unsigned long long	tmp;

	s = 1;
	n = 0;
	*valid = 0;
	while (str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s *= -1;
		(str)++;
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		(1) && (tmp = n, n = n * 10 + *str - '0');
		if (tmp > n || n > 1844674407370955169)
			return (0);
		str++;
	}
	return (*valid = 1, s * n);
}

void	ft_exit(t_var *exec, char **arg, int len)
{
	int			valid;
	long long	n;

	valid = 1;
	if (len < 2)
		ft_putstr_fd("exit\n", exec->f_out);
	if (!arg || !arg[1])
		(c_malloc(0, 0), exit(g_stat));
	n = ft_valid_arg(arg[1], &valid);
	if (!valid)
	{
		ft_error("minishell: exit: ", arg[1], ": numeric argument required");
		(c_malloc(0, 0), exit(255));
	}
	if (arg[2])
	{
		ft_error("minishell: ", "exit: ", "too many arguments");
		g_stat = 1;
		return ;
	}
	(c_malloc(0, 0), exit(n));
}
