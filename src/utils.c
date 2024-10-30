#include "../minishell.h"

int	free_str(char *str)
{
	free(str);
	str = NULL;
	return (FAILURE);
}

t_split	*lstlast(t_split *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

t_split	*lstnew(char *line)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (new == 0)
		return (0);
	new->line = line;
	new->next = 0;
	new->prev = 0;
	return (new);
}

void	lstadd_back(t_split **lst, t_split *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		if (new->prev != NULL)
			new->prev = NULL;
		return ;
	}
	new->prev = lstlast(*lst);
	new->prev->next = new;
}

void	delete_node(t_split *lst)
{
	if (lst->prev == NULL && lst->next == NULL)
		;
	else if (lst->prev == NULL)
		lst->next->prev = NULL;
	else if (lst->next == NULL)
		lst->prev->next = NULL;
	else
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	free_str(lst->line);
	free(lst);
	lst = NULL;
}

size_t	lstsize(t_split *lst)
{
	size_t	size;

	if (lst == 0)
		return (0);
	size = 0;
	while (lst != NULL)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}