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
