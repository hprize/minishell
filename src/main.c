/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:53:06 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/29 22:29:07 by junlee           ###   ########.fr       */
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
	
	while(1)
	{
		g_signal = 0;

		char	*input = readline("minishell$ ");
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