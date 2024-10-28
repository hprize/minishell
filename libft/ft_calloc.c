/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:05 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:15:35 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	arr = (void *)malloc(nmemb * size);
	if (!arr)
		return (0);
	arr = ft_memset(arr, 0, nmemb * size);
	return (arr);
}
