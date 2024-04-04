#include "../minishell.h"

char	*ft_lstfind_env(t_env **env, char *line, char *new_line)
{
    t_env	*tmp;
	char	*find;

    if (!env || !*env || !line)
        return (NULL);
    tmp = *env;
    while (tmp)
    {
        if (ft_strncmp(tmp -> line, line, ft_strlen(line)) == 0)
        {
            if (!new_line || !*new_line)
			{
				find = ft_strdup(tmp->line);//add protection for strdup
                return (find);//add protection for strdup
			}
            free(tmp -> line); // ++>
            tmp -> line = ft_strdup(new_line);//add protection for strdup
            // tmp -> line = ft_strdup(new_line);
            // free(new_line);
			find = ft_strdup(tmp->line);//add protection for strdup
            return (find);//add protection for strdup
        }
        tmp = tmp -> next;
    }
    return (NULL);
}

char	*ft_get_line(t_data *data, char *line, int i)
{
	t_env	*tmp;
	char	*res;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp -> line, line, ft_strlen(line)) == 0)
		{
			res = ft_strdup(tmp->line + i + 1);//add protection for strdup
			return (res); // add protection for strdup
		}
			// return (tmp->line + i); 
		tmp = tmp->next;
	}
	return (NULL);
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

// void	ft_lstdelone_env(t_env *env)
// {
// 	if (env)
// 	{
//         free(env->line);
// 		free(env);
// 	}
// }

t_env   *ft_get_env(t_data **data, char **env)
{
    t_env   *p;
	char	*pwd;

    p = NULL;
	*data = (t_data *)malloc(sizeof(t_data));
	if(!*data)
		return (NULL);
	(*data)->stat = 0;
	if (!env || !*env)
	{
		pwd = getcwd(NULL, 0);
		p = ft_lstnew_env(ft_strjoin("PWD=", pwd));//add malloc protection!!!
		// ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("SHLVL=1")));//same here
		// ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("_=/usr/bin/env")));
		free(pwd);
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
