#ifndef SIGNAL_H
# define SIGNAL_H
#include "../../minishell.h"

void	sig_int_prompt(int signo);
void	sig_int_execve(int signo);
void	sig_quit_execve(int signo);
void	sig_int_heredoc(int signo);
void	signal_handel_prompt();
void	signal_all_ign();
void	signal_all_dfl();
void	signal_handle_execve();
void	signal_handle_heredoc();

#endif