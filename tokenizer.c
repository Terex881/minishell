#include "minishell.h"
#include <stdio.h>

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
	if (*c == 32 || (*c >= 9 && *c <= 32))
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
	// node->value = tmp;
	free(str);
	if ((line[j] == '\"' || line[j] == '\'') && line[*i] == '\0')
		return (ft_putstr_fd("33\n", 2), free(tmp), free(node), NULL);
	if (line[j] == '\"')
		node->type = D_Q;
	else if (line[j] == '\'')
		node->type = S_Q;
	return (node);
}

t_list *ft_add_var(char *line, int *i, t_list *node)
{
	int j;
	char *tmp;
	j = *i;

	while(line[*i+1] && ft_isalpha(line[*i+1]) != 0)
		(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if (!tmp)
		return (NULL);
	node = ft_lstnew(tmp);
	// node->value = tmp;
	if ((line[j]) == '$' && ft_isalpha(line[j + 1]) == 1)
		node->type = VARIABLE;
	else
	 	node->type = WORD;
	return node;
}
t_list	*ft_add_word(char *line, int *i, t_list *node)
{
	int		j;
	char	*tmp;

	j = *i;
	if (ft_check(line[*i]) == 2)
		return (ft_add_douple_single(line, i, node));
	else if (ft_check(line[*i]) == 3)
		return (ft_add_var(line, i, node));
	else
		while (line[*i + 1] && (ft_check(line[*i + 1]) == 0))
			(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if (!tmp)
		return (NULL);
	node = ft_lstnew(tmp);
	// node->value = tmp;
	node->type = WORD;
	return (node);
}
int ft_token(char *line, t_list *node, t_list **list)
{
	int i;

	node = NULL;
	*list = NULL;
	i = 0;
	line = readline("minishell :");
	if (line == NULL)
		return (0);
	add_history(line);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			while (line[i + 1] && (line[i + 1] == 32 || (line[i + 1] >= 9 && line[i + 1] <= 13)))
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
	return (free(line), 1);
}

void	ft_all(t_list **list, char **env, t_exit info)
{
	t_list	*node;
	t_var	*exec;
	t_data	*data;;
	// t_exit *info;
	// info->exitstat = 0;
	char	*line;

	line = NULL;
	node = NULL;
	exec = NULL;
	/***************************************/ // add function ft_fill_data 
	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_get_env(env);
	data->path = ft_get_line(data, "PATH", 5);
	// printf("path = %s\n", data->path);
	data->old_pwd = ft_get_line(data, "PWD", 4);
	/***************************************/
	while (1)
	{
		ft_signal();
		if(!ft_token(line, node, list))
			return (printf("exit") ,ft_lstclear(list));
		if (ft_syntax_error(list) == 0)
		{
			// ft_expand(list, env); // fix vraiable
			exec = ft_allocate_list(list);
			ft_open_her_doc(list, exec);
			if (ft_open_files(list, exec) == 0)
			{
				ft_len_node_elem(list, exec);
				ft_copy_to_list(list, exec);
				ft_execution(exec, env, info, data);
				printf("==> %d\n", info.exitstat);

			}
		}
		// ft_print_var(exec);
		// ft_print(*list);
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
