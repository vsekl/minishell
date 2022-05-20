/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:45:54 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:49:20 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"
# include "parser.h"
# include "executor.h"
# include "errors.h"

# define PROMPT_MAIN "minishell>> "
# define PROMPT_ADD_INPUT "> "
# define PROMPT_HEREDOC "heredoc > "
# define PROTOTYPE_HEREDOC ".tmp_heredoc"
# define MESS_SIG_EOF "exit\n"
# define MESS_QUIT "Quit: 3\n"

# define END1 0
# define END2 1

# define ON 0
# define OFF 1

typedef struct s_main
{
	int		fd[3][2];
	int		status;
	char	**envp;
	t_env	*env;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
}				t_main;

t_main	g_data;

char	**new_envp(char **envp);
void	init_shlvl(char ***new_env);
void	init_g_data(void);

void	display_ctrl_c(int display);
void	sigint_handler_main(int signum);
void	sigint_handler_child(int signum);

void	end_program(char *mess, int code, int mode);

void	clear_data_loop(void);
void	clear_g_data(void);
void	free_and_exit(t_pipex pipex, char *error);

int		check_last_pipe(char *input);
void	add_input(void);
int		check_open_quotes(char *input);
int		invalid_tokens(t_token *tokens);
int		invalid_redirects(t_cmd *cmds);
void	unlink_tmp_files(t_cmd *cmds);

int		max(int a, int b);
char	**malloc_two_array_char(int len);
void	free_two_array_char(char **array);
void	add_back_elem_two_array_char(char **array, char *elem, int len);
char	*find_str(char **array, char *str);
int		size_two_array_char(char **array);
int		ft_is_num(char *str);
int		ft_wexitstatus(int x);

void	error_mess(char *mess, int code);
int		warning(char *mess, int code);

#endif