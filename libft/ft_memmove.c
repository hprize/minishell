/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:18:00 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:12:57 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	const unsigned char	*c_src;
	size_t				i;

	c_dest = (unsigned char *)dest;
	c_src = (const unsigned char *)src;
	i = 0;
	while (c_src >= c_dest && i < n)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	while (c_src < c_dest && n)
	{
		n--;
		c_dest[n] = c_src[n];
	}
	return ((void *)c_dest);
}
