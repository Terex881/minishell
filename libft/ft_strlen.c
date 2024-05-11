/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:06:58 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/11 19:20:56 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (!s[i])
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_arglen(char **arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}
