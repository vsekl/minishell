/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:14 by vjose             #+#    #+#             */
/*   Updated: 2022/05/06 21:24:51 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_update_envp(void)
{
	t_env	*env;
	int		i;

	env = g_data.env;
	i = 0;
	while (env)
	{
		write(g_data.fd[0][1], env->str, ft_strlen(env->str));
		write(g_data.fd[0][1], "\n", 1);
		env = env->next;
		i++;
	}
	close(g_data.fd[0][1]);
	write(g_data.fd[1][1], &i, sizeof(int));
	close(g_data.fd[1][1]);
	write(g_data.fd[2][1], &g_data.status, sizeof(int));
	close(g_data.fd[2][1]);
}

void	get_update_envp(void)
{
	int		i;
	int		j;

	read(g_data.fd[1][0], &i, sizeof(int));
	read(g_data.fd[2][0], &g_data.status, sizeof(int));
	free_two_array_char(g_data.envp);
	g_data.envp = malloc_two_array_char(i + 1);
	if (!g_data.envp)
		end_program(ERROR_MALLOC_ENVP, 1, END1);
	j = 0;
	while (j < i)
	{
		get_next_line(g_data.fd[0][0], &g_data.envp[j]);
		g_data.envp[j][ft_strlen(g_data.envp[j]) - 1] = '\0';
		j++;
	}
}
