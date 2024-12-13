#ifndef PARSER_H
# define PARSER_H

# include "parser_struct.h"
# include "../../minishell.h"

// -- parser.c -- //
t_tree	*parse_pipe(t_token **current);
t_tree	*parse_exec(t_token **current);
void	parse_reds_opt(t_tree *exec_node, t_token **current);
t_tree	*parse_reds(t_token **current);
t_tree	*parse_cmd(t_token **current);
t_tree	*parse(t_token *tokens);

// -- parser_utils.c -- //
void	add_token(t_token **head, t_token **current, t_token *new_token);
t_token	*create_token(token_type type, const char *value);
void	merge_token(t_token **current, char *new_value);
t_tree	*create_tree_node(node_type type, const char *value);
void	add_child(t_tree *parent, t_tree *child);

// -- tokenize.c -- //
void	process_op(t_token **head, t_token **current, t_token_context *ctx);
void	process_quote(t_token **head, t_token **current, t_env *u_envp, \
t_token_context *ctx);
void	process_word(t_token **head, t_token **current, t_env *u_envp, \
t_token_context *ctx);
t_token	*tokenize(const char *input, t_env *u_envp);

// -- replace_env -- //
char	*ft_strjoin_free2(char *s1, char *s2);
int		is_valid_env_char(char c, int is_first);
void	process_env_replacement(char **value, t_env *u_envp);


#endif