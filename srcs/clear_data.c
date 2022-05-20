/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:49:18 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:29:35 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_program(char *mess, int code, int mode)
{
	clear_g_data();
	if (mode == END1 && mess)
		ft_putstr_fd(mess, STDERR_FILENO);
	else if (mode == END2)
		perror(mess);
	exit (code);
}

void	clear_data_loop(void)
{
	if (g_data.env)
		free_list_env(g_data.env);
	if (g_data.input)
		free (g_data.input);
	if (g_data.tokens)
		free_tokens();
	if (g_data.cmds)
		free_cmd();
	close(g_data.fd[0][0]);
	close(g_data.fd[0][1]);
	close(g_data.fd[1][0]);
	close(g_data.fd[1][1]);
	close(g_data.fd[2][0]);
	close(g_data.fd[2][1]);
}

void	clear_g_data(void)
{
	if (g_data.envp)
		free_two_array_char(g_data.envp);
	if (g_data.env)
		g_data.env = free_list_env(g_data.env);
	if (g_data.input)
		free (g_data.input);
	if (g_data.tokens)
		free_tokens();
	if (g_data.cmds)
		free_cmd();
	close(g_data.fd[0][0]);
	close(g_data.fd[0][1]);
	close(g_data.fd[1][0]);
	close(g_data.fd[1][1]);
	close(g_data.fd[2][0]);
	close(g_data.fd[2][1]);
}

void	free_and_exit(t_pipex pipex, char *error)
{
	free (pipex.pid);
	end_program(error, errno, END2);
}
