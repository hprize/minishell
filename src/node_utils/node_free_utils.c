/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:17:47 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:17:49 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_utils.h"

void	free_node(t_env *head)
{
	t_env	*cur;
	t_env	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		if (cur->var)
		{
			if (cur->var->name)
				free(cur->var->name);
			if (cur->var->content)
				free(cur->var->content);
			free(cur->var);
		}
		free(cur);
		cur = next;
	}
}

void	free_env(t_env *node)
{
	free(node->var->name);
	free(node->var->content);
	free(node->var);
	free(node);
}
