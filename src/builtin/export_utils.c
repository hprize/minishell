/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:23:44 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:23:51 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

void	insert_sorted(t_env **sorted_head, t_env *new_node)
{
	t_env	*cur;

	if (*sorted_head == NULL || \
	(ft_strcmp((*sorted_head)->var->name, new_node->var->name) >= 0))
	{
		new_node->next = *sorted_head;
		*sorted_head = new_node;
	}
	else
	{
		cur = *sorted_head;
		while (cur->next != NULL && \
		(ft_strcmp(cur->next->var->name, new_node->var->name) < 0))
			cur = cur->next;
		new_node->next = cur->next;
		cur->next = new_node;
	}
}

t_env	*sorted_envp_list(t_env *head)
{
	t_env	*sorted_head;
	t_env	*cur;
	t_env	*new;

	sorted_head = NULL;
	cur = head;
	while (cur != NULL)
	{
		new = new_node(cur->var);
		insert_sorted(&sorted_head, new);
		cur = cur->next;
	}
	return (sorted_head);
}
