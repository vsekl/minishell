/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:46:58 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:21:23 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_fd_error(char *str)
{
	ft_putstr_fd(ERROR_SYNTAX_INVALID_REDIRECT_1, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(ERROR_SYNTAX_INVALID_REDIRECT_2, STDERR_FILENO);
	return (0);
}

static int	check_dict(t_dict *dict)
{
	while (dict)
	{
		if (!dict->value)
		{
			ft_putstr_fd(ERROR_SYNTAX_NO_REDIRECT, STDERR_FILENO);
			return (0);
		}
		if (!ft_strcmp(dict->value, "<<"))
			return (print_fd_error("<<"));
		if (!ft_strcmp(dict->value, ">>"))
			return (print_fd_error(">>"));
		if (!ft_strcmp(dict->value, "<"))
			return (print_fd_error("<"));
		if (!ft_strcmp(dict->value, ">"))
			return (print_fd_error(">"));
		if (!ft_strcmp(dict->value, "|"))
			return (print_fd_error("|"));
		dict = dict->next;
	}
	return (1);
}

int	invalid_redirects(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (!check_dict(tmp->infd) || !check_dict(tmp->outfd))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	unlink_tmp_files(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->tmpname && unlink(tmp->tmpname) < 0)
			end_program(tmp->tmpname, errno, END2);
		tmp = tmp->next;
	}
}
