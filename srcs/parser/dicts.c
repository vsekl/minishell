/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dicts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:19:53 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:20:47 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dict	*new_dict(int key, t_token *token)
{
	t_dict	*new;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		end_program(ERROR_INIT_DICT, 1, END1);
	new->key = key;
	if (token && token->type != PIPE)
	{
		new->value = ft_strdup(token->content);
		if (!new->value)
		{
			free (new);
			end_program(ERROR_INIT_DICT, 1, END1);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_dict	*last_dict(t_dict *dict)
{
	t_dict	*tmp;

	tmp = dict;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_dict(t_dict **dict, t_dict *new)
{
	if (new)
	{
		if (!*dict)
			*dict = new;
		else
			last_dict(*dict)->next = new;
	}
}

t_dict	*free_dict(t_dict *dict)
{
	t_dict	*tmp;
	t_dict	*del;

	del = dict;
	if (del)
	{
		while (del)
		{
			tmp = del->next;
			if (del->value)
				free (del->value);
			free (del);
			del = tmp;
		}
	}
	return (NULL);
}
