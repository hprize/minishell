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

void print_tree(t_tree *node, int level);
void free_tree(t_tree *node);
void free_tokens(t_token *tokens);

#endif
