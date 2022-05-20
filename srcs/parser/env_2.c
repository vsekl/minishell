/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:19:58 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:21:22 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*last_elem_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_elem_env(t_env **env, t_env *new)
{
	if (new)
	{
		if (!*env)
			*env = new;
		else
			last_elem_env(*env)->next = new;
	}
}

t_env	*list_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		new = new_elem_env(envp[i]);
		if (!new)
		{
			free_list_env(env);
			end_program(ERROR_INIT_LIST_ENV, 1, END1);
		}
		add_elem_env(&env, new);
		i++;
	}
	return (env);
}

t_env	*free_list_env(t_env *env)
{
	t_env	*tmp;
	t_env	*del;

	del = env;
	while (del)
	{
		tmp = del->next;
		if (del->key)
			free (del->key);
		if (del->value)
			free (del->value);
		if (del->str)
			free (del->str);
		free(del);
		del = tmp;
	}
	return (NULL);
}
