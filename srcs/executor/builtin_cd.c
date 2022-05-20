/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:24:27 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:20:47 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_update_oldpwd(char *old_path)
{
	char	*str;
	t_env	*tmp;

	str = ft_strjoin("OLDPWD=", old_path);
	if (!str)
		end_program("Error: malloc in updating OLDPWD\n", 1, END1);
	tmp = find_elem_env(&g_data.env, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = old_path;
		free(tmp->str);
		tmp->str = str;
	}
	else
	{
		tmp = new_elem_env(str);
		free (str);
		if (!tmp)
			end_program("Error malloc\n", 1, END1);
		add_elem_env(&g_data.env, tmp);
	}
}

static void	cd_update_pwd(void)
{
	char	*pwd;
	char	*str;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", pwd);
	tmp = find_elem_env(&g_data.env, "PWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = pwd;
		free(tmp->str);
		tmp->str = str;
	}
	else
	{
		tmp = new_elem_env(str);
		free (pwd);
		free (str);
		if (!tmp)
			end_program("Error malloc\n", 1, END1);
		add_elem_env(&g_data.env, tmp);
	}
}

void	cd_update_env(char *old_path)
{
	cd_update_oldpwd(old_path);
	cd_update_pwd();
}

void	execute_cd(char **args, int flag)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		end_program(NULL, errno, END2);
	if (flag && args[1])
	{
		if (!chdir(args[1]))
		{
			cd_update_env(old_path);
			g_data.status = 0;
		}
		else
		{
			free(old_path);
			ft_putstr_fd("cd: ", STDERR_FILENO);
			perror(args[1]);
			g_data.status = 1;
		}
	}
	else
		g_data.status = 0;
}
