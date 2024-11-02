#include "../minishell.h"

// 9. 트리 출력 함수
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

// 10. 트리 메모리 해제 함수
void free_tree(t_tree *node) {
	if (node == NULL) return;

	// 모든 자식 노드 해제
	for (int i = 0; i < node->child_count; i++) {
		free_tree(node->children[i]);
	}

	// 자식 배열 해제
	free(node->children);

	// 노드의 값 해제
	free(node->value);

	// 노드 자체 해제
	free(node);
}

// 11. 토큰 메모리 해제 함수
void free_tokens(t_token *tokens) {
	while (tokens != NULL) {
		t_token *next = tokens->next;
		if (tokens->value) free(tokens->value);
		free(tokens);
		tokens = next;
	}
}