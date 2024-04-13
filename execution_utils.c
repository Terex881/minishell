/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:24:07 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/13 20:18:38 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str1, char *str2, char *str3)
{
	int	i;

	i = 0;
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}

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

char	**get_args(t_var *exec)
{
	char	**arg;
	char	**args;
	
	arg = ft_split(exec->arg[0], ' ');
	if (!arg || !arg[0])
		return (NULL);
	args = arg_join(arg, &exec->arg[1]);
	if (!args || !args[0])
		return (NULL);
	return (args);
}

char	**arg_join(char **args, char **arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	if (!args && !*args)
		return (arg);
	if (!arg && !*arg)
		return (args);
	while (args && args[i])
		i++;
	while (arg && arg[j])
		j++;
	new_args = c_malloc(sizeof(char *) * (i + j + 1), 1);
	if (!new_args)
		return (NULL);
	i = -1;
	while (args && args[++i])
		new_args[i] = ft_strdup(args[i]);
	j = -1;
	while (arg && arg[++j])
		new_args[i++] = ft_strdup(arg[j]);
	new_args[i] = NULL;
	return (new_args);
}
