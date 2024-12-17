/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:00:45 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:00:47 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_reds_opt(t_tree *exec_node, t_token **current)
{
	t_tree	*red_node;

	while ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC)
	{
		red_node = parse_reds(current);
		if (red_node)
			add_child(exec_node, red_node);
	}
}

t_tree	*parse_reds(t_token **current)
{
	t_tree	*red_node;
	t_tree	*filename_node;

	if ((*current)->type == TOKEN_RED)
		red_node = create_tree_node(NODE_RED, (*current)->value);
	else
		red_node = create_tree_node(NODE_HEREDOC, (*current)->value);
	*current = (*current)->next;
	if ((*current)->type == TOKEN_FILENAME)
	{
		filename_node = create_tree_node(NODE_FILENAME, (*current)->value);
		add_child(red_node, filename_node);
		*current = (*current)->next;
	}
	return (red_node);
}

t_tree	*parse_cmd(t_token **current)
{
	t_tree	*cmd_node;
	t_tree	*arg_node;

	if ((*current)->type != TOKEN_CMD)
		return (NULL);
	cmd_node = create_tree_node(NODE_CMD, (*current)->value);
	*current = (*current)->next;
	while (*current && (*current)->type == TOKEN_ARG)
	{
		arg_node = create_tree_node(NODE_ARG, (*current)->value);
		add_child(cmd_node, arg_node);
		*current = (*current)->next;
	}
	return (cmd_node);
}

t_tree	*parse(t_token *tokens)
{
	t_token	*current;
	t_tree	*root ;

	current = tokens;
	root = parse_pipe(&current);
	if (root == NULL)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		return (NULL);
	}
	if (current->type != TOKEN_END)
	{
		ft_putstr_fd("minishell: command terminated unexpectedly\n", 2);
		free_tree(root);
		return (NULL);
	}
	return (root);
}
