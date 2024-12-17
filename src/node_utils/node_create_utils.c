/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:17:38 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:17:39 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_utils.h"

t_env	*creat_node(char *data)
{
	t_env	*new;
	char	*cont;

	new = create_t_env();
	cont = ft_strchr(data, '=');
	if (cont == 0)
	{
		new->var->flag_env = 1;
		new->var->name = ft_strdup(data);
		new->var->content = NULL;
	}
	else
	{
		new->var->flag_env = 0;
		new->var->name = ft_substr(data, 0, ft_strchr_len(data, '='));
		new->var->content = ft_strdup(cont + 1);
	}
	return (new);
}

void	add_node_back(t_env **head, t_env *new)
{
	t_env	*current;

	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current -> next)
		{
			current = current -> next;
		}
		current ->next = new;
	}
}

t_env	*new_node(t_var *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->var = malloc(sizeof(t_var));
	if (new == NULL || new->var == NULL)
		strerror_exit();
	new->var->name = ft_strdup(var->name);
	if (var->content)
		new->var->content = ft_strdup(var->content);
	else
		new->var->content = NULL;
	new->var->flag_env = var->flag_env;
	new->var->flag_export = var->flag_export;
	new->next = NULL;
	return (new);
}

void	append_node(t_env **head, char *data)
{
	t_env	*current;
	t_env	*new;

	new = creat_node(data);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current -> next)
		{
			current = current -> next;
		}
		current ->next = new;
	}
}

void	append_cust_node_back(t_env **head, char *name, char *value, int flag)
{
	t_env	*new;

	new = create_t_env();
	new->var->name = ft_strdup(name);
	new->var->content = ft_strdup(value);
	new->var->flag_env = flag;
	new->var->flag_export = flag;
	add_node_back(head, new);
}
