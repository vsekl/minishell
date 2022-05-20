/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:20:21 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:23:23 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *str, int type, int *index)
{
	t_token	*token;

	if (!str)
		end_program(ERROR_INIT_TOKEN, 1, END1);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		free (str);
		end_program(ERROR_INIT_TOKEN, 1, END2);
	}
	token->content = str;
	token->type = type;
	token->next = NULL;
	*index = *index + ft_strlen(str) - 1;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (new)
	{
		tmp = *tokens;
		if (!tmp)
			*tokens = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

void	free_tokens(void)
{
	t_token	*tmp;
	t_token	*del;

	del = g_data.tokens;
	while (del)
	{
		tmp = del->next;
		free (del->content);
		free (del);
		del = tmp;
	}
	g_data.tokens = NULL;
}
