#include "minishell.h"

char *ft_get_variable(char *str)
{
	int i;
	int index;
	char c;

	i = 0;
	int j = i;
	// opendir()
	while (str[i] && ft_isalpha(str[i]) != 0 && ft_check(str[i]) == 0)
		i++;
	index = i - j ;
	return (ft_substr(str, j, i- j));

}
void ft_expand(t_list *list)
{
	char *str;
	char *tmp;
	t_list *node;
	int i;

	i = 0;
	str = list->value;
	
	while (*str)
	{
		if(*str == '$')
		{
			str++;
			if (ft_isalpha(*str) == 1)
			{
	 			char *tt = ft_get_variable(str);
				printf("%s\n", getenv(tt));

			}
		}
		str++;
	}
}

int main ()
{
	t_list *list;	

	list = NULL;

	ft_token(&list);
	ft_print(list);

	// ft_lstclear(&list);
}
