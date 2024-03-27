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
void ft_echo(char **arg)
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

void ft_pwd(char *arg)
{
	char tab[100];

	getcwd(tab, 100);
	write(1, tab, ft_strlen(tab));
	write(1, "\n", 1);
}

void ft_env(char **env)
{
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

