#include "../minishell.h"

void	ft_error_export(char *line, t_data *data)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if(data)
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
		return (ft_error_export(name, data),  0);
		// return (ft_error_export(name, data), free(name), 0);
	}
	if (ft_valid_char(line[i]))
		i++;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		if (!ft_valid_char(line[i]) && line[i] != '=' && line[i] != '+')
		{
			name = ft_var_name(line);
			return (ft_error_export(name, data),  0);
			// return (ft_error_export(name, data), free(name), 0);
		}
		i++;
	}
	// free(name);
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
		// ft_lstclear_env(&env_cpy);
		return (1);
	}
	
	// if (!ft_valid_export(line, data))
	// {
	// 	data->stat = 1;		
	// 	return (1);
	// }
	return (0);
}

void	ft_export(t_var *exec, t_data *data, char **args)
{
	char	*tmp;
	char	*var;
	char	*name;
	int		i;

	data->stat = 0;
	if (ft_export_no_args(exec, data, args))
		return ;
	i = 1;
	while (args[i])
	{
		if (!ft_valid_export(args[i], data))
		{
			data->stat = 1;		
			return ;
		}
		(1) && (tmp = ft_strchr(args[i], '=')/*, var = NULL*/);
		if (tmp)
		{
			name = ft_var_name(args[i]);
			// if (ft_lstfind_env(&data->env, name, NULL))
			var = ft_lstfind_env(&data->env, name, NULL);
			if (!var && !ft_strncmp(tmp - 1, "+=", 2))
				ft_lstadd_back_env(&data->env,
					ft_lstnew_env(ft_strdup(ft_remove_plus(args[i]))));//protection needed for dup and lstnew
					
			else if (var && !ft_strncmp(tmp - 1, "+=", 2))
			{
				if (!ft_strchr(var, '='))
					ft_lstfind_env(&data->env, name, ft_strjoin(ft_strjoin(var, "="), tmp + 1));//add protection for strjoin
				else
					ft_lstfind_env(&data->env, name, ft_strjoin(var, tmp + 1));//add protection for strjoin
			}
			else if (var)
				ft_lstfind_env(&data->env, name, args[i]);
			else
				ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(args[i])));//protection needed for dup and lstnew
			// (free(name), free(var));
		}
		else if (ft_strchr(args[i], '+'))
			ft_error_export(args[i], data);
		else if (!ft_lstfind_env(&data->env, args[i], NULL))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(args[i])));
		i++;
	}
}
