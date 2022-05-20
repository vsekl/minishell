/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:19:56 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:21:09 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *key, char *str)
{
	int		i;

	if (str && str[0] == '=')
	{
		free (key);
		return (NULL);
	}
	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	ft_strlcpy(key, str, i + 1);
	return (key);
}

char	*get_value(char *value, char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (!str[i])
	{
		free (value);
		return (NULL);
	}
	if (str[i] == '=')
		i++;
	ft_strlcpy(value, str + i, ft_strlen(str + i) + 1);
	return (value);
}

t_env	*parsing_str_var_env(t_env *env, char *str)
{
	env->key = get_key(env->key, str);
	env->value = get_value(env->value, str);
	ft_strlcpy(env->str, str, ft_strlen(str) + 1);
	return (env);
}

t_env	*new_elem_env(char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	new->value = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	new->str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new->key || !new->value || !new->str)
		return (free_elem_env(new));
	new = parsing_str_var_env(new, str);
	new->next = NULL;
	return (new);
}

t_env	*free_elem_env(t_env *env)
{
	if (env)
	{
		if (env->key)
			free (env->key);
		if (env->value)
			free (env->value);
		if (env->str)
			free (env->str);
		free (env);
	}
	return (NULL);
}
