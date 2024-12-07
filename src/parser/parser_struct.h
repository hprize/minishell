#ifndef PARSER_STRUCT_H
# define PARSER_STRUCT_H

typedef struct	s_token_context
{
	const char	*input_p;
	int			prev_space;
	int			cmd_set;
}	t_token_context;

typedef enum
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_RED,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_FILENAME,
	TOKEN_END,
	TOKEN_INVALID
}	token_type;

typedef struct	s_token
{
	token_type	type;
	char		*value;
	struct s_token	*next;
}	t_token;

typedef enum
{
	NODE_PIPE,
	NODE_EXEC,
	NODE_CMD,
	NODE_ARG,
	NODE_RED,
	NODE_HEREDOC,
	NODE_FILENAME
}	node_type;

typedef struct	s_tree
{
	node_type		type;
	char			*value;
	struct s_tree	**children;
	int				child_count;
}	t_tree;

#endif