#include "../minishell.h"

// <pipe> ::= <exec> | <exec> "|" <pipe>
t_tree *parse_pipe(t_token **current)
{
	t_tree *pipe_node;
	t_tree *exec_node;
	
	pipe_node = create_tree_node(NODE_PIPE, "PIPE");
	exec_node = parse_exec(current);
	if (exec_node == NULL)
	{
		printf("파싱 실패: pipe\n");
		free_tree(pipe_node);
		return (NULL);
	}
	add_child(pipe_node, exec_node);

	while ((*current)->type == TOKEN_PIPE)
	{
		*current = (*current)->next;
		exec_node = parse_exec(current);
		if (exec_node == NULL)
		{
			printf("파싱 실패: exec\n");
			free_tree(pipe_node);
			return (NULL);
		}
		add_child(pipe_node, exec_node);
	}

	return (pipe_node);
}

// <exec> ::= <reds_opt> <cmd> <reds_opt>
t_tree *parse_exec(t_token **current)
{
	t_tree *exec_node;
	t_tree *reds_before;
	t_tree *cmd_node;
	t_tree *reds_after;

	exec_node = create_tree_node(NODE_EXEC, "EXEC");

	reds_before = parse_reds_opt(current);
	if (reds_before != NULL)
		add_child(exec_node, reds_before);
	
	cmd_node = parse_cmd(current);
	if (cmd_node == NULL)
	{
		printf("파싱 실패: cmd\n");
		free_tree(exec_node);
		return (NULL);
	}
	add_child(exec_node, cmd_node);

	reds_after = parse_reds_opt(current);
	if (reds_after != NULL)
		add_child(exec_node, reds_after);
	return (exec_node);
}

// <reds_opt> ::= <reds> | /* 빈 문자열 */
t_tree *parse_reds_opt(t_token **current)
{
	if ((*current)->type == TOKEN_REDIRECTION)
		return (parse_reds(current));
	return (NULL);
}

// <reds> ::= <red> | <red> <reds>
t_tree *parse_reds(t_token **current)
{
	t_tree *reds_node;
	t_tree *red_node;
	
	reds_node = create_tree_node(NODE_REDIRECTION, "REDS");
	red_node = parse_red(current);
	if (red_node == NULL)
	{
		printf("파싱 실패: red\n");
		free_tree(reds_node);
		return (NULL);
	}
	add_child(reds_node, red_node);

	while ((*current)->type == TOKEN_REDIRECTION)
	{
		red_node = parse_red(current);
		if (red_node == NULL)
		{
			printf("파싱 실패: 추가 reds\n");
			free_tree(reds_node);
			return (NULL);
		}
		add_child(reds_node, red_node);
	}

	return (reds_node);
}

// <cmd> ::= <command> <args_opt>
t_tree *parse_cmd(t_token **current)
{
	t_tree *cmd_node;
	t_tree *args_opt;

	if ((*current)->type != TOKEN_COMMAND)
	{
		printf("다른 토큰(TOKEN_COMMAND)\n");
		return (NULL);
	}
	cmd_node = create_tree_node(NODE_EXEC, (*current)->value);
	*current = (*current)->next;

	args_opt = parse_args_opt(current);
	if (args_opt != NULL)
		add_child(cmd_node, args_opt);

	return (cmd_node);
}

// <args_opt> ::= <args> | /* 빈 문자열 */
t_tree *parse_args_opt(t_token **current)
{
	if ((*current)->type == TOKEN_ARG)
		return (parse_args(current));
	return NULL;
}

// <args> ::= <arg> | <arg> <args>
t_tree *parse_args(t_token **current)
{
	t_tree *args_node;
	t_tree *arg_node;

	args_node = create_tree_node(NODE_ARG, "ARGS");
	arg_node = create_tree_node(NODE_ARG, (*current)->value);
	add_child(args_node, arg_node);
	*current = (*current)->next;

	while ((*current)->type == TOKEN_ARG)
	{
		arg_node = create_tree_node(NODE_ARG, (*current)->value);
		add_child(args_node, arg_node);
		*current = (*current)->next;
	}

	return (args_node);
}

// <red> ::= <redirection> <filename>
t_tree *parse_red(t_token **current) {
	char *redir_op;
	t_tree	*red_node;
	t_tree *filename_node;

	if ((*current)->type != TOKEN_REDIRECTION)
	{
		printf("다른 토큰(TOKEN_REDIRECTION)\n");
		return (NULL);
	}

	redir_op = (*current)->value;
	red_node = create_tree_node(NODE_REDIRECTION, redir_op);
	*current = (*current)->next;

	if ((*current)->type != TOKEN_FILENAME)
	{
		printf("다른 토큰(TOKEN_FILENAME)\n");
		free_tree(red_node);
		return (NULL);
	}

	filename_node = create_tree_node(NODE_FILENAME, (*current)->value);
	add_child(red_node, filename_node);
	*current = (*current)->next;

	return (red_node);
}

// 메인 파싱 함수
t_tree *parse(t_token *tokens)
{
	t_token	*current;
	t_tree	*root ;

	current = tokens;
	
	root = parse_pipe(&current);


	if (root == NULL)
	{
		printf("파싱 실패\n");
		return (NULL);
	}
	if (current->type != TOKEN_END)
	{
		printf("토큰 에러(TOKEN_END)\n");
		free_tree(root);
		return (NULL);
	}
	return (root);
}
