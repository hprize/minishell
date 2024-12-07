#include "../minishell.h"

void	sig_int_prompt(int signo)
{
	g_signal = signo;
	// perror("");
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
//	prompt
void	signal_handel_prompt()
{
	// ctrl c
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

void	signal_handle_execve()
{
	signal(SIGINT, sig_int_execve);
	signal(SIGQUIT, sig_quit_execve);
}

void	sig_int_heredoc(int signo)
{
	g_signal = signo;
	// signal(SIGINT, SIG_DFL);
	write(1, "sig_int_heredoc_in\n", 19);
	// write(1, NULL, 0);
	// rl_redisplay();
	// exit(130);
}

void	signal_handle_heredoc()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
