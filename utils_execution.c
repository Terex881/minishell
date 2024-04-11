/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:24:07 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/11 16:35:21 by cmasnaou         ###   ########.fr       */
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
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}
