/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:09:49 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:09:52 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
