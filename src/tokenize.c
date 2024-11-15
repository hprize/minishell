#include "../minishell.h"

void	process_op(t_token **head, t_token **current, const char **input_p)
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
	if (*op == '|' && len == 1)
		type = TOKEN_PIPE;
	else if (**input_p == '<' && *(*input_p + 1) == '<')
		type = TOKEN_HEREDOC;
	else
		type = TOKEN_RED;
	
	*input_p += len;

	while (**input_p == ' ')
		(*input_p)++;
	
	if (type == TOKEN_RED && (**input_p == '\0' || **input_p == '|' || **input_p == '<' || **input_p == '>')) {
		printf("minishell: syntax error near unexpected token 'newline'\n");
		free(op);
		exit(1);
	}

	new_token = create_token(type, op);
	free(op);
	add_token(head, current, new_token);
}

// quote 처리 함수
void	process_quote(t_token **head, t_token **current, const char **input_p)
{
	char 		quote;
	const char	*start;
	int			len;
	char		*quoted;
	token_type	type;
	t_token		*new_token;

	quote = **input_p;
	start = *input_p + 1; // 시작 quote 건너뛰기
	(*input_p)++;
	while (**input_p && **input_p != quote)
		(*input_p)++;
	if (**input_p != quote)
	{
		printf("minishell: syntax error unexpected end of file (unclosed quote)\n");
		exit(EXIT_FAILURE);
	}
	len = *input_p - start;
	quoted = ft_strndup(start, len);
	(*input_p)++;

	if (*head == NULL || (*current && (*current)->type == TOKEN_PIPE))
		type = TOKEN_CMD;
	else if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else
		type = TOKEN_ARG;
	new_token = create_token(type, quoted);
	free(quoted);
	add_token(head, current, new_token);
}

// 이외에 다른 단어 처리 함수
void	process_word(t_token **head, t_token **current, const char **input_p)
{
	const char	*start;
	int			len;
	char		*word;
	token_type	type;
	t_token		*new_token;
	
	start = *input_p;
	while (**input_p && !ft_isspace(**input_p) && **input_p != '>' && **input_p != '<' && **input_p != '|')
		(*input_p)++;
	len = *input_p - start;
	word = ft_strndup(start, len);

	if (*head == NULL || 
		(*current && ((*current)->type == TOKEN_PIPE || (*current)->type == TOKEN_FILENAME)))
		type = TOKEN_CMD;
	else if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else
		type = TOKEN_ARG;

	new_token = create_token(type, word);
	free(word);

	add_token(head, current, new_token);
}

// 메인 토큰화 함수
t_token	*tokenize(const char *input)
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
	return (head);
}
