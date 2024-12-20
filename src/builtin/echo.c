/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:54:57 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/19 02:23:01 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

int	ft_echo(char **args)
{
	int	newline;
	int	i;

	i = 0;
	newline = 0;

	if (args == NULL || args[0] == NULL)
		return (0);

	while (args[i] && ft_strcmp("-n", args[i]) == 0)
	{
		newline = 1;
		i++;
	}
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
