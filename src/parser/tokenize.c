/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:09:49 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/18 21:49:56 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_input(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	while (*(ctx->input_p))
	{
		skip_whitespace(ctx);
		if (*(ctx->input_p) == '\0')
			break ;
		if (*(ctx->input_p) == '>' || *(ctx->input_p) == '<' || \
			*(ctx->input_p) == '|')
		{
			if (handle_operator(head, current, ctx) == 1)
			{
				free(ctx);
				free_tokens(*head);
				*head = NULL;
				return ;
			}
		}
		else if (*(ctx->input_p) == '"' || *(ctx->input_p) == '\'')
			handle_quote(head, current, u_envp, ctx);
		else
			handle_word(head, current, u_envp, ctx);
	}
}

t_token	*tokenize(const char *input, t_env *u_envp)
{
	t_token			*head;
	t_token			*current;
	t_token			*end_token;
	t_token_context	*ctx;

	set_local(&head, &current, &ctx);
	set_ctx(&ctx, input);
	process_input(&head, &current, u_envp, ctx);
	if (head == NULL)
		return (NULL);
	end_token = create_token(TOKEN_END, NULL);
	set_current(&current, &head, end_token);
	free(ctx);
	return (head);
}
