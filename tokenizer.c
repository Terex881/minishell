#include "minishell.h"
#include <unistd.h>

int	ft_check(char c)
{
	if (c == ' '  || c == '>' || c == '<' || c == '|' || c == '\t')
		return (1);
	if (c == '\"' || c == '\'')
		return (2);
	if (c == '$')
		return (3);
	return (0);
}
t_list	*ft_add_special_character(t_list *node, char *c, int *i)
{
	node = ft_lstnew(c);
	if (!node)
		return (NULL);
	if (*c == ' ' || *c == '\t')
		(node->type = SPACE_, node->value = NULL);
	else if (*c == '>' &&  *(c+1) == '>')
		(node->type = APPEND, node->value = NULL, (*i)++);
	else if (*c == '<' && *(c+1)  == '<')
		(node->type = HER_DOC, node->value = NULL, (*i)++);
	else if (*c == '>')
		(node->type = R_OUT, node->value = NULL);
	else if (*c == '<')
		(node->type = R_IN, node->value = NULL);
	else if (*c == '|')
		(node->type = PIPE, node->value = NULL);
	return (node);
}
t_list	*ft_add_douple_single(char *line, int *i, t_list *node)
{
	int		j;
	char	*tmp;
	char	c;
	char	*str;

	j = *i;
	c = line[*i];
	(*i)++;
	while(line[*i] && line[*i] != c)
		(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if(!tmp)
		return(free(tmp), NULL);
	str = tmp;
	tmp = ft_strtrim(tmp, "\"");
	node = ft_lstnew(tmp);
	node->value =  tmp;
	free(str);
	if ((line[j] == '\"' || line[j] == '\'') && line[*i] == '\0')
		return(ft_putstr_fd("33\n", 2), free(tmp), NULL);
	if (line[j] == '\"')
		node->type = D_Q;
	else if (line[j] == '\'')
		node->type = S_Q;
	return(node);
}

t_list	*ft_add_word(char *line, int *i, t_list *node)
{
	int j;
	j = *i;
	char *tmp;

	if (ft_check(line[*i]) == 2)
		return(ft_add_douple_single(line, i, node));
	else
		while(line[*i+1] && (ft_check(line[*i+1]) == 0))
			(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1); // check +1
	if (!tmp)
		return(NULL);
	node = ft_lstnew(tmp);
	node->value = tmp;
	if ((line[j]) == '$' && ft_isalpha(line[j+1]))
		node->type = VARIABLE;
	else
		node->type = WORD;
	return(node);
}

void	ft_token(t_list **list)
{
	t_list	*node;
	char	*line;
	int		i;

	// while(1)
	// {
		line = readline("minishell :");
		add_history(line);
		node = NULL;
		*list = NULL;
		i = 0;
		if(!line)
			exit(1);
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == '\t')
				while (line[i + 1] && (line[i + 1] == ' ' || line[i + 1] == '\t'))
					i++;
			if (line[i] && ft_check(line[i]) == 1)
				node = ft_add_special_character(node, &line[i], &i);
			else if (line[i])
				node = ft_add_word(line, &i, node);
			if(!node)
				ft_lstclear(list);
			ft_lstadd_back(list, node);
			i++;
		}
	// 	free(line);
	// 	ft_syntax_error(list);
	// 	ft_lstclear(list);	
	// }
}

void ft_print(t_list *list)
{
	while (list)
	{
		if (list->type == WORD)
			printf("Word   %s\n", list->value);
		if (list->type == PIPE)
			printf("pipe   %s\n", list->value);
		if (list->type == HER_DOC)
			printf("here_doc   %s\n", list->value);
		if (list->type == R_IN)
			printf("R_IN   %s\n", list->value);
		if (list->type == R_OUT)
			printf("R_OUT   %s\n", list->value);
		if (list->type == SPACE_)
			printf("space   %s\n", list->value);
		if (list->type == APPEND)
			printf("append   %s\n", list->value);
		if (list->type == D_Q)
			printf("D_Q   %s\n", list->value);
		if (list->type == S_Q)
			printf("S_Q   %s\n", list->value);
		if (list->type == VARIABLE)
			printf("variable   %s\n", list->value);
		list = list->next;
	}
}
 