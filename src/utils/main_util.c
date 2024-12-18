/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:14:24 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/18 21:40:31 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_final(t_tree *parse_tree, t_token *tokens, char \
	*inter, char *input)
{
	free_tree(parse_tree);
	free_tokens(tokens);
	free(inter);
	free(input);
}

void	right_input(char *input, t_envp **master, char *inter)
{
	t_token	*tokens;
	t_tree	*parse_tree;

	add_history(input);
	tokens = tokenize(input, (*master)->u_envp);
	if (tokens == NULL)
	{
		replace_content((*master)->u_envp, "LAST_EXIT_STATUS", "2");
		free(inter);
		return ;
	}
	if (check_cmd_path(tokens, (*master)) == -1)
		wrong_cmd_path(tokens, input, master);
	else
	{
		parse_tree = parse(tokens);
		if (parse_tree == NULL)
			parse_tree_err(tokens, input);
		else
		{
			execute_tree(parse_tree, (*master));
			free_final(parse_tree, tokens, inter, input);
			remove_heredoc_files();
		}
	}
}
