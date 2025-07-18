/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:09:35 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/12 21:44:40 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_var(t_list **list, char *str)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp && tmp->value && !ft_strncmp(tmp->value, "$?", 2))
	{
		tmp->value = ft_strjoin(ft_itoa(exit_status(0, 0)),
				ft_substr(tmp->value, 2, ft_strlen(tmp->value) - 2));
	}
	if (str && !ft_strncmp(str, "$?", 2) && tmp->type == D_Q)
	{
		tmp->value = ft_strjoin(ft_substr(tmp->value, 0, str - tmp->value),
				ft_itoa(exit_status(0, 0)));
		tmp->value = ft_strjoin(tmp->value,
				ft_substr(str, 2, ft_strlen(str) - 2));
	}
}

void	ft_expand_val(t_list **list, t_list **old_tmp, t_data *data, char *str)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp && !ft_strcmp(tmp->value, "$?"))
	{
		tmp->value = ft_itoa(exit_status(0, 0));
	}
	else if (tmp && (tmp->type == D_Q || tmp->type == VARIABLE))
	{
		tmp->value = ft_search_var(tmp->value, data);
		if (!tmp->value)
			(*old_tmp)->next = tmp->next;
	}
	else if (tmp && tmp->next && !ft_strcmp(tmp->value, "$")
		&& !ft_type(tmp->next))
		tmp->value = ft_strdup("$");
	else if (str && *str && *(str + 1) == '0')
		tmp->value = ft_strjoin("minishell", str + 2);
	else if (str && *str && *(str + 1) >= '0' && *(str + 1) <= '9')
		tmp->value = ft_strdup(str + 2);
}

void	ft_expand(t_list **list, t_data *data)
{
	t_list	*tmp;
	t_list	*old_tmp;
	char	*str;

	tmp = *list;
	old_tmp = tmp;
	while (tmp)
	{
		str = ft_strchr(tmp->value, '$');
		if (tmp->type == HER_DOC)
		{
			tmp = ft_next(tmp->next);
			tmp = tmp->next;
			continue ;
		}
		ft_expand_var(&tmp, str);
		ft_expand_val(&tmp, &old_tmp, data, str);
		old_tmp = tmp;
		tmp = tmp->next;
	}
}
