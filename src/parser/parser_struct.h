/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:10:00 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:10:01 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_STRUCT_H
# define PARSER_STRUCT_H

typedef struct s_token_context
{
	const char	*input_p;
	int			prev_space;
	int			cmd_set;
}	t_token_context;

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_RED,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_FILENAME,
	TOKEN_END,
	TOKEN_INVALID
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_EXEC,
	NODE_CMD,
	NODE_ARG,
	NODE_RED,
	NODE_HEREDOC,
	NODE_FILENAME
}	t_node_type;

typedef struct s_tree
{
	t_node_type		type;
	char			*value;
	struct s_tree	**children;
	int				child_count;
}	t_tree;

#endif