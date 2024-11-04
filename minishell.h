/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: junlee <junlee@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/28 22:37:02 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/11/02 17:44:30 by junlee		   ###   ########.fr	   */
/*																			*/
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
# include "parsing.h"

t_tree *parse(t_token *tokens);
t_token *tokenize(const char *input);

void add_token(t_token **head, t_token **current, t_token *new_token);
t_token *create_token(token_type type, const char *value);
t_tree *create_tree_node(node_type type, const char *value);
void add_child(t_tree *parent, t_tree *child);
void free_tree(t_tree *node);
void free_tokens(t_token *tokens);

t_tree *parse_pipe(t_token **current);
t_tree *parse_exec(t_token **current);
t_tree *parse_reds_opt(t_token **current);
t_tree *parse_reds(t_token **current);
t_tree *parse_cmd(t_token **current);
t_tree *parse_args_opt(t_token **current);
t_tree *parse_args(t_token **current);
t_tree *parse_red(t_token **current);

// testing.c
void print_tree(t_tree *node, int level);
void print_tree_linear(t_tree *node);

#endif
