/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:37:02 by hyebinle          #+#    #+#             */
/*   Updated: 2024/11/01 01:43:18 by hyebinle         ###   ########.fr       */
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

typedef struct s_master	t_master;
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
int	test(const char *input, t_master *master);
int	lexing(t_split *splitted, t_token **tokens, char **envp);

int	free_str(char *str);
t_split	*lstlast(t_split *lst);
t_split	*lstnew(char *line);
void	lstadd_back(t_split **lst, t_split *new);
void	delete_node(t_split *lst);
size_t	lstsize(t_split *lst);

typedef struct	s_envp
{
	int		is_first;
	char	*cmd;
	char	*user;
	char	*host;
	char	*root;
	char	*pwd;
	char	*where;
	// int		is_su;
}				t_envp;

typedef struct	s_master
{
	char	**envp;
}				t_master;


char	*set_envp(t_envp *envp, const char **r_envp);
void	free_struct(t_envp *s);
char	*get_word(char *word, const char **r_envp);
int		is_cmd(char *token, char **envp);



#endif
