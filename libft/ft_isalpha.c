#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	if (c  == '?')
		return (3);
	
	return (0);
}