/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:45:29 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:54:14 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define SEPARATOR 1
# define WORD 2
# define QUOTES 3
# define DQUOTES 4
# define RDR_IN 5
# define RDR_OUT 6
# define RDR_SRC 7
# define RDR_APD 8
# define PIPE 9

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}				t_arg;

typedef struct s_dict
{
	int				key;
	char			*value;
	struct s_dict	*next;
}				t_dict;

typedef struct s_cmd
{
	char			*id;
	char			**args;
	t_arg			*l_arg;
	int				count;
	t_dict			*infd;
	t_dict			*outfd;
	char			*tmpname;
	struct s_cmd	*next;
}				t_cmd;

char	*get_key(char *key, char *str);
char	*get_value(char *value, char *str);
t_env	*parsing_str_var_env(t_env *env, char *str);
t_env	*new_elem_env(char *str);
t_env	*free_elem_env(t_env *env);

t_env	*last_elem_env(t_env *env);
void	add_elem_env(t_env **env, t_env *new);
t_env	*list_env(char **envp);
t_env	*free_list_env(t_env *env);

int		len_list_env(t_env **env);
void	swap_list_env(t_env *env1, t_env *env2);
void	sort_list_env(t_env **env);
int		check_valid_name_var(char *name);
t_env	*find_elem_env(t_env **env, char *key);

void	lexer(void);
void	lexer_update_tokens(void);
void	open_variable(t_token *token);

t_token	*new_token(char *str, int type, int *index);
void	add_token(t_token **tokens, t_token *new);
void	free_tokens(void);

t_arg	*new_arg(char *content);
void	add_back_list_arg(t_arg **args, t_arg *new);
t_arg	*free_list_arg(t_arg *args);

void	parser(void);
void	init_id_cmd(void);

t_cmd	*new_cmd(void);
t_cmd	*last_cmd(t_cmd *cmds);
void	add_cmd(t_cmd **cmds, t_cmd *new);
void	free_cmd(void);

t_dict	*new_dict(int key, t_token *token);
t_dict	*last_dict(t_dict *dict);
void	add_dict(t_dict **dict, t_dict *new);
t_dict	*free_dict(t_dict *dict);
int		count_cmds(t_cmd *cmds);

#endif