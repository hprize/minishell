#include "../minishell.h"

static int	get_token_type(char *token)
{
	if (token[0] == '|')
		return (T_PIPE);
	else if (token[0] == '>' || token[0] == '<')
		return (T_REDIRECTION);
	else if (token[0] == '\0')
		return (T_NULL);
	else
		return (T_WORD);
}

int	lexing(t_split *splitted, t_token **tokens)
{
	int		i;
	t_split	*tmp;

	*tokens = NULL;
	*tokens = (t_token *)malloc(sizeof(t_token)
			* (lstsize(splitted) + 1));
	if (!(*tokens))
		return (MALLOC_ERROR);
	i = 0;
	tmp = splitted;
	while (tmp != NULL)
	{
		(*tokens)[i].type = get_token_type(tmp->line);
		(*tokens)[i].value = ft_strdup(tmp->line);
		tmp = tmp->next;
		++i;
	}
	(*tokens)[i].value = NULL;
	(*tokens)[i].type = T_NULL;
	return (0);
}