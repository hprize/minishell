/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:57:11 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/19 02:42:19 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "../../minishell.h"

void	handle_execve_error(t_tree *node);
void	strerror_exit(void);

#endif