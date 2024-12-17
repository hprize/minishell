#include "../minishell.h"

void print_tree(t_tree *node, int level) {
	if (node == NULL) return;

	// 들여쓰기
	for (int i = 0; i < level; i++) {
		printf("  ");
	}
	switch (node->type) {
		case NODE_PIPE:
			printf("PIPE\n");
			break;
		case NODE_EXEC:
			printf("EXEC: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_CMD:
			printf("CMD: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_ARG:
			printf("ARG: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_RED:
			printf("RED: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_HEREDOC:
			printf("HEREDOC: %s\n", node->value ? node->value : "NULL");
			break;
		case NODE_FILENAME:
			printf("FILENAME: %s\n", node->value ? node->value : "NULL");
			break;
		default:
			printf("UNKNOWN NODE\n");
	}

	for (int i = 0; i < node->child_count; i++) {
		print_tree(node->children[i], level + 1);
	}
}

// 일렬로 트리 출력 함수 (전위 순회)
void print_tree_linear(t_tree *node) {
	if (node == NULL)
		return;

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
		case NODE_RED:
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

	for (int i = 0; i < node->child_count; i++) {
		print_tree_linear(node->children[i]);
	}
}

// 토큰 타입을 문자열로 변환하는 함수
const char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case TOKEN_CMD: return "COMMAND";
		case TOKEN_ARG: return "ARGUMENT";
		case TOKEN_RED: return "REDIRECTION";
		case TOKEN_PIPE: return "PIPE";
		case TOKEN_HEREDOC: return "HEREDOC";
		case TOKEN_FILENAME: return "FILENAME";
		case TOKEN_END: return "END";
		case TOKEN_INVALID: return "INVALID";
		default: return "UNKNOWN";
	}
}

// 토큰들을 출력하는 함수
void print_tokens(t_token *head)
{
	t_token *current = head;

	while (current != NULL)
	{
		printf("Type: %s, Value: %s\n", token_type_to_string(current->type), current->value ? current->value : "NULL");
		current = current->next;
	}
}