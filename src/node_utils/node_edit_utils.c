/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_edit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:17:43 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:17:44 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_utils.h"

int	replace_content(t_env *head, char *name, char *content)
{
	t_env	*cur;
	char	*temp;

	if (head == NULL)
		return (0);
	cur = head;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, name) == 0)
		{
			temp = cur->var->content;
			cur->var->content = ft_strdup(content);
			free(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

char	*find_content(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (NULL);
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			return (cur->var->content);
		}
		cur = cur->next;
	}
	return (NULL);
}

char	*return_env_value(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (NULL);
	if (*arg == '$')
		arg++;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			if (cur->var->content != NULL)
				return (ft_strdup(cur->var->content));
			else
				return (NULL);
		}
		cur = cur->next;
	}
	return (NULL);
}
