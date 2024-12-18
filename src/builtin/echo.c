/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:54:57 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 22:24:07 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

int	ft_echo(char **args)
{
	int	newline;
	int	i;

	i = -1;
	newline = 0;
	if (*args == NULL)
		return (0);
	while (ft_strcmp("-n", args[++i]) == 0)
		newline = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		if (!args[i + 1])
		{
			if (newline == 0)
				printf("\n");
		}
		i++;
	}
	return (0);
}
