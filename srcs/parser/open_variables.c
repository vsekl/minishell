/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:20:14 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:22:29 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_value_variable(char *src, int len, t_env *env)
{
	t_env	*tmp;
	char	*var;

	var = (char *)malloc(sizeof(char) * (len + 1));
	if (!var)
		end_program(ERROR_OPEN_VAR, 1, END1);
	ft_strlcpy(var, src, len + 1);
	tmp = find_elem_env(&env, var);
	if (tmp)
	{
		free (var);
		var = ft_strdup(tmp->value);
		if (!var)
			end_program(ERROR_OPEN_VAR, 1, END1);
		return (var);
	}
	if (!ft_strcmp(var, "?"))
	{
		free (var);
		return (ft_itoa(g_data.status));
	}
	free(var);
	return (NULL);
}

static void	replace_variable(t_token *token, char *variable, \
int *i, int len_name_var)
{
	char	*old;
	char	*new;
	int		start;
	int		len_value_var;

	old = token->content;
	start = *i - len_name_var - 1;
	len_value_var = ft_strlen(variable);
	new = (char *)malloc(sizeof(char) * (ft_strlen(old) + len_value_var));
	if (!new)
	{
		free (variable);
		end_program(ERROR_OPEN_VAR, 1, END1);
	}
	ft_strlcpy(new, old, start + 1);
	if (variable)
		ft_strlcpy(new + start, variable, len_value_var + 1);
	ft_strlcpy(new + start + len_value_var, old + start + len_name_var + 1, \
	ft_strlen(old + start + len_name_var) + 1);
	free (token->content);
	token->content = ft_strdup(new);
	if (!token->content)
		end_program(ERROR_OPEN_VAR, 1, END1);
	(*i) = start;
	free (new);
}

static int	allocate_variable(char *content, int *i)
{
	int	len;

	len = 0;
	if (content[*i] == '?' || ft_isdigit(content[*i]))
	{
		len++;
		(*i)++;
	}
	else
	{
		while (content[*i] && (ft_isalnum(content[*i]) || content[*i] == '_'))
		{
			len++;
			(*i)++;
		}
	}
	return (len);
}

static void	insert_variable(t_token *token, char *content, int *i, t_env *env)
{
	char	*variable;
	int		len;

	(*i)++;
	len = allocate_variable(content, i);
	if (!len)
		return ;
	variable = get_value_variable(content + *i - len, len, env);
	if (!variable)
	{
		if (token->type == DQUOTES && (int)ft_strlen(token->content) - 3 == len)
		{
			free (token->content);
			token->content = NULL;
			return ;
		}
		if (token->type == WORD && (int)ft_strlen(token->content) - 1 == len)
		{
			free (token->content);
			token->content = NULL;
			return ;
		}
	}
	replace_variable(token, variable, i, len);
	free (variable);
}

void	open_variable(t_token *token)
{
	char	*content;
	int		i;
	int		dquotes;
	int		quotes;

	content = token->content;
	i = 0;
	dquotes = 0;
	quotes = 0;
	while (content && content[i])
	{
		if (content[i] == '"' && quotes % 2 == 0)
			dquotes++;
		if (content[i] == '\'')
			quotes++;
		if ((quotes % 2 == 0 || dquotes % 2 == 1) && content[i] == '$')
		{
			insert_variable(token, content, &i, g_data.env);
			content = token->content;
		}
		else
			i++;
	}
}
