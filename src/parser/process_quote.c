/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:05:36 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:05:38 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
