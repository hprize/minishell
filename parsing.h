/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: junlee <junlee@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/02 20:25:49 by junlee			#+#	#+#			 */
/*   Updated: 2024/11/04 21:11:29 by junlee		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_REDIRECTION,
	TOKEN_PIPE,
	TOKEN_FILENAME,
	TOKEN_END,
	TOKEN_INVALID
} token_type;

typedef struct s_token
{
	token_type type;
	char *value;
	struct s_token *next;
} t_token;

typedef enum
{
	NODE_PIPE,
	NODE_EXEC,
	NODE_REDIRECTION,
	NODE_ARG,
	NODE_FILENAME
} node_type;

typedef struct s_tree
{
	node_type type;
	char *value;
	struct s_tree **children;
	int child_count;
} t_tree;

#endif