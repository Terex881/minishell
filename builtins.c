#include "minishell.h"

void	ft_unset(t_var *exec, t_data *data, char *line)
{
	t_env *p;
	t_env *tmp;
	
	p = data->env;
	tmp = NULL;
	if (ft_strncmp(line, "PATH", 5) == 0)
		data->path = NULL;
	while (p)
	{
		if (ft_strncmp(p->line, line, ft_strlen(line)) == 0)
		{
			if (tmp)
				tmp->next = p->next;
			else
				data->env = p->next;
			free(p->line);
			// free(p);
			// ft_lstdelone_env(p);
			return ;
		}
		tmp = p;
		p = p->next;
	}
}

void	ft_cd(char *path, t_data *data)
{
	t_env *tmp;
	int n;
	
	if (!path || !*path || (path[0] == '~' && path[1] == '\0'))
		path = ft_lstfind_env(&data->env, "HOME", NULL)->line + 5;
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
	{
		write(2, "minishell: ", 11);
		perror(path);
	}
	return ;
}


void	ft_env(t_var *exec, t_data *data)
{
	t_env *p;
	static int	i;//🌸

	if (!i)//🌸
		ft_unset(exec, data, "OLDPWD");//🌸to remove oldpwd at start
	i++;//🌸
	p = data->env;
    while (p)
    {
		write(exec->f_out, p->line, ft_strlen(p->line));
		write(exec->f_out, "\n", 1);
        p = p->next;
    }
}

void ft_pwd(t_var *exec, t_env *env)
{
	t_env *tmp;

	tmp = ft_lstfind_env(&env, "PWD", NULL);
	write(exec->f_out, tmp->line + 4, ft_strlen(tmp->line + 4));
	write(exec->f_out, "\n", 1);
	return ;
}
