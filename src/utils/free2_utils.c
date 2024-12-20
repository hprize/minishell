/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:13:04 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/19 01:59:42 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	handle_no_input(t_envp *master)
{
	replace_content(master->u_envp, "LAST_EXIT_STATUS", "130");
	free_master(master);
	// free(inter);
	exit(0);
}

void	wrong_cmd_path(t_token *tokens, char *input, t_envp **master)
{
	free_tokens(tokens);
	free(input);
	replace_content((*master)->u_envp, "LAST_EXIT_STATUS", "127");
}

void	parse_tree_err(t_token *tokens, char *input)
{
	free_tokens(tokens);
	free(input);
}
