#include "minishell.h"

static char *ft_var_name(char *line)
{
	int i = 0;

	while (line[i] && line[i] != '=')
		i++;
	if (line[i - 1] == '+')
		i--;
	return (ft_substr(line, 0, i));
}

static char *ft_remove_plus(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] == '+')
		{
			i++;
			while (line[i])
			{
				line[i - 1] = line[i];
				i++;
			}
			break ;
		}
		i++;
	}
	line[i - 1] = '\0';
	return (line);
}

static int  ft_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}


static void	ft_error_export(char *line)
{
	write(2, "minishell :export: `", 20);
	write(2, line, ft_strlen(line));
	write(2, "': not a valid identifier\n", 26);
}

static int	ft_valid_export(char *line)
{
	int i = 0;

	if (line[0] == '=' || line[0] == '+' || (line[0] >= '0' && line[0] <= '9'))
	{
		ft_error_export(ft_var_name(line));
		return (0);
	}
	if (ft_valid_char(line[i]))
		i++;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		if (!ft_valid_char(line[i]) && line[i] != '=' && line[i] != '+')
		{
			ft_error_export(ft_var_name(line));
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_export_no_args(t_data *data, char *line, char **env)
{
	t_env *env_cpy;

	if (!line)
	{
		env_cpy = ft_lstcpy_env(data->env);
		ft_sort_env(env_cpy, ft_strcmp);
		ft_lstclear_env(&env_cpy);
		return (1);
	}
	return (0);
}

void	ft_export(t_var *exec, t_data *data, char *line, char **env)
{
	char *tmp;
	char *var;

	if (ft_export_no_args(data, line, env))
		return ;
	if (!ft_valid_export(line))
		return ;
	tmp = ft_strchr(line, '=');
	var = NULL;
	if (tmp)
	{
		if (ft_lstfind_env(&data->env, ft_var_name(line), NULL))
			var = ft_lstfind_env(&data->env, ft_var_name(line), NULL)->line;
		if (!var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(ft_remove_plus(line))));
		else if (var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstfind_env(&data->env, ft_var_name(line), ft_strjoin(var, tmp + 1));
		else if (var)
			ft_lstfind_env(&data->env, ft_var_name(line), line);
		else
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(line)));
	}
	else if (ft_strchr(line, '+'))
		ft_error_export(line);
}
