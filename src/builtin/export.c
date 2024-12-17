/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:55:41 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:23:21 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

int	print_export(t_env *head)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = sorted_envp_list(head);
	temp = sorted;
	while (temp)
	{
		if (ft_strcmp(temp->var->name, "LAST_EXIT_STATUS") == 0)
			temp = temp->next;
		else
		{
			if (temp->var->content != NULL)
				printf("declare -x %s=\"%s\"\n", \
				temp->var->name, temp->var->content);
			else
				printf("declare -x %s\n", temp->var->name);
			temp = temp->next;
		}
	}
	free_node(sorted);
	return (0);
}

int	check_name(char *name)
{
	int	i;

	if (ft_strlen(name) == 0)
	{
		write(2, " not valid identifier\n", 22);
		return (1);
	}
	if (ft_isdigit(name[0]) == 1 && ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		write(2, " not valid identifier\n", 22);
		return (1);
	}
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			write(2, " not valid identifier\n", 22);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_overlap(t_env *head, t_env *new)
{
	t_env	*cur;
	char	*temp;

	if (head == NULL)
		return (0);
	cur = head;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, new->var->name) == 0)
		{
			temp = cur->var->content;
			if (new->var->content != NULL)
				cur->var->content = ft_strdup(new->var->content);
			else
				cur->var->content = NULL;
			free_env(new);
			if (temp != NULL)
				free(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	value_export(char **args, t_env *env)
{
	int		result;
	t_env	*new;
	int		i;

	i = -1;
	result = 0;
	while (args[++i])
	{
		new = creat_node(args[i]);
		if (check_name(new->var->name) == 1)
		{
			result = 1;
			free_env(new);
		}
		else if (check_overlap(env, new) == 0)
			add_node_back(&env, new);
	}
	return (result);
}

int	export(t_tree *node, char **args, t_env *env)
{
	int	result;

	if (args[0] == NULL)
		result = print_export(env);
	else
		result = value_export(args, env);
	return (result);
}
