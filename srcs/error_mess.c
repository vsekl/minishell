/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:49:21 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:49:22 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_mess(char *mess, int code)
{
	perror(mess);
	exit (code);
}

int	warning(char *mess, int code)
{
	ft_putstr_fd(mess, STDERR_FILENO);
	return (code);
}
