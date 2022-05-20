/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:09 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:24:10 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*heredoc(char *stop)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*input;

	input = NULL;
	tmp1 = readline(PROMPT_HEREDOC);
	while (ft_strncmp(tmp1, stop, ft_strlen(stop)))
	{
		tmp2 = ft_strjoin(tmp1, "\n");
		if (input)
		{
			tmp3 = ft_strjoin(input, tmp2);
			free (input);
			input = ft_strdup(tmp3);
			free (tmp3);
		}
		else
			input = ft_strdup(tmp2);
		free (tmp2);
		free (tmp1);
		tmp1 = readline(PROMPT_HEREDOC);
	}
	free (tmp1);
	return (input);
}

static void	create_tmp_file(char *stop, t_cmd *cmd)
{
	char	*input;
	int		fd;

	input = heredoc(stop);
	cmd->tmpname = ft_strjoin(PROTOTYPE_HEREDOC, cmd->id);
	if (!cmd->tmpname)
	{
		free (input);
		end_program(ERROR_CREATE_HEREDOC, 1, END1);
	}
	fd = open(cmd->tmpname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free (input);
		end_program(ERROR_CREATE_HEREDOC, errno, END2);
	}
	write(fd, input, ft_strlen(input));
	close(fd);
	free (input);
}

void	handling_heredoc(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	t_dict	*tmp_dict;

	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		tmp_dict = tmp_cmd->infd;
		while (tmp_dict)
		{
			if (tmp_dict->key == RDR_SRC)
				create_tmp_file(tmp_dict->value, tmp_cmd);
			tmp_dict = tmp_dict->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
