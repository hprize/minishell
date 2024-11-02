#include "../minishell.h"

// 6. 트리 노드 생성 및 관리 함수
t_tree *create_tree_node(node_type type, const char *value) {
	t_tree *node = malloc(sizeof(t_tree));
	if (!node) {
		perror("Failed to allocate memory for tree node");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	node->value = value ? strdup(value) : NULL;
	node->children = NULL;
	node->child_count = 0;
	return node;
}

void add_child(t_tree *parent, t_tree *child) {
	parent->children = realloc(parent->children, sizeof(t_tree*) * (parent->child_count + 1));
	if (!parent->children) {
		perror("Failed to allocate memory for children");
		exit(EXIT_FAILURE);
	}
	parent->children[parent->child_count++] = child;
}

// 7. 파서 함수 선언
t_tree *parse_pipe(t_token **current);
t_tree *parse_exec(t_token **current);
t_tree *parse_reds_opt(t_token **current);
t_tree *parse_reds(t_token **current);
t_tree *parse_cmd(t_token **current);
t_tree *parse_args_opt(t_token **current);
t_tree *parse_args(t_token **current);
t_tree *parse_red(t_token **current);

// 8. 파서 함수 구현

// <pipe> ::= <exec> | <exec> "|" <pipe>
t_tree *parse_pipe(t_token **current) {
	t_tree *pipe_node = create_tree_node(NODE_PIPE, "PIPE");

	// 첫 번째 exec 파싱
	t_tree *exec_node = parse_exec(current);
	if (exec_node == NULL) {
		fprintf(stderr, "Error: Failed to parse exec in pipe\n");
		free_tree(pipe_node);
		return NULL;
	}
	add_child(pipe_node, exec_node);

	// 파이프가 있는 동안 계속 exec 파싱
	while ((*current)->type == TOKEN_PIPE) {
		// 파이프 토큰 건너뛰기
		*current = (*current)->next;

		// 다음 exec 파싱
		exec_node = parse_exec(current);
		if (exec_node == NULL) {
			fprintf(stderr, "Error: Failed to parse exec after pipe\n");
			free_tree(pipe_node);
			return NULL;
		}
		add_child(pipe_node, exec_node);
	}

	return pipe_node;
}

// <exec> ::= <reds_opt> <cmd> <reds_opt>
t_tree *parse_exec(t_token **current) {
	t_tree *exec_node = create_tree_node(NODE_EXEC, "EXEC");

	// <reds_opt> (앞)
	t_tree *reds_before = parse_reds_opt(current);
	if (reds_before != NULL) {
		add_child(exec_node, reds_before);
	}

	// <cmd> 파싱
	t_tree *cmd_node = parse_cmd(current);
	if (cmd_node == NULL) {
		fprintf(stderr, "Error: Failed to parse cmd in exec\n");
		free_tree(exec_node);
		return NULL;
	}
	add_child(exec_node, cmd_node);

	// <reds_opt> (뒤)
	t_tree *reds_after = parse_reds_opt(current);
	if (reds_after != NULL) {
		add_child(exec_node, reds_after);
	}

	return exec_node;
}

// <reds_opt> ::= <reds> | /* 빈 문자열 */
t_tree *parse_reds_opt(t_token **current) {
	if ((*current)->type == TOKEN_REDIRECTION) {
		return parse_reds(current);
	}
	return NULL; // 빈 문자열
}

// <reds> ::= <red> | <red> <reds>
t_tree *parse_reds(t_token **current) {
	t_tree *reds_node = create_tree_node(NODE_REDIRECTION, "REDS");

	// 첫 번째 <red> 파싱
	t_tree *red_node = parse_red(current);
	if (red_node == NULL) {
		fprintf(stderr, "Error: Failed to parse redirection\n");
		free_tree(reds_node);
		return NULL;
	}
	add_child(reds_node, red_node);

	// 추가 리다이렉션 파싱
	while ((*current)->type == TOKEN_REDIRECTION) {
		red_node = parse_red(current);
		if (red_node == NULL) {
			fprintf(stderr, "Error: Failed to parse additional redirection\n");
			free_tree(reds_node);
			return NULL;
		}
		add_child(reds_node, red_node);
	}

	return reds_node;
}

// <cmd> ::= <command> <args_opt>
t_tree *parse_cmd(t_token **current) {
	if ((*current)->type != TOKEN_COMMAND) {
		fprintf(stderr, "Error: Expected command, found %s\n", (*current)->value ? (*current)->value : "NULL");
		return NULL;
	}

	t_tree *cmd_node = create_tree_node(NODE_EXEC, (*current)->value);
	// 명령어 토큰 건너뛰기
	*current = (*current)->next;

	// <args_opt> 파싱
	t_tree *args_opt = parse_args_opt(current);
	if (args_opt != NULL) {
		add_child(cmd_node, args_opt);
	}

	return cmd_node;
}

// <args_opt> ::= <args> | /* 빈 문자열 */
t_tree *parse_args_opt(t_token **current) {
	if ((*current)->type == TOKEN_ARG) {
		return parse_args(current);
	}
	return NULL; // 빈 문자열
}

// <args> ::= <arg> | <arg> <args>
t_tree *parse_args(t_token **current) {
	t_tree *args_node = create_tree_node(NODE_ARG, "ARGS");

	// 첫 번째 <arg> 파싱
	t_tree *arg_node = create_tree_node(NODE_ARG, (*current)->value);
	add_child(args_node, arg_node);
	// arg 토큰 건너뛰기
	*current = (*current)->next;

	// 추가 인수 파싱
	while ((*current)->type == TOKEN_ARG) {
		arg_node = create_tree_node(NODE_ARG, (*current)->value);
		add_child(args_node, arg_node);
		// arg 토큰 건너뛰기
		*current = (*current)->next;
	}

	return args_node;
}

// <red> ::= <redirection> <filename>
t_tree *parse_red(t_token **current) {
	if ((*current)->type != TOKEN_REDIRECTION) {
		fprintf(stderr, "Error: Expected redirection, found %s\n", (*current)->value ? (*current)->value : "NULL");
		return NULL;
	}

	char *redir_op = (*current)->value;
	t_tree *red_node = create_tree_node(NODE_REDIRECTION, redir_op);
	// 리다이렉션 토큰 건너뛰기
	*current = (*current)->next;

	if ((*current)->type != TOKEN_FILENAME) {
		fprintf(stderr, "Error: Expected filename after redirection, found %s\n", (*current)->value ? (*current)->value : "NULL");
		free_tree(red_node);
		return NULL;
	}

	// <filename> 파싱
	t_tree *filename_node = create_tree_node(NODE_FILENAME, (*current)->value);
	add_child(red_node, filename_node);
	// 파일 이름 토큰 건너뛰기
	*current = (*current)->next;

	return red_node;
}

// 12. 전체 파싱 함수
t_tree *parse(t_token *tokens) {
	t_token *current = tokens;
	t_tree *root = parse_pipe(&current);
	if (root == NULL) {
		fprintf(stderr, "Parsing failed.\n");
		return NULL;
	}

	if (current->type != TOKEN_END) {
		fprintf(stderr, "Error: Unexpected tokens after complete parsing.\n");
		free_tree(root);
		return NULL;
	}

	return root;
}