/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_bzero.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/28 18:01:48 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/03 18:12:12 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c_s;
	size_t			i;

	c_s = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		c_s[i] = '\0';
		i++;
	}
}
