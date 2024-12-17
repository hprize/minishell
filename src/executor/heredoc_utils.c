/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:02:09 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:22:47 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_char_index(char *index_i, char *index_j)
{
	free(index_i);
	free(index_j);
}

char	*generate_filename(int i, int j)
{
	char	*filename;
	char	*index_i;
	char	*index_j;
	size_t	filename_len;

	index_i = ft_itoa(i);
	index_j = ft_itoa(j);
	if (!index_i || !index_j)
	{
		free_char_index(index_i, index_j);
		return (NULL);
	}
	filename_len = ft_strlen(index_i) + ft_strlen(index_j) + 2;
	filename = malloc(filename_len + ft_strlen(HEREDOC_TMP));
	if (!filename)
	{
		free_char_index(index_i, index_j);
		return (NULL);
	}
	ft_strcpy(filename, HEREDOC_TMP);
	ft_strcat(filename, index_i);
	ft_strcat(filename, "_");
	ft_strcat(filename, index_j);
	free_char_index(index_i, index_j);
	return (filename);
}
