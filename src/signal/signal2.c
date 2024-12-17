#include "signal.h"

void	signal_handel_prompt(void)
{
	signal(SIGINT, sig_int_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_all_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_all_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handle_execve(void)
{
	signal(SIGINT, sig_int_execve);
	signal(SIGQUIT, sig_quit_execve);
}

void	signal_handle_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
