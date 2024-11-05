#include "../minishell.h"

// 연산자(>, >>, <, <<, |) 처리 함수
void process_op(t_token **head, t_token **current, const char **input_p)
{
	int 		len;
	char		*op;
	token_type	type;
	t_token		*new_token;

	len = 1;
	if ((**input_p == '>' && *(*input_p + 1) == '>') || 
		(**input_p == '<' && *(*input_p + 1) == '<'))
		len = 2;
	op = strndup(*input_p, len);
	if (*op == '|')
		type = TOKEN_PIPE;
	else
		type = TOKEN_REDIRECTION;
	new_token = create_token(type, op);
	free(op);
	*input_p += len;
	add_token(head, current, new_token);
}

// 꿔따! 처리 함수
void process_quote(t_token **head, t_token **current, const char **input_p)
{
	char 		quote;
	const char	*start;
	int			len;
	char		*quoted;
	token_type	type;
	t_token		*new_token;

	quote = **input_p;
	start = *input_p + 1; // 시작 인용부호 건너뛰기
	(*input_p)++;
	while (**input_p && **input_p != quote)
		(*input_p)++;
	if (**input_p != quote)
	{
		printf("꿔뜨 맞춰서 써야지 이자식아!\n");
		exit(EXIT_FAILURE);
	}
	len = *input_p - start;
	quoted = ft_strndup(start, len);
	(*input_p)++;

	if (*head == NULL || (*current && (*current)->type == TOKEN_PIPE))
		type = TOKEN_COMMAND;
	else if (*current && (*current)->type == TOKEN_REDIRECTION)
		type = TOKEN_FILENAME;
	else
		type = TOKEN_ARG;
	new_token = create_token(type, quoted);
	free(quoted);
	add_token(head, current, new_token);
}

// 이외에 다른 단어 처리 함수
void process_word(t_token **head, t_token **current, const char **input_p)
{
	const char *start;
	int len;
	char *word;
	token_type type;
	t_token *new_token;
	
	start = *input_p;
	while (**input_p && !ft_isspace(**input_p) && **input_p != '>' && **input_p != '<' && **input_p != '|')
		(*input_p)++;
	len = *input_p - start;
	word = ft_strndup(start, len);

	if (*head == NULL || (*current && (*current)->type == TOKEN_PIPE))
		type = TOKEN_COMMAND;
	else if (*current && (*current)->type == TOKEN_REDIRECTION)
		type = TOKEN_FILENAME;
	else
		type = TOKEN_ARG;

	new_token = create_token(type, word);
	free(word);

	add_token(head, current, new_token);
}

// 메인 토큰화 함수
t_token *tokenize(const char *input)
{
	t_token		*head;
	t_token		*current;
	t_token		*end_token;
	const char	*input_p;

	head = NULL;
	current = NULL;
	input_p = input;
	while (*input_p)
	{
		while (ft_isspace(*input_p))
			input_p++;
		if (*input_p == '\0')
			break;
		if (*input_p == '>' || *input_p == '<' || *input_p == '|')
		{
			process_op(&head, &current, &input_p);
			continue;
		}
		if (*input_p == '"' || *input_p == '\'')
		{
			process_quote(&head, &current, &input_p);
			continue;
		}
		process_word(&head, &current, &input_p);
	}
	end_token = create_token(TOKEN_END, NULL);
	if (current)
		current->next = end_token;
	else
		head = end_token;
	return head;
}
