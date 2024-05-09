/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:49:34 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/09 14:42:28 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_add_special_character(t_list *node, char *c, int *i)
{
	node = ft_lstnew(c);
	if (!node)
		return (NULL);
	if (*c == 32 || (*c >= 9 && *c <= 32))
		(1) && (node->type = SPACE_, node->value = NULL);
	else if (*c == '>' && *(c + 1) == '>')
		(1) && (node->type = APPEND, node->value = NULL, (*i)++);
	else if (*c == '<' && *(c + 1) == '<')
		(1) && (node->type = HER_DOC, node->value = NULL, (*i)++);
	else if (*c == '>')
		(1) && (node->type = R_OUT, node->value = NULL);
	else if (*c == '<')
		(1) && (node->type = R_IN, node->value = NULL);
	else if (*c == '|')
		(1) && (node->type = PIPE, node->value = NULL);
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
		return (NULL);
	str = tmp;
	tmp = ft_strtrim(tmp, line[j]);
	node = ft_lstnew(tmp);
	if ((line[j] == '\"' || line[j] == '\'') && line[*i] == '\0')
		return (ft_putstr_fd("syntax error\n", 2), exit_status(258, 1), NULL);
	if (line[j] == '\"')
		node->type = D_Q;
	else if (line[j] == '\'')
		node->type = S_Q;
	return (node);
}

t_list	*ft_add_var(char *line, int *i, t_list *node)
{
	int		j;
	char	*tmp;

	j = *i;
	while (line[*i + 1] && ft_isalpha(line[*i + 1]) != 0)
		(*i)++;
	tmp = ft_substr(line, j, (*i - j) + 1);
	if (!tmp)
		return (NULL);
	node = ft_lstnew(tmp);
	if ((line[j]) == '$' && ft_isalpha(line[j + 1]) == 1)
		node->type = VARIABLE;
	else if ((line[j]) == '$' && line[j + 1] == '?')
		node->type = VARIABLE;
	else
		node->type = WORD;
	return (node);
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
	node->type = WORD;
	return (node);
}

int	ft_token(char *line, t_list *node, t_list **list)
{
	int	i;

	node = NULL;
	*list = NULL;
	i = 0;
	line = readline("minishell: ");
	if (line == NULL)
		return (0);
	if (line[i])
		add_history(line);
	while (line && line[i])
	{
		if (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
			while (line[i + 1] && (line[i + 1] == 32
					|| (line[i + 1] >= 9 && line[i + 1] <= 13)))
				i++;
		if (line[i] && ft_check(line[i]) == 1)
			node = ft_add_special_character(node, &line[i], &i);
		else if (line[i])
			node = ft_add_word(line, &i, node);
		if (!node)
			return (free(line), -1);
		(ft_lstadd_back(list, node), i++);
	}
	return (free(line), 1);
}
