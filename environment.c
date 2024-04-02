#include "minishell.h"


t_env	*ft_lstnew_env(char *line)
{
	t_env	*p;

	p = (t_env *)malloc(sizeof (t_env));
	if (!p)
		return (NULL);
	p -> line = line;
	p -> next = NULL;
	return (p);
}

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
            tmp -> line = ft_strdup(new_line);
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
			return (ft_strdup(tmp->line + i + 1)); // added this line
			// return (tmp->line + i); 
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	if (env)
	{
		if (*env && new)
			ft_lstlast_env(*env)-> next = new;
		else if (new)
			*env = new;
	}
}

// int	ft_lstsize_env(t_env *env)
// {
// 	int		count;

// 	count = 0;
// 	while (env)
// 	{
// 		env = env -> next;
// 		count++;
// 	}
// 	return (count);
// }

t_env	*ft_lstcpy_env(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	while (env)
	{
		tmp = ft_lstnew_env(ft_strdup(env -> line));
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
		// printf("declare -x %s\n", tmp -> line);
		tmp = tmp -> next;
	}
	tmp = env;
	while (tmp)
	{
		printf("declare -x %s\n", tmp -> line);
		tmp = tmp -> next;
	}
	return (env);
}
// t_env	*sort_list_env(t_env *env, int (*cmp)(char *, char *))
// {
// 	t_env	*tmp;
// 	t_env	*t;
// 	char	*m;

// 	if (!env || !cmp)
// 		return ((t_env *){0});
// 	tmp = env;
// 	while (tmp -> next)
// 	{
// 		t = tmp -> next;
// 		while (t -> next)
// 		{
// 			if (cmp(tmp -> line, t -> line) > 0)
// 			{
// 				m = tmp -> line;
// 				tmp -> line = t -> line;
// 				t -> line = m;
// 				// (1) && (t -> line = ft_strdup(m), free(m));

// 			}
// 			t = t -> next;
// 		}
// 		printf("declare -x %s\n", tmp -> line);
// 		tmp = tmp -> next;
// 	}
// 	return (env);
// }

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

// int ft_size_env(char **env)
// {
//     int i = 0;
//     while (env[i])
//         i++;
//     return (i);
// }

t_env   *ft_get_env(t_data **data, char **env)
{
    t_env   *p;

    p = NULL;
	*data = (t_data *)malloc(sizeof(t_data));
	if(!*data)
		return (NULL);

	if (!env || !*env)
	{
		p = ft_lstnew_env(ft_strjoin("PWD=", getcwd(NULL, 0)));
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("SHLVL=1")));
		// ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup("_=/usr/bin/env")));
		(*data)->env = p;
		(*data)->path = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		return (p);
	}
    while (*env)
	{
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup(*env)));
		env++;
	}
	(*data)->env = p;
	(*data)->path = ft_get_line((*data), "PATH", 5);
    return (p);
}


// int main(int ac, char **av, char **env)
// {
//     t_env *p;
//     int i = 0;
//     p = ft_get_env(env);
//     while (p)
//     {
//         printf("%s\n", p->line);
//         p = p->next;
//     }
//     ft_lstclear_env(&p);
//     return (0);
// }