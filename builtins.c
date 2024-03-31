#include "minishell.h"
#include <stdio.h>

static int	check_n(char *s)
{
	int i = 0;
	if (s[0] != '-')
		return (0);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);	
}

void	ft_echo(char **arg,t_var *exec )
{
    int i = 0;
    int n = 0;
	int j = 0;
	char *var;

	if (!arg || !*arg)
		return ((void)write(exec->f_out, "\n", 1));
	if (check_n(arg[0]))
        (n = 1, i = 1);
	if (!arg[i])
		return ;
    while (arg[i])
    {
		write(exec->f_out, arg[i], ft_strlen(arg[i])); 
		// ft_putstr_fd(arg[i], exec->f_out); // i added this 
        if (arg[i + 1])
        	write(exec->f_out, " ", 1);
        i++;
    }
    if (!n)
        write(exec->f_out, "\n", 1);
}

char *ft_varname(char *line)
{
	int i = 0;
	char *tmp;

	while (line[i] && line[i] != '=')
		i++;
	if (line[i - 1] == '+')
		i--;
	return (ft_substr(line, 0, i));
}

char *ft_removeplus(char *line)
{
	int i = 0;
	int j = 0;

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

void	ft_export(t_var *exec, t_data *data, char *line, char **env)
{
	char *tmp;
	char *var;
	t_env *env_cpy;

	if (!line)
	{
		env_cpy = ft_lstcpy_env(data->env);
		ft_sort_env(env_cpy, ft_strcmp);
		return ((void)ft_lstclear_env(&env_cpy));
	}
	tmp = ft_strchr(line, '=');
	var = NULL;
	if (tmp)
	{
		if (ft_lstfind_env(&data->env, ft_varname(line), NULL))
			var = ft_lstfind_env(&data->env, ft_varname(line), NULL)->line;
		if (!var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(ft_removeplus(line))));
		else if (var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstfind_env(&data->env, ft_varname(line), ft_strjoin(var, tmp + 1));
		else if (var)
			ft_lstfind_env(&data->env, ft_varname(line), line);
		else
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(line)));
	}
}

void	ft_unset(t_var *exec, t_data *data, char *line)
{
	t_env *p;
	t_env *tmp;
	
	p = data->env;
	tmp = NULL;
	while (p)
	{
		if (ft_strncmp(p->line, line, ft_strlen(line)) == 0)
		{
			if (tmp)
				tmp->next = p->next;
			else
				data->env = p->next;
			ft_lstdelone_env(p);
			return ;
		}
		tmp = p;
		p = p->next;
	}
}

void	ft_exit(t_var *exec, t_data **data)//🌸
{
	// clear data before exit
	(void)data;
	// ft_lstclear_env(&(*data)->env);
	// free((*data)->path);
	// free(*data);
	write(exec->f_out, "exit\n", 5);
	exit(0);
}

void	ft_cd(char *path, t_data *data)//remove OLDPWD at first use unset and export
{
	t_env *tmp;
	int n;
	
	if (!path || !*path || (path[0] == '~' && path[1] == '\0'))
		path = ft_lstfind_env(&data->env, "HOME", NULL)->line + 5;
		// path = getenv("HOME");// no tworking if unset env
	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
	n = chdir(path);
	if (!n && getcwd(NULL, 0))
	{
		ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", tmp->line + 4));
		ft_lstfind_env(&data->env, "PWD", ft_strjoin("PWD=", getcwd(NULL, 0)));
	}
	else if (!n)
	{
		ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", tmp->line + 4));
		ft_lstfind_env(&data->env, "PWD", ft_strjoin(tmp->line, "/.."));
	}
	else
		perror("chdir");
	return ;
}

void	ft_env(t_var *exec, t_data *data)
{
	t_env *p;

	p = data->env;
    while (p)
    {
		write(exec->f_out, p->line, ft_strlen(p->line));
		write(exec->f_out, "\n", 1);
        p = p->next;
    }
}

void ft_pwd(t_var *exec, t_env *env, t_data *data)//romove dataq
{
	t_env *tmp;

	tmp = ft_lstfind_env(&env, "PWD", NULL);
	write(exec->f_out, tmp->line + 4, ft_strlen(tmp->line + 4));
	write(exec->f_out, "\n", 1);
	return ;
}
