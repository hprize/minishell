/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:10:12 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:12:47 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	while (n--)
	{
		if (*c_s == (unsigned char)c)
			return ((void *)c_s);
		c_s++;
	}
	return (0);
}
