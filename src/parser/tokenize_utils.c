/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:48:20 by junlee            #+#    #+#             */
/*   Updated: 2024/12/18 21:50:29 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_whitespace(t_token_context *ctx)
{
	while (ft_isspace(*(ctx->input_p)))
	{
		ctx->input_p++;
		ctx->prev_space = 1;
	}
}

void	set_ctx(t_token_context **ctx, const char *input)
{
	(*ctx)->input_p = input;
	(*ctx)->prev_space = 1;
	(*ctx)->cmd_set = 0;
}

void	set_current(t_token **current, t_token **head, t_token *end_token)
{
	if (*current)
		(*current)->next = end_token;
	else
		*head = end_token;
}

void	set_local(t_token **head, t_token **current, t_token_context **ctx)
{
	*head = NULL;
	*current = NULL;
	(*ctx) = malloc(sizeof(t_token_context));
	if (!ctx)
		strerror_exit();
}
