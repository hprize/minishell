#include "../minishell.h"

int	del_split(const char *input, char delimiter, char **str1, char **str2)
{
	char	*pos;
	int		len1;

	if (!input || !str1 || !str2)
		return (1);
	pos = ft_strchr(input, delimiter);
	if (!pos)
		return (1);
	len1 = pos - input;
	*str1 = (char *)malloc(len1 + 1);
	if (*str1 == NULL)
		return (1);
	ft_strlcpy(*str1, input, len1 + 1);
	*str2 = ft_strdup(pos);
	if (*str2 == NULL)
	{
		free(*str1);
		*str1 = NULL;
		return (1);
	}
	return (0);
}

void	process_env_replacement(t_token *current, t_env *u_envp)
{
	char	*str;
	char	*env_name;
	char	*env_value;
	char	*new_value;

	str = NULL;
	env_name = NULL;
	if (del_split(current->value, '$', &str, &env_name) == 0)
	{
		env_value = is_envp(env_name, u_envp);
		if (env_value != NULL)
		{
			new_value = ft_strjoin(str, env_value);
			if (new_value != NULL)
			{
				free(current->value);
				current->value = new_value;
			}
		}
	}
	free(str);
	free(env_name);
}


void	replace_env(t_token *tokens, t_env *u_envp)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != TOKEN_END)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_ARG || current->type == TOKEN_FILENAME)
		{
			process_env_replacement(current, u_envp);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			if (current->next && current->next->type == TOKEN_FILENAME)
				current = current->next;
		}
		current = current->next;
	}
}
