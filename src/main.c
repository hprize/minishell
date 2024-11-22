#include "../minishell.h"

int	g_signal;

void	signal_exit(int sig)
{
	printf("caught signal %d\n", sig);
	g_signal = 1;
}

void	exit_func(t_envp *s)
{
	free_struct(s);
	free(s);
	s = NULL;
	exit(1);
}

int	main(int argc, char **argv, const char **envp)
{
	t_envp		*u_envp;
	t_master	*master;
	char		*cmd;


//
	u_envp = ft_calloc(1, sizeof(t_envp));
	if (u_envp == NULL)
		exit(1);

	// ft_memset(u_envp, 0, sizeof(t_envp));

	master = ft_calloc(1, sizeof(t_master));
	if (master == NULL)
		exit(1);
	//master_init()함수로 빼기
	master->envp = (char **)envp;
	master->path_list = find_path(master->envp);
// - 함수로 따로 빼기

	while(1)
	{
		g_signal = 0;
		
		//커맨드 창을 받아서 readline에 뱉도록.
		// printf("%s@%s:%s$", u_envp->user, u_envp->host, u_envp->where);
		cmd = set_envp(u_envp, envp);
		char	*input = readline(cmd);
		if (input)
		{
			add_history(input);
			printf("entered : %s\n", input);
			test(input, master);
			free(input);
			
		}
		else if (!input)
		{
			free_struct_envp (u_envp);
			free_struct_master (master);
			exit(0);
		}
		// signal(SIGINT, signal_exit);
		// if (g_signal == 1)
		// 	exit_func(u_envp);
	}
}