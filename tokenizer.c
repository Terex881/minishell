#include "minishell.h"

int	ft_check(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t')
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
	{
		node->type = SPACE_;
		node->value = NULL;
	}
	else if (*c == '>' && *(c + 1) == '>')
	{
		node->type = APPEND;
		node->value = NULL;
		(*i)++;
	}
	else if (*c == '<' && *(c + 1) == '<')
	{
		node->type = HER_DOC;
		node->value = NULL;
		(*i)++;
	}
	else if (*c == '>')
	{
		node->type = R_OUT;
		node->value = NULL;
	}
	else if (*c == '<')
	{
		node->type = R_IN;
		node->value = NULL;
	}
	else if (*c == '|')
	{
		node->type = PIPE;
		node->value = NULL;
	}
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
	while (line[*i] && line[*i] != c)
		(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if (!tmp)
		return (free(tmp), NULL);
	str = tmp;
	tmp = ft_strtrim(tmp, line[j]);
	node = ft_lstnew(tmp);
	node->value = tmp;
	free(str);
	if ((line[j] == '\"' || line[j] == '\'') && line[*i] == '\0')
		return (ft_putstr_fd("33\n", 2), free(tmp), free(node), NULL);
	if (line[j] == '\"')
		node->type = D_Q;
	else if (line[j] == '\'')
		node->type = S_Q;
	return (node);
}

t_list	*ft_add_word(char *line, int *i, t_list *node)
{
	int		j;
	char	*tmp;

	j = *i;
	if (ft_check(line[*i]) == 2)
		return (ft_add_douple_single(line, i, node));
	else
		while (line[*i + 1] && (ft_check(line[*i + 1]) == 0))
			(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if (!tmp)
		return (NULL);
	node = ft_lstnew(tmp);
	node->value = tmp;
	if ((line[j]) == '$' && ft_isalpha(line[j + 1]))
		node->type = VARIABLE;
	else
		node->type = WORD;
	return (node);
}
void ft_token(char *line, t_list *node, t_list **list)
{
	int i;

	line = readline("minishell :");
	add_history(line);
	node = NULL;
	*list = NULL;
	i = 0;
	if (!line) // check this
		return;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			while (line[i + 1] && (line[i + 1] == 32 || line[i + 1] == 9))
				i++;
		if (line[i] && ft_check(line[i]) == 1)
			node = ft_add_special_character(node, &line[i], &i);
		else if (line[i])
			node = ft_add_word(line, &i, node);
		if (!node)
			ft_lstclear(list);
		ft_lstadd_back(list, node);
		i++;
	}
	free(line);
}

void	ft_all(t_list **list, char **env)
{
	t_list	*node;
	t_var	*exec;
	char	*line;

	line = NULL;
	node = NULL;
	exec = NULL;
	while (1)
	{
		ft_token(line, node, list);
		ft_syntax_error(list);
		exec = ft_allocate_list(list);
		ft_open_her_doc(list, exec);
		ft_open_files(list, exec);
		ft_len_node_elem(list, exec);
		ft_copy_to_list(list, exec);
		ft_print_var(exec);
		ft_execution(exec, env);
		ft_lstclear(list);
		ft_lstclear_var(&exec);
	}
}

void	ft_print(t_list *list)
{
	while (list)
	{
		if (list && list->type == WORD)
			printf("Word   %s\n", list->value);
		else if (list && list->type == PIPE)
			printf("pipe   %s\n", list->value);
		else if (list && list->type == HER_DOC)
			printf("here_doc   %s\n", list->value);
		else if (list && list->type == R_IN)
			printf("R_IN   %s\n", list->value);
		else if (list && list->type == R_OUT)
			printf("R_OUT   %s\n", list->value);
		else if (list && list->type == SPACE_)
			printf("space   %s\n", list->value);
		else if (list && list->type == APPEND)
			printf("append   %s\n", list->value);
		else if (list && list->type == D_Q)
			printf("D_Q   %s\n", list->value);
		else if (list && list->type == S_Q)
			printf("S_Q   %s\n", list->value);
		else if (list && list->type == VARIABLE)
			printf("variable   %s\n", list->value);
		list = list->next;
	}
}
