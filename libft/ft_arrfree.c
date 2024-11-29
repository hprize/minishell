/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:28:23 by hyebinle          #+#    #+#             */
/*   Updated: 2024/11/29 18:39:14 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree(char **str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	while ((str)[++i])
		free((str)[i]);
	free(str);
	str = NULL;
}
