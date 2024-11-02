/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcpy.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/27 19:17:57 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/03 18:12:54 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	const unsigned char	*c_src;
	int					i;

	c_dest = (unsigned char *)dest;
	c_src = (const unsigned char *)src;
	i = 0;
	while (n--)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return ((void *)c_dest);
}
