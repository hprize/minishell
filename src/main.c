/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:53:06 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/31 01:43:56 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	signal_exit(int sig)
{
	printf("caught signal %d\n", sig);
	exit(1);
}

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*u_envp;

	u_envp = malloc(sizeof(t_envp));
	if (u_envp == NULL)
		exit(1);

	u_envp->envp = (char **)envp;
	// ft_memset(u_envp, 0, sizeof(t_envp));
	
	while(1)
	{
		g_signal = 0;
		char *cmd;
		
		//커맨드 창을 받아서 readline에 뱉도록.
		cmd = set_envp(u_envp);
		// printf("%s@%s:%s$", u_envp->user, u_envp->host, u_envp->where);

		char	*input = readline(cmd);
		if (input)
		{
			add_history(input);
			printf("entered : %s\n", input);
			test(input);
			free(input);
			
		}
		signal(SIGINT, signal_exit);

	}
}