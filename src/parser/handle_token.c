/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:09:38 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:09:42 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_operator(t_token **head, t_token **current, \
	t_token_context *ctx)
{
	process_op(head, current, ctx);
	ctx->prev_space = 1;
}

void	handle_quote(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	process_quote(head, current, u_envp, ctx);
	ctx->prev_space = 0;
}

void	handle_word(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx)
{
	process_word(head, current, u_envp, ctx);
	ctx->prev_space = 0;
}
