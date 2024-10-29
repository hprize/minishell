#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 100

const char *input;

void nextToken(char *token)
{
	while (isspace(*input)) input++; // 공백 건너뛰기
	int i = 0;
	while (*input && !isspace(*input)) {
		token[i++] = *input++;
	}
	token[i] = '\0'; // 토큰의 끝
}

// COMMAND -> WORD OPTIONS ARGUMENTS
void parse_COMMAND();

// OPTIONS -> OPTION OPTIONS | ε
void parse_OPTIONS();

// ARGUMENTS -> WORD ARGUMENTS | ε
void parse_ARGUMENTS();

void parse_COMMAND() {
	char token[MAX_TOKEN_SIZE];
	nextToken(token);

	if (strlen(token) == 0) {
		printf("Error: 명령어가 없습니다.\n");
		return;
	}
	printf("명령어: %s\n", token);

	// OPTIONS와 ARGUMENTS 파싱
	parse_OPTIONS();
	parse_ARGUMENTS();
}

void parse_OPTIONS() {
	char token[MAX_TOKEN_SIZE];
	nextToken(token);

	// 옵션은 '-'로 시작
	while (token[0] == '-') {
		printf("옵션: %s\n", token);
		nextToken(token);  // 다음 옵션 또는 인수로 이동
	}

	// 다음에 올 인수를 위해 input 포인터를 되돌립니다.
	input -= strlen(token);
}

void parse_ARGUMENTS() {
	char token[MAX_TOKEN_SIZE];
	nextToken(token);

	while (strlen(token) > 0) {
		printf("인수: %s\n", token);
		nextToken(token);
	}
}

int main() {
	input = "echo -n Hello World";
	parse_COMMAND();

	return 0;
}
