/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:58:27 by cmasnaou          #+#    #+#             */
/*   Updated: 2024/05/12 10:09:16 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_var_name(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (i > 0 && line[i - 1] == '+')
		i--;
	return (ft_substr(line, 0, i));
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

t_env	*ft_sort_env(t_env *env, int (*cmp)(char *, char *))
{
	t_env	*tmp;
	t_env	*t;
	char	*m;

	if (!env || !cmp)
		return ((t_env *){0});
	tmp = env;
	while (tmp && tmp->next)
	{
		t = tmp -> next;
		while (t)
		{
			if (cmp(tmp -> line, t -> line) > 0)
			{
				m = tmp -> line;
				tmp -> line = t -> line;
				t -> line = m;
			}
			t = t -> next;
		}
		tmp = tmp -> next;
	}
	return (env);
}

void	ft_print_export(t_var *exec, t_data *data, t_env *env)
{
	t_env	*tmp;
	char	*var;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, "_=", 2)
			|| (data->no_env && !ft_strncmp(tmp->line, "PATH=", 5))
			|| (data->no_pwd && !ft_strncmp(tmp->line, "OLDPWD=", 7)))
		{
			tmp = tmp -> next;
			continue ;
		}
		ft_putstr_fd("declare -x ", exec->f_out);
		var = ft_strchr(tmp->line, '=');
		if (var)
			ft_put_line(exec, var, ft_var_name(tmp->line));
		else
			ft_putstr_fd(tmp->line, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
		tmp = tmp -> next;
	}
}
