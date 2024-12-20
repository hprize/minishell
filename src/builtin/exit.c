/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:55:07 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 19:55:22 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

void	ft_exit_call(int count, char **args, t_env *envp)
{
	int	result;

	result = ft_atoi(find_content("LAST_EXIT_STATUS", envp));
	if (count > 1)
	{
		write(2, "too many arguments\n", 19);
		exit (1);
	}
	if (ft_isalldigit(args[0]) == 0)
	{
		write(2, "numeric argument required\n", 26);
		exit (2);
	}
	else if (count == 1)
		exit (ft_atoi(args[0]) % 256);
	else
		exit (result);
}
