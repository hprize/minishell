/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:16:09 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:16:12 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_utils.h"

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

void	print_node(t_env *head)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		printf("flag_env = %d f_export = %d || %s : %s\n", cur->var->flag_env, \
		cur->var->flag_export, cur->var->name, cur->var->content);
		cur = cur->next;
	}
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
			cur->var->flag_export = 1;
		cur->var->flag_env = 0;
		cur = cur->next;
	}
	return ;
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = -1;
	while (envp[++i])
	{
		append_node(&head, envp[i]);
	}
	set_envp_flag(head);
	append_cust_node_back(&head, "LAST_EXIT_STATUS", "0", 1);
	append_cust_node_back(&head, "SIG_TYPE", "prompt", 1);
	return (head);
}
