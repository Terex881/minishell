#include "minishell.h"

void ft_get_variable(char *str)
{
	int i;
	int index;
	char c;

	i = 0;
	int j = i;
	while (str[i] && ft_check(str[i]) == 0)
		i++;
	index = i - j ;
	printf("===> %d\n", index);

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
			// str++;
			if (ft_isalpha(*str) == 1)
	 			ft_get_variable(str);
				// printf("%s\n", getenv(str));
		}
		str++;
	}
}

// 0x0000602 00 0 0 0 0 2 b 0
// 0x0000602 00 0 0 0 0 2 b 1
int main ()
{
	t_list *list;	

	list = NULL;

	ft_token(&list);
	ft_print(list);

	// ft_lstclear(&list);
}
