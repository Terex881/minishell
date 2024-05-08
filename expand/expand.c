/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:09:35 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/08 18:09:40 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/signal.h>

void	ft_expand_var(t_list **list, char *str, int *g_stat)
{
	t_list	*tmp;
	tmp = *list;
	if (tmp && tmp->value && !ft_strncmp(tmp->value, "$?", 2))
	{
		tmp->value = ft_strjoin(ft_itoa(*g_stat), ft_substr(tmp->value, 2, ft_strlen(tmp->value) - 2));
	}
	if (str && !ft_strncmp(str, "$?", 2) && tmp->type == D_Q)
	{
		tmp->value = ft_strjoin(ft_substr(tmp->value, 0, str - tmp->value), ft_itoa(*g_stat));
		tmp->value = ft_strjoin(tmp->value, ft_substr(str, 2, ft_strlen(str) - 2));
	}
}

void	ft_expand_val(t_list **list, t_list **old_tmp, t_data *data, char *str, int *g_stat)
{
	t_list	*tmp;

	tmp = *list;
	// printf("global is %d\n", global);
	if(global == 12)
		(*g_stat = 1, global = 0);
	if(global == 10)
		(*g_stat = 0, global = 0);
	if (tmp && !ft_strcmp(tmp->value, "$?"))
	{
		tmp->value = ft_itoa(*g_stat);
	}
	else if (tmp && (tmp->type == D_Q || tmp->type == VARIABLE))
	{
		tmp->value = ft_search_var(tmp->value, data);
		if (!tmp->value)
			(*old_tmp)->next = tmp->next;
	}
	else if (tmp && tmp->next && !ft_strcmp(tmp->value, "$") && !ft_type(tmp->next))
		tmp->value = ft_strdup("$");
	else if (tmp && tmp->next && !ft_strcmp(tmp->value, "$"));
	else if (str && *str && *(str + 1) == '0')
		tmp->value = ft_strjoin("minishell", str + 2);
	else if (str && *str && *(str + 1) >= '0' && *(str + 1) <= '9')
		tmp->value = ft_strdup(str + 2);
}

void	ft_expand(t_list **list, t_data *data, int *g_stat)
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
		ft_expand_var(&tmp, str, g_stat);
		ft_expand_val(&tmp, &old_tmp, data, str, g_stat);
		old_tmp = tmp;
		tmp = tmp->next;
	}
}
