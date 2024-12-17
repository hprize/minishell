/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:25:25 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:25:29 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	char	*input;
	char	*inter;

	set_master(&master, envp);
	while (1)
	{
		g_signal = 0;
		signal_handel_prompt();
		inter = interface(master->u_envp);
		input = readline(inter);
		signal_all_dfl();
		if (input == NULL)
			handle_no_input(master, inter);
		else if (ft_strlen(input) == 0)
			free(input);
		else if (input)
			right_input(input, &master, inter);
	}
}
