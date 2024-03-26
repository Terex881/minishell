#include "../minishell.h"

void	*ft_memcpy(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	src = src1;
	dest = dest1;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
