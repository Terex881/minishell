#include "minishell.h"




t_env	*ft_lstlast_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env -> next)
		env = env -> next;
	return (env);
}


t_env	*ft_lstfind_env(t_env **env, char *line, char *new_line)
{
    t_env *tmp;

    if (!env || !*env || !line)
        return (NULL);
    tmp = *env;
    while (tmp)
    {
        if (ft_strncmp(tmp -> line, line, ft_strlen(line)) == 0)
        {
            if (!new_line || !*new_line)
                return (tmp);
            free(tmp -> line); // ++>
            tmp -> line = ft_strdup(new_line);//add protection for strdup
            // tmp -> line = ft_strdup(new_line);
            free(new_line);
            return (tmp);
        }
        tmp = tmp -> next;
    }
    return (NULL);
}

char	*ft_get_line(t_data *data, char *line, int i)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp -> line, line, ft_strlen(line)) == 0)
			return (ft_strdup(tmp->line + i + 1)); // add protection for strdup
			// return (tmp->line + i); 
		tmp = tmp->next;
	}
	return (NULL);
}



int	ft_lstsize_env(t_env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	// printf("len is : %d\n", count);
	return (count);
}

t_env	*ft_lstcpy_env(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	while (env)
	{
		tmp = ft_lstnew_env(ft_strdup(env -> line));//add protection for strdup and lstnew
		if (!tmp)
		{
			ft_lstclear_env(&copy);
			return (NULL);
		}
		ft_lstadd_back_env(&copy, tmp);
		env = env -> next;
	}
	return (copy);
}

void	ft_print_export(t_var *exec, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", exec->f_out);
		ft_putstr_fd(tmp->line, exec->f_out);
		ft_putstr_fd("\n", exec->f_out);
		tmp = tmp -> next;
	}
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

void	ft_lstdelone_env(t_env *env)
{
	if (env)
	{
        free(env->line);
		free(env);
	}
}


void	ft_lstclear_env(t_env **env)
{
	t_env	*p;

	if (!env)
		return ;
	if (*env)
	{
		while (*env)
		{
			p = (*env)-> next;
			ft_lstdelone_env(*env);
			*env = p;
		}
		*env = NULL;
	}
}

t_env   *ft_get_env(t_data **data, char **env)
{
    t_env   *p;

    p = NULL;
	*data = (t_data *)malloc(sizeof(t_data));
	if(!*data)
		return (NULL);

	if (!env || !*env)
	{
		p = ft_lstnew_env(ft_strjoin("PWD=", getcwd(NULL, 0)));//add malloc protection!!!
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("SHLVL=1")));//same here
		// ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("_=/usr/bin/env")));
		(*data)->env = p;
		(*data)->path = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		return (p);
	}
    while (*env)
	{
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup(*env)));//add protection for lstnew 
		env++;
	}
	(*data)->env = p;
	(*data)->path = ft_get_line((*data), "PATH", 5);
    return (p);
}
