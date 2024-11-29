#include "../minishell.h"


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
		return (ft_isalpha(c) || c == '_'); // 첫 글자는 영문자 또는 '_'
	return (ft_isalnum(c) || c == '_'); // 나머지는 영문자, 숫자, '_'
}

void	process_env_replacement(char **value, t_env *u_envp)
{
	char	*input;
	char	*result;
	char	*env_name;
	char	*env_value;
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
			if (ft_isdigit(input[i]))
			{
				i++;
				continue;
			}
			// '$'만 있는 경우 처리
			if (!input[i] || !is_valid_env_char(input[i], 1))
			{
				result = ft_strjoin_free2(result, "$");
				continue;
			}

			while (input[i] && is_valid_env_char(input[i], i == start))
				i++;
			env_name = ft_substr(input, start, i - start);
			if (!env_name)
			{
				free(result);
				return;
			}

			env_value = is_envp(env_name, u_envp);
			if (env_value)
				result = ft_strjoin_free2(result, env_value);
			else
				result = ft_strjoin_free2(result, "");
			free(env_name);
			if (env_value)
				free(env_value);
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
