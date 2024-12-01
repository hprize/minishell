#include "parser.h"

void	process_op(t_token **head, t_token **current, t_token_context *ctx)
{
	int 		len;
	char		*op;
	token_type	type;
	t_token		*new_token;

	len = 1;
	if ((*(ctx->input_p) == '>' && *(ctx->input_p + 1) == '>') || 
		(*(ctx->input_p) == '<' && *(ctx->input_p + 1) == '<'))
		len = 2;
	op = strndup(ctx->input_p, len);
	if (*op == '|' && len == 1)
	{
		type = TOKEN_PIPE;
		ctx->cmd_set = 0;
	}
	else if (*(ctx->input_p) == '<' && *(ctx->input_p + 1) == '<')
		type = TOKEN_HEREDOC;
	else
		type = TOKEN_RED;
	
	ctx->input_p += len;

	while (*(ctx->input_p) == ' ')
		ctx->input_p++;
	
	if (type == TOKEN_RED && (*(ctx->input_p) == '\0' || *(ctx->input_p) == '|' || *(ctx->input_p) == '<' || *(ctx->input_p) == '>')) {
		printf("minishell: syntax error near unexpected token 'newline'\n");
		free(op);
		exit(1);
	}

	new_token = create_token(type, op);
	free(op);
	add_token(head, current, new_token);
}

void	process_quote(t_token **head, t_token **current, t_env *u_envp, t_token_context *ctx)
{
	char 		quote;
	const char	*start;
	int			len;
	char		*quoted;
	token_type	type;
	t_token		*new_token;

	quote = *(ctx->input_p);
	start = ctx->input_p + 1;
	ctx->input_p++;
	while (*(ctx->input_p) && *(ctx->input_p) != quote)
		ctx->input_p++;
	if (*(ctx->input_p) != quote)
	{
		printf("minishell: syntax error unexpected end of file (unclosed quote)\n");
		exit(EXIT_FAILURE);
	}
	len = ctx->input_p - start;
	quoted = ft_strndup(start, len);
	if (quote != '\'')
		process_env_replacement(&quoted, u_envp);
	ctx->input_p++;

	if (!ctx->prev_space && *current && 
		((*current)->type == TOKEN_CMD || (*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, quoted);
		free(quoted);
		return;
	}

	if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else if (ctx->cmd_set == 0)
	{
		type = TOKEN_CMD;
		ctx->cmd_set = 1;
	}
	else
		type = TOKEN_ARG;

	new_token = create_token(type, quoted);
	free(quoted);
	add_token(head, current, new_token);
}

void	process_word(t_token **head, t_token **current, t_env *u_envp, t_token_context *ctx)
{
	const char	*start;
	int			len;
	char		*word;
	token_type	type;
	t_token		*new_token;

	start = ctx->input_p;
	while (*(ctx->input_p) && !ft_isspace(*(ctx->input_p)) && *(ctx->input_p) != '>' && *(ctx->input_p) != '<' && *(ctx->input_p) != '|' \
		&& *(ctx->input_p) != '"' && *(ctx->input_p) != '\'')
		ctx->input_p++;
	len = ctx->input_p - start;
	word = ft_strndup(start, len);
	process_env_replacement(&word, u_envp);
	if (!ctx->prev_space && *current && 
		((*current)->type == TOKEN_CMD || (*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, word);
		free(word);
		return;
	}

	if (*current && ((*current)->type == TOKEN_RED || (*current)->type == TOKEN_HEREDOC))
		type = TOKEN_FILENAME;
	else if (ctx->cmd_set == 0)
	{
		type = TOKEN_CMD;
		ctx->cmd_set = 1;
	}
	else
		type = TOKEN_ARG;

	new_token = create_token(type, word);
	free(word);

	add_token(head, current, new_token);
}

t_token	*tokenize(const char *input, t_env *u_envp)
{
	t_token			*head;
	t_token			*current;
	t_token			*end_token;
	t_token_context	*ctx;

	head = NULL;
	current = NULL;
	ctx = malloc(sizeof(t_token_context));
	if (!ctx)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ctx->input_p = input;
	ctx->prev_space = 1;
	ctx->cmd_set = 0;

	while (*(ctx->input_p))
	{
		while (ft_isspace(*(ctx->input_p)))
		{
			ctx->input_p++;
			ctx->prev_space = 1;
		}
		if (*(ctx->input_p) == '\0')
			break;
		if (*(ctx->input_p) == '>' || *(ctx->input_p) == '<' || *(ctx->input_p) == '|')
		{
			process_op(&head, &current, ctx);
			ctx->prev_space = 1;
			continue;
		}
		if (*(ctx->input_p) == '"' || *(ctx->input_p) == '\'')
		{
			process_quote(&head, &current, u_envp, ctx);
			ctx->prev_space = 0;
			continue;
		}
		process_word(&head, &current, u_envp, ctx);
		ctx->prev_space = 0;
	}
	end_token = create_token(TOKEN_END, NULL);
	if (current)
		current->next = end_token;
	else
		head = end_token;
	free(ctx);
	return (head);
}
