#include "../minishell.h"

char	*ft_var_name(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i - 1] == '+')
		i--;
	return (ft_substr(line, 0, i));//add protection for substr
}

char	*ft_remove_plus(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '+')
		{
			while (line[++i])
				line[i - 1] = line[i];
			break ;
		}
	}
	line[i - 1] = '\0';
	return (line);
}

int	ft_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

void	ft_print_export(t_var *exec, t_env *env)// fix ""
{
	t_env	*tmp;
	char	*var;
	char	*name;


	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", exec->f_out);
		var = ft_strchr(tmp->line, '=');
		if (var)
		{
			name = ft_var_name(tmp->line);
			ft_putstr_fd(name, exec->f_out);
			free(name);
			ft_putstr_fd("=", exec->f_out);
			ft_putstr_fd("\"", exec->f_out);
			ft_putstr_fd(var + 1, exec->f_out);
			ft_putstr_fd("\"", exec->f_out);
		}
		else
			ft_putstr_fd(tmp->line, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
		tmp = tmp -> next;
	}

}

