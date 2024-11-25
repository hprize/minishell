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

	new_token = create_token(type, QUOTE_NONE, op);
	free(op);
	add_token(head, current, new_token);
}

// quote 처리 함수
void	process_quote(t_token **head, t_token **current, const char **input_p, int prev_space, int *cmd_set)
{
	char 		quote;
	const char	*start;
	int			len;
	char		*quoted;
	token_type	type;
	quote_type	quote_state;
	t_token		*new_token;

	quote = **input_p;
	if (quote == '\'')
		quote_state = QUOTE_SINGLE;
	else
		quote_state = QUOTE_DOUBLE;
	start = *input_p + 1; // 시작 따옴표 건너뛰기
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

	if (!prev_space && *current && 
		((*current)->type == TOKEN_CMD || (*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, quoted, quote_state);
		free(quoted);
		return;
	}

	if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else if (*cmd_set == 0)
	{
		type = TOKEN_CMD;
		*cmd_set = 1;
	}
	else
		type = TOKEN_ARG;

	new_token = create_token(type, quote_state, quoted);
	free(quoted);
	add_token(head, current, new_token);
}

// 이외에 다른 단어 처리 함수
void	process_word(t_token **head, t_token **current, const char **input_p, int prev_space, int *cmd_set)
{
	const char	*start;
	int			len;
	char		*word;
	token_type	type;
	t_token		*new_token;

	start = *input_p;
	while (**input_p && !ft_isspace(**input_p) && **input_p != '>' && **input_p != '<' && **input_p != '|' \
		&& **input_p != '"' && **input_p != '\'')
		(*input_p)++;
	len = *input_p - start;
	word = ft_strndup(start, len);

	if (!prev_space && *current && 
		((*current)->type == TOKEN_CMD || (*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, word, QUOTE_NONE);
		free(word);
		return;
	}

	if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else if (*cmd_set == 0)
	{
		type = TOKEN_CMD;
		*cmd_set = 1;
	}
	else
		type = TOKEN_ARG;

	new_token = create_token(type, QUOTE_NONE, word);
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
	int			prev_space;
	int			cmd_set;

	head = NULL;
	current = NULL;
	input_p = input;
	prev_space = 1; // 처음에는 스페이스로
	cmd_set = 0;
	while (*input_p)
	{
		while (ft_isspace(*input_p))
		{
			input_p++;
			prev_space = 1;
		}
		if (*input_p == '\0')
			break;
		if (*input_p == '>' || *input_p == '<' || *input_p == '|')
		{
			process_op(&head, &current, &input_p);
			prev_space = 1;
			continue;
		}
		if (*input_p == '"' || *input_p == '\'')
		{
			process_quote(&head, &current, &input_p, prev_space, &cmd_set);
			prev_space = 0;
			continue;
		}
		process_word(&head, &current, &input_p, prev_space, &cmd_set);
		prev_space = 0;
	}
	end_token = create_token(TOKEN_END, QUOTE_NONE, NULL);
	if (current)
		current->next = end_token;
	else
		head = end_token;
	return (head);
}
