/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:09:38 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 21:13:07 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_operator(t_token **head, t_token **current, \
	t_token_context *ctx)
{
	if (process_op(head, current, ctx) == 1)
		return (1);
	ctx->prev_space = 1;
	return (0);
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
