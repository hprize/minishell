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

void	process_env_replacement(char **value, t_env *u_envp)
{
	char	*input;
	char	*result;
	char	*env_name;
	size_t	i;
	size_t	start;

	if (!value || !*value)
		return;
	input = *value;
	result = ft_strdup("");
	if (!result)
		return;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			start = ++i;
			if (input[i] == '?')
				handling_questoinmark(u_envp, &i, &result);
			else if (ft_isdigit(input[i]))
				i++;
			else if (!input[i] || !is_valid_env_char(input[i], 1))
				result = ft_strjoin_free2(result, "$");
			else
			{
				env_name = set_env_name(input, &i, start, &result);
				if (!env_name)
					return ;
				set_env_value(u_envp, env_name, &result);
				free(env_name);
			}
		}
		else
		{
			char tmp[2] = {input[i++], '\0'};
			result = ft_strjoin_free2(result, tmp);
		}
	}
	free(*value);
	*value = result;
}
