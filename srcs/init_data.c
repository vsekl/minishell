/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:49:24 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:49:25 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**new_envp(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc_two_array_char(size_two_array_char(envp));
	if (!new_envp)
		exit(warning(ERROR_MALLOC_ENVP, 1));
	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_two_array_char(new_envp);
			exit(warning(ERROR_MALLOC_ENVP, 1));
		}
		i++;
	}
	init_shlvl(&new_envp);
	return (new_envp);
}

void	init_g_data(void)
{
	g_data.env = NULL;
	g_data.input = NULL;
	g_data.tokens = NULL;
	g_data.cmds = NULL;
	g_data.env = list_env(g_data.envp);
	if (pipe(g_data.fd[0]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
	if (pipe(g_data.fd[1]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
	if (pipe(g_data.fd[2]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
}
