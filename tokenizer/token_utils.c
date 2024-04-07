/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:14:18 by sdemnati          #+#    #+#             */
/*   Updated: 2024/04/07 01:17:28 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_skip_space(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (tmp && tmp->next && tmp->next->type == SPACE_
		&& tmp->next->next == NULL)
	{
		tmp->next = NULL;
	}
}

char	**ft_cpy_to_2d(t_env *tmp)
{
	char	**ret;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize_env(tmp);
	ret = c_malloc(sizeof(char *) * (len + 1), 1);
	if (!ret)
		return (NULL);
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
