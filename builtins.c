#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}

int	check_n(char *s)
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
void echo_(char **arg)
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

void pwd_(char *arg)
{
	char tab[100];

	getcwd(tab, 100);
	write(1, tab, ft_strlen(tab));
	write(1, "\n", 1);
}

void env_(char **env)
{
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

int main(int ac, char **av, char **env)
{
	char tab[100];
	if (ac == 1)
		return (0);
	if (!ft_strncmp(av[1], "echo", 5))
		echo_(av + 2);
	if (!ft_strncmp(av[1], "pwd", 4))
		pwd_(av[1]);
	if (!ft_strncmp(av[1], "env", 4))
	{
		if (av[2])
			return (write(1, "Error\n", 7), 1);
		else
			env_(env);
	}
	return (0);
}
