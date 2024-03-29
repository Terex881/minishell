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
void	ft_echo(char **arg)
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
		write(1, arg[i], ft_strlen(arg[i]));
        if (arg[i + 1])
        	write(1, " ", 1);
        i++;
    }
    if (!n)
        write(1, "\n", 1);
}

// void	ft_pwd(char *arg)
// {
// 	char tab[100];

// 	getcwd(tab, 100);
// 	write(1, tab, ft_strlen(tab));
// 	write(1, "\n", 1);
// }

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



void ft_pwd(t_env *env, t_data *data)//update pwd in env!!🌸
{
	// char tab[100];
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (errno == ENOENT)
			// printf("path no longer exist \n");
			printf("%s\n", ft_lstfind_env(&env, "PWD", NULL)->line + 4);//pwd or oldpwd? //add /..
		// write(1, "Error\n", 6);
		return ;
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

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

void	ft_cd(char *path, t_data *data)
{
	(void)data;
	if (!path || (ft_strlen(path) == 1 && path[0] == '~'))
	{
		if (chdir(getenv("HOME")) < 0)
			return (perror(NULL));
	}
	else if (chdir(path) < 0)
		return (perror(NULL));
}

void	ft_exit()//🌸
{
	write(1, "exit\n", 5);
	exit(0);
}

