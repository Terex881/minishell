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
            free(tmp -> line);
            tmp -> line = ft_strdup(new_line);
            // tmp -> line = ft_strdup(new_line);
            // free(new_line);
            return (tmp);
        }
        tmp = tmp -> next;
    }
    return (NULL);
}

char	*ft_get_line(t_data *data, char *line, int i)
{
	t_env	*tmp;

	tmp = data -> env;
	while (tmp)
	{
		if (ft_strncmp(tmp -> line, line, ft_strlen(line)) == 0)
			return (tmp -> line + i);
		tmp = tmp -> next;
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

t_env   *ft_get_env(char **env)
{
    t_env   *p;

    p = NULL;
    while (*env)
	{
		ft_lstadd_back_env(&p, ft_lstnew_env(ft_strdup(*env)));
		env++;
	}
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