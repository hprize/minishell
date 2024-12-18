/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:10:20 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/18 21:33:39 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	sig_int_prompt(int signo)
{
	g_signal = signo;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int_execve(int signo)
{
	g_signal = signo;
	write(1, "\n", 1);
	rl_redisplay();
}

void	sig_quit_execve(int signo)
{
	g_signal = signo;
	write(1, "Quit (core dumped)\n", 19);
	rl_redisplay();
}

void	sig_int_heredoc(int signo)
{
	g_signal = signo;
	write(1, "sig_int_heredoc_in\n", 19);
}

void	set_execute_pipe_sig(void)
{
	signal_all_dfl();
	signal_handle_execve();
}
