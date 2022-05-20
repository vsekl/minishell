/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:20 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:18:41 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_find_next_arg(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg->next;
	while (tmp)
	{
		if (tmp->value)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_echo(t_cmd *cmd)
{
	t_arg	*tmp;

	g_data.status = 0;
	if (!cmd->l_arg->next)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	tmp = cmd->l_arg->next;
	while (tmp && tmp->value && *tmp->value && !ft_strcmp(tmp->value, "-n"))
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			if (echo_find_next_arg(tmp))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	if (cmd->l_arg->next && cmd->l_arg->next->value && \
	ft_strcmp(cmd->l_arg->next->value, "-n"))
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		end_program("Error: malloc in pwd\n", 1, END1);
	ft_putstr_fd(path, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free (path);
	g_data.status = 0;
}

void	execute_env(void)
{
	int	i;

	i = 0;
	while (g_data.envp && g_data.envp[i])
	{
		ft_putstr_fd(g_data.envp[i++], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_data.status = 0;
}

void	execute_exit(t_cmd *cmd, int flag)
{
	if (!flag)
	{
		g_data.status = 0;
		return ;
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->args[1])
	{
		if (!ft_is_num(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			end_program(NULL, 255, END1);
		}
		else if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_data.status = 1;
			return ;
		}
		end_program(NULL, ft_atoi(cmd->args[1]), END1);
	}
	end_program(NULL, g_data.status, END1);
}
