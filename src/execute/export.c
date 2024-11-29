#include "bulitin.h"

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
	t_env	*temp;

	sorted = sorted_envp_list(head);
	temp = sorted;
	while (temp)
	{
		if (temp->var->flag_export == 0)
			printf("declare -x %s=\"%s\"\n", temp->var->name, temp->var->content);
		temp = temp->next;
	}
	free_node(sorted);
	return (0);
}

int	check_name(char *name)
{
	int	i;

	if (ft_isdigit(name[0]) == 1 && ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		printf("\'%s\': not valid identifier\n", name);
		return (1);
	}
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			printf("\'%s\': not valid identifier\n", name);
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
			cur->var->content = ft_strdup(new->var->content);
			free_env(new);
			free(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	value_export(char **args, t_env *env)
{
	int	result;
	t_env	*new;
	int	i;

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
		{
			add_node_back(&env, new);
		}
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