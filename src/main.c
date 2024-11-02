#include "../minishell.h"

// 13. 메인 함수 예시
int main() {
	const char *input = "echo \"HELLO WORLD\" | cat -e >> test.txt | grep \"pattern\"";
	printf("Input Command: %s\n\n", input);

	// 토큰화
	t_token *tokens = tokenize(input);

	// 파싱
	t_tree *parse_tree = parse(tokens);
	if (parse_tree == NULL) {
		fprintf(stderr, "Parsing failed.\n");
		free_tokens(tokens);
		return 1;
	}

	// 트리 출력
	printf("Parsed Tree:\n");
	print_tree(parse_tree, 0);

	// 메모리 해제
	free_tree(parse_tree);
	free_tokens(tokens);

	return 0;
}