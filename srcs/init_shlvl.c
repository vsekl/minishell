/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:01:39 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:37:09 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_shlvl_default(char **env)
{
	*env = ft_strdup("SHLVL=1");
	if (!(*env))
		end_program(ERROR_SHLVL, 1, END1);
}

static void	set_shlvl_num_positive(char **env, int num)
{
	char	*shlvl;

	if (num >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(num, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
		set_shlvl_default(env);
	}
	else if (num == 999)
	{
		*env = ft_strdup("SHLVL=");
		if (!(*env))
			end_program(ERROR_SHLVL, 1, END1);
	}
	else
	{
		shlvl = ft_itoa(num + 1);
		if (!shlvl)
			end_program(ERROR_SHLVL, 1, END1);
		*env = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
		if (!(*env))
			end_program(ERROR_SHLVL, 1, END1);
	}
}

static void	set_shlvl_num(char **env, char *value)
{
	int	num;

	num = ft_atoi(value);
	if (num >= -1)
		set_shlvl_num_positive(env, num);
	else
	{
		*env = ft_strdup("SHLVL=0");
		if (!(*env))
			end_program(ERROR_SHLVL, 1, END1);
	}
}

static void	set_shlvl_empty(char ***env)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	len = i;
	new_env = malloc_two_array_char(len + 1);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
			end_program(ERROR_SHLVL, 1, END1);
		i++;
	}
	new_env[i] = ft_strdup("SHLVL=1");
	if (!(new_env[i]))
		end_program(ERROR_SHLVL, 1, END1);
	free_two_array_char(*env);
	*env = new_env;
}

void	init_shlvl(char ***new_env)
{
	char	*value;
	char	**env;

	env = *new_env;
	while (*env)
	{
		if (!ft_strncmp(*env, "SHLVL", 5))
		{
			value = ft_substr(*env, 6, ft_strlen(*env) - 6);
			if (!value)
				end_program(ERROR_SHLVL, 1, END1);
			free(*env);
			if (ft_is_num(value))
				set_shlvl_num(env, value);
			else
				set_shlvl_default(env);
			free(value);
			return ;
		}
		env++;
	}
	set_shlvl_empty(new_env);
}
