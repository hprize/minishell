#include "../minishell.h"


char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2); // 기존 ft_strjoin 호출
	free(s1); // s1 해제
	return (result);
}



// 환경변수 이름 규칙 검사 함수
int	is_valid_env_char(char c, int is_first)
{
	if (is_first)
		return (ft_isalpha(c) || c == '_'); // 첫 글자는 영문자 또는 '_'
	return (ft_isalnum(c) || c == '_');     // 나머지는 영문자, 숫자, '_'
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
	result = ft_strdup(""); // 결과 문자열 초기화
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
				result = ft_strjoin_free2(result, "");
				i++;
				continue;
			}
			// '$'만 있는 경우 처리
			if (!input[i] || !is_valid_env_char(input[i], 1))
			{
				result = ft_strjoin_free2(result, "$");
				continue;
			}

			// 환경변수 이름 탐색
			while (input[i] && is_valid_env_char(input[i], i == start))
				i++;
			env_name = ft_substr(input, start, i - start);
			if (!env_name)
			{
				free(result);
				return;
			}

			env_value = is_envp(env_name, u_envp);

			// 치환된 값 추가
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
			// 일반 문자 추가
			char tmp[2] = {input[i++], '\0'};
			result = ft_strjoin_free2(result, tmp);
		}
	}

	free(*value); // 기존 값 해제
	*value = result; // 새로운 문자열 반환
}



void	replace_env(t_token *tokens, t_env *u_envp)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != TOKEN_END)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_ARG || current->type == TOKEN_FILENAME)
		{
			if (current->quote_state != QUOTE_SINGLE)
				process_env_replacement(&current->value, u_envp);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			if (current->next && current->next->type == TOKEN_FILENAME)
				current = current->next;
		}
		current = current->next;
	}
}
