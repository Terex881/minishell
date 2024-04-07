/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:55:03 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:05:35 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count ++;
	while (n != 0)
	{
		n = n / 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n1)
{
	long int	tmp;
	int			count;
	char		*arr;

	tmp = n1;
	count = counter(tmp);
	arr = c_malloc(count + 1, 1);
	if (!arr)
		return (NULL);
	arr[count] = '\0';
	if (tmp < 0)
	{
		arr[0] = '-';
		tmp = -tmp;
	}
	else if (tmp == 0)
		arr[0] = '0';
	while (tmp != 0)
	{
		count--;
		arr[count] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	return (arr);
}
