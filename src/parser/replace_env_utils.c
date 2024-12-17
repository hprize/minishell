/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:03:33 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:03:35 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handling_questoinmark(t_env *u_envp, size_t *i, char **result)
{
	char	*env_value;

	(*i)++;
	env_value = return_env_value("LAST_EXIT_STATUS", u_envp);
	if (env_value)
		*result = ft_strjoin_free2(*result, env_value);
	else
		*result = ft_strjoin_free2(*result, "");
	if (env_value)
		free(env_value);
}

void	set_env_value(t_env *u_envp, char *env_name, char **result)
{
	char	*env_value;

	env_value = return_env_value(env_name, u_envp);
	if (env_value)
		*result = ft_strjoin_free2(*result, env_value);
	else
		*result = ft_strjoin_free2(*result, "");
	if (env_value)
		free(env_value);
}

char	*set_env_name(char *input, size_t *i, size_t start, char **result)
{
	char	*env_name;

	while (input[*i] && is_valid_env_char(input[*i], *i == start))
		(*i)++;
	env_name = ft_substr(input, start, *i - start);
	if (!env_name)
	{
		free(*result);
		return (NULL);
	}
	return (env_name);
}

void	handle_env_var(char *input, t_env *u_envp, size_t *i, char **result)
{
	size_t	start;
	char	*env_name;

	start = *i;
	if (input[*i] == '?')
		handling_questoinmark(u_envp, i, result);
	else if (ft_isdigit(input[*i]))
		(*i)++;
	else if (!input[*i] || !is_valid_env_char(input[*i], 1))
		*result = ft_strjoin_free2(*result, "$");
	else
	{
		env_name = set_env_name(input, i, start, result);
		if (!env_name)
			return ;
		set_env_value(u_envp, env_name, result);
		free(env_name);
	}
}

void	append_normal_char(char input, char **result)
{
	char	tmp[2];

	tmp[0] = input;
	tmp[1] = '\0';
	*result = ft_strjoin_free2(*result, tmp);
}
