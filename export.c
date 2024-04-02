#include "minishell.h"

static void	ft_error_export(char *line)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	ft_valid_export(char *line)
{
	int		i;
	char	*name;

	i = 0;
	if (line[0] == '=' || line[0] == '+' || (line[0] >= '0' && line[0] <= '9'))
	{
		name = ft_var_name(line);
		return (ft_error_export(name), free(name), 0);
	}
	if (ft_valid_char(line[i]))
		i++;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		if (!ft_valid_char(line[i]) && line[i] != '=' && line[i] != '+')
		{
			name = ft_var_name(line);
			return (ft_error_export(name), free(name), 0);
		}
		i++;
	}
	return (1);
}

static int	ft_export_no_args(t_data *data, char *line)
{
	t_env	*env_cpy;

	if (!line)
	{
		env_cpy = ft_lstcpy_env(data->env);
		ft_sort_env(env_cpy, ft_strcmp);
		ft_lstclear_env(&env_cpy);
		return (1);
	}
	if (!ft_valid_export(line))
		return (1);
	return (0);
}

void	ft_export(t_var *exec, t_data *data, char *line)
{
	char	*tmp;
	char	*var;
	char	*name;

	if (ft_export_no_args(data, line))
		return ;
	(1) && (tmp = ft_strchr(line, '='), var = NULL);
	if (tmp)
	{
		name = ft_var_name(line);
		if (ft_lstfind_env(&data->env, name, NULL))
			var = ft_lstfind_env(&data->env, name, NULL)->line;
		if (!var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstadd_back_env(&data->env,
				ft_lstnew_env(ft_strdup(ft_remove_plus(line))));
		else if (var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstfind_env(&data->env, name, ft_strjoin(var, tmp + 1));
		else if (var)
			ft_lstfind_env(&data->env, name, line);
		else
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(line)));
		free(name);
	}
	else if (ft_strchr(line, '+'))
		ft_error_export(line);
}
