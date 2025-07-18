/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:36 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/12 10:30:27 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_export(char *line, t_data *data)
{
	ft_error(ft_strjoin("export: `", line), "': not a valid identifier");
	if (data)
		exit_status(1, 1);
}

static int	ft_valid_export(char *line, t_data *data)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (line[0] == '=' || line[0] == '+' || (line[0] >= '0' && line[0] <= '9'))
		return (ft_error_export(line, data), 0);
	if (ft_valid_char(line[i]))
		i++;
	if (line[0] == '\0')
		return (ft_error_export(line, data), 0);
	while (line[i] && line[i] != '=')
	{
		if (line[i] == '+')
			count++;
		if (count > 1 || (line[i] == '+' && line[i + 1] != '='))
			return (ft_error_export(line, data), 0);
		if (!ft_valid_char(line[i]) && line[i] != '=' && line[i] != '+')
			return (ft_error_export(line, data), 0);
		i++;
	}
	return (1);
}

static int	ft_export_no_args(t_var *exec, t_data *data, char **args)
{
	t_env	*env_cpy;

	if (!args[1] || args[1][0] == '#')
	{
		env_cpy = ft_lstcpy_env(data->env);
		ft_print_export(exec, data, ft_sort_env(env_cpy, ft_strcmp));
		return (1);
	}
	return (0);
}

void	ft_export_args(t_data **data, char *arg, char *tmp)
{
	char	*name;
	char	*var;

	name = ft_var_name(arg);
	var = ft_lstfind_env(&(*data)->env, name, NULL);
	if (!var && !ft_strncmp(tmp - 1, "+=", 2))
		ft_lstadd_back_env(&(*data)->env,
			ft_lstnew_env(ft_strdup(ft_remove_plus(arg))));
	else if (var && !ft_strncmp(tmp - 1, "+=", 2))
	{
		if (!ft_strchr(var, '='))
			ft_lstfind_env(&(*data)->env, name,
				ft_strjoin(ft_strjoin(var, "="), tmp + 1));
		else
			ft_lstfind_env(&(*data)->env, name, ft_strjoin(var, tmp + 1));
	}
	else if (var)
		ft_lstfind_env(&(*data)->env, name, arg);
	else
		ft_lstadd_back_env(&(*data)->env, ft_lstnew_env(ft_strdup(arg)));
	if (ft_strcmp(name, "PATH") == 0 && arg[4] == '=')
		ft_lstfind_env(&(*data)->env, "PATH=", "");
}

void	ft_export(t_var *exec, t_data *data, char **args)
{
	char	*tmp;
	int		i;

	exit_status(0, 1);
	if (ft_export_no_args(exec, data, args))
		return ;
	i = 1;
	while (args[i])
	{
		if (!ft_valid_export(args[i], data))
		{
			(1) && (exit_status(1, 1), i++);
			continue ;
		}
		tmp = ft_strchr(args[i], '=');
		if (!ft_strcmp(args[i], "PATH"))
			data->no_env = 0;
		if (tmp)
			ft_export_args(&data, args[i], tmp);
		else if (ft_strchr(args[i], '+'))
			ft_error_export(args[i], data);
		else if (!ft_lstfind_env(&data->env, args[i], NULL))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(args[i])));
		i++;
	}
}
