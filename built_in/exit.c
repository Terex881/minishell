/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:56 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/06 21:47:48 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_valid_arg(char *str, int *valid)
{
	short				s;
	unsigned long long	n;
	unsigned long long	tmp;

	s = 1;
	n = 0;
	*valid = 0;
	while (str && *str == 32 || (*str >= 9 && *str <= 13))
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

void	ft_exit(t_var *exec, t_data **data, char **arg, int len)
{
	int			valid;
	long long	n;

	valid = 1;
	if (len < 2) //len == 1
		write(exec->f_out, "exit\n", 5);
	if (!arg || !arg[1])
		(c_malloc(0, 0), exit(0));
	if (arg[2])
		return ((void)write(2, "minishell: exit: too many arguments\n", 36));
	n = ft_valid_arg(arg[1], &valid);
	if (!valid)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": numeric argument required\n", 29);
		(c_malloc(0, 0), exit(255));
	}
	(c_malloc(0, 0), exit(n));
}
