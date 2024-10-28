/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:53:06 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/29 01:00:18 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	signal_exit(int sig)
{
	printf("caught signal %d\n", sig);
	exit(1);
}

int	main(void)
{
	signal(SIGINT, signal_exit);
	
	while(1)
	{
		g_signal = 0;
		

		char	*input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			printf("entered : %s\n", input);
			free(input);
			// if (*input == 'Z')
			// {
			// 	printf("exit\n");
			// 	exit(1);
			// }
		}
		else
		{
			printf("exit\n");
			exit(1);
		}
	}
}