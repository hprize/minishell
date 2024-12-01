/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:56:28 by junlee            #+#    #+#             */
/*   Updated: 2024/12/01 01:28:39 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_mem(t_lst **lst, char **pnew)
{
	if (*lst)
	{
		if ((*lst)->buffer)
		{
			free((*lst)->buffer);
			(*lst)->buffer = NULL;
		}
		free(*lst);
		*lst = NULL;
	}
	if (*pnew)
	{
		free(*pnew);
		*pnew = NULL;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

// void	ft_strcpy(char *dst, char *src)
// {
// 	int	i;

// 	if (src == NULL)
// 	{
// 		*dst = '\0';
// 		return ;
// 	}
// 	i = 0;
// 	while (*(src + i))
// 	{
// 		*(dst + i) = *(src + i);
// 		i++;
// 	}
// 	*(dst + i) = '\0';
// }
