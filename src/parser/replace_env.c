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

static void	handling_questoinmark(t_env *u_envp, size_t *i, char **result)
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

static void	set_env_value(t_env *u_envp, char *env_name, char **result)
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

static char	*set_env_name(char *input, size_t *i, size_t start, char **result)
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

static void	handle_env_var(char *input, t_env *u_envp, size_t *i, char **result)
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

static void	append_normal_char(char input,char **result)
{
	char	tmp[2];

	tmp[0] = input;
	tmp[1] = '\0';
	*result = ft_strjoin_free2(*result, tmp);
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
