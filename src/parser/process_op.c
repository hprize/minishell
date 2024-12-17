/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:05:43 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:24:57 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
