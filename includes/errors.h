/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:45:51 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:00:14 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERROR_NUM_ARGS "Error: num args in input minishell\n"
# define ERROR_MALLOC_ENVP "Error: malloc in envp\n"
# define ERROR_SHLVL "Error: amlloc in init SHLVL\n"
# define ERROR_INIT_LIST_ENV "Error: init list env\n"
# define ERROR_G_PIPE "g_data.pipe"
# define ERROR_READLINE "Error: readline\n"
# define ERROR_ADD_INPUT "minishell: syntax error: unexpected end of file\nexit\n"
# define ERROR_SYNTAX_OPEN_QUOTES "minishell: syntax error: open quotes\n"

# define ERROR_INIT_TOKEN "Error: init token\n"
# define ERROR_OPEN_VAR "Error: open variable\n"
# define ERROR_OPEN_QUOTES "Error: malloc in open quotes\n"
# define ERROR_COMBINE_TOKEN "Error: malloc in combine token\n"

# define ERROR_SYNTAX_FIRST_PIPE "minishell: syntax error near \
unexpected token `|'\n"
# define ERROR_SYNTAX_DOUBLE_PIPE "minishell: syntax error near \
unexpected token `||'\n"
# define ERROR_SYNTAX_DOUBLE_PIPE_SEP "minishell: syntax error near \
unexpected token `|'\n"

# define ERROR_MALLOC_CMD "Error: malloc cmd\n"
# define ERROR_ADD_ELEM_TWO_ARR "Error: malloc in add elem two arr\n"
# define ERROR_INIT_LIST_ARG "Error: malloc list arg in init cmd\n"
# define ERROR_INIT_DICT "Error: init dict\n"
# define ERROR_INIT_ID_CMD "Error: malloc id cmd\n"

# define ERROR_SYNTAX_NO_REDIRECT "minishell: syntax error near \
unexpected token `newline'\n"
# define ERROR_SYNTAX_INVALID_REDIRECT_1 "minishell: syntax error near \
unexpected token `"
# define ERROR_SYNTAX_INVALID_REDIRECT_2 "'\n"

# define ERROR_CREATE_HEREDOC "heredoc tmpfile"
# define ERROR_INIT_PIPE_EXECUTOR "pipex.pipe"
# define ERROR_FORK "pipex.fork"
# define ERROR_FORK_BIN "Error: fork in execute binary\n"

# define ERROR_EXEC_BIN_INIT "Error: malloc in execute binaty cmd\n"
# define ERROR_PARS_ENVP_PATH "Error: parsing ENVP PATH\n"
# define ERROR_NO_BINARY_FILE "Error: binary file not exist\n"

#endif