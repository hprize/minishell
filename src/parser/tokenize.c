#include "parser.h"

static int	set_len(const char *input_p)
{
	if ((*(input_p) == '>' && *(input_p + 1) == '>') || \
		(*(input_p) == '<' && *(input_p + 1) == '<'))
		return (2);
	else
		return (1);
}

static void	set_op_type(t_token_context *ctx, char **op, t_token_type *type, \
						int *len)
{
	*op = strndup(ctx->input_p, *len);
	if (**op == '|' && *len == 1)
	{
		*type = TOKEN_PIPE;
		ctx->cmd_set = 0;
	}
	else if (*(ctx->input_p) == '<' && *(ctx->input_p + 1) == '<')
		*type = TOKEN_HEREDOC;
	else
		*type = TOKEN_RED;
}

void	process_op(t_token **head, t_token **current, t_token_context *ctx)
{
	int				len;
	char			*op;
	t_token_type	type;
	t_token			*new_token;

	len = set_len((ctx->input_p));
	op = strndup(ctx->input_p, len);
	set_op_type(ctx, &op, &type, &len);
	ctx->input_p += len;
	while (*(ctx->input_p) == ' ')
		ctx->input_p++;
	if (type == TOKEN_RED && (*(ctx->input_p) == '\0' || *(ctx->input_p) == \
		'|' || *(ctx->input_p) == '<' || *(ctx->input_p) == '>'))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		free(op);
		exit(1);
	}
	new_token = create_token(type, op);
	free(op);
	add_token(head, current, new_token);
}

static void	check_quote(const char **start, t_token_context *ctx, char *quote)
{
	*start = ctx->input_p + 1;
	ctx->input_p++;
	while (*(ctx->input_p) && *(ctx->input_p) != *quote)
		ctx->input_p++;
	if (*(ctx->input_p) != *quote)
	{
		printf("minishell: syntax error unexpected end of file \
			(unclosed quote)\n");
		exit(EXIT_FAILURE);
	}
}

static void	set_cur_type(t_token **current, t_token_context *ctx, \
	t_token_type *type)
{
	if (*current && ((*current)->type == TOKEN_RED || \
		(*current)->type == TOKEN_HEREDOC))
		*type = TOKEN_FILENAME;
	else if (ctx->cmd_set == 0)
	{
		*type = TOKEN_CMD;
		ctx->cmd_set = 1;
	}
	else
		*type = TOKEN_ARG;
}

void	process_quote(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	char			quote;
	const char		*start;
	char			*quoted;
	t_token_type	type;
	t_token			*new_token;

	quote = *(ctx->input_p);
	check_quote(&start, ctx, &quote);
	quoted = ft_strndup(start, (ctx->input_p - start));
	if (quote != '\'')
		process_env_replacement(&quoted, u_envp);
	ctx->input_p++;
	if (!ctx->prev_space && *current && ((*current)->type == TOKEN_CMD || \
		(*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, quoted);
		free(quoted);
		return ;
	}
	set_cur_type(current, ctx, &type);
	new_token = create_token(type, quoted);
	free(quoted);
	add_token(head, current, new_token);
}

static int	check_input_p(t_token_context *ctx)
{
	if (*(ctx->input_p) && !ft_isspace(*(ctx->input_p)) && \
		*(ctx->input_p) != '>' && *(ctx->input_p) != '<' && \
		*(ctx->input_p) != '|' && *(ctx->input_p) != '"' && \
		*(ctx->input_p) != '\'')
		return (1);
	return (0);
}

static void	set_cur_token_type(t_token **current, t_token_context *ctx, \
	t_token_type *type)
{
	if (*current && ((*current)->type == TOKEN_RED || \
		(*current)->type == TOKEN_HEREDOC))
		*type = TOKEN_FILENAME;
	else if (ctx->cmd_set == 0)
	{
		*type = TOKEN_CMD;
		ctx->cmd_set = 1;
	}
	else
		*type = TOKEN_ARG;
}

void	process_word(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	const char		*start;
	int				len;
	char			*word;
	t_token_type	type;
	t_token			*new_token;

	start = ctx->input_p;
	while (check_input_p(ctx))
		ctx->input_p++;
	len = ctx->input_p - start;
	word = ft_strndup(start, len);
	process_env_replacement(&word, u_envp);
	if (!ctx->prev_space && *current && ((*current)->type == TOKEN_CMD || \
		(*current)->type == TOKEN_ARG || (*current)->type == TOKEN_FILENAME))
	{
		merge_token(current, word);
		free(word);
		return ;
	}
	set_cur_token_type(current, ctx, &type);
	new_token = create_token(type, word);
	free(word);
	add_token(head, current, new_token);
}

static void	handle_operator(t_token **head, t_token **current, \
	t_token_context *ctx)
{
	process_op(head, current, ctx);
	ctx->prev_space = 1;
}

static void	handle_quote(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	process_quote(head, current, u_envp, ctx);
	ctx->prev_space = 0;
}

static void	handle_word(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	process_word(head, current, u_envp, ctx);
	ctx->prev_space = 0;
}

static void	skip_whitespace(t_token_context *ctx)
{
	while (ft_isspace(*(ctx->input_p)))
	{
		ctx->input_p++;
		ctx->prev_space = 1;
	}
}

static void	set_ctx(t_token_context **ctx, const char *input)
{
	(*ctx)->input_p = input;
	(*ctx)->prev_space = 1;
	(*ctx)->cmd_set = 0;
}

static void	set_current(t_token **current, t_token *head, t_token *end_token)
{
	if (*current)
		(*current)->next = end_token;
	else
		head = end_token;
}

void	set_local(t_token **head, t_token **current, t_token_context **ctx)
{
	*head = NULL;
	*current = NULL;
	(*ctx) = malloc(sizeof(t_token_context));
	if (!ctx)
		strerror_exit();
}

t_token	*tokenize(const char *input, t_env *u_envp)
{
	t_token			*head;
	t_token			*current;
	t_token			*end_token;
	t_token_context	*ctx;

	set_local(&head, &current, &ctx);
	set_ctx(&ctx, input);
	while (*(ctx->input_p))
	{
		skip_whitespace(ctx);
		if (*(ctx->input_p) == '\0')
			break ;
		if (*(ctx->input_p) == '>' || *(ctx->input_p) == '<' || \
			*(ctx->input_p) == '|')
			handle_operator(&head, &current, ctx);
		else if (*(ctx->input_p) == '"' || *(ctx->input_p) == '\'')
			handle_quote(&head, &current, u_envp, ctx);
		else
			handle_word(&head, &current, u_envp, ctx);
	}
	end_token = create_token(TOKEN_END, NULL);
	set_current(&current, head, end_token);
	free(ctx);
	return (head);
}
