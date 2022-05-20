/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:25 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:24:26 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_error_mess(char *name)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

static void	export_no_args(char **envp)
{
	t_env	*tmp;
	t_env	*begin;

	tmp = list_env(envp);
	sort_list_env(&tmp);
	begin = tmp;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	tmp = free_list_env(begin);
}

static int	check_valid_export(t_env *env)
{
	t_env	*tmp;
	int		flag_error;

	tmp = env;
	flag_error = 0;
	while (tmp)
	{
		if (!tmp->key || !check_valid_name_var(tmp->key))
		{
			export_error_mess(tmp->key);
			flag_error = 1;
		}
		tmp = tmp->next;
	}
	return (flag_error);
}

static void	insert_var_env(t_env *env, t_env *new)
{
	t_env	*tmp;
	t_env	*tmp_new;
	int		update;

	tmp = env;
	update = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, new->key))
		{
			update = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (update)
		swap_list_env(tmp, new);
	else
	{
		tmp_new = new_elem_env(new->str);
		if (!tmp_new)
			end_program("error malloc\n", 1, END1);
		add_elem_env(&env, tmp_new);
	}
}

void	execute_export(char **envp, t_env *env, char **args)
{
	t_env	*tmp;
	int		flag_error;

	flag_error = 0;
	if (!args[1])
		export_no_args(envp);
	else
	{
		tmp = list_env(args + 1);
		flag_error = check_valid_export(tmp);
		while (tmp)
		{
			if (tmp->key && check_valid_name_var(tmp->key) && tmp->value)
				insert_var_env(env, tmp);
			tmp = tmp->next;
		}
		free_list_env(tmp);
	}
	g_data.status = 0 + flag_error;
}
