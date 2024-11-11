#include "bulitin.h"

t_env*	new_node(t_var *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		exit(1);
	new->var = var;
	new->next = NULL;
	return (new);
}

void	insert_sorted(t_env **sorted_head, t_env *new_node)
{
	t_env	*cur;

	if (*sorted_head == NULL || (ft_strcmp((*sorted_head)->var->name, new_node->var->name) >= 0))
	{
		new_node->next = *sorted_head;
		*sorted_head = new_node;
	}
	else
	{
		cur = *sorted_head;
		while (cur->next != NULL && (ft_strcmp(cur->next->var->name, new_node->var->name) < 0))
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

int	print_export(t_env *head)
{
	t_env	*sorted;

	sorted = sorted_envp_list(head);
	while (sorted)
	{
		if (!(ft_strlen(sorted->var->name) == 1 \
		&& ft_strncmp(sorted->var->name, "_", 1) == 0))
			printf("declare -x %s=\"%s\"\n", sorted->var->name, sorted->var->content);
		sorted = sorted->next;
	}
	free_node(sorted);
	return (0);
}
int	export(t_tree *node, char **args, t_env **env)
{
	if (*args == NULL)
		print_export(*env);
	else
		value_export(node, args, env);
}