/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:29:36 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/04/08 22:35:24 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_export(char *line, t_data *data)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if (data)
		data->stat = 1;
}

static int	ft_valid_export(char *line, t_data *data)
{
	int		i;
	char	*name;

	name = NULL;
	data->stat = 0;
	i = 0;
	if (line[0] == '=' || line[0] == '+' || (line[0] >= '0' && line[0] <= '9'))
	{
		name = ft_var_name(line);
		return (ft_error_export(name, data), 0);
	}
	if (ft_valid_char(line[i]))
		i++;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		if (!ft_valid_char(line[i]) && line[i] != '=' && line[i] != '+')
		{
			name = ft_var_name(line);
			return (ft_error_export(name, data), 0);
		}
		i++;
	}
	return (1);
}

static int	ft_export_no_args(t_var *exec, t_data *data, char **args)
{
	t_env	*env_cpy;

	data->stat = 0;
	if (!args[1])
	{
		env_cpy = ft_lstcpy_env(data->env);
		ft_print_export(exec, ft_sort_env(env_cpy, ft_strcmp));
		return (1);
	}
	return (0);
}

static void	ft_export_args(t_data **data, char *arg, char *tmp)
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
	if (ft_strcmp(name, "PATH") == 0 && arg[4] == '=') //still need to be fixed
		(*data)->path = NULL;
}

void	ft_export(t_var *exec, t_data *data, char **args)
{
	char	*tmp;
	int		i;

	data->stat = 0;
	if (ft_export_no_args(exec, data, args))
		return ;
	i = 1;
	while (args[i])
	{
		if (!ft_valid_export(args[i], data))
			return ((void)(data->stat = 1));
		tmp = ft_strchr(args[i], '=');
		if (!ft_strncmp(ft_var_name(args[i]), "PATH", 5)
			&& !ft_lstfind_env(&data->env, "PATH", NULL))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(data->path));
		if (tmp)
			ft_export_args(&data, args[i], tmp);
		else if (ft_strchr(args[i], '+'))
			ft_error_export(args[i], data);
		else if (!ft_lstfind_env(&data->env, args[i], NULL))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(args[i])));
		i++;
	}
}
