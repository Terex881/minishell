#include "minishell.h"

int ff(char *c)
{
	if (*c == ' '  || *c == '>' || *c == '<' || *c == '|' || *c == '\t')
		return (1);
	if (*c == '\"' || *c == '\'')
		return (2);
	if (*c == '$')
		return (3);
	if (*c >= '0' && *c <= '9')
		return (4);
	return (0);
}
void ft_special_character(t_list *node, char *c, t_list **list, int *i)
{
	node = ft_lstnew(c);
	if (*c == ' ')
		(node->type = SPACE_, node->value = " ");
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

	if (ff(&line[*i]) == 2)
	{
		(*i)++;
		while (line[*i] && ff(&line[*i]) != 2)
			(*i)++;
	}
	while (line[*i] && ff(&line[*i]) != 1)
		(*i)++;
	tmp = ft_substr(line, j, *i - j);
	node = ft_lstnew(tmp);
	free(tmp);
	node->value = tmp;
	if (ff(&line[j]) == 3 && ff(&line[j+1]) == 0)
		node->type = VARIABLE;
	else
		node->type= WORD;
	ft_lstadd_back(list, node);
	(*i)--;
}
void ft_token(t_list **list)
{
	char *line;
	int i;
	t_list *node;

	node = NULL;
	i = 0;
	line = readline("minishell :");
	if(!line)
		exit(1);
	// while(line)
	// {
		while (line[i])
		{
			if (ff(&line[i]) == 1)
				ft_special_character(node, &line[i], list, &i);
			else if (ff(&line[i]) != 1 && ff(&line[i]) != 3)
				ft_add_word(line, &i, list, node);
			else
				ft_add_word(line, &i, list, node);
			i++;
		}
		free(line);
	// 	line = readline("minishell :");
	// }
}
void ft_print(t_list *list)
{
	while (list)
	{
		if (list->type==WORD)
			printf("Word   %s\n", list->value);
		if (list->type==PIPE)
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

void f1()
{
	system("leaks minishell");
}
int main ()
{
	t_list *list;
	
	list = NULL;
	// atexit(f1);
	ft_token(&list);
	ft_print(list);
	ft_lstclear(&list);


}
// minishell :ls           -la
// Word   