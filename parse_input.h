/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:31:36 by junlee            #+#    #+#             */
/*   Updated: 2024/10/30 18:31:39 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

# define T_NULL 1
# define T_PIPE 2
# define T_REDIRECTION 3
# define T_WORD 4

# define NODE_PIPE 1
# define NODE_PHRASE 2
# define NODE_REDIRS 3
# define NODE_IO_REDIR 4
# define NODE_COMMAND 5
# define NODE_REDIR_TYPE 6
# define NODE_FILE_NAME 7
# define NODE_FILE_PATH 8
# define NODE_ARGV 9

# define PARSE_ERROR -1

typedef struct s_split		t_split;

typedef struct s_token
{
	int			type;
	char		*value;
}	t_token;

#endif