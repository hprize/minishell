/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:03:26 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 21:12:36 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// -- parser_m_utils.c -- //
t_tree	*parse_pipe(t_token **current);
void	current_type(t_token **current, t_tree *exec_node);
t_tree	*parse_exec(t_token **current);

// -- parser_utils.c -- //
void	add_token(t_token **head, t_token **current, t_token *new_token);
t_token	*create_token(t_token_type type, const char *value);
void	merge_token(t_token **current, char *new_value);
t_tree	*create_tree_node(t_node_type type, const char *value);
void	add_child(t_tree *parent, t_tree *child);

// -- tokenize.c -- //
int		process_op(t_token **head, t_token **current, t_token_context *ctx);
void	process_quote(t_token **head, t_token **current, t_env *u_envp, \
t_token_context *ctx);
void	process_word(t_token **head, t_token **current, t_env *u_envp, \
t_token_context *ctx);
t_token	*tokenize(const char *input, t_env *u_envp);

// -- replace_env -- //
char	*ft_strjoin_free2(char *s1, char *s2);
int		is_valid_env_char(char c, int is_first);
void	process_env_replacement(char **value, t_env *u_envp);

// -- replace_env_utils -- //
void	handling_questoinmark(t_env *u_envp, size_t *i, char **result);
void	set_env_value(t_env *u_envp, char *env_name, char **result);
char	*set_env_name(char *input, size_t *i, size_t start, char **result);
void	handle_env_var(char *input, t_env *u_envp, size_t *i, char **result);
void	append_normal_char(char input, char **result);

// -- handle_token.c -- //
int		handle_operator(t_token **head, t_token **current, \
	t_token_context *ctx);
void	handle_quote(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx);
void	handle_word(t_token **head, t_token **current, t_env *u_envp, \
	t_token_context *ctx);

#endif