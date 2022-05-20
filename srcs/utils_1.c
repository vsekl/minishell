/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:20:49 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:34:05 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**malloc_two_array_char(int len)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i <= len)
		array[i++] = NULL;
	return (array);
}

void	free_two_array_char(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free (array[i++]);
	free (array);
	array = NULL;
}

void	add_back_elem_two_array_char(char **array, char *elem, int len)
{
	int	i;

	i = 0;
	while (array && i < len && array[i])
		i++;
	if (i < len)
		array[i] = ft_strdup(elem);
	if (!array[i])
		end_program(ERROR_ADD_ELEM_TWO_ARR, 1, END1);
}

int	size_two_array_char(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
