#include "minishell.h"

static int	check_n(char *s)
{
	int i = 0;

	if (s[0] != '-')
		return (0);
	if (!s[1])
		return (0);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);	
}

void	ft_echo(char **arg, t_var *exec)
{
    int i = 0;
    int n = 0;

	if (!arg || !*arg)
		return ((void)write(exec->f_out, "\n", 1));
	if (check_n(arg[0]))
        (n = 1, i++);
	if (!arg[i])
		return ;
    while (arg && arg[i])
    {
		if (n == 1 && check_n(arg[i]))
        {
			i++;
			continue ;
		}
		ft_putstr_fd(arg[i], exec->f_out);
        if (arg[i] && arg[i + 1])
        	write(exec->f_out, " ", 1);
        i++;
    }
    if (!n)
        write(exec->f_out, "\n", 1);
}
