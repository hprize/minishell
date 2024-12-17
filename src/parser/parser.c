#include "parser.h"

t_tree	*parse_pipe(t_token **current)
{
	t_tree	*pipe_node;
	t_tree	*exec_node;

	exec_node = parse_exec(current);
	if (!exec_node)
		return (NULL);
	if ((*current)->type != TOKEN_PIPE)
		return (exec_node);
	pipe_node = create_tree_node(NODE_PIPE, NULL);
	add_child(pipe_node, exec_node);
	while ((*current)->type == TOKEN_PIPE)
	{
		*current = (*current)->next;
		exec_node = parse_exec(current);
		if (!exec_node)
			return (NULL);
		add_child(pipe_node, exec_node);
	}
	return (pipe_node);
}

void	current_type(t_token **current, t_tree *exec_node)
{
	t_tree	*red_node;

	red_node = parse_reds(current);
	if (red_node)
		add_child(exec_node, red_node);
}

t_tree	*parse_exec(t_token **current)
{
	t_tree	*exec_node;
	t_tree	*cmd_node;
	t_tree	*arg_node;

	exec_node = create_tree_node(NODE_EXEC, "EXEC");
	parse_reds_opt(exec_node, current);
	cmd_node = parse_cmd(current);
	if (cmd_node)
		add_child(exec_node, cmd_node);
	while (*current && (*current)->type != TOKEN_PIPE && \
		(*current)->type != TOKEN_END)
	{
		if ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC)
			current_type(current, exec_node);
		else if ((*current)->type == TOKEN_ARG)
		{
			arg_node = create_tree_node(NODE_ARG, (*current)->value);
			add_child(cmd_node, arg_node);
			*current = (*current)->next;
		}
	}
	return (exec_node);
}

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
