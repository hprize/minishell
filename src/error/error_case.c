/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:42 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 19:56:48 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	handle_execve_error(t_tree *node)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(node->value, 2);
		ft_putendl_fd(": Permission denied\n", 2);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(node->value, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd(node->value, 2);
		ft_putendl_fd(": Is a directory\n", 2);
		exit(126);
	}
	else
	{
		ft_putstr_fd(node->value, 2);
		ft_putendl_fd(": Execution failed\n", 2);
		exit(1);
	}
}

void	strerror_exit(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}
