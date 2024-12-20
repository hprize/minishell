/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:25:25 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/19 02:23:03 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	char	*input;
	// char	*inter;

	if (argc || argv)
		argc = 1;
	set_master(&master, envp);
	while (1)
	{
		g_signal = 0;
		signal_handel_prompt();
		// inter = interface(master->u_envp);
		input = readline("minishell: ");
		signal_all_dfl();
		if (input == NULL)
			handle_no_input(master);
		else if (ft_strlen(input) == 0)
			free(input);
		else if (input)
			right_input(input, &master);
	}
}
