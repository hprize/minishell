/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:36:27 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:13:31 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	while (src[index] && index + 1 < size)
	{
		dst[index] = src[index];
		index++;
	}
	if (size)
		dst[index] = '\0';
	return (ft_strlen(src));
}
