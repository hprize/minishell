/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:06:23 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:06:24 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
