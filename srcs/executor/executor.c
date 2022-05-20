/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:01 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:45:37 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pipex(t_pipex *pipex, t_cmd *cmds)
{
	pipex->i = 0;
	pipex->num = count_cmds(cmds);
	pipex->used_pipes = 0;
	pipex->pipes[0][0] = -1;
	pipex->pipes[0][1] = -1;
	pipex->pipes[1][0] = -1;
	pipex->pipes[1][1] = -1;
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->num);
	if (!pipex->pid)
		end_program("Error: malloc in init pipex\n", 1, END1);
}

static void	wait_child_process(t_pipex pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex.num)
	{
		waitpid(pipex.pid[i], &status, 0);
		i++;
	}
	g_data.status = ft_wexitstatus(status);
}

static void	execute_cd_exit(t_cmd *cmd, int index)
{
	int	flag_execute;

	if (count_cmds(cmd) == 1 && !index)
		flag_execute = 1;
	else
		flag_execute = 0;
	if (*cmd->args && !ft_strcmp(cmd->args[0], "exit"))
		execute_exit(cmd, flag_execute);
	if (*cmd->args && !ft_strcmp(cmd->args[0], "cd"))
		execute_cd(cmd->args, flag_execute);
}

static void	kernel_executor(t_pipex pipex, t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (pipex.i < pipex.num)
	{
		execute_cd_exit(cmd, pipex.i);
		if (pipe(pipex.pipes[pipex.used_pipes]) < 0)
			free_and_exit(pipex, ERROR_INIT_PIPE_EXECUTOR);
		pipex.pid[pipex.i] = fork();
		if (pipex.pid[pipex.i] < 0)
			free_and_exit(pipex, ERROR_FORK);
		if (!pipex.pid[pipex.i])
			child_process(&pipex, cmd);
		close(pipex.pipes[1 - pipex.used_pipes][0]);
		close(pipex.pipes[pipex.used_pipes][1]);
		if (pipex.i == pipex.num - 1 && define_builtin(cmd))
			get_update_envp();
		pipex.used_pipes = 1 - pipex.used_pipes;
		pipex.i++;
		cmd = cmd->next;
	}
}

void	executor(t_cmd *cmds)
{
	t_pipex	pipex;

	init_pipex(&pipex, cmds);
	handling_heredoc(cmds);
	kernel_executor(pipex, cmds);
	wait_child_process(pipex);
	free (pipex.pid);
	unlink_tmp_files(cmds);
}
