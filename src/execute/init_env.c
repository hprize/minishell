#include "bulitin.h"

t_env	*creat_node(char *data)
{
	t_env	*new;
	char	*cont;

	new = malloc(sizeof(t_env));
	new->var = malloc(sizeof(t_var));
	if (!new || !(new->var))
	{
		perror("malloc error\n");
		exit(1);
	}
	cont = ft_strchr(data, '=');
	if (cont == 0)
	{
		new->var->flag = 0;
		new->var->name = ft_strdup(data);
		new->var->content = ft_strdup("");
	}
	else
	{
		new->var->flag = 1;
		new->var->name = ft_substr(data, 0, ft_strchr_len(data, '='));
		new->var->content = ft_strdup(cont + 1);
	}
	new->next = NULL;
	return (new);
}

// void	delete_node(t_env **head, )

void	add_node_back(t_env *head, t_env *new)
{
	t_env	*current;

	if (head == NULL)
		head = new;
	else
	{
		current = head;
		while (current -> next)
		{
			current = current -> next;
		}
		current ->next = new;
	}
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

void	print_node(t_env *head)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		printf("flag = %d || %s : %s\n", cur->var->flag, cur->var->name, cur->var->content);
		cur = cur->next;
	}
}

void	free_node(t_env *head)
{
	t_env	*cur;
	t_env	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		free(cur->var->name);
		free(cur->var->content);
		free(cur->var);
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

t_env	*init_env(char **envp)
{
	t_env	*head;
	// char	**sort_list;
	int		i;

	// sort_list = sort_arc(envp);
	head = NULL;
	i = -1;
	while (envp[++i])
	{
		append_node(&head, envp[i]);
	}

//test
	// print_node(head);

	return (head);
}