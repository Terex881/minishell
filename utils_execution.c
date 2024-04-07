/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:24:07 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/07 01:05:27 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char *path)
{
	int		j;
	char	*tmp;
	char	**paths;

	j = 0;
	if (!path)
		return (NULL);
	while (path[j] != '\n' && path[j] != '\0')
		j++;
	tmp = ft_substr(path, 5, --j);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	ft_error(char *str1, char *str2, char *str3)
{
	int	i;

	i = 0;
	while (str1 && str1[i])
		write(2, &str1[i++], 1);
	i = 0;
	while (str2 && str2[i])
		write(2, &str2[i++], 1);
	i = 0;
	while (str3 && str3[i])
		write(2, &str3[i++], 1);
	write(2, "\n", 1);
}
