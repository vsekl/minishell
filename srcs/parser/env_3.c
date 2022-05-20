/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:20:02 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:20:03 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_list_env(t_env **env)
{
	t_env	*tmp;
	int		i;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	swap_list_env(t_env *env1, t_env *env2)
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_str;

	tmp_key = env1->key;
	tmp_value = env1->value;
	tmp_str = env1->str;
	env1->key = env2->key;
	env1->value = env2->value;
	env1->str = env2->str;
	env2->key = tmp_key;
	env2->value = tmp_value;
	env2->str = tmp_str;
}

void	sort_list_env(t_env **env)
{
	t_env	*tmp;
	int		i;
	int		j;
	int		k;

	tmp = *env;
	i = 0;
	j = len_list_env(&tmp);
	while (i < j - 1)
	{
		k = 0;
		tmp = *env;
		while (k < j - i - 1)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
				swap_list_env(tmp, tmp->next);
			k++;
			tmp = tmp->next;
		}
		i++;
	}
}

int	check_valid_name_var(char *name)
{
	int	i;

	if (name && ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name && name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_elem_env(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
