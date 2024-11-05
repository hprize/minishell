#include "../minishell.h"

void print_tree(t_tree *node, int level) {
	if (node == NULL) return;

	// 들여쓰기
	for (int i = 0; i < level; i++) {
		printf("  ");
	}

	// 노드 정보 출력
	switch (node->type) {
		case NODE_PIPE:
			printf("PIPE\n");
			break;
		case NODE_EXEC:
			printf("EXEC: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_REDIRECTION:
			printf("REDIR: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_ARG:
			printf("ARG: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_FILENAME:
			printf("FILENAME: %s\n", node->value ? node->value : "NULL");
			break;
		default:
			printf("UNKNOWN NODE\n");
	}

	// 자식 노드 재귀 호출
	for (int i = 0; i < node->child_count; i++) {
		print_tree(node->children[i], level + 1);
	}
}

// 일렬로 트리 출력 함수 (전위 순회)
void print_tree_linear(t_tree *node) {
	if (node == NULL)
		return;

	// 노드 정보 출력
	switch (node->type) {
		case NODE_PIPE:
			printf("PIPE ");
			break;
		case NODE_EXEC:
			if (node->value)
				printf("EXEC: %s ", node->value);
			else
				printf("EXEC: NULL ");
			break;
		case NODE_REDIRECTION:
			if (node->value)
				printf("REDIR: %s ", node->value);
			else
				printf("REDIR: NULL ");
			break;
		case NODE_ARG:
			if (node->value)
				printf("ARG: %s ", node->value);
			else
				printf("ARG: NULL ");
			break;
		case NODE_FILENAME:
			if (node->value)
				printf("FILENAME: %s ", node->value);
			else
				printf("FILENAME: NULL ");
			break;
		default:
			printf("UNKNOWN_NODE ");
	}

	// 자식 노드를 순서대로 재귀적으로 방문
	for (int i = 0; i < node->child_count; i++) {
		print_tree_linear(node->children[i]);
	}
}