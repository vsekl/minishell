/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:23 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:24:24 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_error_mess(char *name)
{
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

static int	check_valid_unset(char **args)
{
	int	i;
	int	flag_error;

	flag_error = 0;
	i = 1;
	while (args && args[i])
	{
		if (!check_valid_name_var(args[i]))
		{
			unset_error_mess(args[i]);
			flag_error = 1;
		}
		i++;
	}
	return (flag_error);
}

void	delete_var_env(t_env **env, t_env *del)
{
	t_env	*tmp1;

	if (*env == del)
		*env = del->next;
	else
	{
		tmp1 = *env;
		while (tmp1 && tmp1->next != del)
			tmp1 = tmp1->next;
		tmp1->next = del->next;
	}
	free (del->key);
	free (del->value);
	free (del->str);
	free (del);
}

void	execute_unset(t_env **env, char **args)
{
	int		i;
	int		flag_error;
	t_env	*del;

	if (!args[1])
		flag_error = 0;
	else
	{
		flag_error = check_valid_unset(args);
		i = 1;
		while (args && args[i])
		{
			del = find_elem_env(env, args[i]);
			if (check_valid_name_var(args[i]) && del)
				delete_var_env(env, del);
			i++;
		}
	}
	g_data.status = 0 + flag_error;
}
