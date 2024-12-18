/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:03:42 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:03:44 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

int	is_valid_env_char(char c, int is_first)
{
	if (is_first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

void	process_env_replacement(char **value, t_env *u_envp)
{
	char	*input;
	char	*result;
	size_t	i;

	if (!value || !*value)
		return ;
	input = *value;
	result = ft_strdup("");
	if (!result)
		return ;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			++i;
			handle_env_var(input, u_envp, &i, &result);
		}
		else
			append_normal_char(input[i++], &result);
	}
	free(*value);
	*value = result;
}
