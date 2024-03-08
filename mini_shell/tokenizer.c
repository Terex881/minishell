#include "minishell.h"
#include <stdio.h>

int ft_check(char *c)
{
	if (*c == ' '  || *c == '>' || *c == '<' || *c == '|' || *c == '\t')
		return (1);
	if (*c == '\"' || *c == '\'' )
		return (2);
	if (*c == '\"' || *c == '\'' )
		return (2);
	if (*c == '$')
		return (3);
	if (*c >= '0' && *c <= '9')
		return (4);
	return (0);
}
void	ft_add_special_character(t_list *node, char *c, t_list **list, int *i)
{
	node = ft_lstnew(c);
	if (*c == ' ' || *c == '\t')
	{
		(node->type = SPACE_, node->value = " ");
	}
	else if (*c == '>' &&  *(c+1) == '>')
		(node->type = APPEND, node->value = ">>", (*i)++);
	else if (*c == '<' && *(c+1)  == '<')
		(node->type = HER_DOC, node->value = "<<", (*i)++);
	else if (*c == '>')
		(node->type = R_OUT, node->value = ">");
	else if (*c == '<')
		(node->type = R_IN, node->value = "<");
	else if (*c == '|')
		(node->type = PIPE, node->value = "|");
	ft_lstadd_back(list, node);
}
void ft_add_word(char *line, int *i, t_list **list, t_list *node)
{
	int j;
	j = *i;
	char *tmp;

	if (ft_check(&line[*i]) == 2)
	{
		(*i)++;
		while (line[*i] && ft_check(&line[*i]) != 2)
			(*i)++;
		if(ft_check(&line[*i]) != 2)
			perror("66"); // to check if there is one D_Q or S_Q
	}
	while (line[*i] && ft_check(&line[*i]) != 1)
		(*i)++;
	tmp = ft_substr(line, j, *i - j);
	node = ft_lstnew(tmp);
	// free(tmp);
	node->value = tmp;
	if (line[j] == '\"')
		node->type = D_Q;
	else if (line[j] == '\'')
		node->type = S_Q;
	else if (ft_check(&line[j]) == 3 && ft_check(&line[j+1]) == 0)
		node->type = VARIABLE;
	else
		node->type= WORD;
	
	ft_lstadd_back(list, node);
	(*i)--;
}

void ft_token(t_list **list)
{
	t_list	*node;
	char	*line;
	int		i;

	line = readline("minishell :");
	while(line)
	{
		*list = NULL;
		node = NULL;
		i = 0;
		if(!line)
			exit(1);
		while (line[i])
		{
			if (line[i] == 32)
			{
				ft_add_special_character(node, &line[i], list, &i);
				while (line[i] == ' ' || line[i] == '\t')
					i++;	
			}
			if (line[i] && ft_check(&line[i]) == 1)
				ft_add_special_character(node, &line[i], list, &i);
			else if (line[i])
				ft_add_word(line, &i, list, node);
			i++;
		}
		free(line);
		ft_parsing(*list);
		line = readline("minishell :");
	}
}

void ft_print(t_list *list)
{
	while (list)
	{
		if (list->type == WORD)
			printf("Word   %s\n", list->value);
		if (list->type == PIPE)
			printf("pipe   %s\n", list->value);
		if (list->type==HER_DOC)
			printf("here_doc   %s\n", list->value);
		if (list->type==R_IN)
			printf("R_IN   %s\n", list->value);
		if (list->type==R_OUT)
			printf("R_OUT   %s\n", list->value);
		if (list->type==SPACE_)
			printf("space   %s\n", list->value);
		if (list->type==APPEND)
			printf("append   %s\n", list->value);
		if (list->type==D_Q)
			printf("D_Q   %s\n", list->value);
		if (list->type==S_Q)
			printf("S_Q   %s\n", list->value);
		if (list->type==VARIABLE)
			printf("variable   %s\n", list->value);
		list = list->next;
	}
}
