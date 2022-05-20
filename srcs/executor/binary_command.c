/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:35 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:48:25 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*enviroment_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			end_program(ERROR_EXEC_BIN_INIT, 1, END1);
		path_cmd = ft_strjoin(tmp, cmd);
		if (!path_cmd)
		{
			free (tmp);
			end_program(ERROR_EXEC_BIN_INIT, 1, END1);
		}
		free (tmp);
		if (!access(path_cmd, X_OK))
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

static char	*search_paths(char **paths, char *cmd)
{
	char	*path;

	if (*cmd && (!ft_strncmp(cmd, "./", 2) || cmd[0] == '/'))
	{
		if (!access(cmd, X_OK))
		{
			path = ft_strdup(cmd);
			if (!path)
				end_program(ERROR_EXEC_BIN_INIT, 1, END1);
			return (path);
		}
	}
	path = enviroment_path(paths, cmd);
	return (path);
}

static int	parsing_paths(char ***paths, char **envp)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = find_str(envp, "PATH=");
	if (!tmp1)
		return (1);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		return (2);
	*paths = ft_split(tmp2, ':');
	if (!*paths)
	{
		free(tmp2);
		return (2);
	}
	free (tmp2);
	return (0);
}

static void	child_process_binary(t_cmd *cmd, char **envp)
{
	char	**paths_envp;
	char	*path_cmd;
	int		res;

	res = parsing_paths(&paths_envp, envp);
	if (res == 1)
		exit(warning(ERROR_NO_BINARY_FILE, EXIT_FAILURE));
	else if (res == 2)
		exit(warning(ERROR_PARS_ENVP_PATH, EXIT_FAILURE));
	if (!cmd->args[0])
		exit(warning(ERROR_NO_BINARY_FILE, 127));
	path_cmd = search_paths(paths_envp, cmd->args[0]);
	if (!path_cmd)
	{
		free_two_array_char(paths_envp);
		exit(warning(ERROR_NO_BINARY_FILE, 127));
	}
	execve(path_cmd, cmd->args, g_data.envp);
	free_two_array_char(paths_envp);
	free (path_cmd);
	error_mess("execve", errno);
}

int	execute_binary(t_cmd *cmd)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (warning(ERROR_FORK_BIN, 1));
	if (!child)
		child_process_binary(cmd, g_data.envp);
	else
		waitpid(child, &g_data.status, 0);
	g_data.status = ft_wexitstatus(g_data.status);
	return (0);
}
