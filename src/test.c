#include "../minishell.h"

#include "../minishell.h"

static void	*free_split_list(t_split *list)
{
	t_split	*current;
	t_split	*next;

	current = list;
	while (current != NULL)
	{
		next = current->next;
		delete_node(current);
		current = next;
	}
	return (NULL);
}

// 검토 필요.
static int	validate_tokens(t_token *tokens)
{
	t_token	*current = tokens;

	while (current->type != T_NULL)
	{
		if (current->type == T_REDIRECTION && (current + 1)->type != T_WORD)
		{
			printf("minishell: parse error near '%s'\n", current->value);
			return (1);
		}
		current++;
	}
	return (0);
}

static void	free_token_array(t_token *tokens)
{
	int	i = 0;

	while (tokens[i].type != T_NULL)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
}

static void	print_split_list(t_split *head)
{
	t_split *current = head;

	while (current != NULL)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}

static void	print_token_array(t_token **tokens)
{
	int i = 0;

	while ((*tokens)[i].type != T_NULL)
	{
		printf("%s -- %d\n", (*tokens)[i].value, (*tokens)[i].type);
		i++;
	}
}

int	test(const char *input)
{
	t_split	*split_list = NULL;
	t_token	*tokens = NULL;
	int		result;

	result = split_input(input, &split_list);
	if (result == MALLOC_ERROR || FAILURE)
	{
		free_split_list(split_list);
		return (result);
	}
	print_split_list(split_list);

	lexing(split_list, &tokens);
	if (validate_tokens(tokens))
	{
		free_token_array(tokens);
		free_split_list(split_list);
		return (PARSE_ERROR);
	}
	print_token_array(&tokens);

	free_token_array(tokens);
	free_split_list(split_list);

	return (SUCCESS);
}

