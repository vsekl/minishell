/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:18 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:41:05 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	define_input_output(t_pipex *pipex, t_cmd *cmd)
{
	if (!cmd->infd && pipex->i > 0)
	{
		dup2(pipex->pipes[1 - pipex->used_pipes][0], STDIN_FILENO);
		close(pipex->pipes[1 - pipex->used_pipes][0]);
	}
	else
		redirect_input(pipex, cmd);
	if (!cmd->outfd && pipex->i < pipex->num - 1)
	{
		dup2(pipex->pipes[pipex->used_pipes][1], STDOUT_FILENO);
		close(pipex->pipes[pipex->used_pipes][0]);
		close(pipex->pipes[pipex->used_pipes][1]);
	}
	else
		redirect_output(pipex, cmd);
}

static void	execute_builtin(t_cmd *cmd, int type_builtin)
{
	if (type_builtin == BUILTIN_ECHO)
		execute_echo(cmd);
	else if (type_builtin == BUILTIN_PWD)
		execute_pwd();
	else if (type_builtin == BUILTIN_ENV)
		execute_env();
	else if (type_builtin == BUILTIN_UNSET)
		execute_unset(&g_data.env, cmd->args);
	else if (type_builtin == BUILTIN_EXPORT)
		execute_export(g_data.envp, g_data.env, cmd->args);
}

static int	ft_strcmp_lower_case(char const *str1, char const *str2)
{
	char	chr;
	size_t	i;

	i = 0;
	while (i < ft_strlen(str1) || i < ft_strlen(str2))
	{
		chr = str1[i];
		if (chr >= 'A' && chr <= 'Z')
			chr = chr + 32;
		if (chr != str2[i] || !str1[i] || !str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	define_builtin(t_cmd *cmd)
{
	if (cmd->args && cmd->args[0])
	{
		if (!ft_strcmp_lower_case(cmd->args[0], "echo"))
			return (BUILTIN_ECHO);
		else if (!ft_strcmp_lower_case(cmd->args[0], "pwd"))
			return (BUILTIN_PWD);
		else if (!ft_strcmp_lower_case(cmd->args[0], "env"))
			return (BUILTIN_ENV);
		else if (!ft_strcmp(cmd->args[0], "unset"))
			return (BUILTIN_UNSET);
		else if (!ft_strcmp(cmd->args[0], "export"))
			return (BUILTIN_EXPORT);
		else if (!ft_strcmp(cmd->args[0], "exit"))
			return (BUILTIN_EXIT);
		else if (!ft_strcmp_lower_case(cmd->args[0], "cd"))
			return (BUILTIN_CD);
	}
	return (0);
}

void	child_process(t_pipex *pipex, t_cmd *cmd)
{
	int	type_builtin;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
	define_input_output(pipex, cmd);
	type_builtin = define_builtin(cmd);
	if (type_builtin)
		execute_builtin(cmd, type_builtin);
	else
	{
		if (cmd->args && cmd->args[0])
			execute_binary(cmd);
	}
	if (pipex->i == pipex->num - 1 && define_builtin(cmd))
		save_update_envp();
	close(pipex->pipes[1 - pipex->used_pipes][0]);
	close(pipex->pipes[pipex->used_pipes][1]);
	exit (g_data.status);
}
