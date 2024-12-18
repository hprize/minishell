/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:42 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:21:43 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_tree(t_tree *node)
{
	int	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < node->child_count)
	{
		free_tree(node->children[i]);
		i++;
	}
	free(node->children);
	node->children = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	free_master(t_envp *master)
{
	ft_arrfree(master->path_list);
	ft_arrfree(master->envp);
	free_node(master->u_envp);
	free(master);
}
