/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:11:09 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:11:10 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	src = src1;
	dest = dest1;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
