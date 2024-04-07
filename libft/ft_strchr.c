/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:06:47 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:12:08 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s1, int c)
{
	int		i;

	i = 0;
	if (!s1 || !s1[i])
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == c)
			return (&s1[i]);
		i++;
	}
	if (s1[i] == c)
		return (&s1[i]);
	return (NULL);
}
