/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:45:45 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:53:48 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# define BUILTIN_ECHO 1
# define BUILTIN_PWD 2
# define BUILTIN_ENV 3
# define BUILTIN_UNSET 4
# define BUILTIN_EXPORT 5
# define BUILTIN_EXIT 6
# define BUILTIN_CD 7

typedef struct s_pipex
{
	int		i;
	int		num;
	int		used_pipes;
	int		pipes[2][2];
	pid_t	*pid;
}				t_pipex;

void	executor(t_cmd *cmds);
void	handling_heredoc(t_cmd *cmds);
void	child_process(t_pipex *pipex, t_cmd *cmd);
void	redirect_input(t_pipex *pipex, t_cmd *cmd);
void	redirect_output(t_pipex *pipex, t_cmd *cmd);

int		define_builtin(t_cmd *cmd);

void	execute_echo(t_cmd *cmd);
void	execute_pwd(void);
void	execute_env(void);
void	execute_unset(t_env **env, char **args);
void	execute_export(char **envp, t_env *env, char **args);
void	execute_cd(char **args, int flag);
void	execute_exit(t_cmd *cmd, int flag);

void	save_update_envp(void);
void	get_update_envp(void);

int		execute_binary(t_cmd *cmd);

#endif