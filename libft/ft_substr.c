/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:07:23 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:07:26 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	j;
	char	*arr;

	j = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str) || len == 0)
		return (ft_strdup(""));
	if (len > (ft_strlen(str) - start))
		arr = c_malloc ((ft_strlen(str) - start) + 1, 1);
	else
		arr = c_malloc (len + 1, 1);
	if (!arr)
		return (NULL);
	while (j < len && str[start])
	{
		arr[j] = str[start];
		j++;
		start++;
	}
	arr[j] = '\0';
	return (arr);
}
