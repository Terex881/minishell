#include "../minishell.h"

static long long	ft_valid_arg(char *str, int *valid)
{
	short				s;
	unsigned long long	n;
	unsigned long long	tmp;

	s = 1;
	n = 0;
	*valid = 0;
	while(str && *str == 32 || (*str >= 9 && *str <= 13)) // i add this
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s *= -1;
		(str)++;
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		tmp = n;
		n = n * 10 + *str - '0';
		if (tmp > n || n > 1844674407370955169)
			return (0);
		str++;
	}
	*valid = 1;
	return (s * n);
}

void	ft_exit(t_var *exec, t_data **data, char **arg, int len)
{
	int			valid;
	long long	n;


	valid = 1;
	ft_lstclear_env(&(*data)->env);
	free((*data)->path);
	free(*data);
	if (len == 1)
		write(exec->f_out, "exit\n", 5);
	if (!arg || !arg[1])
		exit(0);
	if (arg[2])
		return ((void)write(2, "minishell: exit: too many arguments\n", 36));
	n = ft_valid_arg(arg[1], &valid);
	if (!valid)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	printf("--> %lld\n", n);
	exit(n);
}
