/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:37:02 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/30 18:22:53 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "parse_input.h"

typedef enum e_status
{
	SUCCESS,
	FAILURE,
	MALLOC_ERROR
}	t_status;

typedef struct s_split
{
	char			*line;
	struct s_split	*next;
	struct s_split	*prev;
}	t_split;

int	split_input(const char *input, t_split **splitted);
int	test(const char *input);
int	lexing(t_split *splitted, t_token **tokens);

int	free_str(char *str);
t_split	*lstlast(t_split *lst);
t_split	*lstnew(char *line);
void	lstadd_back(t_split **lst, t_split *new);
void	delete_node(t_split *lst);
size_t	lstsize(t_split *lst);

#endif
