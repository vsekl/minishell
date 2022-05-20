/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:49:31 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:51:21 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_last_pipe(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0)
	{
		if (input[i] == ' ' || input[i] == '\t')
			i--;
		else if (input[i] == '|')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	add_input(void)
{
	char	*new_input;
	char	*line;

	line = readline(PROMPT_ADD_INPUT);
	if (!line)
		end_program(ERROR_ADD_INPUT, 2, END1);
	new_input = ft_strjoin(g_data.input, line);
	if (!new_input)
	{
		free (line);
		end_program(ERROR_READLINE, 1, END1);
	}
	free (g_data.input);
	g_data.input = new_input;
}

int	check_open_quotes(char *input)
{
	int		i;
	char	quote;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i])
			{
				if (input[i] == quote)
					break ;
				i++;
			}
			if (!g_data.input[i])
				return (warning(ERROR_SYNTAX_OPEN_QUOTES, 1));
		}
	}
	return (0);
}

int	invalid_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (tokens->type == SEPARATOR && tokens->next == NULL)
		return (1);
	if (tokens->type == PIPE || \
	(tokens->type == SEPARATOR && tokens->next->type == PIPE))
		return (warning(ERROR_SYNTAX_FIRST_PIPE, 1));
	tmp = tokens;
	while (tmp)
	{
		if ((tmp->next) && \
		(tmp->type == PIPE && tmp->next->type == PIPE))
			return (warning(ERROR_SYNTAX_DOUBLE_PIPE, 1));
		else if ((tmp && tmp->next && tmp->next->next) && \
		(tmp->type == PIPE && tmp->next->type == SEPARATOR && \
		tmp->next->next->type == PIPE))
			return (warning(ERROR_SYNTAX_DOUBLE_PIPE_SEP, 1));
		tmp = tmp->next;
	}
	return (0);
}
