#include "../minishell.h"

static int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static int	get_operator_length(const char *input)
{
	int		length;

	if (input[0] == '<')
	{
		if (input[1] == '<')
			return (2);
		else
			return (1);
	}
	else if (input[0] == '>')
	{
		if (input[1] == '>')
			return (2);
		else
			return (1);
	}
	else if (input[0] == '|')
		length = 1;
	else
		length = 0;
	return (length);
}

static int	get_token_length(const char *input)
{
	int		index;
	int		double_quote_open;
	int		single_quote_open;

	index = 0;
	double_quote_open = 0;
	single_quote_open = 0;
	if (is_operator(input[index]))
		return (get_operator_length(input));
	while (input[index] != '\0')
	{
		if (input[index] == '"')
			double_quote_open = !double_quote_open;
		else if (input[index] == '\'')
			single_quote_open = !single_quote_open;
		else if (input[index] == ' ' && double_quote_open == 0 && single_quote_open == 0)
			break;
		else if (is_operator(input[index]) && double_quote_open == 0 && single_quote_open == 0)
			break;
		index++;
	}
	if (double_quote_open || single_quote_open)
		return (-1);
	return (index);
}

int	split_input(const char *input, t_split **splitted_tokens)
{
	t_split	*new_token;
	int		token_length;

	while (*input == ' ')
		input++;
	while (*input != '\0')
	{
		token_length = get_token_length(input);
		if (token_length == -1)
		{
			printf("아니 따옴표 쓸 거면 맞춰서 써야 할 것 아닌가!\n");
			return (FAILURE);
		}
		new_token = lstnew(ft_substr(input, 0, token_length));
		if (new_token == NULL || new_token->line == NULL)
			return (MALLOC_ERROR);
		lstadd_back(splitted_tokens, new_token);
		input += token_length;
		while (*input == ' ')
			input++;
	}
	return (0);
}
