#include "minishell.h"

char	*ft_var_name(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i - 1] == '+')
		i--;
	return (ft_substr(line, 0, i));//add protection for substr
}

char	*ft_remove_plus(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '+')
		{
			while (line[++i])
				line[i - 1] = line[i];
			break ;
		}
	}
	line[i - 1] = '\0';
	return (line);
}

int	ft_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
