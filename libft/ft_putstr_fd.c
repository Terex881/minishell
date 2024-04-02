#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (fd >= 0 && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (!s || fd < 0)
// 		return ;
// 	write(fd, s, ft_strlen(s));
// }