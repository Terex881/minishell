#include "minishell.h"

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
		return ((void)write(1, "\n", 1));
	if (check_n(arg[0]))
        (1) && (n = 1, i = 1);
	if (!arg[i])
		return ;
    while (arg[i])
    {
		// write(1, arg[i], ft_strlen(arg[i])); 
		ft_putstr_fd(arg[i], exec->f_out); // i added this 
        if (arg[i + 1])
        	write(1, " ", 1);
        i++;
    }
    if (!n)
        write(1, "\n", 1);
}

// static char	*old_pwd(char **env)//🌸
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)//pwd
// 			return (env[i] + 7);
// 		i++;
// 	}
// 	return (NULL);
// }



// void ft_pwd(t_env *env, t_data *data)//update pwd in env!!🌸
// {
// 	// char tab[100];
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 	{
// 		if (errno == ENOENT)
// 			// printf("path no longer exist \n");
// 			printf("%s\n", ft_lstfind_env(&env, "PWD", NULL)->line + 4);//pwd or oldpwd? //add /..
// 		// write(1, "Error\n", 6);
// 		return ;
// 	}
// 	write(1, pwd, ft_strlen(pwd));
// 	write(1, "\n", 1);
// }

void ft_pwd(t_env *env, t_data *data)//update pwd in env!!🌸
{
	// char tab[100];
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (errno == ENOENT)
		{
			printf("path no longer exist \n");
			// printf("%s\n", ft_lstfind_env(&env, "PWD", NULL)->line + 4);//pwd or oldpwd? //add /..
			printf("%s\n", data->old_pwd + 4);//pwd or oldpwd? //add /..
			// write(1, "Error\n", 6);
			return ;
		}
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

// void	ft_env(t_var *exec, t_data *data)
// {
// 	t_data *q;
// 	t_env *p;
// 	t_env *tmp;
	
// 	q = data;
// 	p = data->env;
// 	// exec->old_pwd = old_pwd(exec->env);
// 	if (getcwd(NULL, 0) != NULL)
// 	{
// 		// while (q)
// 		// {
// 			tmp = ft_lstfind_env(&q->env, "PWD", ft_strjoin("PWD=", getcwd(NULL, 0)));
// 			q->old_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
// 			// printf(" ==> %s\n\n", q->old_pwd);
// 		// 	q = q->next;
// 		// }
// 	}
// 	// printf("---- %s\n\n", tmp->line);
// 	// else
// 		// printf(" ==> %s\n\n", q->old_pwd);
//     while (p)
//     {
//         printf("%s\n", p->line);
//         p = p->next;
//     }
// }

void	ft_env(t_var *exec, t_data *data)
{
	t_data *q;
	t_env *p;
	t_env *tmp;
	
	q = data;
	p = data->env;
	// exec->old_pwd = old_pwd(exec->env);
	if (getcwd(NULL, 0) != NULL)
	{
		// while (q)
		// {
			tmp = ft_lstfind_env(&q->env, "PWD", ft_strjoin("PWD=", getcwd(NULL, 0)));
			q->old_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
			// printf(" ==> %s\n\n", q->old_pwd);
		// 	q = q->next;
		// }
	}
	// printf("---- %s\n\n", tmp->line);
	// else
		// printf(" ==> %s\n\n", q->old_pwd);
    while (p)
    {
        printf("%s\n", p->line);
        p = p->next;
    }
}

// void	ft_cd(char *path, t_data *data)
// {
// 	(void)data;
// 	if (!path || (ft_strlen(path) == 1 && path[0] == '~'))
// 	{
// 		if (chdir(getenv("HOME")) < 0)
// 			return (perror(NULL));
// 	}
// 	else if (chdir(path) < 0)
// 		return (perror(NULL));
// }

void	ft_cd(char *path, t_data *data)
{
	static int count;
	(void)data;
	char *tmp;
	int i = 0;
	
	tmp = getcwd(NULL, 0);
	if (tmp)
		ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", getcwd(NULL, 0)));
	if (!path || (ft_strlen(path) == 1 && path[0] == '~'))
	{
		if (chdir(getenv("HOME")) < 0)
		{
			// data->old_pwd = getcwd(NULL, 0);
			// printf("%s\n", data->old_pwd);
			return (perror(NULL));
		}
	}
	if (chdir(path) < 0)
	{
		// ft_lstfind_env(&data->env, "OLDPWD", ft_strjoin("OLDPWD=", getcwd(NULL, 0)));
		// tmp1 = ft_strjoin(tmp1, "/..");
		data->old_pwd = ft_strjoin(data->old_pwd, "/..");
		// printf("%s\n", tmp1);
		return (perror(NULL));
	}
}

char *ft_varname(char *line)
{
	int i = 0;
	char *tmp;

	while (line[i] && line[i] != '=')
		i++;
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

void	ft_export(t_var *exec, t_data *data, char *line)
{
	char *tmp;
	char *var;

	if (!line)//print sorted env
		return ;
	tmp = ft_strchr(line, '=');
	var = NULL;
	// printf("tmp = %s\n", tmp);
	if (tmp)
	{
		if (ft_lstfind_env(&data->env, ft_varname(line), NULL))
			var = ft_lstfind_env(&data->env, ft_varname(line), NULL)->line;
		// printf("tmp = %s   %d\n", tmp - 1, ft_strncmp(tmp - 1, "+=", 2));
		//if var doesnt exist and += is found put only =
		if (!var && !ft_strncmp(tmp - 1, "+=", 2))
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(ft_removeplus(line))));
		else if (var && !ft_strncmp(tmp - 1, "+=", 2))
		{
			// printf("i am here\n");
			ft_lstfind_env(&data->env, ft_varname(line), ft_strjoin(var, tmp + 1));
		}
		else if (var)
			ft_lstfind_env(&data->env, ft_varname(line), line);
		else
			ft_lstadd_back_env(&data->env, ft_lstnew_env(ft_strdup(line)));
	}
}
void	ft_unset(t_var *exec, t_data *data, char *line)// to fix
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
			free(p->line);
			free(p);
			return ;
		}
		tmp = p;
		p = p->next;
	}
}

void	ft_exit(t_data **data)//🌸
{
	(void)data;
	// clear data before exit
	write(1, "exit\n", 5);
	exit(0);
}

