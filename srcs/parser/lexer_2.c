/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:20:08 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:21:34 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_outer_quotes(char *src)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(src) - 1);
	if (!dest)
		end_program(ERROR_OPEN_QUOTES, 1, END1);
	ft_strlcpy(dest, src + 1, ft_strlen(src) - 1);
	free (src);
	return (dest);
}

static void	upgrade_token(t_token *token)
{
	t_token	*tmp1;
	t_token	*tmp2;
	char	*new_content;

	tmp1 = token;
	tmp2 = token->next;
	new_content = ft_strjoin(tmp1->content, tmp2->content);
	if (!new_content)
		end_program(ERROR_COMBINE_TOKEN, 1, END1);
	free (tmp1->content);
	tmp1->content = new_content;
	tmp1->next = tmp2->next;
	free (tmp2->content);
	free (tmp2);
}

static void	combine_token(void)
{
	t_token	*tmp;

	tmp = g_data.tokens;
	while (tmp && tmp->next)
	{
		if ((tmp->type == WORD && tmp->next->type == QUOTES) || \
		(tmp->type == WORD && tmp->next->type == DQUOTES) || \
		(tmp->type == WORD && tmp->next->type == WORD) || \
		(tmp->type == QUOTES && tmp->next->type == QUOTES) || \
		(tmp->type == QUOTES && tmp->next->type == DQUOTES) || \
		(tmp->type == QUOTES && tmp->next->type == WORD) || \
		(tmp->type == DQUOTES && tmp->next->type == QUOTES) || \
		(tmp->type == DQUOTES && tmp->next->type == DQUOTES) || \
		(tmp->type == DQUOTES && tmp->next->type == WORD))
		{
			upgrade_token(tmp);
			tmp = g_data.tokens;
		}
		tmp = tmp->next;
	}
}

void	lexer_update_tokens(void)
{
	t_token	*tmp;

	tmp = g_data.tokens;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == DQUOTES)
			open_variable(tmp);
		if (tmp->type == QUOTES || tmp->type == DQUOTES)
		{
			if (tmp->content)
				tmp->content = remove_outer_quotes(tmp->content);
		}
		tmp = tmp->next;
	}
	combine_token();
}
