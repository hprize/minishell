/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:10:32 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/18 21:25:41 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# include "../../minishell.h"

void	sig_int_prompt(int signo);
void	sig_int_execve(int signo);
void	sig_quit_execve(int signo);
void	sig_int_heredoc(int signo);
void	set_execute_pipe_sig(void);
void	signal_handel_prompt(void);
void	signal_all_ign(void);
void	signal_all_dfl(void);
void	signal_handle_execve(void);
void	signal_handle_heredoc(void);

#endif