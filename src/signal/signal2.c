#include "signal.h"

void	signal_handel_prompt()
{
	signal(SIGINT, sig_int_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_all_ign()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_all_dfl()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handle_execve()
{
	signal(SIGINT, sig_int_execve);
	signal(SIGQUIT, sig_quit_execve);
}

void	signal_handle_heredoc()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
