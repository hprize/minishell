#include "../minishell.h"

// PIPE 구조 파싱: <exec> | <exec> | ...
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

// EXEC 노드를 파싱 - (CMD, RED, ARG 포함)
t_tree	*parse_exec(t_token **current)
{
	t_tree	*exec_node;
	t_tree	*cmd_node;

	exec_node = create_tree_node(NODE_EXEC, "EXEC");
	parse_reds_opt(exec_node, current);

	cmd_node = parse_cmd(current);
	if (!cmd_node)
		return (NULL);
	add_child(exec_node, cmd_node);

	parse_reds_opt(exec_node, current);
	return (exec_node);
}

// 선택적 리다이렉션 파싱
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

// 리다이렉션을 파싱하고 리다이렉션이 있는 경우에만 노드 생성
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

// 명령어와 인자 파싱, CMD 노드의 자식으로 ARG를 추가
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

// 메인 파싱 함수
t_tree	*parse(t_token *tokens)
{
	t_token	*current;
	t_tree	*root ;

	current = tokens;
	root = parse_pipe(&current);
	if (root == NULL)
	{
		printf("minishell: parse error\n");
		return (NULL);
	}
	if (current->type != TOKEN_END)
	{
		printf("minishell: command terminated unexpectedly\n");
		free_tree(root);
		return (NULL);
	}
	return (root);
}
