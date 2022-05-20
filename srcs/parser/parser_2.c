/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:20:18 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:20:19 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_id_cmd(void)
{
	t_cmd	*tmp;
	int		id;

	id = 1;
	tmp = g_data.cmds;
	while (tmp)
	{
		tmp->id = ft_itoa(id);
		if (!tmp->id)
			end_program(ERROR_INIT_ID_CMD, 1, END1);
		id++;
		tmp = tmp->next;
	}
}
