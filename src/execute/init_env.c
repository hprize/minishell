#include "bulitin.h"

t_env	*create_t_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->var = malloc(sizeof(t_var));
	if (!new || !(new->var))
	{
		perror("malloc error\n");
		exit(1);
	}
	new->next = NULL;
	return (new);
}

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
		new->var->content = ft_strdup("");
	}
	else
	{
		new->var->flag_env = 0;
		new->var->name = ft_substr(data, 0, ft_strchr_len(data, '='));
		new->var->content = ft_strdup(cont + 1);
	}
	return (new);
}

// void	delete_node(t_env **head, )

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

void	append_custom_node_back(t_env **head, char *name, char *value, int flag)
{
	t_env	*new;

	new = create_t_env();
	new->var->name = ft_strdup(name);
	new->var->content = ft_strdup(value);
	new->var->flag_env = flag;
	new->var->flag_export = flag;
	add_node_back(head, new);
}

void	print_node(t_env *head)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		printf("flag_env = %d f_export = %d || %s : %s\n", cur->var->flag_env, cur->var->flag_export, cur->var->name, cur->var->content);
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

void	set_envp_flag(t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return ;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, "_") == 0)
		{
			cur->var->flag_export = 1;
		}
		cur->var->flag_env = 0;
		cur = cur->next;
	}
	return ;
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
	set_envp_flag(head);
	append_custom_node_back(&head, "LAST_EXIT_STATUS", "0", 1);
	append_custom_node_back(&head, "SIG_TYPE", "prompt", 1);
//test
	// print_node(head);

	return (head);
}
